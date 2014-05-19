//---------------------------------------------------------------------------


#pragma hdrstop

#include "Server.h"
#include <mmsystem.h>
#include "StringSplitter.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

ServerConfigEntry::ServerConfigEntry() {
        this->address = "";
        this->watch = false;
        this->favorite = false;
        this->persistent = false;
        this->blocked = false;
        this->gamestate = 0;
        this->gametime = 0;
        this->autojoin = false;
        this->autojoinConf = "";
}

ServerConfigEntry::ServerConfigEntry(String address) {
        this->address = address;
        this->watch = false;
        this->favorite = false;
        this->persistent = false;
        this->blocked = false;
        this->gamestate = 0;
        this->gametime = 0;
        this->autojoin = false;
        this->autojoinConf = "";
}

__fastcall Server::Server(int serverID, String ip, int port) {
        this->watch = false;
        this->favorite = false;
        this->persistent = false;
        this->blocked = false;
        this->clear();
        this->serverID = serverID;
        this->ip = ip;
        this->timeouts = 0;
        this->ping = 0;
        this->gamespyport = port;
}

__fastcall Server::Server(int serverID, String ip, int port, ServerConfigEntry entry) {
        this->watch = entry.watch;
        this->favorite = entry.favorite;
        this->persistent = entry.persistent;
        this->blocked = entry.blocked;
        this->clear();
        this->serverID = serverID;
        this->ip = ip;
        this->timeouts = 0;
        this->ping = 0;
        this->gamespyport = port;
}

void Server::clear() {
        this->online = false;
        this->autojoin = false;
        this->autojoinConf = "";
        this->gameport = 0;
        this->timeleft = "";
        this->gametime = 0;
        this->players = 0;
        for(int i = 0; i < 30; i++) {
                if(this->playerArray[i] != NULL) {
                        delete (this->playerArray[i]);
                        this->playerArray[i] = NULL;
                }
        }
        this->playersInArray = 0;
        this->maxplayers = 0;
        this->mission = "";
        this->name = "";
        this->gamestate = 0;
        this->impl = "";
        this->param1 = "";
        this->param2 = "";
        this->island = "";
        this->actver = 0;
        this->reqver = 0;
        this->platform = "";
        this->password = -1;
        this->mod = "";
        this->equalMod = 0;
        this->messageSent = 0;
        this->queryid = 0;
        this->missedQueryTurns = 1;
        this->emptyServerCounter = 0;
        this->selectedToDisplay = false;
        this->dontTrustNumPlayers = false;
}

__fastcall Server::~Server() {
        for(int i = 0; i < 30; i++) {
                if(this->playerArray[i] != NULL) {
                        delete (this->playerArray[i]);
                        this->playerArray[i] = NULL;
                }
        }
        while(this->statusChanges.size() > 0) {
                StatusChange *sc = this->statusChanges.front();
                this->statusChanges.pop_front();
                delete sc;
        }
}

String Server::getIP() {
        return this->ip;
}

String Server::getAddress() {
        String out = this->ip + ":";
        if(this->gameport > 0) {
                out += IntToStr(this->gameport);
        } else {
                out += IntToStr(this->gamespyport - 1);
        }
        return out;
}

String Server::getGamespyAddress() {
        return (this->ip + ":" + IntToStr(this->gamespyport));
}

int Server::getGamespyPort() {
        return this->gamespyport;
}

ServerConfigEntry* Server::createServerConfigEntry() {
        ServerConfigEntry *sI = new ServerConfigEntry(this->getGamespyAddress());
        sI->watch = this->watch;
        sI->favorite = this->favorite;
        sI->persistent = this->persistent;
        sI->blocked = this->blocked;
        sI->gamestate = this->gamestate;
        sI->gametime = this->gametime;
        sI->autojoin = this->autojoin;
        sI->autojoinConf = this->autojoinConf;
        return sI;
}

bool Server::isPlayerOnServer(String playerName, bool exactMatch) {
        bool found = false;
        for(int i = 0; i < this->playersInArray; i++) {
                String name = this->playerArray[i]->getName().LowerCase();
                if((exactMatch && playerName.LowerCase() == name) ||
                   (!exactMatch && name.Pos(playerName.LowerCase()))) {
                        found = true;
                        break;
                }
        }
        return found;
}

