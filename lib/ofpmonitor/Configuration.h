//---------------------------------------------------------------------------

#ifndef ConfigurationH
#define ConfigurationH

#include <vcl.h>
#include "OFPMonitorDefinitions.h"

class Configuration {
        public:
                Configuration(OFPGames gameid, String label, String mods, String password, String parameters);
                Configuration(OFPGames gameid, String label, TStringList *mods, String password, String parameters, bool nosplash, bool nomap);
                Configuration(OFPGames gameid, String label, TStringList *mods, String password, String parameters, bool nosplash, bool nomap, bool window);
                ~Configuration();
                String createModLine();
                String createStartLine(String ip, int port, String player, bool passwordRequired, String enteredPassword);
                String createStartLineLocal(bool multiplayer, String player);
                String createParameterLine(bool forceNoHost, bool forceNoConnect, bool forceNoPort, bool forceNoServer, bool forceNoNoSplash, bool forceNoNoMap);
                Configuration* clone();
                String createListEntry();
                void setLabel(String label);
                void setPassword(String password);
                void setAddParameters(String parameters);
                void setNoSplash(bool on);
                void setNoMap(bool on);
                void setWindow(bool on);
                String getLabel();
                String getPassword();
                bool isNoSplashSet();
                bool isNoMapSet();
                bool isWindowSet();
                OFPGames getGameId();
                TStringList* getMods();
                void setMods(TStringList *newmods);
                void getSettingsFileEntry(TStringList *settings);



        private:
                String label;
                TStringList *mods;
                String password;
                TStringList *addParameters;
                OFPGames gameid;
                bool nosplash;
                bool nomap;
                bool window;
};





//---------------------------------------------------------------------------
#endif
