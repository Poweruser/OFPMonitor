//---------------------------------------------------------------------------

#ifndef PlayerH
#define PlayerH

#include <vcl.h>

/**
   Object which holds all data of one player on a server
 */

class Player {
        public:
                String name;
                String team;
                int deaths;
                int score;
                Player();
                Player(String name, int score, int deaths, String team);
                String getName();
                int getScore();
                int getDeaths();
                String getTeam();
                void clear();
};
//---------------------------------------------------------------------------
#endif
