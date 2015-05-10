//---------------------------------------------------------------------------


#pragma hdrstop

#include "StatusChange.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

StatusChange::StatusChange(String address, int oldStatus, int currentStatus) {
        this->serverAddress = address;
        this->oldStatus = oldStatus;
        this->currentStatus = currentStatus;
}

String StatusChange::getServerAddress() {
        return this->serverAddress;
}

int StatusChange::getOldStatus() {
        return this->oldStatus;
}

int StatusChange::getCurrentStatus() {
        return this->currentStatus;
}


