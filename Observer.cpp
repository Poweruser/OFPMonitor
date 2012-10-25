//---------------------------------------------------------------------------


#pragma hdrstop

#include "Observer.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Observable::Observable() {
        this->observers = new TList;
}

Observable::~Observable() {
        this->observers->Clear();
        delete this->observers;
}

void Observable::NotifyObserver() {
        for(int i = 0; i < this->observers->Count; i++) {
                Observer *obs = (Observer*)(this->observers->Items[i]);
                if(obs != NULL) {
                       obs->update(this);
                }
        }
}

void Observable::SetObserver(Observer *o) {
        if(this->observers->IndexOf(o) < 0) {
                this->observers->Add(o);
        }
}

void Observable::RemoveObserver(Observer *o) {
        this->observers->Remove(o);
}

