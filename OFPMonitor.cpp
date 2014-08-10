//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <list.h>
#include "FileVersion.h"
#include "OFPMonitorModel.h"
#include "OFPMonitorDefinitions.h"
#include "ServerList.h"
#include "GameControl.h"
#include "ProcessFinder.h"
#include "FontSettings.h"
#include "LanguageDB.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#pragma hdrstop

#pragma resource "DefaultLanguage.res"

//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", WINDOW_SETTINGS);
USEFORM("Unit4.cpp", WINDOW_INFO);
USEFORM("Unit3.cpp", WINDOW_LOCALGAME);
USEFORM("Unit5.cpp", WINDOW_UPDATE);
//---------------------------------------------------------------------------
HANDLE hMutex;

bool MyAppAlreadyRunning() {
        hMutex = CreateMutex(NULL,true,"OFPMonitor");
        if (GetLastError() == ERROR_ALREADY_EXISTS ) {
                CloseHandle(hMutex);
                return true; // Already running
        } else {
                return false; // First instance
        }
}

void releaseMutex() {
        CloseHandle(hMutex);
}

WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
        if(MyAppAlreadyRunning()) {
                ProcessFinder *finder = new ProcessFinder();
                TStringList *startsWith = new TStringList();
                startsWith->Add("OFPMonitor");
                TStringList *moduleIncludes = new TStringList();
                moduleIncludes->Add(ExtractFileName(Application->ExeName));
                if(finder->enumerate(startsWith, moduleIncludes)) {
                        ProcessInfo p = finder->output.front();
                        SendMessage(p.hWindow, WM_KEYDOWN, VK_F13, NULL);
                        SendMessage(p.hWindow, WM_KEYUP,   VK_F13, NULL);
                        SetForegroundWindow(p.hWindow);
                }
                delete finder;
                delete startsWith;
                delete moduleIncludes;
                return 0;
        } else {
                String langFile = ExtractFileDir(Application->ExeName) + "\\OFPM_English.lang";
                if(!FileExists(langFile)) {
                        TResourceStream *rs = new TResourceStream((int)hInstance, "DefaultLanguage", RT_RCDATA);
                        rs->Position = 0;
                        rs->SaveToFile(langFile);
                        delete rs;
                }

                /*
                   Extracting the watched sounds from the exe's resources if the
                   subdirectory \sound does not exist yet
                */

                String soundDir = ExtractFileDir(Application->ExeName) + "\\sound\\";
                if(!DirectoryExists(soundDir)) {
                        CreateDir(soundDir);
                        for(int i = 1; i <= 5; i++) {
                                String files[5] = { "creating.wav", "waiting.wav", "briefing.wav", "playing.wav", "debriefing.wav" };
                                String fileName = soundDir + files[i - 1];
                                if(!FileExists(fileName)) {
                                        HMODULE hModule = GetModuleHandle(NULL);
                                        HRSRC resourceInfo = FindResource(hModule, MAKEINTRESOURCE(i), "WAVE");
                                        if(hModule && resourceInfo) {
                                                HGLOBAL data = LoadResource(hModule, resourceInfo);
                                                DWORD size = SizeofResource(hModule, resourceInfo);
                                                if(data && size > 0) {
                                                        TMemoryStream *ms = new TMemoryStream();
                                                        ms->WriteBuffer(data, size);
                                                        ms->SaveToFile(fileName);
                                                        ms->Clear();
                                                        delete ms;
                                                }
                                        }
                                }
                        }
                }
        }

        String settingsFile = ExtractFileDir(Application->ExeName) + "\\OFPMonitor.ini";
        ServerList *sL = new ServerList();
        OFPMonitorModel *ofpm = new OFPMonitorModel(settingsFile, sL);
        GameControl *gameControl = new GameControl(ofpm);
        FontSettings *fontSettings = new FontSettings();
        WindowSettings *windowSettings = new WindowSettings();
        ServerFilter *serverFilter = new ServerFilter();
        ChatSettings *chatSettings = new ChatSettings();
        LanguageDB *languageDB = new LanguageDB();

        TStringList *file = new TStringList;
        bool existingSettingsFileWasLoaded = true;
        if(FileExists(settingsFile)) {
                try {
                        file->LoadFromFile(settingsFile);
                } catch (Exception &E) {
                        existingSettingsFileWasLoaded = false;
                        String message = "Unable to load the settings file. Saving of settings is disabled.\nException message: ";
                        message += E.Message;
                        ShowMessage(message);
                }
        }
        sL->readSettings(file);
        ofpm->readSettings(file);
        gameControl->readSettings(file);
        fontSettings->readSettings(file);
        windowSettings->readSettings(file);
        serverFilter->readSettings(file);
        chatSettings->readSettings(file);

        try {
                Application->Initialize();
                FileVersion *fv = new FileVersion(Application->ExeName);
                Application->Title = "OFPMonitor " + fv->getFullVersion();
                delete fv;
                Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TWINDOW_UPDATE), &WINDOW_UPDATE);
                 Application->CreateForm(__classid(TWINDOW_INFO), &WINDOW_INFO);
                 Application->CreateForm(__classid(TWINDOW_LOCALGAME), &WINDOW_LOCALGAME);
                 Application->CreateForm(__classid(TWINDOW_SETTINGS), &WINDOW_SETTINGS);
                 Form1->setFontSettings(fontSettings);
                Form1->setWindowSettings(windowSettings);
                Form1->setChatSettings(chatSettings);
                Form1->setServerFilter(serverFilter);
                Form1->setGameControl(gameControl);
                Form1->setLanguageDB(languageDB);
                Form1->setModel(ofpm);
                Form1->enableSavingOfSettings(existingSettingsFileWasLoaded);
                WINDOW_SETTINGS->setLanguageDB(languageDB);
                WINDOW_LOCALGAME->setLanguageDB(languageDB);
                WINDOW_INFO->setLanguageDB(languageDB);
                WINDOW_UPDATE->setLanguageDB(languageDB);
                languageDB->setModel(ofpm);
                languageDB->SetObserver(Form1);
                languageDB->SetObserver(WINDOW_SETTINGS);
                languageDB->SetObserver(WINDOW_LOCALGAME);
                languageDB->SetObserver(WINDOW_INFO);
                ofpm->SetObserver(languageDB);
                languageDB->update(ofpm);
                fontSettings->SetObserver(Form1);
                gameControl->SetObserver(Form1);
                ofpm->SetObserver(Form1);
                Form1->update(fontSettings);
                Form1->update(gameControl);
                Form1->update(ofpm);
                WINDOW_SETTINGS->setModel(ofpm);
                WINDOW_SETTINGS->setChatSettings(chatSettings);
                WINDOW_LOCALGAME->setModel(ofpm);
                Form1->applyWindowSettings();
                Application->Run();
                Form1->saveSettings();
        } catch (Exception &exception) {
                Application->ShowException(&exception);
        } catch (...) {
                try {
                        throw Exception("");
                } catch (Exception &exception) {
                        Application->ShowException(&exception);
                }
        }

        gameControl->RemoveAllObservers();
        ofpm->RemoveAllObservers();
        fontSettings->RemoveAllObservers();
        languageDB->RemoveAllObservers();
        delete gameControl;
        delete ofpm;
        delete fontSettings;
        delete windowSettings;
        delete serverFilter;
        delete chatSettings;
        delete file;
        delete languageDB;
        return 0;
}
//---------------------------------------------------------------------------

