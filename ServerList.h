//---------------------------------------------------------------------------

#ifndef ServerListH
#define ServerListH

#include "Message.h"
#include "Server.h"
#include "QueryRequest.h"
#include "Address.h"
#include <list.h>
#include <vcl.h>

class ServerList {
        public:
                ServerList();
                ~ServerList();
                bool hasServer(String address);
                Server* getServer(String address);
                Server* getServer(int index);
                bool addServer(String address);
                bool addServer(ServerConfigEntry entry);
                bool removeServer(String address);
                Server* findPlayerOnServer(String playerName, bool exactMatch);
                bool incomingMessage(Message *msg);
                void createQueryRequests(std::list<QueryRequest*> &list, BandwidthUsage bU);
                int getServerCount();
                void readSettings(TStringList *file);
                void removeOfflineServers();
                void getSettingsFileEntry(TStringList *settings);

        private:
                TStringList *list;
                int indexCounter;
                Address checkAddressValid(String address);
};








//---------------------------------------------------------------------------
#endif
