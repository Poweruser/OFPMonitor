//---------------------------------------------------------------------------


#pragma hdrstop

#include "Message.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Message::Message(String ip, int port, String content, DWORD toa) {
        this->ip = ip;
        this->port = port;
        this->content = content;
        this->toa = toa;
}
