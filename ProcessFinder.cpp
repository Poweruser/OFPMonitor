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

ProcessInfo::ProcessInfo() {
        this->clear();
}

void ProcessInfo::clear() {
        this->pid = 0;
        this->hWindow = 0;
        this->title = "";
        this->moduleName = "";
}

bool ProcessInfo::equals(ProcessInfo p) {
        return (this->pid == p.pid &&
                this->hWindow == p.hWindow &&
                this->title == p.title &&
                this->moduleName == p.moduleName);
};

bool ProcessInfo::equals(ProcessInfo *p) {
        return (this->pid == p->pid &&
                this->hWindow == p->hWindow &&
                this->title == p->title &&
                this->moduleName == p->moduleName);
};

bool CALLBACK MyEnumWindowsProc(HWND hWnd, LPARAM lParam) {
        DWORD PID = 0;
        ProcessFinder *pf = (ProcessFinder*) lParam;
        GetWindowThreadProcessId(hWnd, &PID);
        for(int i = 0; i < pf->titleStartsWith->Count; i++) {
                int len = pf->titleStartsWith->Strings[i].Length() + 1;
                if(len > 2047) { len = 2048; }
                char *title = new char[len];
                GetWindowText(hWnd, title, len);
                AnsiString t = AnsiString(title);
                delete[] title;
                if(t.AnsiPos(pf->titleStartsWith->Strings[i]) == 1) {
                        pf->matchingProcesses.push_back(ProcessInfo(PID, hWnd, t, ""));
                }
        }
        return true;
}

ProcessFinder::ProcessFinder() { }
ProcessFinder::~ProcessFinder() {
        this->output.clear();
        this->matchingProcesses.clear();
}

bool ProcessFinder::enumerate(TStringList *titleStartsWith, TStringList *moduleIncludes) {
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
                                        for(int j = 0; j < moduleIncludes->Count; j++) {
                                                if(str.LowerCase().AnsiPos(moduleIncludes->Strings[j].LowerCase()) > 0) {
                                                        (*ci).moduleName = str;
                                                        this->output.push_back(*ci);
                                                        break;
                                                }
                                        }
                                }
                        }
                }
                CloseHandle(hProcess);
        }
        return (this->output.size() > 0);
}




