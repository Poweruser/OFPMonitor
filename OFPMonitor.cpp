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
#include "Form_Main.h"
#include "Form_Settings.h"
#include "Form_Localgame.h"
#include "Form_Info.h"
#include "Form_Update.h"
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("lib\ofpmonitor\Form_Main.cpp", WINDOW_MAIN);
USEFORM("lib\ofpmonitor\Form_Settings.cpp", WINDOW_SETTINGS);
USEFORM("lib\ofpmonitor\Form_Localgame.cpp", WINDOW_LOCALGAME);
USEFORM("lib\ofpmonitor\Form_Info.cpp", WINDOW_INFO);
USEFORM("lib\ofpmonitor\Form_Update.cpp", WINDOW_UPDATE);
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

TResourceStream* createResourceStreamToDefaultLanguageFile(HINSTANCE hInstance) {
        return new TResourceStream((int)hInstance, "DefaultLanguage", RT_RCDATA);
}

WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
        bool languageFileExists = true;
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
                        TResourceStream *rs = createResourceStreamToDefaultLanguageFile(hInstance);
                        rs->Position = 0;
                        try {
                                rs->SaveToFile(langFile);
                        } catch(Exception &E) {
                                languageFileExists = false;
                        }
                        delete rs;
                }

                /*
                   Extracting the watched sounds from the exe's resources if the
                   subdirectory \sound does not exist yet
                */

                String soundDir = ExtractFileDir(Application->ExeName) + "\\sound\\";
                if(!DirectoryExists(soundDir)) {
                        if(CreateDir(soundDir)) {
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
                                                                try {
                                                                        ms->SaveToFile(fileName);
                                                                } catch(Exception &E) {}
                                                                ms->Clear();
                                                                delete ms;
                                                        }
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
        if(!languageFileExists) {
                TResourceStream *rs = createResourceStreamToDefaultLanguageFile(hInstance);
                rs->Position = 0;
                languageDB->loadResourceStream(rs);
                delete rs;
        }

        TStringList *file = new TStringList;
        bool loadingOfExistingSettingsFileFailed = false;
        bool settingsFileExists = FileExists(settingsFile);
        if(settingsFileExists) {
                try {
                        file->LoadFromFile(settingsFile);
                } catch (Exception &E) {
                        loadingOfExistingSettingsFileFailed = true;
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
                Application->CreateForm(__classid(TWINDOW_MAIN), &WINDOW_MAIN);
                 Application->CreateForm(__classid(TWINDOW_UPDATE), &WINDOW_UPDATE);
                 Application->CreateForm(__classid(TWINDOW_INFO), &WINDOW_INFO);
                 Application->CreateForm(__classid(TWINDOW_LOCALGAME), &WINDOW_LOCALGAME);
                 Application->CreateForm(__classid(TWINDOW_SETTINGS), &WINDOW_SETTINGS);
                 WINDOW_MAIN->setFontSettings(fontSettings);
                WINDOW_MAIN->setWindowSettings(windowSettings);
                WINDOW_MAIN->setChatSettings(chatSettings);
                WINDOW_MAIN->setServerFilter(serverFilter);
                WINDOW_MAIN->setGameControl(gameControl);
                WINDOW_MAIN->setLanguageDB(languageDB);
                WINDOW_MAIN->setModel(ofpm);
                WINDOW_MAIN->enableSavingOfSettings(!loadingOfExistingSettingsFileFailed);
                WINDOW_SETTINGS->setLanguageDB(languageDB);
                WINDOW_LOCALGAME->setLanguageDB(languageDB);
                WINDOW_INFO->setLanguageDB(languageDB);
                WINDOW_UPDATE->setLanguageDB(languageDB);
                languageDB->setModel(ofpm);
                languageDB->SetObserver(WINDOW_MAIN);
                languageDB->SetObserver(WINDOW_SETTINGS);
                languageDB->SetObserver(WINDOW_LOCALGAME);
                languageDB->SetObserver(WINDOW_INFO);
                ofpm->SetObserver(languageDB);
                languageDB->update(ofpm);
                fontSettings->SetObserver(WINDOW_MAIN);
                gameControl->SetObserver(WINDOW_MAIN);
                ofpm->SetObserver(WINDOW_MAIN);
                WINDOW_MAIN->update(fontSettings);
                WINDOW_MAIN->update(gameControl);
                WINDOW_MAIN->update(ofpm);
                WINDOW_SETTINGS->setModel(ofpm);
                WINDOW_SETTINGS->setChatSettings(chatSettings);
                WINDOW_LOCALGAME->setModel(ofpm);
                WINDOW_MAIN->applyWindowSettings();
                WINDOW_MAIN->checkIfWindowIsReachable();
                if(!settingsFileExists) {
                        WINDOW_MAIN->saveSettings();
                }
                Application->Run();
                WINDOW_MAIN->saveSettings();
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

