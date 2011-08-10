#include "Unit1.h"
#include "Unit2.h"
#include "irc.h"
#include <vector.h>
#include <set.h>
#include <time.h>
#include <sstream.h>

//#define ALVOIRC_DEBUG_MSG
#ifdef ALVOIRC_DEBUG_MSG
        #define ALVOIRC_INPUTOUT 1
#else
        #define ALVOIRC_INPUTOUT 0
#endif

extern int tcpsocket(void) ;
extern int timeout(int sock, int sec);
extern unsigned long dnsdb(char *host);

static DWORD WINAPI irc_ThreadProc( LPVOID lpThreadParameter );
static struct irc_thread__parm * ircThreadInstance;
static void getplayername(bool connectionFailedBefore ); 
static void start_conversation( int sd, char * name ); 
static void sendMessage(const char * xmsg);

static string after(string& in, string& needle);
static string before(string& in, string& needle);
static int starts(string& in, string& needle);
extern unsigned long resolv(char *host) ;  
static string currentTimeString();
static string plrname_localtoirc(  char * name  );
static string name_irctolocal(string& n);

static string allowedExtraCharacters = "_-[]^";

struct irc_thread__parm {
        TForm1 * tform1 ;
        vector<string> messages;
        vector<string> userz;
        vector<string> playersParted;
        vector<string> playersJoined;    
        set<string> userzSorted;
        string hoscht;

        int updatePlayers;
        bool controlledShutdown;
        bool connectionLost;
        int sd;
        int loggedIn;
        void consume(char* c, int i);
        int sentVersion;
        int timeouts;
        public:
                irc_thread__parm():sentVersion(0),updatePlayers(0),timeouts(0),
                controlledShutdown(false),connectionLost(false){
                }
                int sendString(string&);
};

static char playerName[1024];
HANDLE chatListener;

void chat_client_disconnect() {
        if (ircThreadInstance && ircThreadInstance->sd) {
                ircThreadInstance->controlledShutdown = true;
                closesocket(ircThreadInstance->sd);
                ircThreadInstance->sd = 0;
                ircThreadInstance->hoscht.clear();
                ircThreadInstance->userz.clear();
                ircThreadInstance->playersParted.clear();
                ircThreadInstance->playersJoined.clear();
 	        ircThreadInstance->userzSorted.clear();
                TerminateThread(chatListener, 0);
        }
}

void chat_client_connect() {
        bool connectionFailedBefore = false;
        if (ircThreadInstance) {
                TerminateThread(chatListener, 0);
                connectionFailedBefore = ircThreadInstance->connectionLost;
                delete ircThreadInstance;
        }
        getplayername(connectionFailedBefore);
        ircThreadInstance = new irc_thread__parm();
        int sd = tcpsocket();
        ircThreadInstance->sd = sd;
        if(ircThreadInstance->sd) {
                chatListener = CreateThread(0, 0, irc_ThreadProc, ircThreadInstance, 0, 0);
        } else {
                closesocket(sd);
                Form1->ChatConnected(false);
        }
}
static string name_irctolocal(string& n) {
        string playername = n;
        if (starts(playername , "@")){
                playername = after(playername , "@");
        }
        string k(ofpprefix);
        int p = playername.find(k, 0);
        if (p >= 0) {
                return string(playername, p + k.size());
        }
        return playername;
}              

string plrname_localtoirc(  char * name  ) {
        string n ( name );
        for(unsigned int i = 0; i < n.size(); i++){
                char c = n.at(i);
                int isSmall = c >= 'a' && c <= 'z';
                int isBig   = c >= 'A' && c <= 'Z';
                int isNum   = c >= '0' && c <= '9';
                int extra   = Form1->doNameFilter(allowedExtraCharacters.c_str(), c);
                if (!isSmall  &&  !isBig  &&  !(i > 1 && isNum) && !extra){
                        n[i] = '_';
                }
        }
        return ofpprefix + n;
}

