//---------------------------------------------------------------------------
#pragma hdrstop
#include "QueryAnswer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

QueryAnswer::QueryAnswer () {
        this->clear();
}

void QueryAnswer::clear() {
        this->id = "";
        this->part = "";
        this->final = false;
        this->content.clear();
}

