//---------------------------------------------------------------------------


#pragma hdrstop

#include "Address.h"
#include "Unit1.h"
#include <list.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

                Address::Address() {
                        this->ip = "";
                        this->port = 0;
                }

                Address::Address(String ip, int port) {
                        this->ip = ip;
                        this->port = port;
                }

                bool Address::getAddress(String address, int defaultPort) {
                        if(address.IsEmpty()) { return false; }
                        list<String> ipAndPort = Form1->splitUpMessage(address,":");
                        if(ipAndPort.size() > 2 || ipAndPort.size() == 0) { return false; }
                        String ip = ipAndPort.front();
                        int port = defaultPort;
                        if(ipAndPort.size() == 2) {
                                try {
                                        port = StrToInt(ipAndPort.back());
                                        if(port <= 0 || port > 65535) { return false; }
                                } catch (...) { return false; }
                        }
                        list<String> octets = Form1->splitUpMessage(ip, ".");
                        if(octets.size() != 4) { return false; }
                        while(octets.size() > 0) {
                                try {
                                        int item = StrToInt(octets.front());
                                        if(item < 0 || item > 255) { return false; }
                                } catch (...) {
                                        return false;
                                }
                                octets.pop_front();
                        }
                        this->ip = ip;
                        this->port = port;
                        return true;
                }
