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

bool doingUpdate = false;
String updateLocation = "https://raw.github.com/wiki/Poweruser/OFPMonitor/";

void TWINDOW_UPDATE::checkForNewVersion (bool userTriggered) {
        WINDOW_UPDATE->Timer1->Tag = userTriggered;
        WINDOW_UPDATE->Timer1->Enabled = true;
}

void checkForUpdate(bool userTriggered) {
        TIdHTTP *http = new TIdHTTP(WINDOW_UPDATE);
        TIdSSLIOHandlerSocketOpenSSL *ssl = new TIdSSLIOHandlerSocketOpenSSL(WINDOW_UPDATE);
        http->HandleRedirects = true;
        http->IOHandler = ssl;
        http->ReadTimeout = 4000;
        http->OnWorkBegin = WINDOW_UPDATE->IdHTTPWorkBegin;
        http->OnWork = WINDOW_UPDATE->IdHTTPWork;
        String applicationExe = Application->ExeName;
        String mainDir = GetCurrentDir();
        String updateDir = mainDir + "\\update";
        String backupDir = mainDir + "\\backup";
        String remoteVersion = "";
        FileVersion *fv = new FileVersion(Application->ExeName);
        String localVersion = fv->getFullVersion();
        delete fv;
	TMemoryStream *ms = new TMemoryStream;
       	TStringList *stringList = new TStringList;
        try {
                http->Get(updateLocation + "update.txt", ms);
        } catch (...) {
                ms->Clear();
        }
        ms->Position = 0;
        stringList->LoadFromStream(ms);
        int begin = stringList->IndexOf("[Header)");
        int end = stringList->IndexOf("[\\Header]");
        for(int i = begin + 1; i < end; i++) {
                if(stringList->Strings[i].SubString(1,7) == "Version") {
                        remoteVersion = getValue(stringList->Strings[i]);
                }
        }

        list<String> local = Form1->splitUpMessage(localVersion, ".");
        list<String> remote = Form1->splitUpMessage(remoteVersion, ".");
        list<String>::iterator li = local.begin();
        list<String>::iterator ri = remote.begin();
        bool newVersion = false;
        for (; li != local.end() && ri != remote.end(); ++li, ++ri) {
                try {
                        int l = StrToInt(*li);
                        int r = StrToInt(*ri);
                        newVersion = (r > l);
                        if(newVersion || (r < l)) {
                                break;
                        }
                } catch (...) {
                        newVersion = false;
                        break;
                }
        }
        int answer = mrNo;
        if(newVersion) {
                answer = MessageDlg(WINDOW_SETTINGS->getGuiString("STRING_UPDATE1") + "  " +
                                remoteVersion + "\n" + WINDOW_SETTINGS->getGuiString("STRING_UPDATE2"),
                                mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0);
        } else {
                if(userTriggered) {
                        ShowMessage(WINDOW_SETTINGS->getGuiString("STRING_UPDATE_ALREADYLATEST"));
                }
        }
        if(newVersion && answer == mrYes) {
                Application->ProcessMessages();
                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Clear();
                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Updating from version " + localVersion + " to " + remoteVersion);
                WINDOW_SETTINGS->Hide();
                Form1->CoolTrayIcon1->IconVisible = false;
                Form1->Enabled = false;
                Form1->Hide();
                WINDOW_UPDATE->Show();
                Application->ProcessMessages();
                begin = stringList->IndexOf("[Files]");
                end = stringList->IndexOf("[\\Files]");
                if(!DirectoryExists(updateDir)) {
                        CreateDir(updateDir);
                }
                WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Max = end - (begin + 1);
                WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position = 0;
                TStringList *filesToInstall = new TStringList;
                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Downloading files ...");
                for(int i = begin + 1; i < end; i++) {
                        Application->ProcessMessages();
                        list<String> item = Form1->splitUpMessage(stringList->Strings[i].Trim(), ":");
                        String file = item.front();
                        String fileSize = item.back();
                        String target = updateLocation + file;
                        TMemoryStream *fs = new TMemoryStream;
                        WINDOW_UPDATE->LABEL_UPDATE_CURRENTFILE->Caption = file;
                        try {
                                http->Get(target, fs);
                                Application->ProcessMessages();
                                if(String(fs->Size) == fileSize) {

                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + file);
                                        filesToInstall->Add(file);
                                } else {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + file + " - invalid file size: " + String(fs->Size) + " expected: " + fileSize);
                                }
                                fs->SaveToFile(updateDir + "\\" + file);
                        } catch (...) {
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Could not download: " + file);
                        }
                        delete fs;
                        int t = WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position;
                        WINDOW_UPDATE->PROGRESSBAR_UPDATE_OVERALL->Position = t + 1;
                }
                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("... done.");
                if(!DirectoryExists(backupDir)) {
                        CreateDir(backupDir);
                }
                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("Installing files ...");
                for(int i = 0; i < filesToInstall->Count; i++) {
                        String item = filesToInstall->Strings[i];
                        if(FileExists(mainDir + "\\" + item)) {
                                if(FileExists(backupDir + "\\" + item)) {
                                        DeleteFile(backupDir + "\\" + item);
                                }
                                if(!RenameFile(mainDir + "\\" + item, backupDir + "\\" + item)) {
                                        WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Could not backup: " + item);
                                }
                        }
                        if(RenameFile(updateDir + "\\" + item, mainDir + "\\" + item)) {
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   " + item);
                        } else {
                                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("   Could not install: " + item);
                        }
                }
                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->Add("... done.");
                WINDOW_UPDATE->MEMO_UPDATE_LOG->Lines->SaveToFile(mainDir + "\\updateLog.txt");
                delete filesToInstall;
                releaseMutex();
                Form1->Close();
                ShellExecute(NULL, "open", PChar(applicationExe.c_str()), PChar(""), PChar(mainDir.c_str()), SW_NORMAL);
        }
        stringList->Clear();
        delete stringList;
        delete ms;
        http->Disconnect();
        delete http;
        delete ssl;
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
        Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_UPDATE::IdHTTPWork(TObject *ASender,
      TWorkMode AWorkMode, __int64 AWorkCount)
{
        PROGRESSBAR_UPDATE_CURRENTFILE->Position = (int)AWorkCount;
        Application->ProcessMessages();
}
//---------------------------------------------------------------------------
                                                
void __fastcall TWINDOW_UPDATE::Timer1Timer(TObject *Sender)
{
        Timer1->Enabled = false;
        if(!doingUpdate) {
                doingUpdate = true;
                checkForUpdate(Timer1->Tag);
                doingUpdate = false;
        }
}
//---------------------------------------------------------------------------

