//---------------------------------------------------------------------------


#pragma hdrstop

#include "StringSplitter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


StringSplitter::StringSplitter(String str) {
        this->keep = true;
        this->str = str;
}

void StringSplitter::setKeepEmptyParts(bool keep) {
        this->keep = keep;
}

TStringList* StringSplitter::split(String splitter) {
        TStringList *out = new TStringList;
        int start = 1;
        if(splitter == "\\") {
                start = 2;
        }
        int last = start;
        for(int i = start; i < this->str.Length(); i++) {
                if(this->str.SubString(i,splitter.Length()) == splitter) {
                        String part = this->str.SubString(last, i - last);
                        if(!part.IsEmpty() || this->keep) {
                                out->Add(part);
                        }
                        last = i + splitter.Length();
                }
        }
        String part = this->str.SubString(last, (this->str.Length() + 1) - last);
        if(!part.IsEmpty() || this->keep) {
                out->Add(part);
        }
        return out;
}
