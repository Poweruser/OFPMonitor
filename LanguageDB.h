//---------------------------------------------------------------------------

#ifndef LanguageDBH
#define LanguageDBH

#include <vcl.h>
#include "Observer.h"
#include "OFPMonitorModel.h"

class LineParser {
        private:
                String ident;
                String value;

        public:
                LineParser();
                bool parseLine(String line, String seperator);
                String getValue();
                String getIdent();
};

class LanguageDB : public Observable, public Observer  {
        private:
                OFPMonitorModel *ofpm;
                TStringList *map;
                String currentFile;
                void clearMap();
                bool loadFile(String file);

        public:
                LanguageDB();
                ~LanguageDB();
                void addGuiString(String ident, String value);
                String getGuiString(String ident);
                void setModel(OFPMonitorModel *ofpm);
                void update(Observable *o);
};

//---------------------------------------------------------------------------
#endif
