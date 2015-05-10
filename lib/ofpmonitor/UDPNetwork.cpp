//---------------------------------------------------------------------------


#pragma hdrstop

#include "UDPNetwork.h"
#include <mmsystem.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)


UDPNetwork::UDPNetwork() {
        this->udpSocket = new TIdUDPServer(NULL);
        //this->udpSocket->ThreadedEvent = true;
        this->udpSocket->DefaultPort = 0;
        this->udpSocket->BroadcastEnabled = false;
        this->udpSocket->ReuseSocket = rsOSDependent;
        this->udpSocket->IPVersion = Id_IPv4;
        this->udpSocket->OnUDPRead = this->IdUDPServerUDPRead;
}

UDPNetwork::~UDPNetwork() {
        delete (this->udpSocket);
        while(this->messageList.size() > 0) {
                Message *m = this->messageList.front();
                this->messageList.pop_front();
                delete m;
        }
}

bool UDPNetwork::sendUdpMessage(String ip, int port, String msg) {
        try {
                this->udpSocket->Send(ip, port, msg);
        } catch (EIdSocketError &E) {
                //ShowMessage("send EIdSocketError");
                return false;
        } catch (EIdException &E) {
                //ShowMessage("send EIdException");
                return false;
        } catch (Exception &E) {
                //ShowMessage("send Exception");
                return false;
        }
        return true;
}

void __fastcall UDPNetwork::IdUDPServerUDPRead(TIdUDPListenerThread *AThread,
      TIdBytes AData, TIdSocketHandle *ABinding)
{
        if(AData.Length > 0) {
                this->messageList.push_back(
                        new Message(    ABinding->PeerIP,
                                        ABinding->PeerPort,
                                        BytesToString(AData),
                                        timeGetTime()));
        }
}
