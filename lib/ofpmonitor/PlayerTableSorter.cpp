//---------------------------------------------------------------------------


#pragma hdrstop

#include "PlayerTableSorter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


PlayerTableSorter::PlayerTableSorter() {
        this->currentColumn = PTC_NAME;
        this->normalOrder = true;
}

void PlayerTableSorter::reset() {
        this->setName();
        this->normalOrder = true;
}

void PlayerTableSorter::setProperty(PlayerTableColumn ptc) {
        if(this->currentColumn == ptc) {
                this->normalOrder = !this->normalOrder;
        } else {
                this->currentColumn = ptc;
                this->normalOrder = true;
        }
}
void PlayerTableSorter::setName() {
        this->setProperty(PTC_NAME);
}

void PlayerTableSorter::setScore() {
        this->setProperty(PTC_SCORE);
}

void PlayerTableSorter::setDeaths() {
        this->setProperty(PTC_DEATHS);
}

void PlayerTableSorter::setTeam() {
        this->setProperty(PTC_TEAM);
}

bool PlayerTableSorter::isNameSet() {
        return this->currentColumn == PTC_NAME;
}

bool PlayerTableSorter::isScoreSet() {
        return this->currentColumn == PTC_SCORE;
}

bool PlayerTableSorter::isDeathsSet() {
        return this->currentColumn == PTC_DEATHS;
}

bool PlayerTableSorter::isTeamSet() {
        return this->currentColumn == PTC_TEAM;
}

bool PlayerTableSorter::isNormalOrder() {
        return this->normalOrder;
}
