//---------------------------------------------------------------------------

#ifndef ServerTableSorterH
#define ServerTableSorterH

#include <vcl.h>

/**
   This object keeps track of how the server table is currently sorted
 */

enum ServerTableColumn { STC_ID=0, STC_NAME=1, STC_PLAYERS=2, STC_STATE=3, STC_ISLAND=4, STC_MISSION=5, STC_PING=6 };

class ServerTableSorter {
        public:
                ServerTableSorter();
                void reset();
                void setId();
                void setName();
                void setPlayers();
                void setStatus();
                void setIsland();
                void setMission();
                void setPing();
                bool isIdSet();
                bool isNameSet();
                bool isPlayersSet();
                bool isStatusSet();
                bool isIslandSet();
                bool isMissionSet();
                bool isPingSet();
                bool isNormalOrder();

        private:
                ServerTableColumn currentColumn;
                bool normalOrder;
                void setProperty(ServerTableColumn stc);
};

//---------------------------------------------------------------------------
#endif
