//---------------------------------------------------------------------------

#ifndef ServerFilterH
#define ServerFilterH

#include <vcl.h>

class ServerFilter {
        public:
                ServerFilter();
                ServerFilter(TStringList *missions, TStringList *servers, TStringList *players);
                ~ServerFilter();
                bool guiNeedsUpdate();
                void setMissionName(String mission);
                void setPlayerName(String player);
                void setServerName(String server);
                String getMissionName();
                String getPlayerName();
                String getServerName();
                int minPlayers;
                int maxPlayers;
                bool creating;
                bool waiting;
                bool settingup;
                bool briefing;
                bool playing;
                bool debriefing;
                bool withPassword;
                bool withoutPassword;
                TStringList *missionNames;
                TStringList *serverNames;
                TStringList *playerNames;
                void readSettings(TStringList *file);
                bool testMissionName(String mission);
                bool testServerName(String mission);
                void setMinPlayers(int num);
                void setMaxPlayers(int num);
                int getBinaryStatusFilter();
                void parseBinaryStatusFilter(int filter);
                String concatenateFilter(TStringList *list, String splitter);
                void getSettingsFileEntry(TStringList *settings);

        private:

                bool guiUpdate;


};

enum ServerFilterResult { SFR_OFFLINE=0, SFR_NOTPASSED=1, SFR_NOTPASSED_AUTOJOIN=2, SFR_NOTPASSED_FAVORITE=3, SFR_PASSED=4, SFR_PASSED_AUTOJOIN=5, SFR_PASSED_FAVORITE=6};

//---------------------------------------------------------------------------
#endif
