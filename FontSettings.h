//---------------------------------------------------------------------------

#ifndef FontSettingsH
#define FontSettingsH

#include <vcl.h>
#include <list.h>
#include "Observer.h"

class FontSettings : public Observable {
        public:
                FontSettings();
                FontSettings(String name, int size, int charset, bool bold, bool italic);
                void FontSettings::readSettings(TStringList *file);
                TFont* getFont();
                void setFont(TFont *font);
                void getSettingsFileEntry(TStringList *settings);

        private:
                String name;
                int size;
                int charset;
                TFontStyles style;

                String checkBool(bool in);
};

















//---------------------------------------------------------------------------
#endif
