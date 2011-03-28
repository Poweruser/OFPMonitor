

#include <winsock.h>
#include <list>
#include <iostream.h>
#include "Unit1.h" 
#include "irc.h"
#include <vector.h>
#include <sstream>
                           
extern int tcpsocket(void) ;


static DWORD WINAPI irc_ThreadProc( LPVOID lpThreadParameter );
static struct irc_thread__parm * p ;
static void getplayername( ); 
static void start_conversation( int sd, char * name );

struct irc_thread__parm {
    TForm1 * tform1 ;
    vector<string> messages;
    vector<string> userz;
    string hoscht;
    
    int sd;
    void consume(char* c, int i);
}  ;

static char playerName[1024];

void chat_client_disconnect() {
    if (p && p->sd) {
        closesocket(p->sd);
        p->sd = 0;
        p->hoscht.clear();
    }
}


void chat_client_connect(  void * tf ) {
     TForm1 * tform1  = ( TForm1    *  )  tf;

   getplayername();
   if (strlen(playerName) < 1){
        return;
   }
    if (!p) {
        p = new irc_thread__parm();
    }
    CreateThread(0 , 0 , irc_ThreadProc , p , 0 , 0);
}

static string name_irctolocal(string& n){
        string k("ofpmon_");
        int p = n.find(k,0);
        if (p >= 0){
                return string( n , p+k.size() );
        }
        return n;
}

void chat_client_timercallback(  void * t ){
    TForm1 * tform1  = (TForm1 *) t;

    if (p && p->messages.size() > 0) {
         vector<string> m  (p->messages);
         p->messages.clear();

         for( int i = 0; i < m.size(); i++) { 
                 TRichEdit * tr =  tform1->RichEditChatContent;
               
                AnsiString as = tr->Text;//-> = false;
                as += AnsiString(m.at(i).c_str());
                as += "\r\n";
                tr->Text = as;
         }
    }

    if (p && p->userz.size() > 0){
         vector<string> m  (p->userz);
         p->userz.clear();
         for( int i = 0; i < m.size(); i++) {
                TStringGrid * tssg = tform1->StringGrid3;
                int rc =  tssg->RowCount;
                tssg->RowCount = rc + 1;
                string& stre = m.at(i);
                string convertedPlayerName = name_irctolocal( stre );
                tssg->Cells[0][rc] = convertedPlayerName.c_str();
         }
    }
}




DWORD WINAPI irc_ThreadProc (LPVOID lpdwThreadParam__ ) {
    int sd = tcpsocket();
    struct sockaddr_in addr;
    struct irc_thread__parm * p_parm = (struct irc_thread__parm *) lpdwThreadParam__;
    TForm1 * tform1  = p_parm->tform1;
    p_parm->sd = sd;

    memset( &addr , 0 , sizeof(addr));
    // irc.freenode.net = 140.211.167.98
    int ip = inet_addr("140.211.167.98");
    addr.sin_addr.s_addr = ip;
    addr.sin_port        = htons(6666);
    addr.sin_family      = AF_INET;

    int connectRes = connect(sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
      start_conversation(sd, playerName);
      if( connectRes >= 0) {
        char buff [1<<10];
        int r;
            while(p_parm->sd && (r = recv(sd, buff, sizeof(buff) , 0)) > 0){
                    TRichEdit * tr =  tform1->RichEditChatContent;
                    p_parm->consume( buff,r );
            } 
      }
}



string plrname_localtoirc(  char * name  ){
    string n ( name );
    int i;
    for(i = 0; i < n.size(); i++){
        char c = n.at(i);
        int isSmall = c >= 'a' && c <= 'z';
        int isBig = c >= 'A' && c <= 'Z';
        int isNum = c >= '0' && c <= '9';

        if (  !isSmall && !isBig  ){
            n[i]='_';
        }
    }
    while((i = n.find( " " , 0 )) >= 0) {
        n = n.replace( i , 1 , "_");
    }
    return "ofpmon_" + n;
}

void start_conversation( int sd, char * name ) {

      string ircName =   plrname_localtoirc(name);

    stringstream ss;

    ss << "CAP LS\n"
      "NICK " << ircName << "\n"
        << "USER " << ircName << " 0 * :" << ircName << "\n"
        << "CAP REQ :multi-prefix\n"
        <<  "CAP END\n"
        << "USERHOST "<<  ircName <<  "\n"
        << "JOIN #operationflashpoint1\n"
        << "MODE #operationflashpoint1\n";

        string msg =    ss.str();
     int s = send(sd, msg.c_str(), msg.length(), 0);

     return;
}


void  getplayername( ){
    //http://help.github.com/fork-a-repo/
    //"HKEY_CURRENT_USER\Software\Codemasters\Operation Flashpoint"
    char lszValue[100];
    LONG lRet, lEnumRet;
    HKEY hKey = 0;
    DWORD dwLength=100;
    int i=0;

    //char* target=(char*) &lszValue;
    //target=playerName;

    lRet = RegOpenKeyEx (HKEY_CURRENT_USER, "Software\\Codemasters\\Operation Flashpoint", 0L, KEY_READ , &hKey);
    if(lRet == ERROR_SUCCESS)
    {
        DWORD dwType=REG_SZ;
        DWORD dwSize=255;
        lEnumRet = RegQueryValueEx(hKey, "Player Name", NULL, &dwType,(LPBYTE)playerName, &dwSize);
       }
     if (hKey) {
        RegCloseKey(hKey);
    }
}

static vector<string> explode(string s){
        vector<string> r;

        if(s.size()>0){
        int p = 0;
        int t = 0;
                while((t = s.find( "\r\n" ,p ) ) > p){
                        t += 2;
                        r.push_back( string(s, p, t-p) );
                        p = t;
                }
            if (p < s.size() - 1){
                   r.push_back( string(s, p, s.size() - p) );
            }

        }

                       return r;
}

void irc_thread__parm::consume(char* c2, int i2) {
        vector<string> msgs =  explode( string(c2,i2) );
        int it = 0;
        for(;it < msgs.size(); it++ ){
    string& s = msgs.at(it);
    
    if (hoscht.size() == 0) {
      int p = s.find(" NOTICE" , 0);
      if (p > 0) {
          hoscht = string( s , 0, p );
      }
    }


    string playerzNeedle( hoscht + " 353 " );
    int kjo = playerzNeedle.size();
    //when line beginz with diz we have incoming players
    int p = s.find( playerzNeedle );

    // shall be zero eh
    if (p >= 0) {
        int cursorPoz = p + playerzNeedle.size();
        cursorPoz = s.find( ":" , cursorPoz );
        if (cursorPoz > 0) {
            cursorPoz++;
            while (cursorPoz >= 0 && cursorPoz < s.size() ){
                 int cursorNuPoz = s.find( " " , cursorPoz );
                 if (cursorNuPoz <0){
                  break;
                 }
                 if (cursorNuPoz > cursorPoz) {
                     string player( s.c_str() ,  cursorPoz , cursorNuPoz - cursorPoz );
                     userz.push_back(player);
                 } else {
                     string player( s.c_str() ,  cursorPoz , s.size() -cursorPoz - 2 );
                     userz.push_back(player);
                 }
                 cursorPoz = cursorNuPoz + 1;
            }
        }
    }
    messages.push_back( s );
    }
}



