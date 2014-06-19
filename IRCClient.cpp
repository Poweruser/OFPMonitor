//---------------------------------------------------------------------------


#pragma hdrstop

#include "IRCClient.h"
#include <winsock2.h>
#include "ChatMessage.h"
#include "StringSplitter.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
                       
IRCClient::IRCClient(String host, int port, String channel, String userName) {
        this->userName = userName;
        this->ircUserName = this->convertName_LocalToIrc(this->userName);
        this->updatePlayers = false;
        this->timeouts = 0;
        this->host = host;
        this->remoteServer = "";
        this->port = port;
        this->channel = channel;
        this->controlledShutdown = false;
        this->checkStates = true;
        this->status = STATUS_NOTCONNECTED;
        this->userList = new TStringList;
        this->userList->Sorted = true;
        this->userList->Duplicates = dupIgnore;
        this->joinedUsers = new TStringList;
        this->partedUsers = new TStringList;
        this->tcpSocket = NULL;
        this->messageList = new TList;
}

IRCClient::~IRCClient() {
        if(this->isConnected()) {
                this->disconnect();
        }
        delete (this->messageList);
        delete (this->userList);
        delete (this->joinedUsers);
        delete (this->partedUsers);
}

String IRCClient::getChannel() {
        return this->channel;
}

ConnectionStatus IRCClient::getConnectionStatus() {
        return this->status;
}

String IRCClient::getUserNameInUse() {
        return this->ircUserName;
}

bool IRCClient::isConnected() {
        return (this->status == STATUS_CONNECTED);
}

bool IRCClient::isConnectionLost() {
        return (this->status == STATUS_CONNECTIONLOST);
}

bool IRCClient::isDisconnected() {
        return (this->status == STATUS_DISCONNECTED ||
                this->isConnectingFailed());
}

bool IRCClient::isConnectingFailed() {
        return (this->status == STATUS_CONNECTINGFAILED);        
}

unsigned long IRCClient::resolv(String host) {
    struct hostent *hp;
    unsigned long host_ip;
    host_ip = inet_addr(host.c_str());
    if(host_ip == htonl(INADDR_NONE)) {
        hp = gethostbyname(host.c_str());
        if(hp) {
                host_ip = *(unsigned long *)(hp->h_addr);
        } else {
		return INADDR_NONE;
        }
    }
    return(host_ip);
}

