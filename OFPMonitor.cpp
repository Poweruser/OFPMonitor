//---------------------------------------------------------------------------

#include <vcl.h>
#include <Psapi.h>
#include <windows.h>
#include <list.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", WINDOW_SETTINGS);
USEFORM("Unit4.cpp", WINDOW_INFO);
//---------------------------------------------------------------------------
class ProcessInfo {
        public:
                DWORD pid;
                HWND hWindow;

                ProcessInfo(DWORD pid, HWND hWindow) {
                        this->pid = pid;
                        this->hWindow = hWindow;
                }
                ProcessInfo() {
                }
};

list<ProcessInfo> plist;
                              
bool MyAppAlreadyRunning() {
        HANDLE hMutex = CreateMutex(NULL,true,"OFPMonitor");
        if (GetLastError() == ERROR_ALREADY_EXISTS ) {
                CloseHandle(hMutex);
                return true; // Already running
        } else {
                return false; // First instance
        }
}

bool CALLBACK MyEnumWindowsProc(HWND hWnd, LPARAM lParam) {
        DWORD PID = 0;
        GetWindowThreadProcessId(hWnd, &PID);
        char *title = new char[11];
        GetWindowText(hWnd, title, 11);
        if(AnsiString(title) == "OFPMonitor") {
                plist.push_back(ProcessInfo(PID,hWnd));
        }
        return true;
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
                        Application->Title = "OFPMonitor 1.50a";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TWINDOW_INFO), &WINDOW_INFO);
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
                EnumWindows((WNDENUMPROC)MyEnumWindowsProc,(LPARAM) 0);
                for (list<ProcessInfo>::iterator ci = plist.begin(); ci != plist.end(); ++ci) {
                        HMODULE hMods[1024];
                        DWORD cbNeeded;
                        unsigned int i;
                        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, (*ci).pid);
                        if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
                                for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ ) {
                                        TCHAR szModName[MAX_PATH];
                                        if ( GetModuleFileNameExA( hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
                                                AnsiString str = AnsiString(szModName);
                                                if(getExeFromFullPath(str) == getExeFromFullPath(Application->ExeName)) {
                                                        SendMessage((*ci).hWindow,WM_KEYDOWN,VK_F13, NULL);
                                                        SendMessage((*ci).hWindow,WM_KEYUP,VK_F13, NULL);
                                                        SetForegroundWindow((*ci).hWindow);
                                                        return 0;
                                                }
                                        }
                                }
                        }
                }
        }
        plist.clear();
        return 0;
}
//---------------------------------------------------------------------------
