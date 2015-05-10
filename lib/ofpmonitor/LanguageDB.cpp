//---------------------------------------------------------------------------


#pragma hdrstop

#include "LanguageDB.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

LineParser::LineParser() {
        this->ident = "";
        this->value = "";
}

bool LineParser::parseLine(String in, String seperator) {
        int pos = in.Pos(seperator);
        if(pos > 0) {
                this->ident = in.SubString(1, pos - 1).Trim();
                int pos2 = pos + seperator.Length();
                this->value = in.SubString(pos2, in.Length() - (pos2 - 1)).Trim();
                return true;
        }
        return false;
}

String LineParser::getValue() {
        return this->value;
}

String LineParser::getIdent() {
        return this->ident;
}

LanguageDB::LanguageDB() {
        this->map = new TStringList;
        this->map->Duplicates = dupIgnore;
        this->map->Sorted = true;
        this->currentFile = "";
}

LanguageDB::~LanguageDB() {
        this->clearMap();
        delete this->map;
        this->map = NULL;
}

void LanguageDB::clearMap() {
        while(this->map->Count > 0) {
                String *str = (String*)(this->map->Objects[0]);
                delete str;
                this->map->Delete(0);
        }
}

void LanguageDB::addGuiString(String ident, String value) {
        this->map->AddObject(ident, (TObject*) new String(value));
}

String LanguageDB::getGuiString(String ident) {
        int index;
        if(this->map->Find(ident, index)) {
                return *((String*)(this->map->Objects[index]));
        }
        return "";
}

void LanguageDB::setModel(OFPMonitorModel *ofpm) {
        this->ofpm = ofpm;
}

void LanguageDB::update(Observable *o) {
        if(o == this->ofpm) {
                String file = this->ofpm->getWorkDir() + "\\" + this->ofpm->getLanguageFile();
                if(FileExists(file) && file != this->currentFile) {
                                this->currentFile = file;
                                this->loadFile(file);
                }
                this->NotifyObserver();
        }
}

bool LanguageDB::loadFile(String file) {
        bool out = false;
        if(FileExists(file)) {
                TStringList *list = new TStringList;
                try {
                        list->LoadFromFile(file);
                } catch (Exception &E) {
                        ShowMessage(E.Message);
                        delete list;
                        return false;
                }
                this->fillMapFromStringList(list);
                list->Clear();
                delete list;
                out = true;
        }
        return out;
}

void LanguageDB::fillMapFromStringList(TStringList *list) {
        LineParser *lp = new LineParser();
        this->clearMap();
        String sign = "=";
        for(int i = 0; i < list->Count; i++) {
                if(lp->parseLine(list->Strings[i].Trim(), sign)) {
                        this->map->AddObject(lp->getIdent(), (TObject*) new String(lp->getValue()));
                }
        }
        delete lp;
}

void LanguageDB::loadResourceStream(TResourceStream *stream) {
        TStringList *list = new TStringList;
        list->LoadFromStream(stream);
        this->fillMapFromStringList(list);
        delete list;
}