bool Server::processUpdate(Message *msg) {
        if(msg->getIP() != this->ip || msg->getPort() != this->gamespyport) { return false; }
        if(this->parseMessageToQueryAnswer(msg)) {
                this->parseQueryAnswers();
                if(this->messageSent > 1) {
                        this->ping = msg->getTimeOfArrival() - this->messageSent;
                        this->messageSent = 1;
                        this->timeouts = 0;
                        this->online = true;
                }
                if(this->players > 0) {
                        this->emptyServerCounter = 0;
                } else {
                        this->emptyServerCounter++;
                }
        } else {
                // not a queryAnswer or currupted
        }
        return true;
}

String Server::decideQuery(BandwidthUsage bu) {
        String full = "\\info\\rules\\players\\";
        String part = "\\info\\rules\\";
        String none = "";
        bool someplayers = (this->players > 0);
        int missLimit = 1;
        if(this->selectedToDisplay || this->messageSent == 0) {
                return full;
        }
        if(this->isBlocked()) {
                return none;
        }
        switch(bu) {
                case Moderate:
                        if(someplayers) {
                                return full;
                        } else if(this->missedQueryTurns >= missLimit) {
                                return part;
                        }
                        break;
                case VeryLow:
                        missLimit = this->emptyServerCounter > 5 ? 5 : this->emptyServerCounter;
                case Low:
                        if(someplayers) {
                                if(this->players != this->playersInArray) {
                                        return full;
                                } else {
                                        return part;
                                }
                        } else if(this->missedQueryTurns >= missLimit) {
                                return part;
                        }
                        break;
                case High:
                        return full;
                default:
                        return full;
        }
        return none;
}

void Server::queryIsAboutToBeSent(String query, bool sendingSuccess, int timeOutLimit) {
        if(!sendingSuccess) {
                this->clear();
                return;
        }
        if(query.IsEmpty()) {
                this->missedQueryTurns += 1;
        } else {
                if(this->messageSent <= 1) {
                        this->messageSent = timeGetTime();
                } else {
                        if(this->timeouts < timeOutLimit) {
                                this->timeouts += 1;
                        } else {
                                this->clear();
                        }
                }
                this->missedQueryTurns = 0;
        }
}

bool Server::equals(Server *srv) {
        if(srv == NULL) { return false; }
        return (this->ip == srv->getIP() &&
                this->gamespyport == srv->getGamespyPort());
}

bool Server::equals(String serverAddress) {
        return (serverAddress == this->getGamespyAddress());
}

int Server::getCurrentGameState() {
        return this->gamestate;
}

int Server::getActualVersion() {
        return this->actver;
}

int Server::getRequiredVersion() {
        return this->reqver;
}

ServerFilterResult Server::checkFilter(ServerFilter *filter) {
        ServerFilterResult out = SFR_NOTPASSED;
        if(this->blocked || this->name.IsEmpty()) {
                out = SFR_OFFLINE;
        } else {
                bool maxPlayersPass = true;
                if(filter->maxPlayers > filter->minPlayers) {
                        maxPlayersPass = this->players <= filter->maxPlayers;
                }
                if(this->players >= filter->minPlayers && maxPlayersPass) {
                        if(((this->gamestate == SERVERSTATE_CREATING && filter->creating) ||
                            (this->gamestate == SERVERSTATE_WAITING && filter->waiting) ||
                            (this->gamestate == SERVERSTATE_SETTINGUP && filter->settingup) ||
                            (this->gamestate == SERVERSTATE_BRIEFING && filter->briefing) ||
                            (this->gamestate == SERVERSTATE_PLAYING && filter->playing) ||
                            (this->gamestate == SERVERSTATE_DEBRIEFING && filter->debriefing)
                           ) && (
                            (this->password == 1 && filter->withPassword) ||
                            (this->password == 0 && filter->withoutPassword)
                           )) {
                                bool missionfilter = filter->testMissionName(this->mission);
                                if(missionfilter) {
                                        bool namefilter = filter->testServerName(this->name);
                                        if(namefilter) {
                                                TStringList *playerList = this->playerArrayToStringList();
                                                bool playerfilter = filter->testPlayerName(playerList);
                                                playerList->Clear();
                                                delete playerList;
                                                if(playerfilter) {
                                                        out = SFR_PASSED;
                                                }
                                        }
                                }
                        }

                }
        }
        if(this->autojoin) {
                if(out == SFR_PASSED) {
                        out = SFR_PASSED_AUTOJOIN;
                } else if(out == SFR_NOTPASSED) {
                        out = SFR_NOTPASSED_AUTOJOIN;
                }
        }
        if(this->favorite) {
                if(out == SFR_PASSED) {
                        out = SFR_PASSED_FAVORITE;
                } else if(out == SFR_NOTPASSED) {
                        out = SFR_NOTPASSED_FAVORITE;
                }
        }
        return out;
}

