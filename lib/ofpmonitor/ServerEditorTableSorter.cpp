//---------------------------------------------------------------------------


#pragma hdrstop

#include "ServerEditorTableSorter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ServerEditorTableSorter::ServerEditorTableSorter() {
        this->currentColumn = SETC_ID;
        this->normalOrder = true;
}

void ServerEditorTableSorter::reset() {
        this->setID();
        this->normalOrder = true;
}

void ServerEditorTableSorter::setID() {
        this->setProperty(SETC_ID);
}

void ServerEditorTableSorter::setIP() {
        this->setProperty(SETC_IP);
}

void ServerEditorTableSorter::setName() {
        this->setProperty(SETC_NAME);
}

void ServerEditorTableSorter::setFavorites() {
        this->setProperty(SETC_FAVORITES);
}

void ServerEditorTableSorter::setWatched() {
        this->setProperty(SETC_WATCHED);
}

void ServerEditorTableSorter::setPersistent() {
        this->setProperty(SETC_PERSISTENT);
}

void ServerEditorTableSorter::setBlocked() {
        this->setProperty(SETC_BLOCKED);
}

bool ServerEditorTableSorter::isNameSet() {
        return this->currentColumn == SETC_NAME;
}

bool ServerEditorTableSorter::isIDSet() {
        return this->currentColumn == SETC_ID;
}

bool ServerEditorTableSorter::isIPSet() {
        return this->currentColumn == SETC_IP;
}

bool ServerEditorTableSorter::isFavoritesSet() {
        return this->currentColumn == SETC_FAVORITES;
}

bool ServerEditorTableSorter::isWatchedSet() {
        return this->currentColumn == SETC_WATCHED;
}

bool ServerEditorTableSorter::isPersistentSet() {
        return this->currentColumn == SETC_PERSISTENT;
}

bool ServerEditorTableSorter::isBlockedSet() {
        return this->currentColumn == SETC_BLOCKED;
}

bool ServerEditorTableSorter::isNormalOrder() {
        return this->normalOrder;
}

void ServerEditorTableSorter::setProperty(ServerEditorTableColumn setc) {
        if(this->currentColumn == setc) {
                this->normalOrder = !this->normalOrder;
        } else {
                this->currentColumn = setc;
                this->normalOrder = !(setc == SETC_FAVORITES ||
                                      setc == SETC_WATCHED ||
                                      setc == SETC_PERSISTENT ||
                                      setc == SETC_BLOCKED);
        }
}

