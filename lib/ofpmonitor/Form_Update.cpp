//---------------------------------------------------------------------------

#include <vcl.h>
#include <list.h>
#include <unrar.h>
#include "FileVersion.h"
#include "StringSplitter.h"
#include <IdHashMessageDigest.hpp>
#include "HttpFileDownloader.h"
#pragma hdrstop

#include "Form_Main.h"
#include "Form_Settings.h"
#include "Form_Update.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWINDOW_UPDATE *WINDOW_UPDATE;

#define SECTION_HEADER_START "[Header]"
#define SECTION_HEADER_END "[\\Header]"
#define SECTION_LOCATION_START "[DownloadLocation]"
#define SECTION_LOCATION_END "[\\DownloadLocation]"
#define SECTION_RELEASE_START "[ReleaseMD5]"
#define SECTION_RELEASE_END "[\\ReleaseMD5]"

void releaseMutex();

void TWINDOW_UPDATE::setLanguageDB(LanguageDB *languageDB) {
        this->languageDB = languageDB;
}

void TWINDOW_UPDATE::updateGuiLanguage() {
        this->Caption = this->languageDB->getGuiString(this->Name);
}

class UpdateTracker {
  private:
        String applicationExe;
        String mainDir;
        String updateDir;
        String backupDir;

  public:
        int step;
        bool working;
        bool updateDone;
        bool userTriggered;

        HttpFileDownloader *loader;
        TMemoryStream *ms;
        TMemoryStream *fs;
        TStringList *stringList;
        TStringList *filesToInstall;
        HANDLE thread1;
        HANDLE thread2;
        bool newVersion;
        String localVersion;
        String remoteVersion;
        bool error;
        String errorMsg;
        int answer;

        UpdateTracker (bool userTriggered) {
                this->userTriggered = userTriggered;
                this->working = false;
                this->updateDone = false;
                this->newVersion = false;
                this->answer = mrNo;
                this->step = 1;
                this->error = false;
                this->errorMsg = "";
                this->stringList = new TStringList;
                this->filesToInstall = new TStringList;
                FileVersion *fv = new FileVersion(Application->ExeName);
                this->localVersion = fv->getFullVersion();
                delete fv;
                this->applicationExe = Application->ExeName;
                this->mainDir = ExtractFileDir(Application->ExeName);
                this->updateDir = mainDir + "\\update";
                this->backupDir = mainDir + "\\backup";
        }

        bool isNewVersionAvailable() {
                return this->newVersion;
        }

        bool didErrorHappen() {
                return this->error;
        }

        ~UpdateTracker() {
                TerminateThread(this->thread1, 0);
                TerminateThread(this->thread2, 0);
                this->stringList->Clear();
                delete this->stringList;
                delete this->filesToInstall;
        }
        
        String getValue(String in) {
                String out = "";
                String tmp = in.Trim();
                for(int i = 1; i < tmp.Length(); i++) {
                        if(tmp.SubString(i,1) == "=") {
                                out = tmp.SubString(i + 1, tmp.Length() - i).Trim();
                                break;
                        }
                }
                return out;
        }

        String getApplicationExe() {
                return this->applicationExe;
        }

        String getMainDir() {
                return this->mainDir;
        }

        String getUpdateDir() {
                return this->updateDir;
        }

        String getBackupDir() {
                return this->backupDir;
        }

        void errorHappend(String msg, bool log) {
                this->error = true;
                if(this->errorMsg.IsEmpty()) {
                        this->errorMsg = msg;
                }
                if(log) {
                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add(msg);
                }
                this->newVersion = false;
        }

};

UpdateTracker *uT;

