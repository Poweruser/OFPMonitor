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

String Message::getAddress() {
        return (this->ip + ":" + IntToStr(this->port));
}

String Message::getIP() {
        return this->ip;
}

DWORD Message::getTimeOfArrival() {
        return this->toa;
}

int Message::getPort() {
        return this->port;
}

String Message::getContent() {
        return this->content;
}


