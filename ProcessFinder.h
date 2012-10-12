//---------------------------------------------------------------------------

#ifndef ProcessFinderH
#define ProcessFinderH
#include <windows.h>
#include <vcl.h>
#include <list.h>

class ProcessInfo {
        public:
                DWORD pid;
                HWND hWindow;
                String title;
                String moduleName;

                ProcessInfo(DWORD pid, HWND hWindow, String title, String moduleName);
                ProcessInfo();
                bool equals(ProcessInfo p);
                bool equals(ProcessInfo *p);
                void clear();
};

class ProcessFinder {
        public:
        	TStringList *titleStartsWith;
        	list<ProcessInfo> output;
        	ProcessFinder();
        	~ProcessFinder();
        	list<ProcessInfo> matchingProcesses;
        	bool ProcessFinder::enumerate(TStringList *titleStartsWith, TStringList *moduleIncludes);

};


//---------------------------------------------------------------------------
#endif
