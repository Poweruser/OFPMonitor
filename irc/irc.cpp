

#include <winsock.h>
#include "irc.h"

#include <list>
#include <iostream.h>
#include "Unit1.h"

DWORD WINAPI  irc_ThreadProc   (  LPVOID lpThreadParameter  );

struct irc_thread__parm {
    TForm1 * tform1 ;
};
extern               int tcpsocket(void) ;
void start_chat_client(  void * tf ) {
     TForm1 * tform1  = ( TForm1    *  )  tf;

    struct irc_thread__parm * p = (struct irc_thread__parm *) malloc(sizeof(struct irc_thread__parm));
     p->tform1 = tform1;
    CreateThread(0 , 0 , irc_ThreadProc , p , 0 , 0);
}



DWORD WINAPI irc_ThreadProc (LPVOID lpdwThreadParam__ ) {
    struct sockaddr * peer;
    int sd = tcpsocket();
    struct sockaddr_in addr;
    struct irc_thread__parm * p = (struct irc_thread__parm *) lpdwThreadParam__;
     TForm1 * tform1  = p->tform1;

    memset( &addr , 0 , sizeof(addr));

    addr.sin_addr.s_addr = inet_addr("irc.freenode.net");
    addr.sin_port        = htons(6666);
    addr.sin_family      = AF_INET;

    int connectRes = connect(sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    
      if( connectRes >= 0) {
        char buff [1<<10];
        int r;
            while((r = recv(sd, buff, sizeof(buff) , 0)) > 0){
                    TRichEdit * tr =  tform1->RichEditChatContent;
                    if (0) {
                        AnsiString as = tr->Text;//-> = false;
                        as += "Hello \r\n";
                        tr->Text = as;
                    }
                    TStrings * ts = tr->Lines;
                    ts->Append("Hello \r\n");
            }
            // send(sd, buff, len, 0);
              // err = recv(gsTcpSocket, buff + len, dynsz - len, 0);
      }
}



