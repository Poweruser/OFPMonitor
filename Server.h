//---------------------------------------------------------------------------

#ifndef ServerH
#define ServerH

#include <vcl.h>
#include <list.h>
#include "QueryAnswer.h"
#include "Player.h"
#include "Message.h"
#include "OFPMonitorDefinitions.h"
#include "ServerFilter.h"
#include "StatusChange.h"

#define NULL_SERVERID -1

class ServerConfigEntry {
        public:
        	String address;
                int gamestate;
                long gametime;
        	bool watch;
        	bool favorite;
        	bool persistent;
        	bool blocked;
                bool autojoin;
                String autojoinConf;

                ServerConfigEntry();
        	ServerConfigEntry(String address);
};

/**
   Representation of one server

 */

class Server : public TObject {
        public:
                __fastcall Server(int serverID, String ip, int port);
                __fastcall Server(int serverID, String ip, int port, ServerConfigEntry entry);
                __fastcall ~Server();
                
                /**
                   Clears all attributes, used to make servers invalid.
                   e.g. when they go offline
                 */

                void clear();
                bool equals(Server *srv);
                bool equals(String serverAddress);
                String getIP();
                int getGamePort();
                String getAddress();
                int getGamespyPort();
                String getGamespyAddress();
                int getCurrentGameState();
                int getActualVersion();
                int getRequiredVersion();

                ServerConfigEntry* createServerConfigEntry();
                ServerFilterResult checkFilter(ServerFilter *filter);
                bool isPlayerOnServer(String playerName, bool exactMatch);
                bool processUpdate(Message *msg);
                String decideQuery(BandwidthUsage bu);
                void queryIsAboutToBeSent(String query, bool sendingSuccess, int timeOutLimit);
                int compareQueryId(String queryid);
                bool parseMessageToQueryAnswer(Message *msg);
                bool hasStatusChanged();
                StatusChange* takeStatusChange();
                bool isOnline();
                String getIsland();
                String getMission();
                int getPing();
                String getName();
                int getServerID();
                int getGameState();
                int getPlayerNum();
                int getPlayerNumOfPlayerList();
                int getMaxPlayerNum();
                String getPlatform();
                bool hasTimedOut();
                Player* getPlayer(int index);
                bool hasPassword();
                bool requiresEqualMod();
                bool isFavorite();
                bool isAutoJoin();
                bool isPersistent();
                bool isBlocked();
                void setFavorite(bool active);
                void setPersistent(bool active);
                void setBlocked(bool active);
                void setAutoJoin(bool active, String startUpLine);
                bool isWatched();
                void setWatched(bool active);
                bool isStatePlaying();
                String getMod();
                bool hasMods();
                bool doesModMatch(String mod);
                long getStatusTime();
                String createSettingsFileEntry();
                void setSelectedToDisplay(bool active);
                String getAutoJoinConf();

        private:
                int password;
                int actver;
                int reqver;
                int equalMod;
                bool favorite;
                bool watch;
                bool persistent;
                bool blocked;
                bool autojoin;
                bool selectedToDisplay;
                list<StatusChange*> statusChanges;
                bool areQueriesComplete();
                void parseQueryAnswers();
                String autojoinConf;
                String island;
                String platform;
                String param1;
                String param2;
                String mod;
                String queryid;
                String impl;
                Player *playerArray[30];
                QueryAnswer queries[5];
                int missedQueryTurns;
                int emptyServerCounter;
                int serverID;
                int gamespyport;
                int gameport;
                int ping;
                DWORD messageSent;
                int timeouts;
                String ip;
                String timeleft;
                long gametime;
                int players;
                int playersInArray;
                int maxplayers;
                String mission;
                String name;
                int gamestate;
                bool online;
                bool dontTrustNumPlayers;

                TStringList* playerArrayToStringList();
};

//---------------------------------------------------------------------------
#endif
