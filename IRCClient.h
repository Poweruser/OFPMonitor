//---------------------------------------------------------------------------

#ifndef IRCClientH
#define IRCClientH

#include <vcl.h>
#include "Observer.h"
#include "ChatMessage.h"

enum ConnectionStatus { STATUS_NOTCONNECTED, STATUS_CONNECTING, STATUS_CONNECTINGFAILED, STATUS_CONNECTED, STATUS_CONNECTIONLOST, STATUS_DISCONNECTED};

class IRCClient : public Observable {
        private:
                TList *messageList;
                TStringList *userList;
                TStringList *joinedUsers;
                TStringList *partedUsers;
                String remoteServer;
                String host;
                int port;
                String channel;
                ConnectionStatus status;
                bool controlledShutdown;
                bool updatePlayers;
                int timeouts;
                String userName;
                String ircUserName;
                int tcpSocket;
                
                void userJoined(String userName, bool isNew);
                void userLeft(String userName);
                void startConversation();
                int sendString(String msg);
                String convertName_IrcToLocal(String name);
                String convertName_LocalToIrc(String name);
                String extractUserNameFromLine(String line);
                void parseReceivedData(String data);
                unsigned long resolv(String host);

        public:
                IRCClient(String host, int port, String channel, String userName);
                ~IRCClient();
                String getChannel();
                String getUserNameInUse();
                TStringList* getUserList();
                bool hasJoinedUsers();
                bool hasPartedUsers();
                bool hasMessages();
                String takeJoinedUser();
                String takePartedUser();
                ChatMessage* takeMessage();
                ConnectionStatus getConnectionStatus();
                void sendMessage(String receiver, String msg);
                void userSendsMessage(String receiver, String msg);
                bool isConnected();
                bool isConnectionLost();
                bool isDisconnected();
                bool isConnectingFailed();
                void connectAndListen();
                void disconnect();
};



//---------------------------------------------------------------------------
#endif
