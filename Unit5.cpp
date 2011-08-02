//---------------------------------------------------------------------------

#include <vcl.h>
#include <list.h>
#include "FileVersion.h"
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit5.h"
#include "OFPMonitor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdIOHandler"
#pragma link "IdIOHandlerSocket"
#pragma link "IdIOHandlerStack"
#pragma link "IdSSL"
#pragma resource "*.dfm"
TWINDOW_UPDATE *WINDOW_UPDATE;

String updateLocation = "https://raw.github.com/wiki/Poweruser/OFPMonitor/";

class UpdateTracker {
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

        String localVersion;
        String remoteVersion;
        bool newVersion;
        int answer;
        String applicationExe;
        String mainDir;
        String updateDir;
        String backupDir;
        TForm1 *form1;
        TWINDOW_UPDATE *window_update;
        TWINDOW_SETTINGS *window_settings;

        UpdateTracker (bool userTriggered) {
                this->form1 = Form1;
                this->window_update = WINDOW_UPDATE;
                this->window_settings = WINDOW_SETTINGS;
                this->userTriggered = userTriggered;
                this->working = false;
                this->updateDone = false;
                this->newVersion = false;
                this->answer = mrNo;
                this->step = 1;
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
                this->mainDir = GetCurrentDir();
                this->updateDir = mainDir + "\\update";
                this->backupDir = mainDir + "\\backup";
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
};

UpdateTracker *uT;

DWORD WINAPI UpdaterThread_Step1 (LPVOID lpdwThreadParam__ ) {
                UpdateTracker *uTracker = (UpdateTracker*) lpdwThreadParam__;
                try {
                        uTracker->http->Get(updateLocation + "update.txt", uTracker->ms);
                } catch (...) {
                        uTracker->newVersion = false;
                        uTracker->step++;
                        uTracker->working = false;
                        return 0;
                }
                uTracker->ms->Position = 0;
                uTracker->stringList->LoadFromStream(uTracker->ms);
                int begin = uTracker->stringList->IndexOf("[Header)");
                int end = uTracker->stringList->IndexOf("[\\Header]");
                for(int i = begin + 1; i < end; i++) {
                        if(uTracker->stringList->Strings[i].SubString(1,7) == "Version") {
                                uTracker->remoteVersion = uTracker->getValue(uTracker->stringList->Strings[i]);
                        }
                }

                list<String> local = uTracker->form1->splitUpMessage(uTracker->localVersion, ".");
                list<String> remote = uTracker->form1->splitUpMessage(uTracker->remoteVersion, ".");
                list<String>::iterator li = local.begin();
                list<String>::iterator ri = remote.begin();
                uTracker->newVersion = false;
                for (; li != local.end() && ri != remote.end(); ++li, ++ri) {
                        try {
                                int l = StrToInt(*li);
                                int r = StrToInt(*ri);
                                uTracker->newVersion = (r > l);
                                if(uTracker->newVersion || (r < l)) {
                                        break;
                                }
                        } catch (...) {
                                uTracker->newVersion = false;
                                break;
                        }
                }
                uTracker->step++;
                uTracker->working = false;
                return 0;
        }

DWORD WINAPI UpdaterThread_Step2 (LPVOID lpdwThreadParam__ ) {
        UpdateTracker *uTracker = (UpdateTracker*) lpdwThreadParam__;
                if(uTracker->newVersion && uTracker->answer == mrYes) {

                        int begin = uTracker->stringList->IndexOf("[Files]");
                        int end = uTracker->stringList->IndexOf("[\\Files]");
                        if(!DirectoryExists(uTracker->updateDir)) {
                                CreateDir(uTracker->updateDir);
                        }
                        WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Max = end - (begin + 1);
                        WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position = 0;
                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Downloading files ...");
                        
                        for(int i = begin + 1; i < end; i++) {
                                list<String> item = Form1->splitUpMessage(uT->stringList->Strings[i].Trim(), ":");
                                String file = item.front();
                                String fileSize = item.back();
                                String target = updateLocation + file;
                                uT->fs->Clear();
                                WINDOW_UPDATE->LABEL_UPDATE_CURRENTFILE->Caption = file;
                                try {
                                        uT->http->Get(target, uT->fs);
                                        if(String(uT->fs->Size) == fileSize) {
                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + file);
                                                uT->filesToInstall->Add(file);
                                                uT->fs->SaveToFile(uT->updateDir + "\\" + file);
                                        } else {
                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + file + " - invalid file size: " + String(uT->fs->Size) + " expected: " + fileSize);
                                        }
                                } catch (...) {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Could not download: " + file);
                                }
                                int t = WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position;
                                WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position = t + 1;
                        }
                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("... done.");
                        if(!DirectoryExists(uT->backupDir)) {
                                CreateDir(uT->backupDir);
                        }

                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Installing files ...");
                                                
