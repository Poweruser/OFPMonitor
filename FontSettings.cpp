//---------------------------------------------------------------------------


#pragma hdrstop

#include "FontSettings.h"
#include "ConfigReader.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


FontSettings::FontSettings() {
        this->name = "";
        this->size = 10;
        this->charset = DEFAULT_CHARSET;
}

String FontSettings::checkBool(bool in) {
        if(in) { return "1"; }
        return "0";
}

void FontSettings::getSettingsFileEntry(TStringList *settings) {
        settings->Add("[FontSettings]");
        settings->Add("Charset = " + IntToStr(this->charset));
        settings->Add("Name = " + this->name);
        settings->Add("Size = " + IntToStr(this->size));
        settings->Add("Bold = " + IntToStr(this->style.Contains(fsBold)));
        settings->Add("Italic = " + IntToStr(this->style.Contains(fsItalic)));
        settings->Add("[\\FontSettings]");
}

void FontSettings::readSettings(TStringList *file) {
        bool bold = false, italic = false;
        ConfigSection *font = new ConfigSection("FontSettings");
        font->add(new ConfigEntry("Name", dtString, (void*)(&(this->name))));
        font->add(new ConfigEntry("Charset", dtInt, (void*)(&(this->charset))));
        font->add(new ConfigEntry("Size", dtInt, (void*)(&(this->size))));
        font->add(new ConfigEntry("Bold", dtBool, (void*)(&bold)));
        font->add(new ConfigEntry("Italic", dtBool, (void*)(&italic)));
        int index = font->scan(file, 0);
        if(index < file->Count) {
                if(bold) {
                        this->style = this->style << fsBold;
                }
                if(italic) {
                        this->style = this->style << fsItalic;
                }
                this->NotifyObserver();
        }
        delete font;
}

TFont* FontSettings::getFont() {
        TFont *out = new TFont();
        out->Size = this->size;
        out->Name = this->name;
        out->Style = this->style;
        out->Charset = this->charset;
        return out;
}

void FontSettings::setFont(TFont *font) {
        this->size = font->Size;
        this->name = font->Name;
        this->style = font->Style;
        this->charset = font->Charset;
        this->NotifyObserver();
}
