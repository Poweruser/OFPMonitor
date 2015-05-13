//---------------------------------------------------------------------------

#include <vcl.h>
#include <list.h>
#include <unrar.h>
#include "FileVersion.h"
#include "StringSplitter.h"
#include <IdHashMessageDigest.hpp>
#pragma hdrstop

#include "Form_Main.h"
#include "Form_Settings.h"
#include "Form_Update.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdIOHandler"
#pragma link "IdIOHandlerSocket"
#pragma link "IdIOHandlerStack"
#pragma link "IdSSL"
#pragma resource "*.dfm"
TWINDOW_UPDATE *WINDOW_UPDATE;

#define SECTION_HEADER_START "[Header]"
#define SECTION_HEADER_END "[\\Header]"
#define SECTION_LOCATION_START "[DownloadLocation]"
#define SECTION_LOCATION_END "[\\DownloadLocation]"
#define SECTION_RELEASE_START "[ReleaseMD5]"
#define SECTION_RELEASE_END "[\\ReleaseMD5]"

void releaseMutex();

void TWINDOW_UPDATE::update(Observable *o) {
        if(o == this->languageDB) {
                this->updateGuiLanguage();
        }
}

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
        TIdHTTP *http;
        TIdSSLIOHandlerSocketOpenSSL *ssl;
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
                this->http = new TIdHTTP(WINDOW_UPDATE);
                this->ssl = new TIdSSLIOHandlerSocketOpenSSL(WINDOW_UPDATE);
                this->http->HandleRedirects = true;
                this->http->IOHandler = ssl;
                this->http->ReadTimeout = 3000;
                this->http->OnWorkBegin = this->IdHTTPWorkBegin;
                this->http->OnWork = this->IdHTTPWork;
                this->ms = new TMemoryStream;
                this->fs = new TMemoryStream;
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
                delete this->ms;
                delete this->fs;
                this->http->Disconnect();
                delete this->ssl;
                delete this->http;
        }

        void closeOpenConnections() {
                if(this->http->Connected()) {
                        this->http->Disconnect();
                }
        }

        void __fastcall IdHTTPWorkBegin(TObject *ASender,
                TWorkMode AWorkMode, __int64 AWorkCountMax)
        {
                WINDOW_UPDATE->PROGRESSBAR_UPDATE_CURRENTFILE->Max = (int)AWorkCountMax;
                WINDOW_UPDATE->PROGRESSBAR_UPDATE_CURRENTFILE->Position = 0;
        }

        void __fastcall IdHTTPWork(TObject *ASender,
                TWorkMode AWorkMode, __int64 AWorkCount)
        {
                WINDOW_UPDATE->PROGRESSBAR_UPDATE_CURRENTFILE->Position = (int)AWorkCount;
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

        void errorHappend(String msg) {
                this->error = true;
                if(this->errorMsg.IsEmpty()) {
                        this->errorMsg = msg;
                }
                this->newVersion = false;
        }

};

UpdateTracker *uT;

void TWINDOW_UPDATE::cleanUp() {
        this->Timer1->Enabled = false;
        if(uT != NULL) {
                delete uT;
                uT = NULL;
        }
}

