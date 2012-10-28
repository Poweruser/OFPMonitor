//---------------------------------------------------------------------------


#pragma hdrstop

#include "Chat.h"
#include "ChatMessage.h"
#include <time.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

Chat::Chat(ChatSettings *chatSettings, LanguageDB *languageDB) {
        this->languageDB = languageDB;
        this->chatSettings = chatSettings;
        this->activeChats = new TStringList;
        this->activeChats->Sorted = true;
        this->activeChats->Duplicates = dupIgnore;
        this->blockedChatUsers = new TStringList;
        this->blockedChatUsers->Sorted = true;
        this->blockedChatUsers->Duplicates = dupIgnore;
        this->ircClient = NULL;
}

Chat::~Chat() {
        this->disconnect();
        delete (this->activeChats);
        delete (this->blockedChatUsers);
        delete this->ircClient;
}

void Chat::toggleBlockedClient(String client) {
        int index;
        if(this->blockedChatUsers->Find(client, index)) {
                this->blockedChatUsers->Delete(index);
        } else {
                this->blockedChatUsers->Add(client);
        }
}
bool Chat::isClientBlocked(String client) {
        int index;
        return (this->blockedChatUsers->Find(client, index));
}

TStringList* Chat::getBlockedClients() {
        return this->blockedChatUsers;
}

ChatLog* Chat::getChatLog(String conversation) {
        ChatLog *out = NULL;
        int index;
        if(this->activeChats->Find(conversation, index)) {
                out = (ChatLog*) (this->activeChats->Objects[index]);
        }
        return out;
}

bool Chat::hasConversation(String conversation) {
        int index;
        return this->activeChats->Find(conversation, index);
}

bool Chat::hasConversationNewMessages(String conversation) {
        ChatLog *cl = this->getChatLog(conversation);
        if(cl != NULL) {
                return cl->hasNewMessages();
        }
        return false;
}

void Chat::syncChat(String conversation, TMemo *outputMemo) {
        ChatLog *cl = this->getChatLog(conversation);
        if(cl != NULL) {
                cl->syncChat(outputMemo);
        }
}

void Chat::loadThisChat(String conversation, TMemo *outputMemo, TMemo *inputMemo) {
        ChatLog *cl = this->getChatLog(conversation);
        if(cl != NULL) {
                cl->loadThisChat(outputMemo, inputMemo);
        }
}

void Chat::saveCurrentInput(String conversation, TMemo *inputMemo) {
        ChatLog *cl = this->getChatLog(conversation);
        if(cl != NULL) {
                cl->saveCurrentInput(inputMemo);
        }
}

void Chat::incomingMsg(String conversation, String msg, bool control) {
        ChatLog *cl = this->getChatLog(conversation);
        if(cl != NULL) {
                cl->incomingMsg(msg, control);
        } else {
                cl = new ChatLog(conversation);
                this->activeChats->AddObject(conversation, (TObject*) cl);
                cl->incomingMsg(msg, control);
        }
}

void Chat::openConversation(String conversation) {
        if(!this->hasConversation(conversation)) {
                this->incomingMsg(conversation, "", true);
        }
        this->NotifyObserver();
}

void Chat::closeConversation(String conversation) {
        if(conversation != this->chatSettings->getChannel()) {
                int index;
                if(this->activeChats->Find(conversation, index)) {
                        ChatLog *cl = (ChatLog*) (this->activeChats->Objects[index]);
                        this->activeChats->Delete(index);
                        delete cl;
                }
        }
        this->NotifyObserver();
}

String Chat::currentTimeString(bool full) {
        time_t rawTime;
        struct tm *timeInfo;
        char buffer [80];
        time(&rawTime);
        timeInfo = localtime(&rawTime );
        if(full) {
                strftime (buffer, 80, "%c", timeInfo);
        } else {
                strftime (buffer, 80, "%H:%M", timeInfo);
        }
        return String(buffer);
}

String Chat::generateUsername(String userName, bool wasConnectionLost) {
        if(userName.IsEmpty()) {
                return ("Guest" + currentTimeString(false));
        } else if(wasConnectionLost) {
                String oldName = this->ircClient->getUserNameInUse();
                String setName = userName;
                setName = setName.SubString(1, min(oldName.Length(),setName.Length()));
                if(setName < 11) { setName = setName + "_2"; }
                int i = 50;
                while(setName == oldName && i < 58) {
                        setName[setName.Length() - 1] = '_';
                        setName[setName.Length()] = i;
                }
                return setName;
        }
        return userName;
}

void Chat::connect(String userNameOverwrite) {
        String userNameToUse = this->chatSettings->getUserName();
        if(!userNameOverwrite.IsEmpty()) {
                userNameToUse = userNameOverwrite;
        }
        if(userNameToUse.IsEmpty()) {
                userNameToUse = this->generateUsername(userNameToUse, false);
        }
        if(this->ircClient == NULL) {
                this->ircClient = new IRCClient(this->chatSettings->getHost(),
                                                this->chatSettings->getPort(),
                                                this->chatSettings->getChannel(),
                                                userNameToUse);
        }
        this->ircClient->SetObserver(this);
        this->incomingMsg(this->chatSettings->getChannel(), this->languageDB->getGuiString("STRING_CHAT_CONNECTINGTO") +
                        "  " + this->chatSettings->getHost() + ":" + String(this->chatSettings->getPort()), false);
        this->incomingMsg(this->chatSettings->getChannel(), this->languageDB->getGuiString("STRING_CHAT_CHANNEL") +
                        "  " + this->chatSettings->getChannel(), false);
        ircClient->connectAndListen();
}

