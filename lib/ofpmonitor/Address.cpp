//---------------------------------------------------------------------------


#pragma hdrstop

#include "Address.h"
#include "StringSplitter.h"
#include <list.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

                Address::Address() {
                        this->ip = "";
                        this->port = 0;
                        this->valid = false;
                }

                bool Address::readAddress(String address, int defaultPort, bool gamespy) {
                        bool ok = true;
                        if(address.IsEmpty()) {
                                ok = false;
                        }
                        if(ok) {
                                StringSplitter ssp(address);
                                TStringList *ipAndPort = ssp.split(":");
                                if(ipAndPort->Count > 2 || ipAndPort->Count == 0) {
                                        ok = false;
                                }
                                if(ok) {
                                        String ip = ipAndPort->Strings[0];
                                        int port = defaultPort;
                                        if(ipAndPort->Count == 2) {
                                                port = StrToIntDef(ipAndPort->Strings[1], -1);
                                                if(port <= 0 || port > 65535) {
                                                        ok = false;
                                                }
                                        }
                                        StringSplitter sspo(ip);
                                        TStringList *octets = sspo.split(".");
                                        if(octets->Count != 4) {
                                                ok = false;
                                        }
                                        while(octets->Count > 0 && ok) {
                                                int item = StrToIntDef(octets->Strings[0], -1);
                                                if(item < 0 || item > 255) {
                                                        ok = false;
                                                }
                                                octets->Delete(0);
                                        }
                                        if(ok) {
                                                if(!gamespy) { port++; }
                                                this->port = port;
                                                this->ip = ip;
                                                this->valid = ok;
                                        }
                                        delete octets;
                                }
                                delete ipAndPort;
                        }
                        return (this->valid);
                }

                String Address::getIP() {
                        return this->ip;
                }

                int Address::getPort() {
                        return this->port;
                }

                bool Address::isValid() {
                        return this->valid;
                }

                String Address::getAddress() {
                        return (this->ip + ":" + IntToStr(this->port));
                }