void IRCClient::connectAndListen() {
        if(this->status == STATUS_NOTCONNECTED) {
                this->status = STATUS_CONNECTING;
                if(this->tcpSocket) {
                        closesocket(this->tcpSocket);
                        this->tcpSocket = NULL;
                }
                static const struct linger  ling = {1,1};
                this->tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                if(this->tcpSocket != INVALID_SOCKET) {
                        setsockopt(this->tcpSocket, SOL_SOCKET, SO_LINGER, (char *)&ling, sizeof(ling));
                        struct sockaddr_in addr;
                        memset(&addr, 0, sizeof(addr));
                        int ip = this->resolv(this->host);
                        addr.sin_addr.s_addr = ip;
                        addr.sin_port        = htons(this->port);
                        addr.sin_family      = AF_INET;
                        this->status = STATUS_CONNECTING;
                        int connectRes = connect(this->tcpSocket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
                        if(!connectRes) {
                                this->status = STATUS_CONNECTED;
                                int length = 30000;
                                setsockopt(this->tcpSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&length, sizeof(length));
                                this->startConversation();
                                char buff [1<<12];
                                this->checkStates = false;
                                do {
                                        while(this->tcpSocket) {
                                                int receivedBytes = recv(this->tcpSocket, buff, sizeof(buff), 0);
                                                if(receivedBytes > 0) {
                                                        this->parseReceivedData(String(buff, receivedBytes));
                                                } else {
                                                        break;
                                                }
                                        }
                                        this->timeouts++;
                                        if(this->timeouts > 5) {
                                                if(this->tcpSocket) {
                                                        this->sendString("QUIT : \r\n");
                                                        closesocket(this->tcpSocket);
                                                        this->status = STATUS_CONNECTIONLOST;
                                                        this->tcpSocket = NULL;
                                                }
                                        }
                                } while(
                                        this->isConnected() && this->tcpSocket &&
                                        (this->sendString("PING " + this->remoteServer + " \r\n")) >= 0
                                );
                                this->checkStates = true;
                        } else {
                                this->status = STATUS_CONNECTINGFAILED;
                        }
                } else {
                        this->status = STATUS_CONNECTINGFAILED;
                }
        }
        if(this->controlledShutdown) {
                this->status = STATUS_DISCONNECTED;
        } else {
                if(!this->isConnectingFailed()) {
                        this->status = STATUS_CONNECTIONLOST;
                } else {
                        closesocket(this->tcpSocket);
                        this->tcpSocket = NULL;
                }
        }
        this->NotifyObserver();
}

void IRCClient::disconnect() {
        if(this->isConnected()) {
                this->sendString("QUIT : \r\n");
        }
        this->controlledShutdown = true;
        if(this->tcpSocket) {
                closesocket(this->tcpSocket);
                this->tcpSocket = NULL;
        }
        this->userList->Clear();
}

void IRCClient::parseReceivedData(String data) {
        bool sendNotify = false;
        StringSplitter ssp(data);
        TStringList *lines = ssp.split("\r\n");
        for(int i = 0; i < lines->Count; i++) {
                bool handled = true;
                String line = lines->Strings[i];
                if(this->remoteServer.IsEmpty()) {
                        String tmp = line;
                        tmp.Delete(1, tmp.Pos(":"));
                        int position = tmp.Pos(" NOTICE");
                        if(position > 1) {
                                this->remoteServer = tmp.SubString(1, position - 1);
                        }
                }
                bool normalMsg = line.Pos("PRIVMSG ");

                String body = line;
                body.Delete(1, body.Pos(" "));
                if(body.Pos("353 ") == 1) {
                        body.Delete(1, body.Pos(":"));
                        StringSplitter ssusers(body);
                        TStringList *users = ssusers.split(" ");
                        for(int j = 0; j < users->Count; j++) {
                                this->userJoined(convertName_IrcToLocal(users->Strings[j]), false);
                        }
                        delete users;
                } else if(body.Pos("QUIT ") == 1) {
                        String name = extractUserNameFromLine(line);
                        if(!name.IsEmpty()) {
                                name = convertName_IrcToLocal(name);
                                this->userLeft(name);
                        }
                } else if(body.Pos("433 ") == 1) {
                        body.Delete(1, body.Pos(":"));
                        this->sendString("QUIT : \r\n");
                        this->status = STATUS_CONNECTIONLOST;
                        this->messageList->Add((TObject*)(new ChatMessage(this->remoteServer, this->channel, body, true)));
                        closesocket(this->tcpSocket);
                        this->tcpSocket = NULL;
                } else if(body.Pos("PONG ") == 1) {
                        this->timeouts = 0;
                } else if(body.Pos("PING " + this->remoteServer) == 1) {
                        this->timeouts = 0;
                        this->sendString("PONG " + this->remoteServer + "\r\n");
                } else if(body.Pos("JOIN ") == 1) {
                        String name = this->extractUserNameFromLine(line);
                        this->userJoined(name, true);
                } else if(body.Pos("PART ") == 1) {
                        String name = this->extractUserNameFromLine(line);
                        this->userLeft(name);
                } else if(body.Pos("PRIVMSG ") == 1) {
                        bool chanMsg = body.Pos("PRIVMSG " + this->channel) == 1;
                        bool privMsg = body.Pos("PRIVMSG " + this->ircUserName) == 1;
                        String sender = this->convertName_IrcToLocal(this->extractUserNameFromLine(line));
                        String channel = this->channel;
                        if(privMsg) {
                                channel = sender;
                        }
                        String msg = body;
                        msg.Delete(1, msg.Pos(":"));
                        bool isCtcp = msg.Pos("\001") == 1;
                        bool isLoggedInMsg = msg.Pos("Logged in with") == 1;
                        if(!isCtcp) {
                                this->messageList->Add((TObject*)(new ChatMessage(sender, channel, msg, isLoggedInMsg)));
                        }
                } else {
                        handled = false;
                }
                sendNotify = (sendNotify && handled);
        }
        this->NotifyObserver();
}

bool IRCClient::hasJoinedUsers() {
        return (this->joinedUsers->Count > 0);
}


bool IRCClient::hasPartedUsers() {
        return (this->partedUsers->Count > 0);
}

bool IRCClient::hasMessages() {
        return (this->messageList->Count > 0);
}

String IRCClient::takeJoinedUser() {
        String name = "";
        if(this->hasJoinedUsers()) {
                name = this->joinedUsers->Strings[0];
                this->joinedUsers->Delete(0);
        }
        return name;
}

String IRCClient::takePartedUser() {
        String name = "";
        if(this->hasPartedUsers()) {
                name = this->partedUsers->Strings[0];
                this->partedUsers->Delete(0);        
        }
        return name;
}

ChatMessage* IRCClient::takeMessage() {
        ChatMessage *msg = NULL;
        if(this->messageList->Count > 0) {
                msg = (ChatMessage*)(this->messageList->Items[0]);
                this->messageList->Delete(0);
        }
        return msg;
}

void IRCClient::userJoined(String userName, bool isNew) {
        this->userList->Add(userName);
        if(isNew) {
                this->joinedUsers->Add(userName);
        }
}

void IRCClient::userLeft(String userName) {
        int index;
        if(this->userList->Find(userName, index)) {
                this->userList->Delete(index);
        }
        this->partedUsers->Add(userName);
}

String IRCClient::extractUserNameFromLine(String line) {
        String tmp = line;
        int front = tmp.Pos(":"), back = tmp.Pos("!");
        if(front > 0 && back > 1 && front < back) {
                return tmp.SubString(front + 1, back - (1 + front));
        }
        return "";
}

String IRCClient::convertName_IrcToLocal(String name) {
        String n = name;
        if(n.Pos("@") == 1) {
                n.Delete(1, 1);
        }
        return n;
}

String IRCClient::convertName_LocalToIrc(String name) {
        String converted = name;
        for(int i = 1; i <= converted.Length(); i++){
                char c = converted[i];
                bool isSmall = c >= 'a' && c <= 'z';
                bool isBig   = c >= 'A' && c <= 'Z';
                bool isNum   = c >= '0' && c <= '9';
                bool extra   = String("-[]^{|}").Pos(String(c));
                if (!isSmall && !isBig && !(i > 1 && isNum) && !extra){
                        converted[i] = '_';
                }
        }
        return converted;
}

void IRCClient::startConversation() {
        String msg =    "CAP LS\nNICK " +
                        this->ircUserName + "\n" +
                        "USER " + this->ircUserName + " 0 * :" + this->ircUserName + "\n" +
                        "CAP REQ :multi-prefix\n" +
                        "CAP END\n" +
                        "USERHOST " +  this->ircUserName +  "\n" +
                        "JOIN " + this->channel + "\n" +
                        "MODE " + this->channel + "\n";
        this->sendString(msg);
}

void IRCClient::sendMessage(String receiver, String msg) {
        String userMessage = msg;
        if(userMessage.Length() > 450) {
                userMessage = userMessage.SubString(0, 450);
        }
        String str = "PRIVMSG " + receiver + " :" + userMessage + "\r\n";
        this->sendString(str);
}

int IRCClient::sendString(String msg) {
        int sent = -1;
        if(this->tcpSocket && this->isConnected()) {
                sent = send(this->tcpSocket, msg.c_str(), msg.Length(), 0);
        }
        return sent;
}

TStringList* IRCClient::getUserList() {
        return this->userList;
}

void IRCClient::userSendsMessage(String receiver, String msg) {
        this->sendMessage(receiver, msg);
        this->messageList->Add((TObject*)(new ChatMessage(this->ircUserName, receiver, msg, false)));
        this->NotifyObserver();
}

bool IRCClient::checkStatesAllowed() {
        return this->checkStates;
}



