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
                Server* getServerByID(int serverID);
                bool addServer(String address);
                bool addServer(String address, String domainName, bool isDomainName);
                bool addServer(ServerConfigEntry entry);
                bool addServer(ServerConfigEntry entry, String domainName);
                bool removeServer(String address);
                Server* findPlayerOnServer(String playerName, bool exactMatch);
                bool incomingMessage(Message *msg);
                void createQueryRequests(std::list<QueryRequest*> &list, BandwidthUsage bU);
                int getServerCount();
                void readSettings(TStringList *file);
                void removeOfflineServers();
                void getSettingsFileEntry(TStringList *settings);
                String getIPFromDomainName(String domainName);

        private:
                TStringList *list;
                int serverIDCounter;
                Address checkAddressValid(String address);
};








//---------------------------------------------------------------------------
#endif