void TWINDOW_UPDATE::update(Observable *o) {
        if(o == this->languageDB) {
                this->updateGuiLanguage();
        }

        if(o == uT->loader && uT->loader != NULL) {
                int index = 0;
                while(uT->loader->hasQueueIndex(index + 1) && (uT->loader->isDone(index) || uT->loader->checkError(index))) {
                        index++;
                }

                WINDOW_UPDATE->LABEL_UPDATE_CURRENTFILE->Caption = uT->loader->getDescription(index);

                int max = WINDOW_UPDATE->PROGRESSBAR_UPDATE_CURRENTFILE->Tag;
                if(max > 0) {
                        int percent = uT->loader->getProgress(0) * 100 / max;
                        WINDOW_UPDATE->PROGRESSBAR_UPDATE_CURRENTFILE->Position = percent;
                }
        }
}

void TWINDOW_UPDATE::cleanUp() {
        this->Timer1->Enabled = false;
        if(uT != NULL) {
                delete uT;
                uT = NULL;
        }
}

DWORD WINAPI UpdaterThread_Step1 (LPVOID lpdwThreadParam__ ) {
        UpdateTracker *uTracker = (UpdateTracker*) lpdwThreadParam__;
        HttpFileDownloader *loader = new HttpFileDownloader();
        if(!loader->setHost("https://www.github.com")) {
                uTracker->errorHappend(loader->getMainErrorMessage(), false);
                uTracker->step++;
                uTracker->working = false;
                delete loader;
                return 0;
        }
        int queueIndex = loader->queueResourceForDownload("/Poweruser/OFPMonitor/wiki/update.txt");
        loader->downloadInSync();
        if(loader->checkError(queueIndex)) {
                uTracker->errorHappend(loader->getErrorMessage(queueIndex), false);
                uTracker->step++;
                uTracker->working = false;
                delete loader;
                return 0;
        }

        loader->getFileAsList(queueIndex, uTracker->stringList);
        delete loader;

        int begin = uTracker->stringList->IndexOf(SECTION_HEADER_START);
        int end = uTracker->stringList->IndexOf(SECTION_HEADER_END);
        for(int i = begin + 1; i < end; i++) {
                if(uTracker->stringList->Strings[i].SubString(1,7) == "Version") {
                        uTracker->remoteVersion = uTracker->getValue(uTracker->stringList->Strings[i]);
                }
        }
        StringSplitter sspl(uTracker->localVersion);
        TStringList *local = sspl.split(".");
        StringSplitter sspr(uTracker->remoteVersion);
        TStringList *remote = sspr.split(".");
        uTracker->newVersion = false;
        for(int i = 0; i < local->Count && i < remote->Count; i++) {
                int l = StrToIntDef(local->Strings[i], -1);
                int r = StrToIntDef(remote->Strings[i], -1);
                if(l >= 0 && r >= 0) {
                        uTracker->newVersion = (r > l);
                        if(uTracker->newVersion || (r < l)) {
                                break;
                        }
                } else {
                        uTracker->newVersion = false;
                        break;
                }
        }
        delete local;
        delete remote;
        uTracker->step++;
        uTracker->working = false;
        return 0;
}

