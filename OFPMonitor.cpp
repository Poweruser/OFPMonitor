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
                if(finder->enumerate("OFPMonitor", getExeFromFullPath(Application->ExeName))) {
                        ProcessInfo p = finder->output.front();
                        SendMessage(p.hWindow, WM_KEYDOWN, VK_F13, NULL);
                        SendMessage(p.hWindow, WM_KEYUP,   VK_F13, NULL);
                        SetForegroundWindow(p.hWindow);
                }
                delete finder;
        }
        return 0;
}
//---------------------------------------------------------------------------
