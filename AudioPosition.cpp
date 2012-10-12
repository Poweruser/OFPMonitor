//---------------------------------------------------------------------------


#pragma hdrstop

#include "AudioPosition.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AudioPosition::AudioPosition(int position) {
        this->position = position;
        if(position <= 0) {
                this->milli = 0;
                this->sec = 0;
                this->min = 0;
        } else {
                this->milli = position % 1000;
                this->sec =((position - this->milli)/1000) % 60;
                this->min = (((position - this->milli)/1000) - this->sec) / 60;
        }
}

int AudioPosition::getMilliSeconds() {
        return (this->milli);
}

int AudioPosition::getSeconds() {
        return (this->sec);
}

int AudioPosition::getMinutes() {
        return (this->min);
}

int AudioPosition::getPosition() {
        return this->position;
}
