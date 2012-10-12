//---------------------------------------------------------------------------


#pragma hdrstop

#include "ServerTableSorter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


ServerTableSorter::ServerTableSorter() {
        this->currentColumn = STC_PLAYERS;
        this->normalOrder = false;
}

void ServerTableSorter::reset() {
        this->setPlayers();
        this->normalOrder = false;
}

void ServerTableSorter::setProperty(ServerTableColumn stc) {
        if(this->currentColumn == stc) {
                this->normalOrder = !this->normalOrder;
        } else {
                this->currentColumn = stc;
                this->normalOrder = true;
        }
}

void ServerTableSorter::setId() {
        this->setProperty(STC_ID);
}

void ServerTableSorter::setName() {
        this->setProperty(STC_NAME);
}

void ServerTableSorter::setPlayers() {
        this->setProperty(STC_PLAYERS);
}

void ServerTableSorter::setStatus() {
        this->setProperty(STC_STATE);
}

void ServerTableSorter::setIsland() {
        this->setProperty(STC_ISLAND);
}

void ServerTableSorter::setMission() {
        this->setProperty(STC_MISSION);
}

void ServerTableSorter::setPing() {
        this->setProperty(STC_PING);
}

bool ServerTableSorter::isIdSet() {
        return (this->currentColumn == STC_ID);
}

bool ServerTableSorter::isNameSet() {
        return (this->currentColumn == STC_NAME);
}

bool ServerTableSorter::isPlayersSet() {
        return (this->currentColumn == STC_PLAYERS);
}

bool ServerTableSorter::isStatusSet() {
        return (this->currentColumn == STC_STATE);
}

bool ServerTableSorter::isIslandSet() {
        return (this->currentColumn == STC_ISLAND);
}

bool ServerTableSorter::isMissionSet() {
        return (this->currentColumn == STC_MISSION);
}

bool ServerTableSorter::isPingSet() {
        return (this->currentColumn == STC_PING);
}

bool ServerTableSorter::isNormalOrder() {
        return this->normalOrder;
}
