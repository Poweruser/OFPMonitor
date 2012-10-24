//---------------------------------------------------------------------------


#pragma hdrstop

#include "Observer.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Observable::Observable() {
        this->observer = NULL;
}

void Observable::NotifyObserver() {
        if(this->observer != NULL) {
                this->observer->update(this);
        }
}

void Observable::SetObserver(Observer *o) {
        observer = o;
}