void appendText( TForm1 * tform1, string& msg ) {
        TMemo *tr = tform1->MemoChatOutput;
        tr->Lines->Add(msg.c_str());
}

static string currentTimeString() {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        strftime (buffer, 80, "%H:%M", timeinfo);
        return buffer;
}

void chat_client_timercallback(void * t) {
        TForm1 *tform1 = (TForm1 *) t;
        if( ircThreadInstance == NULL) { return; }

        if (ircThreadInstance && ircThreadInstance->messages.size() > 0) {
                vector<string> m  (ircThreadInstance->messages);
                ircThreadInstance->messages.clear();
                //string privMsgNeedle = "PRIVMSG #" + channelname_operationflashpoint1 + " :";
                string privMsgNeedle = Form1->getChatChannel().c_str();
                privMsgNeedle = "PRIVMSG #" + privMsgNeedle + " :";
                for(unsigned int i = 0; i < m.size(); i++) {
                        string& omsg = m.at(i);
                        if (ALVOIRC_INPUTOUT) {
                                appendText(tform1, omsg);
                        }
                        string cmsg = omsg;
                        string playername;
                        int fnd = 0;
                        if ((fnd = cmsg.find(privMsgNeedle,0)) >= 0) {
                                cmsg = string(cmsg, fnd + privMsgNeedle.size());
                                int emp = omsg.find("!", 1);
                                playername = string(omsg, 1, emp - 1);
                                playername = name_irctolocal(playername);
				if(!Form1->isChatUserBlocked(playername.c_str())) {                                
					cmsg = currentTimeString() + " - " + playername + ": " + cmsg;
                                	appendText(tform1, cmsg);
                                        if(Form1->doNameFilter(cmsg.c_str(), playerName) ||
                                           Form1->doNameFilter(cmsg.c_str(), (ofpprefix + plrname_localtoirc(playerName)).c_str())) {
                                               tform1->ChatNotification(cmsg.c_str());
                                        }
				}
                        }
                }
        }

        if (0 && ircThreadInstance && ircThreadInstance->userz.size() > 0) {
                vector<string> m  (ircThreadInstance->userz);
                ircThreadInstance->userz.clear();
                for(unsigned int i = 0; i < m.size(); i++) {
                        TStringGrid *tssg = tform1->StringGrid3;
                        int rc =  tssg->RowCount;
                        tssg->RowCount = rc + 1;
                        string& stre = m.at(i);
                        string convertedPlayerName = name_irctolocal( stre );
                        tssg->Cells[0][rc] = convertedPlayerName.c_str();
                }
        }

        if (ircThreadInstance->updatePlayers) {
                ircThreadInstance->updatePlayers = 0;
                set<string> userzSortedCopy = set<string>(ircThreadInstance->userzSorted);
                TStringGrid *tssg = tform1->StringGrid3;
                tssg->RowCount = userzSortedCopy.size();

                // convert to vector
                vector<string> ulist(userzSortedCopy.begin(), userzSortedCopy.end());
                for(unsigned int i = 0; i < ulist.size(); i++) {
                        tssg->Cells[0][i] = ulist[i].c_str();
                }
        }

        if (ircThreadInstance->playersParted.size() > 0) {
                vector<string> pp =  vector<string>(ircThreadInstance->playersParted);
                ircThreadInstance->playersParted.clear();
                for(unsigned int i = 0; i < pp.size(); i++) {
                        //p->sendString
                        string text = currentTimeString() + "      *******    "  + pp.at(i) + " ";
                        text += WINDOW_SETTINGS->getGuiString("STRING_CHAT_LEFT").c_str();
                        text += "    ******";
                        appendText(tform1, text);
                }
        }
        if (ircThreadInstance->playersJoined.size() > 0) {
                vector<string> pp =  vector<string>(ircThreadInstance->playersJoined);
                ircThreadInstance->playersJoined.clear();
                for(unsigned int i = 0; i < pp.size(); i++) {
                        //p->sendString
                        string text = currentTimeString() + "      *******    "  + pp.at(i) + " ";
                        text += WINDOW_SETTINGS->getGuiString("STRING_CHAT_JOINED").c_str();
                        text += "    ******";
                        appendText(tform1, text);
                }
        }
}

