//---------------------------------------------------------------------------


#pragma hdrstop

// For in_addr struct.
#include "Form_Settings.h"
#include "Form_Update.h"

#include "ServerList.h"
#include "ConfigReader.h"
#include "StringSplitter.h"
#include <list.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
unsigned long resolv(char *host);


ServerList::ServerList() {
        this->serverIDCounter = 0;
        this->list = new TStringList;
        this->list->Sorted = true;
        this->list->Duplicates = dupIgnore;
}

ServerList::~ServerList() {
        while(this->list->Count > 0) {
                Server *svr = this->getServer(0);
                if(svr != NULL) {
                        delete svr;
                }
                this->list->Delete(0);
        }
}

bool ServerList::hasServer(String address) {
        int index;
        if(this->list->Find(address, index)) {
                return true;
        }
        return false;
}

Server* ServerList::getServer(String address) {
        int index = -1;
        if(this->list->Find(address, index)) {
                return this->getServer(index);
        }
        return NULL;
}

Server* ServerList::getServer(int index) {
        Server *srv = NULL;
        if(index >= 0 && index < this->list->Count) {
                srv = (Server*)(this->list->Objects[index]);
        }
        return srv;
}

Server* ServerList::getServerByID(int serverID) {
        for(int i = 0; i < this->list->Count && serverID >= 0; i++) {
                Server *svr = this->getServer(i);
                if(svr->getServerID() == serverID) {
                        return svr;
                }
        }
        return NULL;
}

bool ServerList::addServer(ServerConfigEntry entry) {
        Address add = this->checkAddressValid(entry.address);
        if(add.isValid() && !this->hasServer(add.getAddress())) {
                int id = this->serverIDCounter++;
                this->list->AddObject(add.getAddress(), (TObject*)(new Server(id, add.getIP(), add.getPort(), entry)));
                return true;
        }
        return false;
}

bool ServerList::addServer(ServerConfigEntry entry, String domainName) {
        Address add = this->checkAddressValid(entry.address);
        if(add.isValid() && !this->hasServer(add.getAddress())) {
                int id = this->serverIDCounter++;
                this->list->AddObject(add.getAddress(), (TObject*)(new Server(id, add.getIP(), add.getPort(), entry, true, domainName)));
                return true;
        }
        return false;
}

bool ServerList::addServer(String address, String domainName, bool isDomainName) {
	if(!isDomainName)
		return ServerList::addServer(address);

	Address add = this->checkAddressValid(address);
	if(add.isValid() && !this->hasServer(domainName) ) {
		int id = this->serverIDCounter++;
		this->list->AddObject(add.getAddress(), (TObject*)(new Server(id, add.getIP(), add.getPort(), true, domainName)));
		return true;
	}
	return false;
}

bool ServerList::addServer(String address) {
        Address add = this->checkAddressValid(address);
        if(add.isValid() && !this->hasServer(add.getAddress())) {
                int id = this->serverIDCounter++;
                this->list->AddObject(add.getAddress(), (TObject*)(new Server(id, add.getIP(), add.getPort())));
                return true;
        }
        return false;
}

bool ServerList::removeServer(String address) {
        int index = -1;
        if(this->list->Find(address, index)) {
                Server *svr = this->getServer(index);
                this->list->Delete(index);
                if(svr != NULL) {
                        delete svr;
                }
                return true;
        }
        return false;
}

void ServerList::removeOfflineServers() {
        for(int i = 0; i < this->list->Count; i++) {
                Server *srv = this->getServer(i);
                if(srv != NULL) {
                        if(!srv->isOnline() && !srv->isPersistent()) {
                                this->removeServer(srv->getGamespyAddress());
                                i--;
                        }
                }
        }
}
Address ServerList::checkAddressValid(String address) {
        Address add;
        add.readAddress(address, 2303, true);
        return add;
}

Server* ServerList::findPlayerOnServer(String playerName, bool exactMatch) {
        for(int i = 0; i < this->list->Count; i++) {
                Server *svr = this->getServer(i);
                if(svr != NULL) {
                        if(svr->isPlayerOnServer(playerName, exactMatch)) {
                                return svr;
                        }
                }
        }
        return NULL;
}

