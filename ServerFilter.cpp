//---------------------------------------------------------------------------


#pragma hdrstop

#include "ServerFilter.h"
#include "ConfigReader.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


ServerFilter::ServerFilter() {
        this->creating = true;
        this->waiting = true;
        this->settingup = true;
        this->briefing = true;
        this->playing = true;
        this->debriefing = true;
        this->withPassword = true;
        this->withoutPassword = true;
        this->missionNames = new TStringList;
        this->serverNames = new TStringList;
        this->playerNames = new TStringList;
        this->minPlayers = 0;
        this->maxPlayers = 0;
}

ServerFilter::ServerFilter(TStringList *missions, TStringList *servers, TStringList *players) {
        this->creating = true;
        this->waiting = true;
        this->settingup = true;
        this->briefing = true;
        this->playing = true;
        this->debriefing = true;
        this->withPassword = true;
        this->withoutPassword = true;
        this->missionNames = missions;
        this->serverNames = servers;
        this->playerNames = players;
        this->minPlayers = 0;
        this->maxPlayers = 0;
}

ServerFilter::~ServerFilter() {
        delete (this->missionNames);
        delete (this->serverNames);
        delete (this->playerNames);
}

void ServerFilter::setMissionName(String mission) {
        this->missionNames->Clear();
        if(!mission.IsEmpty()) {
                this->missionNames->Add(mission);
        }
}

void ServerFilter::setPlayerName(String player) {
        this->playerNames->Clear();
        if(!player.IsEmpty()) {
                this->playerNames->Add(player);
        }
}

void ServerFilter::setServerName(String server) {
        this->serverNames->Clear();
        if(!server.IsEmpty()) {
                this->serverNames->Add(server);
        }
}

String ServerFilter::getMissionName() {
        if(this->missionNames->Count > 0) {
                return this->missionNames->Strings[0];
        }
        return "";
}

String ServerFilter::getPlayerName() {
        if(this->playerNames->Count > 0) {
                return this->playerNames->Strings[0];
        }
        return "";
}

String ServerFilter::getServerName() {
        if(this->serverNames->Count > 0) {
                return this->serverNames->Strings[0];
        }
        return "";
}

void ServerFilter::readSettings(TStringList *file) {
        String server="", mission="", player="";
        ConfigSection *filters = new ConfigSection("Filters");
        filters->add(new ConfigEntry("Playing", dtBool, (void*)(&(this->playing))));
        filters->add(new ConfigEntry("Waiting", dtBool, (void*)(&(this->waiting))));
        filters->add(new ConfigEntry("Creating", dtBool, (void*)(&(this->creating))));
        filters->add(new ConfigEntry("Settingup", dtBool, (void*)(&(this->settingup))));
        filters->add(new ConfigEntry("Briefing", dtBool, (void*)(&(this->briefing))));
        filters->add(new ConfigEntry("Debriefing", dtBool, (void*)(&(this->debriefing))));
        filters->add(new ConfigEntry("WithPW", dtBool, (void*)(&(this->withPassword))));
        filters->add(new ConfigEntry("WithoutPW", dtBool, (void*)(&(this->withoutPassword))));
        filters->add(new ConfigEntry("minPlayers", dtInt, (void*)(&(this->minPlayers))));
        filters->add(new ConfigEntry("ServerName", dtString, (void*)(&server)));
        filters->add(new ConfigEntry("MissionName", dtString, (void*)(&mission)));
        filters->add(new ConfigEntry("PlayerName", dtString, (void*)(&player)));
        int i = filters->scan(file, 0);
        delete filters;
        if(i < file->Count) {
                if(!mission.Trim().IsEmpty()) {
                        this->missionNames->Add(mission);
                }
                if(!server.Trim().IsEmpty()) {
                        this->serverNames->Add(server);
                }
                if(!player.Trim().IsEmpty()) {
                        this->playerNames->Add(player);
                }
        }
        this->guiUpdate = true;
}

bool ServerFilter::guiNeedsUpdate() {
        if(this->guiUpdate) {
                this->guiUpdate = false;
                return true;
        }
        return false;
}

bool ServerFilter::testMissionName(String mission) {
        if(this->missionNames->Count == 0) { return true; }
        for(int i = 0; i < this->missionNames->Count; i++) {
                if(mission.LowerCase().Pos(this->missionNames->Strings[i].LowerCase()) > 0) {
                        return true;
                }
        }
        return false;
}
bool ServerFilter::testServerName(String server) {
        if(this->serverNames->Count == 0) { return true; }
        for(int i = 0; i < this->serverNames->Count; i++) {
                if(server.LowerCase().Pos(this->serverNames->Strings[i].LowerCase()) > 0) {
                        return true;
                }
        }
        return false;
}

void ServerFilter::setMinPlayers(int num) {
        if(num < 0) {
                this->minPlayers = 0;
        } else {
                this->minPlayers = num;
        }
}

void ServerFilter::setMaxPlayers(int num) {
        if(num < 0) {
                this->maxPlayers = 0;
        } else {
                this->maxPlayers = num;
        }
}


int ServerFilter::getBinaryStatusFilter() {
        int filters = 0;
        if(this->creating) { filters++; }
        filters = filters << 1;
        if(this->waiting) { filters++; }
        filters = filters << 1;
        if(this->settingup) { filters++; }
        filters = filters << 1;
        if(this->briefing) { filters++; }
        filters = filters << 1;
        if(this->playing) { filters++; }
        filters = filters << 1;
        if(this->debriefing) { filters++; }
        filters = filters << 1;
        if(this->withPassword) { filters++; }
        filters = filters << 1;
        if(this->withoutPassword) { filters++; }
        return filters;
}

void ServerFilter::parseBinaryStatusFilter(int filters) {
        this->withoutPassword = filters & 1;
        filters = filters >> 1;
        this->withPassword = filters & 1;
        filters = filters >> 1;
        this->debriefing = filters & 1;
        filters = filters >> 1;
        this->playing = filters & 1;
        filters = filters >> 1;
        this->briefing = filters & 1;
        filters = filters >> 1;
        this->settingup = filters & 1;
        filters = filters >> 1;
        this->waiting = filters & 1;
        filters = filters >> 1;
        this->creating = filters & 1;
}

String ServerFilter::concatenateFilter(TStringList *list, String splitter) {
        String out = "";
        for(int i = 0; i < list->Count; i++) {
                out += list->Strings[i];
                if(list->Count > i+1) {
                        out += splitter;
                }
        }
        return out;
}

void ServerFilter::getSettingsFileEntry(TStringList *settings) {
        settings->Add("[Filters]");
        settings->Add("Playing = " + IntToStr(this->playing));
        settings->Add("Waiting= " + IntToStr(this->waiting));
        settings->Add("Creating = " + IntToStr(this->creating));
        settings->Add("Settingup = " + IntToStr(this->settingup));
        settings->Add("Briefing = " + IntToStr(this->briefing));
        settings->Add("Debriefing = " + IntToStr(this->debriefing));
        settings->Add("WithPW = " + IntToStr(this->withPassword));
        settings->Add("WithoutPW = " + IntToStr(this->withoutPassword));
        settings->Add("minPlayers = " + IntToStr(this->minPlayers));
        settings->Add("ServerName = " + this->getServerName());
        settings->Add("MissionName = " + this->getMissionName());
        settings->Add("PlayerName = " + this->getPlayerName());
        settings->Add("[\\Filters]");
}
