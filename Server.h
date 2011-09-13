//---------------------------------------------------------------------------

#ifndef ServerH
#define ServerH

#include <vcl.h>
#include <list.h>
#include "QueryAnswer.h"
#include "Player.h"
#include "OFPMonitor.h"

using namespace OFPMonitor_Unit1;

class ServerItem {
        public:
        	String address;
        	bool watch;
        	bool favorite;
        	bool persistent;
        	bool blocked;

                ServerItem();
        	ServerItem(String address);
};

/**
   Representation of one server

 */

class Server {
        public:
                int index;
                int gamespyport;
                int gameport;
                int ping;
                DWORD messageSent;
                int timeouts;
                String ip;
                String timeleft;
                long gametime;
                int players;
                int maxplayers;
                String mission;
                String name;
                int gamestate;
                String island;
                String platform;
                String param1;
                String param2;
                String mod;
                int queryid;
                String impl;
                int password;
                int actver;
                int reqver;
                int equalMod;
                bool favorite;
                bool watch;
                bool persistent;
                bool blocked;
                bool autojoin;
                String autojoinConf;
                list<Player> playerlist;
                QueryAnswer queries[queryArrayLength];
                int notificationRuleIndex;
                int missedQueryTurns;
                int emptyServerCounter;


                /**
                   Default Constructor of a blank server
                 */

                Server();

                /**
                   Constructor

                   @i  the server's ip
                   @p  the server's gamespy port
                   @ind  the server's index in the ServerArray
                 */

                Server(String i, int p, int ind);

                /**
                   Clears all attributes, used to make servers invalid.
                   e.g. when they go offline
                 */

                void clear();

                String getAddress();
                String getGamespyAddress();

                ServerItem* createServerItem();
};

//---------------------------------------------------------------------------
#endif
