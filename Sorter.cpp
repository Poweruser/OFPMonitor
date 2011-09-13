//---------------------------------------------------------------------------


#pragma hdrstop

#include "Sorter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ServerSorter::ServerSorter() {
        this->disableAll();
        this->setPlayers();
        this->normal = false;
}

void ServerSorter::reset() {
        this->disableAll();
        this->setPlayers();
        this->normal = false;
}

void ServerSorter::disableAll() {
        id = false;
        name = false;
        players = false;
        ping = false;
        status = false;
        island = false;
        mission = false;
        normal = true;
}

void ServerSorter::setId() {
        if(id) {
                normal = !normal;
        } else {
                disableAll();
                id = true;
        }
}

void ServerSorter::setName() {
        if(name) {
                normal = !normal;
        } else {
                disableAll();
                name = true;
        }
}

void ServerSorter::setPlayers() {
        if(players) {
                normal = !normal;
        } else {
                disableAll();
                players = true;
        }
}

void ServerSorter::setStatus() {
        if(status) {
                normal = !normal;
        } else {
                disableAll();
                status = true;
        }
}

void ServerSorter::setIsland() {
        if(island) {
                normal = !normal;
        } else {
                disableAll();
                island = true;
        }
}

void ServerSorter::setMission() {
        if(mission) {
                normal = !normal;
        } else {
                disableAll();
                mission = true;
        }
}

void ServerSorter::setPing() {
        if(ping) {
                normal = !normal;
        } else {
                disableAll();
                ping = true;
        }
}

PlayerSorter::PlayerSorter() {
        disableAll();
        setName();
}


void PlayerSorter::disableAll() {
        normal = true;
        name = false;
        score = false;
        deaths = false;
        team = false;
}

void PlayerSorter::setName() {
        if(name) {
                normal = !normal;
        } else {
                disableAll();
                name = true;
        }
}

void PlayerSorter::setScore() {
        if(score) {
                normal = !normal;
        } else {
                disableAll();
                score = true;
        }
}

void PlayerSorter::setDeaths() {
        if(deaths) {
                normal = !normal;
        } else {
                disableAll();
                deaths = true;
        }
}

void PlayerSorter::setTeam() {
        if(team) {
                normal = !normal;
        } else {
                disableAll();
                team = true;
        }
}
