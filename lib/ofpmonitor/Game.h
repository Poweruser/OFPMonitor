//---------------------------------------------------------------------------

#ifndef GameH
#define GameH

#include "OFPMonitorDefinitions.h"
#include "Configuration.h"
#include <vcl.h>
#include <list.h>

class Game {
        public:
                Game(OFPGames id);
                ~Game();
                bool isValid();
                void autodetect(String exe);
                void autodetect(String exe, String player);
                void detectPlayer(String setP);
                void queryVersion();
                bool checkIfCorrectGame(int actVer, int reqVer);
                int getConfigurationsCount();
                void addConfiguration(Configuration *conf);
                void deleteConfiguration(Configuration *conf);
                void setActive(bool active);
                bool isActive();
                void setGameId(OFPGames id);
                OFPGames getGameId();
                String getProfileName();
                void setProfileName(String name);
                Configuration* getConfiguration(int index);
                void exchangeConfs(int index1, int index2);
                String createDefaultStartLine(String ip, int port, String mods, String password);
                String getGameFolder();
                String getGameExe();
                String getGamespyToken();
                String getGamespyKey();
                String getFullName();
                int getFileVersion();
                list<String> findPlayerProfiles();
                void getSettingsFileEntry(TStringList *settings);

        private:
                bool set;
                OFPGames game;
                String exe;
                String folder;
                String player;
                String fullName;
                int version;
                TList *startupConfs;
                String gamespyToken;
                String gamespyKey;

                String getFolder(String path);
};






//---------------------------------------------------------------------------
#endif