void Chat::reconnect() {
        if(this->ircClient != NULL) {
                String newUserName = "";
                if(this->ircClient->isConnectionLost()) {
                        newUserName = this->generateUsername(this->chatSettings->getUserName(), true);
                }
                this->ircClient->disconnect();
                delete this->ircClient;
                this->ircClient = NULL;
                this->connect(newUserName);
        }
}

void Chat::disconnect() {
        if(this->isConnected()) {
                this->ircClient->disconnect();
        }
        this->NotifyObserver();
        for(int i = 0; i < this->activeChats->Count; i++) {
                ChatLog *cl = (ChatLog*) (this->activeChats->Objects[i]);
                delete cl;
        }
        this->activeChats->Clear();
        this->blockedChatUsers->Clear();
}

bool Chat::isConnected() {
        if(this->ircClient != NULL) {
                return this->ircClient->isConnected();
        }
        return false;
}

bool Chat::isConnectionLost() {
        if(this->ircClient != NULL) {
                return this->ircClient->isConnectionLost();
        }
        return false;
}

bool Chat::isDisconnected() {
        if(this->ircClient != NULL) {
                return this->ircClient->isDisconnected();
        }
        return false;
}

bool Chat::isConnectingFailed() {
        if(this->ircClient != NULL) {
                return this->ircClient->isConnectingFailed();
        }
        return false;
}

void Chat::update(Observable *o) {
        if(o == this->ircClient) {
                while(this->ircClient->hasPartedUsers()) {
                        String user = this->ircClient->takePartedUser();
                        String message = currentTimeString(false) + "      *******    " +
                                user + " " + this->languageDB->getGuiString("STRING_CHAT_LEFT") + "    *******";
                        if(this->hasConversation(user)) {
                                this->incomingMsg(user, message, true);
                        }
                        this->incomingMsg(this->ircClient->getChannel(), message, true);
                }
                while(this->ircClient->hasJoinedUsers()) {
                        String user = this->ircClient->takeJoinedUser();
                        String message = currentTimeString(false) + "      *******    " +
                                user + " " + this->languageDB->getGuiString("STRING_CHAT_JOINED") + "    *******";
                        if(this->hasConversation(user)) {
                                this->incomingMsg(user, message, true);
                        }
                        this->incomingMsg(this->ircClient->getChannel(), message, true);
                }
                while(this->ircClient->hasMessages()) {
                        ChatMessage *msg = this->ircClient->takeMessage();
                        if(msg != NULL) {
                                if(!this->isClientBlocked(msg->getSender())) {
                                        this->incomingMsg(msg->getChannel(), currentTimeString(false) + " - " + msg->getSender() + ": " + msg->getMessage(), msg->isControlMsg());
                                }
                                delete msg;
                        }
                }
                if(this->ircClient->isConnectionLost()) {
                        this->incomingMsg(this->ircClient->getChannel(),
                        this->languageDB->getGuiString("STRING_CHAT_CONNECTIONLOST"), true);
                } else if(this->ircClient->isDisconnected()) {
                        this->incomingMsg(this->ircClient->getChannel(),
                        this->languageDB->getGuiString("STRING_CHAT_DISCONNECTED"), true);
                } else if(this->ircClient->isConnectingFailed()) {
                        this->incomingMsg(this->ircClient->getChannel(),
                        this->languageDB->getGuiString("STRING_CHAT_CONNECTINGFAILED"), true);
                }
                this->NotifyObserver();
        }
}

void Chat::userSendsMessage(String conversation, String msg) {
        if(this->isConnected()) {
                this->ircClient->userSendsMessage(conversation, msg);
        }
}

void Chat::writeUserList(TStringGrid *grid) {
        if(this->ircClient != NULL) {
                TStringList *userList = this->ircClient->getUserList();
                if(userList->Count > 0) {
                        for(int i = 0; i < userList->Count; i++) {
                                if(grid->RowCount < i + 1) {
                                        grid->RowCount = i + 1;
                                }
                                grid->Cells[0][i] = userList->Strings[i];
                        }
                        grid->RowCount = userList->Count;
                } else {
                        grid->RowCount = 1;
                        grid->Cells[0][0] = "";
                }
        }
}

void Chat::writeConversations(TTabControl *tab) {
        TStringList *inTab = new TStringList;
        for(int i = 0; i < tab->Tabs->Count; i++) {
                String tmp = tab->Tabs->Strings[i];
                if(this->hasConversation(tmp)) {
                        inTab->Add(tmp);
                } else {
                        tab->Tabs->Delete(i);
                        i--;
                }
        }
        for(int i = 0; i < this->activeChats->Count; i++) {
                String tmp = this->activeChats->Strings[i];
                if(inTab->IndexOf(tmp) < 0) {
                        tab->Tabs->Add(tmp);
                }
        }
        delete inTab;
}

String Chat::getUserNameInUse() {
        String out = "";
        if(this->ircClient != NULL) {
                out = this->ircClient->getUserNameInUse();
        }
        return out;
}
