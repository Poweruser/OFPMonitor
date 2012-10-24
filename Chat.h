//---------------------------------------------------------------------------

#ifndef ChatH
#define ChatH

#include <vcl.h>
#include "Observer.h"
#include "IRCClient.h"
#include "ChatSettings.h"
#include "ChatLog.h"
#include <Grids.hpp>
#include <ComCtrls.hpp>

class Chat : public Observable, Observer {
        private:
                TStringList *activeChats;
                TStringList *blockedChatUsers;
                IRCClient *ircClient;
                ChatSettings *chatSettings;

                ChatLog* getChatLog(String conversation);

        public:
                Chat(ChatSettings *chatSettings);
                ~Chat();
                void openConversation(String conversation);
                void closeConversation(String conversation);
                void toggleBlockedClient(String client);
                bool isClientBlocked(String client);
                TStringList* getBlockedClients();
                bool hasConversation(String conversation);
                bool hasConversationNewMessages(String conversation);
                void syncChat(String conversation, TMemo *outputMemo);
                void loadThisChat(String conversation, TMemo *outputMemo, TMemo *inputMemo);
                void saveCurrentInput(String conversation, TMemo *inputMemo);
                void incomingMsg(String conversation, String msg, bool control);
                void userSendsMessage(String conversation, String msg);
                void update(Observable *o);
                void writeUserList(TStringGrid *grid);
                void writeConversations(TTabControl *tab);
                String currentTimeString(bool full);
                String generateUsername(String userName, bool wasConnectionLost);
                String getUserNameInUse();

                void connect(String userNameOverWrite);
                void disconnect();
                void reconnect();
                bool isConnected();
                bool isConnectionLost();
                bool isDisconnected();
                bool isConnectingFailed();


};

//---------------------------------------------------------------------------
#endif
