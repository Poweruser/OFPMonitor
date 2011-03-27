

#include <winsock.h>
#include "irc.h"

#include <list>
#include <iostream.h>
#include "Unit1.h"
              
#include <vector.h>


DWORD WINAPI  irc_ThreadProc   (  LPVOID lpThreadParameter  );

extern               int tcpsocket(void) ;
static struct irc_thread__parm * p ;
void start_conversation( int sd, char * name );




struct irc_thread__parm {
    TForm1 * tform1 ;
    vector<string> messages;
};


void start_chat_client(  void * tf ) {
     TForm1 * tform1  = ( TForm1    *  )  tf;
    if (!p) {
        p = (struct irc_thread__parm *) malloc(sizeof(struct irc_thread__parm));
    }
     p->tform1 = tform1;
    CreateThread(0 , 0 , irc_ThreadProc , p , 0 , 0);
}


void irc_chat_timer(  void * t ){
    TForm1 * tform1  = (TForm1 *) t;

    if (p && p->messages.size() > 0) {
         vector<string> m = vector<string>(p->messages);
         p->messages.clear();

         for( int i = 0; i < m.size(); i++) { 
                 TRichEdit * tr =  tform1->RichEditChatContent;
               
                AnsiString as = tr->Text;//-> = false;
                as += AnsiString(m.at(i).c_str());
                as += "\r\n";
                tr->Text = as;
         }
    }
}

DWORD WINAPI irc_ThreadProc (LPVOID lpdwThreadParam__ ) {
    int sd = tcpsocket();
    struct sockaddr_in addr;
    struct irc_thread__parm * p_parm = (struct irc_thread__parm *) lpdwThreadParam__;
    TForm1 * tform1  = p_parm->tform1;

    memset( &addr , 0 , sizeof(addr));
    // irc.freenode.net = 140.211.167.98
    int ip = inet_addr("140.211.167.98");
    addr.sin_addr.s_addr = ip;
    addr.sin_port        = htons(6666);
    addr.sin_family      = AF_INET;

    int connectRes = connect(sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
      start_conversation(sd, "avooo");
      if( connectRes >= 0) {
        char buff [1<<10];
        int r;
            while((r = recv(sd, buff, sizeof(buff) , 0)) > 0){
                    TRichEdit * tr =  tform1->RichEditChatContent;
                    p_parm->messages.push_back( string( buff,r ) );
                    if ( 0 ) {
                        AnsiString as = tr->Text;//-> = false;
                        as += AnsiString(buff,r);
                        as += "end \r\n";
                        tr->Text = as;
                    }
                    if (0) {
                    TStrings * ts = tr->Lines;
                  ts->Append(AnsiString(buff,r));
                   ts->Append("Hello \r\n");
//                     tr->Invalidate();
                     }
            }
            // send(sd, buff, len, 0);
              // err = recv(gsTcpSocket, buff + len, dynsz - len, 0);
      }
}




void start_conversation( int sd, char * name ) {

    string msg = "CAP LS\n"
      "NICK ";
      msg += name;
      msg += "\n";
        msg+= "USER owe 0 * :Alvo\n";
        msg +="CAP REQ :multi-prefix\n";
        msg +="CAP END\n";
        msg +="USERHOST Alvo\n";
        msg +="JOIN #operationflashpoint1\n";
        msg +="MODE #operationflashpoint1\n";
     int s = send(sd, msg.c_str(), msg.length(), 0);
     return;
}