//---------------------------------------------------------------------------


#pragma hdrstop

#include "Player.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Player::Player() {
        this->clear();
}

Player::Player(String name, int score, int deaths, String team) {
        this->name = name;
        this->score = score;
        this->deaths = deaths;
        this->team = team;
}

void Player::clear() {
        this->deaths = 0;
        this->score = 0;
        this->team = "";
        this->name = "";
}

String Player::getName() {
        return this->name;
}
int Player::getScore() {
        return this->score;
}

int Player::getDeaths() {
        return this->deaths;
}

String Player::getTeam() {
        return this->team;
}


