//---------------------------------------------------------------------------


#pragma hdrstop
#include "ConfigReader.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

/**
   Returns the value of a String with the format "XYZ = VALUE"
 */

String ConfigEntry::getValue(String in) {
        String out = "";
        String tmp = in.Trim();
        for(int i = 1; i < tmp.Length(); i++) {
                if(tmp.SubString(i,1) == "=") {
                        out = tmp.SubString(i + 1, tmp.Length() - i).Trim();
                        break;
                }
        }
        return out;
}

ConfigEntry::ConfigEntry(String ident, DataType dt, void *dataPointer) {
        this->ident = ident;
        this->dt = dt;
        this->data = dataPointer;
}

bool ConfigEntry::check(String line) {
        bool matches = (line.AnsiPos(this->ident) == 1);
        if(matches || this->ident.IsEmpty()) {
                String value = this->getValue(line);
                switch(this->dt) {
                        int i;
                        case dtInt:
                                i = StrToIntDef(value, -1);
                                if(i != -1) {
                                        *((int*)(this->data)) = i;
                                }
                                break;
                        case dtFloat:
                                try {
                                        *((float*)(this->data)) = atof(value.c_str());
                                } catch (...) {}
                                break;
                        case dtBool:
                                *((bool*)(this->data)) = StrToIntDef(value, 0);
                                break;
                        case dtString:
                                *((String*)(this->data)) = value;
                                break;
                        case dtStringQuoted:
                                *((String*)(this->data)) = this->extractQuotedValue(value);
                                break;
                        case dtServerItem:
                                (*((list<String>*)(this->data))).push_back(line);
                                break;
                }
        }
        return matches;
}

String ConfigEntry::extractQuotedValue(String value) {
        int start = value.Pos("\"");
        if(!start) { return value; }
        int end = 0;
        for(int i = value.Length(); i > start; i--) {
                if(value.SubString(i, 1) == "\"") {
                        end = i;
                        break;
                }
        }
        if(end && start) {
                return value.SubString(start + 1, end - (start + 1));
        }
        return value;

}

ConfigSection::ConfigSection(String name) {
        this->name = name;
}

ConfigSection::~ConfigSection() {
        while(this->items.size() > 0) {
                ConfigEntry *e = this->items.front();
                delete e;
                this->items.pop_front();
        }
}

int ConfigSection::scan(TStringList *file, int lineIndex) {
        int index = lineIndex;
        String line = "";
        while(index < file->Count) {
                line = file->Strings[index].Trim();
                index++;
                if(line.AnsiPos("[" + this->name + "]") == 1) {
                        break;
                }
        }
        while(index < file->Count) {
                line = file->Strings[index].Trim();
                if(line.AnsiPos("[\\" + this->name + "]") == 1) {
                        break;
                }
                for (list<ConfigEntry*>::iterator ce = this->items.begin(); ce != this->items.end(); ++ce) {
                        if((*ce)->check(line)) {
                                break;
                        }
                }
                index++;
        }
        return index;
}

void ConfigSection::add(ConfigEntry *ce) {
        this->items.push_back(ce);
}