DWORD WINAPI irc_ThreadProc (LPVOID lpdwThreadParam__ ) {
        struct irc_thread__parm * p_parm = (struct irc_thread__parm *) lpdwThreadParam__;
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        int ip = resolv(Form1->getChatHost().c_str());
        addr.sin_addr.s_addr = ip;
        addr.sin_port        = htons(Form1->getChatPort());
        addr.sin_family      = AF_INET;
        int connectRes = connect(p_parm->sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
        Form1->ChatConnected(!connectRes);
        if(p_parm->sd && !connectRes) {
                int length = 10000;
                int re = setsockopt(p_parm->sd,SOL_SOCKET,SO_RCVTIMEO,(const char *)&length,sizeof(length));
                start_conversation(p_parm->sd, playerName);
                char buff [1<<10];
                int r, rping;
                do {
                        while(p_parm->sd && (r = recv(p_parm->sd, buff, sizeof(buff), 0)) > 0){
                                p_parm->consume(buff, r);
                        }
                        p_parm->timeouts++;
                        if(p_parm->timeouts > 2) {
                                closesocket(p_parm->sd);
                        }
                } while(  ircThreadInstance &&
                        ircThreadInstance->sd &&
                        (rping = ircThreadInstance->sendString("PING " + ircThreadInstance->hoscht + " \r\n")) >= 0);
                if(!ircThreadInstance->controlledShutdown) {
                        ircThreadInstance->connectionLost = true;
                        Form1->ChatConnectionLost();
                }
        }
        return 0;
}

int irc_thread__parm::sendString(string& s) {
        return   send(sd, s.c_str(), s.length(), 0);
}

void start_conversation( int sd, char * name ) {
        String ircName = plrname_localtoirc(name).c_str();
        String msg =    "CAP LS\nNICK " +
                        ircName + "\n" +
                        "USER " + ircName + " 0 * :" + ircName + "\n" +
                        "CAP REQ :multi-prefix\n" +
                        "CAP END\n" +
                        "USERHOST " +  ircName +  "\n" +
                        "JOIN #" + Form1->getChatChannel() + "\n" +
                        "MODE #" + Form1->getChatChannel() + "\n";
        /*
        stringstream ss;
        ss << "CAP LS\n"
        << "NICK " << ircName << "\n"
        << "USER " << ircName << " 0 * :" << ircName << "\n"
        << "CAP REQ :multi-prefix\n"
        << "CAP END\n"
        << "USERHOST "<<  ircName <<  "\n"
        << "JOIN #" << Form1->getChatChannel() << "\n"
        << "MODE #" << Form1->getChatChannel() << "\n";

        string msg = ss.str();
        */
        int s = send(sd, msg.c_str(), msg.Length(), 0);
        return;
}

void  getplayername(bool previousConnectionFailed) {
        String chatName = Form1->getChatUserName();
        if(chatName.IsEmpty()) {
                string tmp = "Guest" + currentTimeString();
                strcpy(playerName, tmp.c_str());
        } else {
                if(previousConnectionFailed) {
                        String oldName = playerName;
                        if(oldName == chatName) {
                                if(chatName.Length() > 11) {
                                        chatName = chatName.SubString(1,11);
                                }
                                String test = "";
                                for(int i = 2; i < 10; i++) {
                                        test = chatName + "[" + IntToStr(i) + "]";
                                        if(test != oldName) {
                                                chatName = test;
                                                break;
                                        }
                                }
                        }
                }
                strcpy(playerName, chatName.c_str());
        }
        return;
}

static vector<string> explode(string s){
        vector<string> r;
        if(s.size() > 0){
                int p = 0;
                int t = 0;
                while(p < s.size() && (t = s.find("\r\n", p) ) > p) {
                        string line (s, p, t-p);
                        r.push_back( line );
                        p = t + 2;
                }
                if (p < s.size() - 1) {
                        r.push_back( string(s, p, s.size() - p) );
                }
        }
        return r;
}

static string readPlayerFromLine(string& s){
          string name = after(s, ":");
                        name = before(name, "!");
                        name = name_irctolocal(name);
                        return name;
}

void irc_thread__parm::consume(char* c2, int i2) {
        vector<string> msgs = explode( string(c2, i2) );
        unsigned int it = 0;
        for(;it < msgs.size(); it++ ){
                string& s = msgs.at(it);

                if (hoscht.size() == 0) {
                        int p = s.find(" NOTICE" , 0);
                        if (p > 0) {
                                hoscht = string( s , 0, p );
                        }
                }

                //string playerzNeedle( hoscht + " 353 " );
                string body = after(s , " ");
                if (starts(body , "353 ")) {
                        string ps2 = after( body , ":" );
                        while (ps2.size() > 0 ) {
                                int isLastPlayer = ps2.find( " " , 0 ) == -1;
                                string player;
                                if (isLastPlayer) {
                                        player = ps2;
                                } else {
                                        player = before(ps2, " ");
                                }
                                player = name_irctolocal(player);
                                userz.push_back(player);
                                userzSorted.insert(player);
                                updatePlayers = 1;
                                if (isLastPlayer) {
                                        break;
                                }
                                ps2 = after(ps2, " ");
                        }
                } else if ( starts(body , "QUIT ") ){
                    string name = readPlayerFromLine(s);    
                        playersParted.push_back(name);
                        userzSorted.erase(name);
                        updatePlayers = 1;
                } else if ( starts(body , "433 ")) {
                        string ps2 = after( body , ":" );
                        appendText(Form1, ps2);
                        ircThreadInstance->controlledShutdown = true;
                        Form1->ChatConnected(false);
                }
            
                int pingFind = s.find("PING " + hoscht, 0) ;
                int pongFind = s.find(" PONG ", 0);
                int joinFind = s.find(" JOIN ", 0) ;
                int partFind = s.find(" PART ", 0) ;
                int endNameListFind = s.find("End of /NAMES list.",0);

                if(pongFind >= 0) {
                        ircThreadInstance->timeouts = 0;
                }    
                if (pingFind == 0) {
                        ircThreadInstance->timeouts = 0;
                        // sending pong
                        string pong ("PONG " + hoscht + "\r\n");
                        send(sd, pong.c_str(), pong.length(), 0);
                } else if (!sentVersion && endNameListFind >= 0) {
                        sentVersion = 1;
                        sendMessage( ("Logged in with " + Application->Title).c_str());
                } else if (joinFind > 0) {
                        string name = readPlayerFromLine(s);
                        playersJoined.push_back(name);
                        userzSorted.insert(name);
                        updatePlayers = 1;
                } else if (partFind > 0) {
                        string name = readPlayerFromLine(s);
                        playersParted.push_back(name);
                        userzSorted.erase(name);
                        updatePlayers = 1;
                }
                messages.push_back(s);
        }
}

void sendMessage(const char *xmsg) {
        string msg( xmsg );
        string channel = Form1->getChatChannel().c_str();
        msg = "PRIVMSG #" + channel + " :" + msg + "\r\n";
        send(ircThreadInstance->sd, msg.c_str(), msg.length(), 0);
}

void chat_client_pressedReturnKey(void *t, const char *msg) {
        TForm1 *tform1 = (TForm1 *) t;
        if (ircThreadInstance && ircThreadInstance->sd) {
                sendMessage(msg);
                appendText(tform1,  currentTimeString( ) +  " - " + playerName + ": " + msg);
        }
}


static string after(string& in, string& needle) {
        int i = in.find(needle, 0);
        if (i >= 0) {
                return string(in, i + needle.length());
        }
        return "";
}

static string before(string& in, string& needle) {
        int i = in.find(needle, 0);
        if (i > 0) {
                return string(in, 0, i);
        }
        return "";
}

static int starts(string& in, string& needle) {
        return in.find(needle, 0) == 0;
}