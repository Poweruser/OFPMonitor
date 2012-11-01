//---------------------------------------------------------------------------

#ifndef ChatH
#define ChatH

#include <vcl.h>
#include "Observer.h"
#include "IRCClient.h"
#include "ChatSettings.h"
#include "ChatLog.h"
#include "LanguageDB.h"
#include <Grids.hpp>
#include <ComCtrls.hpp>

class Chat : public Observable, public Observer {
        private:
                TStringList *activeChats;
                TStringList *blockedChatUsers;
                IRCClient *ircClient;
                ChatSettings *chatSettings;
                LanguageDB *languageDB;

                ChatLog* getChatLog(String conversation);
                void closeAllConversations();

        public:
                Chat(ChatSettings *chatSettings, LanguageDB *languageDB);
                ~Chat();
                void openConversation(String conversation);
                void closeConversation(String conversation);
                void toggleBlockedClient(String client);
                bool isClientBlocked(String client);
                TStringList* getBlockedClients();
                bool hasConversation(String conversation);
                bool hasConversationNewMessages(String conversation);
                bool hasNewMessages();
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

                void connect(String userNameOverWrite, bool wasConnectionLost);
                void disconnect();
                void reconnect();
                bool isConnected();
                bool isConnectionLost();
                bool isDisconnected();
                bool isConnectingFailed();


};

//---------------------------------------------------------------------------
#endif