int Server::compareQueryId(String queryid) {
        String own = this->queryid;
        String other = queryid;
        while(other.Length() < own.Length()) { other = "0" + other; }
        while(own.Length() < other.Length()) { own = "0" + own; }
        return AnsiCompareText(other, own);
}


bool Server::parseMessageToQueryAnswer(Message *msg) {
        String content = msg->getContent();
        StringSplitter ssp(content);
        ssp.setKeepEmptyParts(true);
        TStringList *data = ssp.split("\\");
        if(! ((data->Count > 1) && (data->Count % 2) == 0) ) {
                delete data;
                return false;
        }
        bool final = content.Pos("\\final\\") > 0;
        if(final) {
                int finalIndex = data->IndexOf("final");
                if(finalIndex + 1 < data->Count) {
                        data->Delete(finalIndex + 1);
                }
                data->Delete(finalIndex);
        }
        int queryIndex = data->IndexOf("queryid");
        if(queryIndex < 0) {
                delete data;
                return false;
        }
        String query = data->Strings[queryIndex + 1];
        if(queryIndex + 1 < data->Count) {
                data->Delete(queryIndex + 1);
        }
        data->Delete(queryIndex);
        StringSplitter sspq(query);
        String queryAnswerId = "";
        int queryAnswerPart;
        TStringList *queryIdPart = sspq.split(".");
        bool failed = false;
        if(queryIdPart->Count == 2) {
                queryAnswerId = queryIdPart->Strings[0];
                queryAnswerPart = StrToIntDef(queryIdPart->Strings[1], 0);
                if(queryAnswerPart < 1 || queryAnswerPart > 5) { failed = true; }
        } else { failed = true; }
        delete queryIdPart;
        if(failed) {
                delete data;
                return false;
        }
        if(this->compareQueryId(queryAnswerId) >= 0) {
                this->queryid = queryAnswerId;
                this->queries[queryAnswerPart - 1].id = queryAnswerId;
                this->queries[queryAnswerPart - 1].part = queryAnswerPart;
                this->queries[queryAnswerPart - 1].final = final;
                this->queries[queryAnswerPart - 1].setContent(data);
        } else {
                delete data; 
                return false;
        }
        return true;
}

bool Server::areQueriesComplete() {
        bool out = false;
        String id = this->queries[0].id;
        for(int i = 0; i < 5; i++) {
                if(id == this->queries[i].id) {
                        if(this->queries[i].final) {
                                out = true;
                                break;
                        }
                }
        }
        return out;
}

bool Server::hasStatusChanged() {
        return (this->statusChanges.size() > 0);
}

StatusChange* Server::takeStatusChange() {
        StatusChange *sc = NULL;
        if(this->hasStatusChanged()) {
                sc = this->statusChanges.front();
                this->statusChanges.pop_front();
        }
        return sc;
}