void checkAndSaveFileToDisk(UpdateTracker *uTracker, TMemoryStream *stream, String fileName, String expectedFileSize, String expectedFileHash) {
        boolean sizeOk = expectedFileSize.IsEmpty() || (String(stream->Size) == expectedFileSize);
        boolean hashOk = expectedFileHash.IsEmpty();
        String calculatedHash = "";
        if(!hashOk) {
                TIdHashMessageDigest5 *md5 = new TIdHashMessageDigest5();
                int streamPosition = stream->Position;
                stream->Position = 0;
                calculatedHash = md5->HashStreamAsHex(stream);
                stream->Position = streamPosition;
                delete md5;
                hashOk = (calculatedHash.LowerCase() == expectedFileHash.LowerCase());
        }
        if(sizeOk && hashOk) {
                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + fileName);
                String fileOnDisk = uTracker->getUpdateDir() + "\\" + fileName;
                try {
                        stream->SaveToFile(fileOnDisk);
                } catch(Exception &E) {
                        String error = "Error while writing " + fileName + " to disk: " + E.Message;
                        uTracker->errorHappend(error, true);
                }
                if(FileExists(fileOnDisk)) {
                        if(fileOnDisk.SubString(fileOnDisk.Length() - 3, 4) == ".rar") {
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Extracting " + fileName + " ...");

                                RAROpenArchiveDataEx rarArchive;
                                memset(&rarArchive, 0, sizeof(rarArchive));
                                rarArchive.ArcName = fileOnDisk.c_str();
                                rarArchive.OpenMode = RAR_OM_EXTRACT;
                                rarArchive.CmtBuf = NULL;
                                rarArchive.CmtBufSize = 0;
                                rarArchive.CmtSize = 0;
                                rarArchive.Callback = NULL;

                                HANDLE rarHandle = RAROpenArchiveEx(&rarArchive);
                                RARHeaderDataEx rarHeader;
                                int retHeader;
                                while((retHeader = RARReadHeaderEx(rarHandle, &rarHeader)) == 0) {
                                        RARProcessFile(rarHandle,RAR_EXTRACT, uTracker->getUpdateDir().c_str(),NULL);
                                        uTracker->filesToInstall->Add(rarHeader.FileName);
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("      " + String(rarHeader.FileName));
                                }
                                if(retHeader == ERAR_BAD_DATA) {
                                        String error = String(rarHeader.FileName) + " - Archive damaged, extraction aborted";
                                        uTracker->errorHappend(error, true);
                                }
                                int ret = RARCloseArchive(rarHandle);
                                if(ret != 0) {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("close error");
                                }
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   ... done.");
                        } else {
                                uTracker->filesToInstall->Add(fileName);
                        }
                }
        }
        if(!sizeOk) {
                String error = "Invalid file size for file " + fileName + " (" + String(stream->Size) + String(" Bytes). Expected size: ") + expectedFileSize + " Bytes";
                uTracker->errorHappend(error, true);
        }
        if(!hashOk) {
                String error = "The file " + fileName + " is damaged. It's current MD5 hash " + calculatedHash + " does not match the expected hash " + expectedFileHash;
                uTracker->errorHappend(error, true);
        }
}

