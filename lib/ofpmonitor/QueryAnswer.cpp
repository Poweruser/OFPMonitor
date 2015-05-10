//---------------------------------------------------------------------------
#pragma hdrstop
#include "QueryAnswer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

QueryAnswer::QueryAnswer () {
        this->id = "";
        this->part = 0;
        this->final = false;
        this->content = NULL;
}

void QueryAnswer::setContent(TStringList *content) {
        if(this->content != NULL) {
                delete(this->content);
                this->content = NULL;
        }
        this->content = content;
}

QueryAnswer::~QueryAnswer() {
        if(this->content != NULL) {
                delete(this->content);
                this->content = NULL;
        }
}

void QueryAnswer::readContent(TStringList *out) {
        for(int i = 0; i < this->content->Count; i++) {
                if(this->content != NULL) {
                        out->Add(this->content->Strings[i]);
                } else { break; }
        }
}

