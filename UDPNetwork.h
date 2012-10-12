//---------------------------------------------------------------------------

#ifndef UDPNetworkH
#define UDPNetworkH

#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <list.h>
#include <vcl.h>
#include "Message.h"

class UDPNetwork {
        public:

                UDPNetwork();
                ~UDPNetwork();
                list<Message*> messageList;

                bool sendUdpMessage(String ip, int port, String msg);

        private:
                TIdUDPServer *udpSocket;
                void __fastcall IdUDPServerUDPRead(TIdUDPListenerThread *AThread,
                                TIdBytes AData, TIdSocketHandle *ABinding);

};


//---------------------------------------------------------------------------
#endif