DWORD WINAPI UpdaterThread_Step2 (LPVOID lpdwThreadParam__ ) {
        UpdateTracker *uTracker = (UpdateTracker*) lpdwThreadParam__;
        if(!DirectoryExists(uTracker->getUpdateDir())) {
                if(!CreateDir(uTracker->getUpdateDir())) {
                        String error = "Could not create the update folder " + uTracker->getBackupDir();
                        uTracker->errorHappend(error, true);
                }
        }
        if(!DirectoryExists(uT->getBackupDir())) {
                if(!CreateDir(uT->getBackupDir())) {
                        String error = "Could not create the backup folder " + uTracker->getBackupDir();
                        uTracker->errorHappend(error, true);
                }
        }
        if(uTracker->newVersion && uTracker->answer == mrYes &&
                   DirectoryExists(uTracker->getUpdateDir()) &&
                   DirectoryExists(uT->getBackupDir())) {
                        int locationBegin = uTracker->stringList->IndexOf(SECTION_LOCATION_START);
                        int locationEnd = uTracker->stringList->IndexOf(SECTION_LOCATION_END);
                        int filesBegin = uTracker->stringList->IndexOf(SECTION_RELEASE_START);
                        int filesEnd = uTracker->stringList->IndexOf(SECTION_RELEASE_END);
                        if(locationBegin < 0 || locationEnd < 0 || locationBegin >= locationEnd || filesBegin < 0 || filesEnd < 0 || filesBegin >= filesEnd) {
                                String error = "The content of the update information file is invalid. Please report this error.";
                                uTracker->errorHappend(error, true);
                                uTracker->updateDone = true;
                                uTracker->step++;
                                uTracker->working = false;
                                return 0;
                        }
                        String location = "";
                        for(int i = locationBegin + 1; i < locationEnd; i++) {
                                String line = uT->stringList->Strings[i].Trim();
                                if(!line.IsEmpty()) {
                                        location = line;
                                        break;
                                }
                        }

                        int count = filesEnd - (filesBegin + 1);
                        int *queueIndexes = new int[count];
                        String *files = new String[count];
                        String *fileHashes = new String[count];
                        String *fileSizes = new String[count];
                        int totalSize = 0;
                        HttpFileDownloader *loader = new HttpFileDownloader();
                        if(!loader->setHost(location)) {
                                uT->errorHappend(loader->getMainErrorMessage(), true);
                                uTracker->updateDone = true;
                                uTracker->step++;
                                uTracker->working = false;
                                return 0;
                        }

                        bool failedToDownloadAFile = false;
                        for(int i = filesBegin + 1; i < filesEnd; i++) {
                                int arrayIndex = i - (filesBegin + 1);

                                queueIndexes[arrayIndex] = -1;
                                files[arrayIndex] = "";
                                fileHashes[arrayIndex] = "";
                                fileSizes[arrayIndex] = "";
                                StringSplitter ssp(uT->stringList->Strings[i].Trim());
                                TStringList *item = ssp.split("#");
                                String file = "";
                                String target = "";
                                int size;
                                for(int element = 0; element < item->Count; element++) {
                                        switch(element) {
                                                case 0:
                                                        file = item->Strings[element];
                                                        files[arrayIndex] = file;
                                                        URL_COMPONENTS url;
                                                        target = location + file;
                                                        if(crackURL(target, url)) {
                                                                String resource = String(url.lpszUrlPath);
                                                                queueIndexes[arrayIndex] = loader->queueResourceForDownload(resource, file);
                                                        }
                                                        break;
                                                case 1:
                                                        fileSizes[arrayIndex] = item->Strings[element];
                                                        try {
                                                                size = StrToInt(fileSizes[arrayIndex]);
                                                                totalSize += size;
                                                        } catch (Exception &E) { }
                                                        break;
                                                case 2:
                                                        fileHashes[arrayIndex] = item->Strings[element];
                                                        break;
                                                default:
                                                        break;

                                        }
                                }

                        }
                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Downloading files ...");
                        WINDOW_UPDATE->PROGRESSBAR_UPDATE_CURRENTFILE->Tag = totalSize;
                        uT->loader = loader;
                        loader->SetObserver(WINDOW_UPDATE);
                        loader->downloadInSync();
                        for(int i = 0; i < count; i++) {
                                int queueIndex = queueIndexes[i];
                                String target = location + files[i];
                                if(queueIndex >= 0) {
                                        if(loader->isDone(queueIndex)) {
                                                TMemoryStream *stream = new TMemoryStream;
                                                loader->getFileAsStream(queueIndex, stream);
                                                checkAndSaveFileToDisk(uTracker, stream, files[i], fileSizes[i], fileHashes[i]);
                                                delete stream;
                                        } else {
                                                String error = "Could not download: " + target + " - Reason: " + loader->getErrorMessage(queueIndex);
                                                failedToDownloadAFile = true;
                                                uT->errorHappend(error, true);
                                        }
                                }
                        }
                        delete loader;
                        uT->loader = NULL;
                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("... done.");
                        if(!failedToDownloadAFile) {

                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Installing files ...");
                                for(int i = 0; i < uT->filesToInstall->Count; i++) {
                                        String item = uT->filesToInstall->Strings[i];
                                        if(FileExists(uT->getMainDir() + "\\" + item)) {
                                                if(FileExists(uT->getBackupDir() + "\\" + item)) {
                                                        DeleteFile(uT->getBackupDir() + "\\" + item);
                                                }
                                                if(!RenameFile(uT->getMainDir() + "\\" + item, uT->getBackupDir() + "\\" + item)) {
                                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Could not backup: " + item);
                                                }
                                        }
                                        if(RenameFile(uT->getUpdateDir() + "\\" + item, uT->getMainDir() + "\\" + item)) {
                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + item);
                                        } else {
                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Could not install: " + item);
                                        }
                                }
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("... done.");
                        }
                        delete queueIndexes;
                        delete files;
                        delete fileHashes;
                        delete fileSizes;
                }
                uTracker->updateDone = true;
                uTracker->step++;
                uTracker->working = false;
                return 0;
}



