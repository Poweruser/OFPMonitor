//---------------------------------------------------------------------------


#pragma hdrstop

#include "WindowSettings.h"
#include "ConfigReader.h"
#include "StringSplitter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

WindowSettings::WindowSettings() {
        this->top = 0;
        this->left = 0;
        this->width = 0;
        this->height = 0;
        this->devider = 0;
        this->alwaysOnTop = false;
        for(int i = 0; i < WS_ServerTableColumns; i++) {
                this->serverTable[i] = 0.0f;
        }
        for(int i = 0; i < WS_PlayerTableColumns; i++) {
                this->playerTable[i] = 0.0f;
        }
}


float WindowSettings::checkIfZero(float in, TStringGrid *grid) {
        if(in - 0.001f < 0) {
                return ((((float)grid->Width / (float)grid->ColCount) -
                (float)grid->GridLineWidth) / (float)grid->Width);
        }
        return in;
}

void WindowSettings::readSettings(TStringList *settings) {
        String ratioST = "", ratioPT = "";
        ConfigSection *window = new ConfigSection("WindowSettings");
        window->add(new ConfigEntry("Left", dtInt, (void*)(&(this->left))));
        window->add(new ConfigEntry("Top", dtInt, (void*)(&(this->top))));
        window->add(new ConfigEntry("Width", dtInt, (void*)(&(this->width))));
        window->add(new ConfigEntry("Height", dtInt, (void*)(&(this->height))));
        window->add(new ConfigEntry("ratioServerTable", dtString, (void*)(&ratioST)));
        window->add(new ConfigEntry("ratioPlayerTable", dtString, (void*)(&ratioPT)));
        window->add(new ConfigEntry("devider", dtInt, (void*)(&(this->devider))));
        window->add(new ConfigEntry("AlwaysOnTop", dtBool, (void*)(&(this->alwaysOnTop))));

        float oldSTR[WS_ServerTableColumns];
        float oldPTR[WS_PlayerTableColumns];
        for(int i = 0; i < WS_ServerTableColumns; i++) {
                oldSTR[i] = 0.0f;
        }
        for(int i = 0; i < WS_PlayerTableColumns; i++) {
                oldPTR[i] = 0.0f;
        }
        window->add(new ConfigEntry("ratioID", dtFloat, (void*)(&oldSTR[0])));
        window->add(new ConfigEntry("ratioSN", dtFloat, (void*)(&oldSTR[1])));
        window->add(new ConfigEntry("ratioPN", dtFloat, (void*)(&oldSTR[2])));
        window->add(new ConfigEntry("ratioST", dtFloat, (void*)(&oldSTR[3])));
        window->add(new ConfigEntry("ratioIS", dtFloat, (void*)(&oldSTR[4])));
        window->add(new ConfigEntry("ratioMN", dtFloat, (void*)(&oldSTR[5])));
        window->add(new ConfigEntry("ratioPI", dtFloat, (void*)(&oldSTR[6])));
        window->add(new ConfigEntry("ratioPL", dtFloat, (void*)(&oldPTR[0])));
        window->add(new ConfigEntry("ratioSC", dtFloat, (void*)(&oldPTR[1])));
        window->add(new ConfigEntry("ratioDE", dtFloat, (void*)(&oldPTR[2])));
        window->add(new ConfigEntry("ratioTE", dtFloat, (void*)(&oldPTR[3])));

        window->scan(settings, 0);
        delete window;
        if(!ratioST.IsEmpty()) {
                StringSplitter ssp(ratioST);
                TStringList *ratios = ssp.split(";");
                for(int i = 0; i < ratios->Count && i < WS_ServerTableColumns; i++) {
                        try {
                                this->serverTable[i] = atof(ratios->Strings[i].c_str());
                        } catch(...) {}
                }
                delete ratios;
        } else {
                for(int i = 0; i < WS_ServerTableColumns; i++) {
                        this->serverTable[i] = oldSTR[i];
                }
        }
        if(!ratioPT.IsEmpty()) {
                StringSplitter ssp(ratioPT);
                TStringList *ratios = ssp.split(";");
                for(int i = 0; i < ratios->Count && i < WS_PlayerTableColumns; i++) {
                        try {
                                this->playerTable[i] = atof(ratios->Strings[i].c_str());
                        } catch(...) {}
                }
                delete ratios;
        } else {
                for(int i = 0; i < WS_PlayerTableColumns; i++) {
                        this->playerTable[i] = oldPTR[i];
                }
        }
}

int WindowSettings::getHeight() {
        return this->height;
}

int WindowSettings::getWidth() {
        return this->width;
}

int WindowSettings::getTop() {
        return this->top;
}

int WindowSettings::getLeft() {
        return this->left;
}

int WindowSettings::getDevider() {
        return this->devider;
}

void WindowSettings::setHeight(int height) {
        this->height = height;
}

void WindowSettings::setWidth(int width) {
        this->width = width;
}

void WindowSettings::setTop(int top) {
        this->top = top;
}

void WindowSettings::setLeft(int left) {
        this->left = left;
}

void WindowSettings::setDevider(int devider) {
        this->devider = devider;
}

void WindowSettings::getSettingsFileEntry(TStringList *settings) {
        settings->Add("[WindowSettings]");
        settings->Add("Top = " + IntToStr(this->top));
        settings->Add("Left = " + IntToStr(this->left));
        settings->Add("Height = " + IntToStr(this->height));
        settings->Add("Width = " + IntToStr(this->width));
        String line = "", tmp = "";
        for(int i = 0; i < WS_ServerTableColumns; i++) {
                line += tmp.sprintf("%.03f", this->serverTable[i]);
                if(i + 1 < WS_ServerTableColumns) {
                        line += ";";
                }
        }
        settings->Add("ratioServerTable = " + line);
        line = "";
        for(int i = 0; i < WS_PlayerTableColumns; i++) {
                line += tmp.sprintf("%.03f", this->playerTable[i]);
                if(i + 1 < WS_PlayerTableColumns) {
                        line += ";";
                }
        }
        settings->Add("ratioPlayerTable = " + line);
        settings->Add("devider = " + IntToStr(this->devider));
        settings->Add("AlwaysOnTop = " + IntToStr(this->alwaysOnTop));
        settings->Add("[\\WindowSettings]");
}

void WindowSettings::setRatioServerTable(int columnIndex, float value) {
        if(columnIndex >= 0 && columnIndex < WS_ServerTableColumns) {
                this->serverTable[columnIndex] = value;
        }
}

void WindowSettings::setRatioPlayerTable(int columnIndex, float value) {
        if(columnIndex >= 0 && columnIndex < WS_PlayerTableColumns) {
                this->playerTable[columnIndex] = value;
        }
}

float WindowSettings::getRatioServerTable(int columnIndex) {
        if(columnIndex >= 0 && columnIndex < WS_ServerTableColumns) {
                return this->serverTable[columnIndex];
        }
        return 0.0f;
}

float WindowSettings::getRatioPlayerTable(int columnIndex) {
        if(columnIndex >= 0 && columnIndex < WS_PlayerTableColumns) {
                return this->playerTable[columnIndex];
        }
        return 0.0f;
}

bool WindowSettings::isAlwaysOnTopSet() {
        return this->alwaysOnTop;
}

void WindowSettings::setAlwaysOnTop(bool active) {
        this->alwaysOnTop = active;
}