void Server::parseQueryAnswers() {
        if(!this->areQueriesComplete()) { return; }
        String id = this->queries[0].id;
        TStringList *data = new TStringList;
        TStringList *uniquePlayers = new TStringList;
        uniquePlayers->Duplicates = dupIgnore;
        for(int i = 0; i < 5; i++) {
                if(id == this->queries[i].id) {
                        this->queries[i].readContent(data);
                        if(this->queries[i].final) { break; }
                }
        }
        int playerCounter = 0;
        String all ="";
        for(int g = 0; g < data->Count; g++) {
                all += IntToStr(g) + ": " + data->Strings[g] + "\n";
        }
        bool queryContainsPlayers = (data->IndexOf("player_0") >= 0);
        String playerData[] = { "player_", "team_", "score_", "deaths_" };
        for(int j = 0; j + 1 < data->Count; j += 2) {
                String ident = data->Strings[j];
                String value = data->Strings[j+1];
                if(ident.Pos(playerData[0]) == 1) {
                        int playerDataOffset = 0;
                        String pName = "", pTeam = "";
                        int pScore = 0, pDeaths = 0;
                        for(int k = 0; k < 4; k++) {
                                playerDataOffset = 2 * k;
                                if(j + playerDataOffset + 1 < data->Count) {
                                        ident = data->Strings[j + playerDataOffset];
                                        value = data->Strings[j + playerDataOffset + 1];
                                        if(ident.Pos(playerData[k]) == 1) {
                                                switch (k) {
                                                        case 0:
                                                                pName = value;
                                                                break;
                                                        case 1:
                                                                pTeam = value;
                                                                break;
                                                        case 2:
                                                                pScore = StrToIntDef(value, 0);
                                                                break;
                                                        case 3:
                                                                pDeaths = StrToIntDef(value, 0);
                                                                break;
                                                }
                                        } else {
                                                break;
                                        }
                                }
                        }
                        j += playerDataOffset;
                        if(!(pName.IsEmpty()) && (uniquePlayers->IndexOf(pName) < 0)) {
                                if(this->playerArray[playerCounter] == NULL) {
                                        this->playerArray[playerCounter] = new Player(pName, pScore, pDeaths, pTeam);
                                } else {
                                        this->playerArray[playerCounter]->name = pName;
                                        this->playerArray[playerCounter]->score = pScore;
                                        this->playerArray[playerCounter]->deaths = pDeaths;
                                        this->playerArray[playerCounter]->team = pTeam;
                                }
                                playerCounter++;
                                uniquePlayers->Add(pName);
                        }
                } else {
                        if(ident == "hostname") {
                                this->name = value;
                        } else if(ident == "hostport") {
                                int p = StrToIntDef(value, -1);
                                if(p > -1) { this->gameport = p; }
                        } else if(ident == "mapname") {
                                this->island = value;
                        } else if(ident == "gametype") {
                                this->mission = value;
                        } else if(ident == "numplayers" && (!this->dontTrustNumPlayers || queryContainsPlayers)) {
                                int p = StrToIntDef(value, -1);
                                if(p > -1) { this->players = p; }
                        } else if(ident == "maxplayers") {
                                int mp = StrToIntDef(value, -1);
                                if(mp > -1) { this->maxplayers = mp; }
                        } else if(ident == "timeleft") {
                                this->timeleft = value;
                        } else if(ident == "param1") {
                                this->param1 = value;
                        } else if(ident == "param2") {
                                this->param2 = value;
                        } else if(ident == "actver") {
                                int av = StrToIntDef(value, -1);
                                if(av > -1) { this->actver = av; }
                        } else if(ident == "reqver") {
                                int rv = StrToIntDef(value, -1);
                                if(rv > -1) { this->reqver = rv; }
                        } else if(ident == "mod") {
                                String m = value;
                                if(m.SubString(1,3) == "RES") {
                                        m = m.SubString(4, m.Length() - 3);
                                }
                                if(m.SubString(1,1) == ";") {
                                        m = m.SubString(2, m.Length() - 1);
                                }
                                this->mod = m;
                        } else if(ident == "equalModRequired") {
                                int emr = StrToIntDef(value, -1);
                                if(emr > -1 && emr <= 1) { this->equalMod = emr; }
                        } else if(ident == "password") {
                                int pw = StrToIntDef(value, -1);
                                if(pw > -1 && pw <= 1) { this->password = pw; }
                        } else if(ident == "gstate") {
                                int oldStatus = this->gamestate;
                                int newStatus = StrToIntDef(value, 0);
                                this->gamestate = newStatus;
                                if(newStatus > 0) {
                                        if(oldStatus != newStatus) {
                                                if(   ((oldStatus == SERVERSTATE_WAITING   ||
                                                        oldStatus == SERVERSTATE_SETTINGUP ||
                                                        oldStatus == SERVERSTATE_BRIEFING) &&
                                                        newStatus == SERVERSTATE_PLAYING)  ||

                                                      ((oldStatus == SERVERSTATE_WAITING   ||
                                                        oldStatus == SERVERSTATE_SETTINGUP) &&
                                                        newStatus == SERVERSTATE_BRIEFING) ||

                                                      ((oldStatus != SERVERSTATE_WAITING) &&
                                                        newStatus == SERVERSTATE_WAITING) ||

                                                      ((oldStatus == SERVERSTATE_PLAYING) &&
                                                        newStatus == SERVERSTATE_DEBRIEFING)) {
                                                        this->gametime = time(0);
                                                } else {
                                                        this->gametime = 0;
                                                }
                                                this->statusChanges.push_back(new StatusChange(this->getGamespyAddress(), oldStatus, newStatus));        
                                        }
                                }
                        } else if(ident == "platform") {
                                this->platform = value;
                        } else if(ident == "impl") {
                                this->impl = value;
                        }
                }
        }
        delete data;
        int uP = uniquePlayers->Count;
        if(uP < this->players && uP > 0 && uP < 20) {
                this->players = uniquePlayers->Count;
                this->dontTrustNumPlayers = true;
        } else if(queryContainsPlayers) {
                this->dontTrustNumPlayers = false;
        }
        delete uniquePlayers;
        if(playerCounter > 0 || this->players == 0) {
                this->playersInArray = playerCounter;
                for(int i = playerCounter; i < 30; i++) {
                        if(this->playerArray[i] != NULL) {
                                delete (this->playerArray[i]);
                                this->playerArray[i] = NULL;
                        } else {
                                break;
                        }
                }
        }
}

