//---------------------------------------------------------------------------

#ifndef SorterH
#define SorterH

/**
   This object keeps track of how the Server table is currently sorted
 */

class ServerSorter {
        public:
                bool normal;
                bool id;
                bool name;
                bool players;
                bool status;
                bool island;
                bool mission;
                bool ping;

                /**
                   Constructor
                 */

                ServerSorter::ServerSorter();

                /**
                   resets the attributes to default
                 */

                void ServerSorter::reset();

                /**
                   Sets all attributes false
                   'false' means that the table is not sorted after this column
                   'true' means that it is sorted after this column
                 */

                void ServerSorter::disableAll();

                /**
                   The table will be sorted after IDs
                 */

                void ServerSorter::setId();

                /**
                   The table will be sorted alphabetically after Server names
                 */

                void ServerSorter::setName();

                /**
                   The table will be sorted after the number of players
                 */

                void ServerSorter::setPlayers();

                /**
                   The table will be sorted alphabetically after the server status
                 */

                void ServerSorter::setStatus();

                /**
                   The table will be sorted alphabetically after island names
                 */

                void ServerSorter::setIsland();

                /**
                   The table will be sorted alphabetically after mission names
                 */

                void ServerSorter::setMission();

                /**
                   The table will be sorted after pings
                 */

                void ServerSorter::setPing();
};

/**
   This object keeps track of how the Player table is currently sorted
 */

class PlayerSorter {
        public:
                bool normal;
                bool name;
                bool score;
                bool deaths;
                bool team;

                PlayerSorter::PlayerSorter();

                /**
                   Sets all attributes false
                   'false' means that the table is not sorted after this column
                   'true' means that it is sorted after this column
                 */

                void PlayerSorter::disableAll();

                /**
                   The table will be sorted alphabetically after Player names
                 */

                void PlayerSorter::setName();

                /**
                   The table will be sorted after scores
                 */

                void PlayerSorter::setScore();

                /**
                   The table will be sorted after deaths
                 */

                void PlayerSorter::setDeaths();

                /**
                   The table will be sorted alphabetically after Team names
                 */

                void PlayerSorter::setTeam();
};
//---------------------------------------------------------------------------
#endif
