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
};

class ProcessFinder {
        public:
        String titleStartsWith;
        list<ProcessInfo> output;
        ProcessFinder();
        list<ProcessInfo> matchingProcesses;
        bool ProcessFinder::enumerate(String titleStartsWith, String moduleIncludes);
        private:

};


//---------------------------------------------------------------------------
#endif