String Server::getIsland() {
        return this->island;
}

String Server::getMission() {
        return this->mission;
}

int Server::getPing() {
        return this->ping;
}

String Server::getName() {
        return this->name;
}

int Server::getServerID() {
        return this->serverID;
}

int Server::getPlayerNum() {
        return this->players;
}

int Server::getPlayerNumOfPlayerList() {
        return this->playersInArray;
}

int Server::getMaxPlayerNum() {
        return this->maxplayers;
}

bool Server::isOnline() {
        return this->online;
}

bool Server::hasTimedOut() {
        return this->timeouts > 0;
}

Player* Server::getPlayer(int index) {
        if(index < 0 || index + 1 > this->playersInArray) {
                return NULL;
        } else {
                return this->playerArray[index];
        }
}

int Server::getGamePort() {
        return this->gameport;
}

String Server::getPlatform() {
        return this->platform;
}

bool Server::hasPassword() {
        return (this->password > 0);
}

bool Server::requiresEqualMod() {
        return (this->equalMod > 0);
}

bool Server::isFavorite() {
        return this->favorite;
}

bool Server::isAutoJoin() {
        return this->autojoin;
}

bool Server::isPersistent() {
        return this->persistent;
}

bool Server::isBlocked() {
        return this->blocked;
}

int Server::getGameState() {
        return this->gamestate;
}

void Server::setAutoJoin(bool active, String startUpLine) {
        this->autojoin = active;
        if(!active) {
                this->autojoinConf = "";
        } else {
                this->autojoinConf = startUpLine;
        }
}

bool Server::isWatched() {
        return this->watch;
}

void Server::setWatched(bool active) {
        this->watch = active;
}

bool Server::isStatePlaying() {
        return this->gamestate == SERVERSTATE_PLAYING;
}

String Server::getMod() {
        return this->mod;
}

bool Server::hasMods() {
        return !this->mod.Trim().IsEmpty();
}

bool Server::doesModMatch(String mod) {
        return (AnsiCompareText(this->mod, mod) == 0);
}

void Server::setFavorite(bool active) {
        this->favorite = active;
}

void Server::setPersistent(bool active) {
        this->persistent = active;
}

void Server::setBlocked(bool active) {
        this->blocked = active;
}

long Server::getStatusTime() {
        return this->gametime;
}

String Server::createSettingsFileEntry() {
        String entry = this->getGamespyAddress();
        String att = "";
        if(this->isWatched()) { att += "W"; }
        if(this->isFavorite()) { att += "F"; }
        if(this->isPersistent()) { att += "P"; }
        if(this->isBlocked()) { att += "B"; }
        if(!att.IsEmpty()) { entry += ";" + att; }
        return entry;
}

void Server::setSelectedToDisplay(bool active) {
        this->selectedToDisplay = active;
}

TStringList* Server::playerArrayToStringList() {
        TStringList *out = new TStringList;
        for(int i = 0; i < this->playersInArray && i < 30; i++) {
                if(this->playerArray[i] != NULL) {
                        out->Add(this->playerArray[i]->getName());
                }
        }
        return out;
}

String Server::getAutoJoinConf() {
        return this->autojoinConf;
}





