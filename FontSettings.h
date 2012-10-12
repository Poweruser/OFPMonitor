//---------------------------------------------------------------------------

#ifndef FontSettingsH
#define FontSettingsH

#include <vcl.h>
#include <list.h>

class FontSettings {
        public:
                FontSettings(TFont *font);
                FontSettings(String name, int size, int charset, bool bold, bool italic);
                void FontSettings::readSettings(TStringList *file);
                TFont* getFont();
                void setFont(TFont *font);
                bool guiNeedsUpdate();
                void getSettingsFileEntry(TStringList *settings);

        private:
                String name;
                int size;
                int charset;
                TFontStyles style;
                bool guiUpdate;

                String checkBool(bool in);


};

















//---------------------------------------------------------------------------
#endif
