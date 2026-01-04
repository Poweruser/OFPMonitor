//---------------------------------------------------------------------------


#pragma hdrstop

#include "Address.h"
#include "StringSplitter.h"
#include <list.h>

#include <IdSocketHandle.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)

unsigned long resolv(char *host) {
    struct      hostent *hp;
    unsigned long   host_ip;

    host_ip = inet_addr(host);
    if(host_ip == htonl(INADDR_NONE)) {
        hp = gethostbyname(host);
        if(!hp) {
		return INADDR_NONE;
        } else host_ip = *(unsigned long *)(hp->h_addr);
    }
    return(host_ip);
}

Address::Address() {
        this->ip = NULL;
        this->hostname = NULL;
        this->gamePort = 0;
        this->gameSpyPort = 0;
        this->valid = false;
}

bool Address::readAddress(String host, int defaultPort, bool gamespy) {
        StringSplitter *ssp = new StringSplitter(host);
        TStringList *parts = ssp->split(":");
        String hostToResolve = host;
        String resolvedIP = NULL;
        int port = defaultPort;
        boolean isAlreadyIP = false;
        if(parts->Count >= 1) {
                hostToResolve = parts->Strings[0];
                if(parts->Count == 2) {
                        port = StrToIntDef(parts->Strings[1], -1);
                }
                isAlreadyIP = this->checkIPFormat(hostToResolve);
                if(!isAlreadyIP) {
                        resolvedIP = this->resolveHostnameToIP(hostToResolve);
                } else {
                        resolvedIP = hostToResolve;
                }
        }
        delete ssp;
        delete parts;

        if(gamespy) {
                port--;
        }
        if(port >= 0 && port <= 65534 && (isAlreadyIP || this->checkIPFormat(resolvedIP))) {
                if(hostToResolve != resolvedIP) {
                        this->hostname = hostToResolve;
                }
                this->gamePort = port;
                this->gameSpyPort = this->gamePort + 1;
                this->ip = resolvedIP;
                this->valid = true;
        }
        return this->valid;
}

String Address::getIP() {
        return this->ip;
}

String Address::getHostname() {
        return this->hostname;
}

bool Address::hasHostname() {
        return (this->hostname != NULL) && (this->hostname != this->ip);
}

int Address::getGamePort() {
        return this->gamePort;
}

void Address::setGamePort(int port) {
        this->gamePort = port;
}

int Address::getGameSpyPort() {
        return this->gameSpyPort;
}

bool Address::isValid() {
        return this->valid;
}

String Address::getAddress(bool name, bool gamespy) {
        if(!this->valid) { return NULL; }
        String out = ((name && (this->hostname != NULL)) ? this->hostname : this->ip);
        out += ":" + (gamespy ? IntToStr(this->gameSpyPort) : IntToStr(this->gamePort));
        return out;
}

String Address::resolveHostnameToIP(String domain) {
        String ip = NULL;
        struct in_addr addr;
        addr.s_addr = resolv(domain.c_str());
        if(addr.s_addr != INADDR_NONE) {
                ip = (String) inet_ntoa(addr);
                if(ip != "62.157.140.133" && ip != "80.156.86.78") {
                        return ip;
                }
        }
        return ip;
}

bool Address::checkIPFormat(String ip) {
        if(ip != NULL) {
                StringSplitter *sspo = new StringSplitter(ip);
                TStringList *octets = sspo->split(".");
                boolean ok = (octets->Count == 4);
                while(ok && octets->Count > 0) {
                        int item = StrToIntDef(octets->Strings[0], -1);
                        ok = (item >= 0 && item <= 255);
                        octets->Delete(0);
                }
                delete sspo;
                delete octets;
                return ok;
        }
        return false;
}
