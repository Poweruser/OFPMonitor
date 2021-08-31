#ifndef OFPMonitorDefinitionsH
#define OFPMonitorDefinitionsH

#include <vcl.h>
#include <list.h>
#include <Registry.hpp>

#define SERVERSTATE_UNDEFINED 0
#define SERVERSTATE_CREATING 2
#define SERVERSTATE_EDITING 4
#define SERVERSTATE_WAITING 6
#define SERVERSTATE_DEBRIEFING 9
#define SERVERSTATE_SETTINGUP 12
#define SERVERSTATE_BRIEFING 13
#define SERVERSTATE_PLAYING 14

#define POWERSERVER_QUERYPORT 28900

enum OFPGames {ARMARES=0, OFPRES=1, ARMACWA=2, GAMESTOTAL=3, UNKNOWNGAME=4 };


String getGameName(OFPGames gameid) {
	String out = "UNKNOWNGAME";
	switch(gameid) {        
		case ARMARES:
			out = "ARMA:RES";
			break;
		case OFPRES:
			out = "OFP:RES";
			break;
		case ARMACWA:
			out = "ARMA:CWA";
	}
	return out;
}

OFPGames getGameId(String name) {
        if(name == "ARMA:RES") { return ARMARES; }
        if(name == "OFP:RES") { return OFPRES; }
        if(name == "ARMA:CWA") { return ARMACWA; }
        return UNKNOWNGAME;
}

bool isValidGameID(OFPGames gameid) {
        return (gameid >= 0 && gameid < GAMESTOTAL);
}


list<String> getExesByGameId(OFPGames gameid, bool includeFWatch) {
        list<String> exes;
	switch(gameid) {
		case ARMARES:
                	exes.push_back("ArmAResistance.exe");
			break;
		case OFPRES:
                        if(includeFWatch) {
                                exes.push_back("fwatch.exe");
                        }
			exes.push_back("FLASHPOINTRESISTANCE.EXE");
                	exes.push_back("OFP.exe");
                	exes.push_back("FLASHPOINTBETA.EXE");
			break;
		case ARMACWA:
                        if(includeFWatch) {
                                exes.push_back("fwatchCWA.exe");
                        }
                	exes.push_back("ColdWarAssault.exe");
	}
	return exes;
}

bool isFileFWatch(String fileName) {
        String lowercase = fileName.LowerCase();
        return (lowercase == "fwatch.exe" || lowercase == "fwatchcwa.exe");
}

String getAppTitleByGameId(OFPGames gameid) {
        String out = "";
	switch(gameid) {
		case ARMARES:
		// out is case sensitivitive.
			out = "ArmA Resistance";
			break;
		case OFPRES:
			out = "Operation Flashpoint";
			break;
		case ARMACWA:
	       		out = "Cold War Assault";
	}
	return out;
}


String getFullGameNameByGameId(OFPGames gameid) {
        String out = "";
	switch(gameid) {
		case ARMARES:
			out = "Arma: Resistance";
			break;
		case OFPRES:
			out = "Operation Flashpoint: Resistance";
			break;
		case ARMACWA:
			out = "ArmA: Cold War Assault";
	}
	return out;
}

list<String> getRegistryPathByGameId(OFPGames gameid) {
	list<String> regFolder;
	switch(gameid) {
		case ARMARES:
		case OFPRES:
			regFolder.push_back("SOFTWARE");
			regFolder.push_back("Codemasters");
			regFolder.push_back("Operation Flashpoint");
			break;
		case ARMACWA:
			regFolder.push_back("SOFTWARE");
			regFolder.push_back("Bohemia Interactive Studio");
			regFolder.push_back("ColdWarAssault");
	}
	return regFolder;
}


String GetRegistryValue(void *root, list<String> a, String key) {
	String str = "";
	TRegistry *Registry = new TRegistry(KEY_READ);
	try {
		Registry->RootKey = root;
		while (a.size() > 0) {
			Registry->OpenKey(a.front(),false);
			a.pop_front();
		}
		str = Registry->ReadString(key);
	}
	__finally {
		delete Registry;
        }
	return str;
}

String getGamePathFromRegistryByGameId(OFPGames gameid) {
	return GetRegistryValue(HKEY_LOCAL_MACHINE, getRegistryPathByGameId(gameid), "Main");
}

list<String> getStreamRegistryPath() {
        list<String> out;
        out.push_back("SOFTWARE");
        out.push_back("Valve");
        out.push_back("Steam");
        return out;
}

String getGamePathOfSteamVersion() {
        String steamInstallPath = GetRegistryValue(HKEY_LOCAL_MACHINE, getStreamRegistryPath(), "InstallPath");
        if(!steamInstallPath.IsEmpty()) {
                if(steamInstallPath.SubString(steamInstallPath.Length(), 1) != "\\") {
                        steamInstallPath += "\\";
                }
                steamInstallPath += "SteamApps\\common\\ARMA Cold War Assault";
        }
        return steamInstallPath;
}

list<String> getExePathsByGameId(OFPGames gameid, bool includeFWatch) {
	String path = getGamePathFromRegistryByGameId(gameid);
	list<String> exes = getExesByGameId(gameid, includeFWatch);
	list<String> out;
	for(list<String>::iterator ci = exes.begin(); ci != exes.end(); ++ci) {
		out.push_back(path + "\\" + (*ci));
	}
        if(gameid == ARMACWA) {
                String steampath = getGamePathOfSteamVersion();
                if(!steampath.IsEmpty()) {
                        for(list<String>::iterator ci = exes.begin(); ci != exes.end(); ++ci) {
                                out.push_back(steampath + "\\" + (*ci));
	                }
                }
        }
	return out;
}

String getGameSpyTokenByGameId(OFPGames gameid) {
	String out = "";
	switch(gameid) {
		case ARMARES:
			out = "opflash";
			break;
		case OFPRES:
		case ARMACWA:
			out = "opflashr";
	}
	return out;
}

String getGameSpyKeyByGameId(OFPGames gameid) {
	String out = "";
	switch(gameid) {
		default:
		case ARMARES:
			break;
		case OFPRES:
		case ARMACWA:
			out = "Y3k7x1";
	}
	return out;
}

enum BandwidthUsage {High=0, Moderate=1, Low=2, VeryLow=3 };

template<typename T, int size>
int GetArrLength(T(&)[size]){return size;}

#endif

