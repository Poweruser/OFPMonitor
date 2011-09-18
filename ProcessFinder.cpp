//---------------------------------------------------------------------------


#pragma hdrstop


#include "ProcessFinder.h"
#include <Psapi.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

ProcessInfo::ProcessInfo(DWORD pid, HWND hWindow, String title, String moduleName) {
        this->pid = pid;
        this->hWindow = hWindow;
        this->title = title;
        this->moduleName = moduleName;
}

ProcessInfo::ProcessInfo() { }

bool CALLBACK MyEnumWindowsProc(HWND hWnd, LPARAM lParam) {
        DWORD PID = 0;
        ProcessFinder *pf = (ProcessFinder*) lParam;
        GetWindowThreadProcessId(hWnd, &PID);
        int len = pf->titleStartsWith.Length() + 1;
        if(len > 2047) { len = 2048; }
        char *title = new char[len];
        GetWindowText(hWnd, title, len);
        AnsiString t = AnsiString(title);
        delete[] title;
        if(t.AnsiPos(pf->titleStartsWith) == 1) {
                pf->matchingProcesses.push_back(ProcessInfo(PID, hWnd, t, ""));
        }
        return true;
}

ProcessFinder::ProcessFinder() { }
bool ProcessFinder::enumerate(String titleStartsWith, String moduleIncludes) {
        this->output.clear();
        this->matchingProcesses.clear();
        this->titleStartsWith = titleStartsWith;
        EnumWindows((WNDENUMPROC) MyEnumWindowsProc, (LPARAM) this);
        for (list<ProcessInfo>::iterator ci = this->matchingProcesses.begin(); ci != this->matchingProcesses.end(); ++ci) {
                HMODULE hMods[1024];
                DWORD cbNeeded;
                unsigned int i;
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, (*ci).pid);
                if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded) ) {
                        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
                                TCHAR szModName[MAX_PATH];
                                if( GetModuleFileNameExA(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)) ) {
                                        AnsiString str = AnsiString(szModName);
                                        if(str.AnsiPos(moduleIncludes) > 0) {
                                                (*ci).moduleName = str;
                                                this->output.push_back(*ci);
                                                break;
                                        }
                                }
                        }
                }
        }
        return (this->output.size() > 0);
}