                        for(int i = 0; i < uT->filesToInstall->Count; i++) {
                                String item = uT->filesToInstall->Strings[i];
                                if(FileExists(uT->mainDir + "\\" + item)) {
                                        if(FileExists(uT->backupDir + "\\" + item)) {
                                                DeleteFile(uT->backupDir + "\\" + item);
                                        }
                                        if(!RenameFile(uT->mainDir + "\\" + item, uT->backupDir + "\\" + item)) {
                                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Could not backup: " + item);
                                        }
                                }
                                if(RenameFile(uT->updateDir + "\\" + item, uT->mainDir + "\\" + item)) {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + item);
                                } else {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Could not install: " + item);
                                }
                        }

                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("... done.");
                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->SaveToFile(uT->mainDir + "\\updateLog.txt");
                        uTracker->updateDone = true;
                } else {
                        uTracker->updateDone = false;
                }
                uTracker->updateDone = true;
                uTracker->step++;
                uTracker->working = false;
                return 0;
}



void TWINDOW_UPDATE::checkForNewVersion (bool userTriggered) {
        WINDOW_SETTINGS->BUTTON_UPDATE->Enabled = false;
        if(uT != NULL) {
                delete uT;
        }
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
                                uT->answer = MessageDlg(WINDOW_SETTINGS->getGuiString("STRING_UPDATE1") + "  " +
                                        uT->remoteVersion + "\n" + WINDOW_SETTINGS->getGuiString("STRING_UPDATE2"),
                                        mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0);
                                if(uT->answer == mrYes) {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Clear();
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Updating from version " + uT->localVersion + " to " + uT->remoteVersion);
                                        WINDOW_SETTINGS->Hide();
                                        Form1->CoolTrayIcon1->IconVisible = false;
                                        Form1->Enabled = false;
                                        Form1->Hide();
                                        WINDOW_UPDATE->Show();
                                        uT->thread2 = CreateThread(0, 0, UpdaterThread_Step2, uT, 0, 0);
                                } else {
                                        WINDOW_SETTINGS->BUTTON_UPDATE->Enabled = true;
                                }
                        } else {
                                if(uT->userTriggered) {
                                        ShowMessage(WINDOW_SETTINGS->getGuiString("STRING_UPDATE_ALREADYLATEST"));
                                }
                                WINDOW_SETTINGS->BUTTON_UPDATE->Enabled = true;
                        }
                } else if(uT->step == 3) {
                        if(uT->updateDone) {
                                Timer1->Enabled = false;
                                String targetExe = uT->applicationExe;
                                String targetDir = uT->mainDir;
                                delete uT;
                                releaseMutex();
                                Form1->Close();
                                ShellExecute(NULL, "open", PChar(targetExe.c_str()), PChar(""), PChar(targetDir.c_str()), SW_NORMAL);
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_UPDATE::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        if(uT != NULL) {
                delete uT;
        }
}
//---------------------------------------------------------------------------