bool ServerList::incomingMessage(Message *msg) {
        String ident = msg->getAddress();
        Server *svr = this->getServer(ident);
        if(svr != NULL) {
                return (svr->processUpdate(msg));
        }
        return false;
}

void ServerList::createQueryRequests(std::list<QueryRequest*> &queryList, BandwidthUsage bU) {
        for(int i = 0; i < this->list->Count; i++) {
                Server *svr = this->getServer(i);
                if(svr != NULL) {
                        queryList.push_back(new QueryRequest(svr->getServerID(), svr->decideQuery(bU)));
                }
        }
}

int ServerList::getServerCount() {
        return this->list->Count;
}

void ServerList::readSettings(TStringList *file) {
        std::list<String> serverList;
        ConfigSection *servers = new ConfigSection("Servers");
        servers->add(new ConfigEntry("", dtServerItem, (void*)(&serverList)));
        servers->scan(file, 0);
        delete servers;
        while(serverList.size() > 0) {
                String s = serverList.front();
                if(s.Length() > 8) {
                        StringSplitter ssp(s);
                        TStringList *res = ssp.split(";");
						
						// int char_index = (res->Strings[0]).Pos("|");
						// if(char_index >= 0) {
							// String domainName = (res->Strings[0]).SubString(char_index, (res->Strings[0]).Length());
						
                        StringSplitter ssp_2(res->Strings[0]);
                        TStringList *domainNameCheck = ssp_2.split("|");
						if(domainNameCheck->Count > 1) {
							
							
							ServerConfigEntry sI( this->getIPFromDomainName(domainNameCheck->Strings[1]) );
							// ServerConfigEntry sI( this->getIPFromDomainName(domainName) );
							if(res->Count > 1) {
									String att = res->Strings[1];
									sI.watch = (att.AnsiPos("W") > 0);
									sI.favorite = (att.AnsiPos("F") > 0);
									sI.persistent = (att.AnsiPos("P") > 0);
									sI.blocked = (att.AnsiPos("B") > 0);
							}
							delete res;
							// this->addServer(sI, domainName);
							this->addServer(sI, (domainNameCheck->Strings[1]));
						} else {
							ServerConfigEntry sI(res->Strings[0]);
							if(res->Count > 1) {
									String att = res->Strings[1];
									sI.watch = (att.AnsiPos("W") > 0);
									sI.favorite = (att.AnsiPos("F") > 0);
									sI.persistent = (att.AnsiPos("P") > 0);
									sI.blocked = (att.AnsiPos("B") > 0);
							}
							delete res;
							this->addServer(sI);
						}
						delete domainNameCheck;
                }
                serverList.pop_front();
        }
}

void ServerList::getSettingsFileEntry(TStringList *settings) {
        if(this->list->Count > 0) {
                settings->Add("[Servers]");
                for(int i = 0; i < this->list->Count; i++) {
                        Server *svr = this->getServer(i);
                        if(svr != NULL) {
                                settings->Add(svr->createSettingsFileEntry());
                        }
                }
                settings->Add("[\\Servers]");
        }
}
String ServerList::getIPFromDomainName(String domainName) {
    int defaultGameport = 2302;
    Address *add = new Address();
	int success = false;
	struct in_addr addr;
	StringSplitter ssp(domainName);
	TStringList *url = ssp.split(":");
	if(url->Count == 1) {
			url->Add(IntToStr(defaultGameport));
	}
	String ip = url->Strings[0];
	addr.s_addr = resolv(ip.c_str());
	if(addr.s_addr != INADDR_NONE) {
		ip = inet_ntoa(addr);
		if(ip != "62.157.140.133" && ip != "80.156.86.78") {
				success = true;
		}
	}
	if(success && add->readAddress(ip + ":" + url->Strings[1], defaultGameport, false))
		return add->getAddress();
	else
		return String("12.34.567.890:2302");
};


