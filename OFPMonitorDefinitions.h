#ifndef OFPMonitorDefinitionsH
#define OFPMonitorDefinitionsH

#include <vcl.h>
#include <list.h>
#include <Registry.hpp>

#define SERVERSTATE_CREATING 2	
#define SERVERSTATE_WAITING 6
#define SERVERSTATE_DEBRIEFING 9
#define SERVERSTATE_SETTINGUP 12
#define SERVERSTATE_BRIEFING 13
#define SERVERSTATE_PLAYING 14

#define POWERSERVER_QUERYPORT 28900

enum OFPGames {OFPCWC=0, OFPRES=1, ARMACWA=2, GAMESTOTAL=3, UNKNOWNGAME=4 };


String getGameName(OFPGames gameid) {
	String out = "UNKNOWNGAME";
	switch(gameid) {        
		case OFPCWC:
			out = "OFP:CWC";
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
        if(name == "OFP:CWC") { return OFPCWC; }
        if(name == "OFP:RES") { return OFPRES; }
        if(name == "ARMA:CWA") { return ARMACWA; }
        return UNKNOWNGAME;
}

bool isValidGameID(OFPGames gameid) {
        return (gameid >= 0 && gameid < GAMESTOTAL);
}


list<String> getExesByGameId(OFPGames gameid) {
        list<String> exes;
	switch(gameid) {
		case OFPCWC:
                	exes.push_back("OperationFlashpoint.exe");
                	exes.push_back("OperationFlashpointbeta.exe");
			break;
		case OFPRES:
			exes.push_back("fwatch.exe");
			exes.push_back("FLASHPOINTRESISTANCE.EXE");
                	exes.push_back("OFP.exe");
                	exes.push_back("FLASHPOINTBETA.EXE");
			break;
		case ARMACWA:
			exes.push_back("fwatchCWA.exe");
                	exes.push_back("ColdWarAssault.exe");
	}
	return exes;
}

String getAppTitleByGameId(OFPGames gameid) {
        String out = "";
	switch(gameid) {
		case OFPCWC:
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
		case OFPCWC:
			out = "Operation Flashpoint: Cold War Crisis";
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
		case OFPCWC:
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

list<String> getExePathsByGameId(OFPGames gameid) {
	String path = getGamePathFromRegistryByGameId(gameid);
	list<String> exes = getExesByGameId(gameid);
	list<String> out;
	for(list<String>::iterator ci = exes.begin(); ci != exes.end(); ++ci) {
		out.push_back(path + "\\" + (*ci));
	}
	return out;
}

String getGameSpyTokenByGameId(OFPGames gameid) {
	String out = "";
	switch(gameid) {
		case OFPCWC:
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
		case OFPCWC:
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