DWORD WINAPI UpdaterThread_Step1 (LPVOID lpdwThreadParam__ ) {
                UpdateTracker *uTracker = (UpdateTracker*) lpdwThreadParam__;
                try {
                        uTracker->http->Get("https://raw.github.com/wiki/poweruser/ofpmonitor/update.txt", uTracker->ms);
                } catch (EIdException &E) {
                        uTracker->errorHappend(E.Message);
                        uTracker->step++;
                        uTracker->working = false;
                        uTracker->closeOpenConnections();
                        return 0;
                }
                uTracker->closeOpenConnections();
                uTracker->ms->Position = 0;
                uTracker->stringList->LoadFromStream(uTracker->ms);
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

DWORD WINAPI UpdaterThread_Step2 (LPVOID lpdwThreadParam__ ) {
        UpdateTracker *uTracker = (UpdateTracker*) lpdwThreadParam__;
                if(!DirectoryExists(uTracker->getUpdateDir())) {
                        if(!CreateDir(uTracker->getUpdateDir())) {
                                String error = "Could not create the update folder " + uTracker->getBackupDir();
                                uTracker->errorHappend(error);
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add(error);
                        }
                }
                if(!DirectoryExists(uT->getBackupDir())) {
                        if(!CreateDir(uT->getBackupDir())) {
                                String error = "Could not create the backup folder " + uTracker->getBackupDir();
                                uTracker->errorHappend(error);
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add(error);
                        }
                }
                if(uTracker->newVersion && uTracker->answer == mrYes &&
                   DirectoryExists(uTracker->getUpdateDir()) &&
                   DirectoryExists(uT->getBackupDir())) {
                        int locationBegin = uTracker->stringList->IndexOf(SECTION_LOCATION_START);
                        int locationEnd = uTracker->stringList->IndexOf(SECTION_LOCATION_END);
                        int filesBegin = uTracker->stringList->IndexOf(SECTION_RELEASE_START);
                        int filesEnd = uTracker->stringList->IndexOf(SECTION_RELEASE_END);
                        if(locationBegin < 0 || locationEnd < 0 || locationBegin > locationEnd || filesBegin < 0 || filesEnd < 0 || filesBegin > filesEnd) {
                                String error = "The content of the update information file is invalid. Please report this error.";
                                uTracker->errorHappend(error);
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add(error);
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

                        WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Max = filesEnd - (filesBegin + 1);
                        WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position = 0;
                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Downloading files ...");

                        bool failedToDownloadAFile = false;
                        for(int i = filesBegin + 1; i < filesEnd; i++) {
                                StringSplitter ssp(uT->stringList->Strings[i].Trim());
                                TStringList *item = ssp.split("#");
                                bool success = false;
                                String fileSize = "", fileHash = "", file = "";
                                for(int element = 0; element < item->Count; element++) {
                                        String target, error;
                                        switch(element) {
                                                case 0:
                                                        file = item->Strings[element];
                                                        target = location + file;
                                                        uT->fs->Clear();
                                                        WINDOW_UPDATE->LABEL_UPDATE_CURRENTFILE->Caption = file;
                                                        try {
                                                                uT->http->Get(target, uT->fs);
                                                                success = true;
                                                        } catch (EIdException &E) {
                                                                error = "Could not download: " + target + " - Reason: " + E.Message;
                                                                uT->errorHappend(error);
                                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + error);
                                                        }
                                                        uT->closeOpenConnections();
                                                        break;
                                                case 1:
                                                        fileSize = item->Strings[element];
                                                        break;
                                                case 2:
                                                        fileHash = item->Strings[element];
                                                        break;
                                                default:
                                                        break;
                                        }
                                }
                                if(success) {
                                        boolean sizeOk = fileSize.IsEmpty() || (String(uT->fs->Size) == fileSize);
                                        boolean hashOk = fileHash.IsEmpty();
                                        String calculatedHash = "";
                                        if(!hashOk) {
                                                TIdHashMessageDigest5 *md5 = new TIdHashMessageDigest5();
                                                int streamPosition = uT->fs->Position;
                                                uT->fs->Position = 0;
                                                calculatedHash = md5->HashStreamAsHex(uT->fs);
                                                uT->fs->Position = streamPosition;
                                                delete md5;
                                                hashOk = (calculatedHash.LowerCase() == fileHash.LowerCase());
                                        }
                                        if(sizeOk && hashOk) {
                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + file);
                                                String fileOnDisk = uT->getUpdateDir() + "\\" + file;
                                                try {
                                                        uT->fs->SaveToFile(fileOnDisk);
                                                } catch(Exception &E) {
                                                        String error = "Error while writing " + file + " to disk: " + E.Message;
                                                        uT->errorHappend(error);
                                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + error);
                                                }
                                                if(FileExists(fileOnDisk)) {
                                                        if(fileOnDisk.SubString(fileOnDisk.Length() - 3, 4) == ".rar") {
                                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Extracting " + file + " ...");

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
                                                                        RARProcessFile(rarHandle,RAR_EXTRACT,uT->getUpdateDir().c_str(),NULL);
                                                                        uT->filesToInstall->Add(rarHeader.FileName);
                                                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("      " + String(rarHeader.FileName));
                                                                }
                                                                if(retHeader == ERAR_BAD_DATA) {
                                                                        String error = String(rarHeader.FileName) + " - Archive damaged, extraction aborted";
                                                                        uT->errorHappend(error);
                                                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("      " + error);
                                                                }
                                                                int ret = RARCloseArchive(rarHandle);
                                                                if(ret != 0) {
                                                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("close error");
                                                                }
                                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   ... done.");
                                                        } else {
                                                                uT->filesToInstall->Add(file);
                                                        }
                                                }
                                        } else if(!sizeOk) {
                                                String error = "Invalid file size for file " + file + " (" + String(uT->fs->Size) + " Bytes). Expected size: " + fileSize + " Bytes";
                                                uT->errorHappend(error);
                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + error);
                                        } else if(!hashOk) {
                                                String error = "The file " + file + " is damaged. It's current MD5 hash " + calculatedHash + " does not match the expected hash " + fileHash;
                                                uT->errorHappend(error);
                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + error);
                                        }
                                } else {
                                        failedToDownloadAFile = true;
                                }
                                int t = WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position;
                                WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position = t + 1;
                        }
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

void __fastcall TWINDOW_UPDATE::IdHTTPWorkBegin(TObject *ASender,
      TWorkMode AWorkMode, __int64 AWorkCountMax)
{
        WINDOW_UPDATE->PROGRESSBAR_UPDATE_CURRENTFILE->Max = (int)AWorkCountMax;
        WINDOW_UPDATE->PROGRESSBAR_UPDATE_CURRENTFILE->Position = 0;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_UPDATE::IdHTTPWork(TObject *ASender,
      TWorkMode AWorkMode, __int64 AWorkCount)
{
        PROGRESSBAR_UPDATE_CURRENTFILE->Position = (int)AWorkCount;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_UPDATE::Timer1Timer(TObject *Sender)
{
        if(!uT->working) {
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


