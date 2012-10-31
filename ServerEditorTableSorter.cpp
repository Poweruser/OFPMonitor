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

bool ServerEditorTableSorter::isNameSet() {
        return this->currentColumn == SETC_NAME;
}

bool ServerEditorTableSorter::isIDSet() {
        return this->currentColumn == SETC_ID;
}

bool ServerEditorTableSorter::isIPSet() {
        return this->currentColumn == SETC_IP;
}

bool ServerEditorTableSorter::isNormalOrder() {
        return this->normalOrder;
}

void ServerEditorTableSorter::setProperty(ServerEditorTableColumn setc) {
        if(this->currentColumn == setc) {
                this->normalOrder = !this->normalOrder;
        } else {
                this->currentColumn = setc;
                this->normalOrder = true;
        }
}