void TWINDOW_UPDATE::checkForNewVersion (bool userTriggered) {
        WINDOW_SETTINGS->BUTTON_UPDATE->Enabled = false;
        this->cleanUp();
        uT = new UpdateTracker(userTriggered);
        WINDOW_UPDATE->Timer1->Enabled = true;
}


//---------------------------------------------------------------------------
__fastcall TWINDOW_UPDATE::TWINDOW_UPDATE(TComponent* Owner)
        : TForm(Owner)
{            
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_UPDATE::Timer1Timer(TObject *Sender)
{
        if(uT != NULL && !uT->working) {
                uT->working = true;
                if(uT->step == 1) {
                        uT->thread1 = CreateThread(0, 0, UpdaterThread_Step1, uT, 0, 0);
                } else if(uT->step == 2) {
                        if(uT->newVersion) {
                                uT->answer = MessageDlg(this->languageDB->getGuiString("STRING_UPDATE1") + "  " +
                                        uT->remoteVersion + "\n" + this->languageDB->getGuiString("STRING_UPDATE2"),
                                        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0);
                                if(uT->answer == mrYes) {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Clear();
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Updating from version " + uT->localVersion + " to " + uT->remoteVersion);
                                        WINDOW_SETTINGS->Hide();
                                        WINDOW_MAIN->CoolTrayIcon1->IconVisible = false;
                                        WINDOW_MAIN->Enabled = false;
                                        WINDOW_MAIN->Hide();
                                        WINDOW_UPDATE->Show();
                                        uT->thread2 = CreateThread(0, 0, UpdaterThread_Step2, uT, 0, 0);
                                } else {
                                        this->cleanUp();
                                        WINDOW_SETTINGS->BUTTON_UPDATE->Enabled = true;
                                }
                        } else {
                                if(uT->userTriggered) {
                                        if(uT->didErrorHappen()) {
                                                ShowMessage("Error: " + uT->errorMsg);
                                                uT->error = false;
                                        } else {
                                                ShowMessage(this->languageDB->getGuiString("STRING_UPDATE_ALREADYLATEST"));
                                        }
                                }
                                this->cleanUp();
                                WINDOW_SETTINGS->BUTTON_UPDATE->Enabled = true;
                        }
                } else if(uT->step == 3) {
                        if(uT->updateDone) {
                                String errorMsg = uT->errorMsg;
                                String targetExe = uT->getApplicationExe();
                                String targetDir = uT->getMainDir();
                                boolean errorHappened = uT->didErrorHappen();
                                this->cleanUp();
                                try {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->SaveToFile(targetDir + "\\updateLog.txt");
                                } catch(Exception &E) {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Error while saving the update log: " + E.Message);
                                }
                                if(errorHappened) {
                                        String message = "Update failed!\n\nFirst error: ";
                                        message += errorMsg;
                                        message += "\nCheck the update log file " + targetDir + "\\updateLog.txt for other errors as well.";
                                        ShowMessage(message);
                                        WINDOW_UPDATE->Hide();
                                        WINDOW_MAIN->Enabled = true;
                                        WINDOW_SETTINGS->BUTTON_UPDATE->Enabled = true;
                                        WINDOW_MAIN->CoolTrayIcon1->IconVisible = true;
                                        WINDOW_MAIN->Show();
                                } else {
                                        releaseMutex();
                                        WINDOW_MAIN->Close();
                                        ShellExecute(NULL, "open", PChar(targetExe.c_str()), PChar(""), PChar(targetDir.c_str()), SW_NORMAL);
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_UPDATE::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        this->cleanUp();
}
//---------------------------------------------------------------------------


