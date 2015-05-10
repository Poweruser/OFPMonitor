//---------------------------------------------------------------------------

#ifndef PlayerTableSorterH
#define PlayerTableSorterH

#include <vcl.h>

/**
   This object keeps track of how the server table is currently sorted
 */

enum PlayerTableColumn { PTC_NAME, PTC_SCORE, PTC_DEATHS, PTC_TEAM };

class PlayerTableSorter {
        public:
                PlayerTableSorter();
                void reset();
                void setName();
                void setScore();
                void setDeaths();
                void setTeam();
                bool isNameSet();
                bool isScoreSet();
                bool isDeathsSet();
                bool isTeamSet();
                bool isNormalOrder();

        private:
                PlayerTableColumn currentColumn;
                bool normalOrder;

                void setProperty(PlayerTableColumn ptc);
};

//---------------------------------------------------------------------------
#endif
