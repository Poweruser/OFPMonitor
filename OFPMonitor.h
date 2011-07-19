#ifndef OFPMonitorUnitH
#define OFPMonitorUnitH


namespace OFPMonitor_Unit1 {

	#define SERVERARRAY_LENGTH 256
	const unsigned int queryArrayLength = 10;
}


namespace OFPMonitor_Unit2 {

	#define GAMEID_OFPCWC 0
	#define GAMEID_OFPRES 1
	#define GAMEID_ARMACWA 2
	#define GAMES_TOTAL 3
	const int confAmount = 50;
}

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

