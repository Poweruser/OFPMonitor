#ifndef OFPMonitorUnitH
#define OFPMonitorUnitH

#include <vcl.h>
#include <list.h>
#include <Registry.hpp>

#define GAMEID_OFPCWC 0
#define GAMEID_OFPRES 1
#define GAMEID_ARMACWA 2
#define GAMES_TOTAL 3

#define DEFAULT_IRCSERVER_HOST "irc.freenode.net"
#define DEFAULT_IRCSERVER_PORT 6666
#define DEFAULT_IRCSERVER_CHANNEL "#operationflashpoint1"

list<String> getExesByGameId(int gameid) {
        list<String> exes;
        if(gameid == GAMEID_OFPCWC) {
                exes.push_back("OperationFlashpoint.exe");
                exes.push_back("OperationFlashpointbeta.exe");
        } else if(gameid == GAMEID_OFPRES) {
                exes.push_back("FLASHPOINTRESISTANCE.EXE");
                exes.push_back("OFP.exe");
                exes.push_back("FLASHPOINTBETA.EXE");
        } else if(gameid == GAMEID_ARMACWA) {
                exes.push_back("ColdWarAssault.exe");
        }
        return exes;
}

String getAppTitleByGameId(int gameid) {
        String out = "";
        if(gameid == GAMEID_OFPCWC || gameid == GAMEID_OFPRES) {
                out = "Operation Flashpoint";
        } else if(gameid == GAMEID_ARMACWA) {
                out = "Cold War Assault";
        }
        return out;
}

String getFullGameNameByGameId(int gameid) {
        String out = "";
        if(gameid == GAMEID_OFPCWC) {
                out = "Operation Flashpoint: Cold War Crisis";
        } else if(gameid == GAMEID_OFPRES) {
                out = "Operation Flashpoint: Resistance";
        } else if(gameid == GAMEID_ARMACWA) {
                out = "ArmA: Cold War Assault";
        }
        return out;
}

namespace OFPMonitor_Unit1 {

	#define SERVERARRAY_LENGTH 256
	const unsigned int queryArrayLength = 10;
}


namespace OFPMonitor_Unit2 {


	const int confAmount = 50;

        /**
                Reads a String from the OS registry. 'a' holds a list of keys to visit in order,
                'key' is the object which content is to read inside the last key
        */

        String GetRegistryValue(void * root, list<String> a, String key) {
                String S = "";
                TRegistry *Registry = new TRegistry(KEY_READ);
                try {
                        Registry->RootKey = root;
                        while (a.size() > 0) {
                                Registry->OpenKey(a.front(),false);
                                a.pop_front();
                        }
                        S = Registry->ReadString(key);
                }
                __finally {
                        delete Registry;
                }
                return S;
        }

        list<String> getRegistryPathByGameId(int gameid) {
                list<String> regFolder;
                if(gameid == GAMEID_OFPCWC || gameid == GAMEID_OFPRES) {
                        regFolder.push_back("SOFTWARE");
                        regFolder.push_back("Codemasters");
                        regFolder.push_back("Operation Flashpoint");
                } else if(gameid == GAMEID_ARMACWA) {
                        regFolder.push_back("SOFTWARE");
                        regFolder.push_back("Bohemia Interactive Studio");
                        regFolder.push_back("ColdWarAssault");
                }
                return regFolder;
        }

        String getGamePathFromRegistryByGameId(int gameid) {
                return GetRegistryValue(HKEY_LOCAL_MACHINE, getRegistryPathByGameId(gameid), "Main");
        }

        list<String> getExePathsByGameId(int gameid) {
                String path = getGamePathFromRegistryByGameId(gameid);
                list<String> exes = getExesByGameId(gameid);
                list<String> out;
                for(list<String>::iterator ci = exes.begin(); ci != exes.end(); ++ci) {
                        out.push_back(path + "\\" + (*ci));
                }
                return out;
        }

        String getGameSpyTokenByGameId(int gameid) {
                String out = "";
                if(gameid == GAMEID_OFPCWC) {
                        out = "opflash";
                } else if(gameid == GAMEID_OFPRES || gameid == GAMEID_ARMACWA) {
                        out = "opflashr";
                }
                return out;
        }


}

void releaseMutex();

enum BandwidthUsage {High, Moderate, Low, VeryLow};

#define SERVERSTATE_CREATING 2	
#define SERVERSTATE_WAITING 6
#define SERVERSTATE_DEBRIEFING 9
#define SERVERSTATE_SETTINGUP 12
#define SERVERSTATE_BRIEFING 13
#define SERVERSTATE_PLAYING 14

template<typename T, int size>
int GetArrLength(T(&)[size]){return size;}

#endif

