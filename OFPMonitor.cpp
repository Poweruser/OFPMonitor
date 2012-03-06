//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <list.h>
#include "FileVersion.h"
#include "OFPMonitor.h"
#include "ProcessFinder.h"
#pragma hdrstop

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

String getExeFromFullPath(String in) {
        String out = in;
        for(int i = in.Length() - 1; i >= 0; i--) {
                if(in.SubString(i,1) == "\\") {
                        out = in.SubString(i + 1, in.Length() - i);
                        break;
                }
        }
        return out;
}

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        if(!MyAppAlreadyRunning()) {
	        try {
                        String soundDir = GetCurrentDir() + "\\sound\\";
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
                        Application->Initialize();
                        FileVersion *fv = new FileVersion(Application->ExeName);
                        Application->Title = "OFPMonitor " + fv->getFullVersion();
                        delete fv;
                        Application->CreateForm(__classid(TForm1), &Form1);
                        Application->CreateForm(__classid(TWINDOW_UPDATE), &WINDOW_UPDATE);
                        Application->CreateForm(__classid(TWINDOW_INFO), &WINDOW_INFO);
                        Application->CreateForm(__classid(TWINDOW_LOCALGAME), &WINDOW_LOCALGAME);
                        Application->CreateForm(__classid(TWINDOW_SETTINGS), &WINDOW_SETTINGS);
                        Application->Run();
                } catch (Exception &exception) {
                        Application->ShowException(&exception);
                } catch (...) {
                        try {
                                throw Exception("");
                        } catch (Exception &exception) {
                                Application->ShowException(&exception);
                        }
                }
	} else {
                ProcessFinder *finder = new ProcessFinder();
                TStringList *startsWith = new TStringList();
                startsWith->Add("OFPMonitor");
                TStringList *moduleIncludes = new TStringList();
                moduleIncludes->Add(getExeFromFullPath(Application->ExeName));
                if(finder->enumerate(startsWith, moduleIncludes)) {
                        ProcessInfo p = finder->output.front();
                        SendMessage(p.hWindow, WM_KEYDOWN, VK_F13, NULL);
                        SendMessage(p.hWindow, WM_KEYUP,   VK_F13, NULL);
                        SetForegroundWindow(p.hWindow);
                }
                delete finder;
                delete startsWith;
                delete moduleIncludes;
        }
        return 0;
}
//---------------------------------------------------------------------------
