//---------------------------------------------------------------------------


#pragma hdrstop

#include "Configuration.h"
#include "StringSplitter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


Configuration::Configuration(OFPGames gameid, String label, String mods, String password, String parameters) {
        this->gameid = gameid;
        this->label = label;
        StringSplitter ssp(mods);
        this->mods = ssp.split(";");
        this->password = password;
        this->addParameters = NULL;
        this->nosplash = false;
        this->nomap = false;
        this->window = false;
        this->setAddParameters(parameters);
}

Configuration::Configuration(OFPGames gameid, String label, TStringList *mods, String password, String parameters, bool nosplash, bool nomap) {
        this->gameid = gameid;
        this->label = label;
        this->mods = mods;
        this->password = password;
        this->addParameters = NULL;
        this->nomap = false;
        this->nosplash = false;
        this->window = false;
        this->setAddParameters(parameters);
        this->nosplash = (this->nosplash || nosplash);
        this->nomap = (this->nomap || nomap);
}

Configuration::Configuration(OFPGames gameid, String label, TStringList *mods, String password, String parameters, bool nosplash, bool nomap, bool window) {
        this->gameid = gameid;
        this->label = label;
        this->mods = mods;
        this->password = password;
        this->addParameters = NULL;
        this->nomap = false;
        this->nosplash = false;
        this->setAddParameters(parameters);
        this->nosplash = (this->nosplash || nosplash);
        this->nomap = (this->nomap || nomap);
        this->window = window;
}

String Configuration::createModLine () {
        String modline = "";
        for (int i = 0; i < this->mods->Count; i++) {
                modline += mods->Strings[i];
                if(this->mods->Count > i+1) {
                        modline += ";";
                }
        }
        return modline;
}

Configuration::~Configuration() {
        if(this->addParameters != NULL) {
                this->addParameters->Clear();
                delete (this->addParameters);
        }
        if(this->mods != NULL) {
                this->mods->Clear();
                delete (this->mods);
        }
}

String Configuration::createStartLine(String ip, int port, String player, bool passwordRequired, String enteredPassword) {
        String out = "";
        out += " " + this->createParameterLine(false, true, true, false, false, false);
        out += " -connect=" + ip;
        out += " -port=" + IntToStr(port);
        String ml = this->createModLine();
        if(!player.IsEmpty()) {
                out += " \"-name=" + player + "\"";
        }
        if(!ml.IsEmpty()) {
                out += " \"-mod="+ ml +"\"";
        }
        if(passwordRequired) {
                if(!this->password.IsEmpty()) {
                        out += " \"-password="  + this->password + "\"";
                } else if(!enteredPassword.IsEmpty()) {
                        out += " \"-password="  + enteredPassword + "\"";
                }
        }
        return out;
}

String Configuration::createParameterLine(bool forceNoHost, bool forceNoConnect, bool forceNoPort, bool forceNoServer, bool forceNoNoSplash, bool forceNoNoMap) {
        String paraline = "";
        if(this->nomap && !forceNoNoMap) {
                paraline += "-nomap ";
        }
        if(this->nosplash && !forceNoNoSplash) {
                paraline += "-nosplash ";
        }
        if(this->window) {
                paraline += "-window ";
        }
        for(int j = 0; j < this->addParameters->Count; j++) {
                String item = this->addParameters->Strings[j];
                bool addIt = true;
                addIt = addIt && !(forceNoHost && item == "-host");
                addIt = addIt && !(forceNoConnect && item.SubString(1,8) == "-connect");
                addIt = addIt && !(forceNoPort && item.SubString(1, 5) == "-port");
                addIt = addIt && !(forceNoServer && item == "-server");
                if(addIt) {
                        paraline += (item + " ");
                }
        }
        return paraline;
}

Configuration* Configuration::clone() {
        return (new Configuration(this->gameid,
                this->label, this->createModLine(), this->password,
                this->createParameterLine(false, false, false, false, false, false)));
}

String Configuration::createListEntry() {
        String out = "";
        if(!this->label.Trim().IsEmpty()) {
                out += this->label + "  ";
        }
        if(!this->password.IsEmpty()) {
                out += "pw:" + this->password + "  ";
        }
        out += this->createModLine();
        return out;
}

String Configuration::createStartLineLocal(bool multiplayer, String player) {
        String out = "";
        out += " " + this->createParameterLine(true, true, true, true, false, false);
        if(multiplayer) {
                out += " -host";
        }
        if(!player.IsEmpty()) {
                out += " \"-name=" + player + "\"";
        }
        String ml = this->createModLine();
        if(!ml.IsEmpty()) {
                out += " \"-mod="+ ml +"\"";
        }
        if(!this->password.IsEmpty()) {
                out += " \"-password="  + this->password + "\"";
        }
        return out;
}

void Configuration::setLabel(String label) {
        this->label = label;
}

void Configuration::setPassword(String password) {
        this->password = password;
}

void Configuration::setAddParameters(String parameters) {
        if(this->addParameters != NULL) {
                delete (this->addParameters);
                this->addParameters = NULL;
        }
        StringSplitter ssp2(parameters);
        ssp2.setKeepEmptyParts(false);
        this->addParameters = ssp2.split(" ");
        int ind;
        bool hasNosplash = (ind = this->addParameters->IndexOf("-nosplash")) > -1;
        if(hasNosplash) {
                this->nosplash = true;
                this->addParameters->Delete(ind);
        }
        bool hasNomap = (ind = this->addParameters->IndexOf("-nomap")) > -1;
        if(hasNomap) {
                this->nomap = true;
                this->addParameters->Delete(ind);
        }
        bool hasWindow = (ind = this->addParameters->IndexOf("-window")) > -1;
        if(hasWindow) {
                this->window = true;
                this->addParameters->Delete(ind);
        }
}

void Configuration::setNoSplash(bool on) {
        this->nosplash = on;
}

void Configuration::setNoMap(bool on) {
        this->nomap = on;
}

void Configuration::setWindow(bool on) {
        this->window = on;
}

String Configuration::getLabel() {
        return this->label;
}

String Configuration::getPassword() {
        return this->password;
}

bool Configuration::isNoSplashSet() {
        return this->nosplash;
}

bool Configuration::isNoMapSet() {
        return this->nomap;
}

bool Configuration::isWindowSet() {
        return this->window;
}

OFPGames Configuration::getGameId() {
        return this->gameid;
}

TStringList* Configuration::getMods() {
        return this->mods;
}

void Configuration::setMods(TStringList *newmods) {
        this->mods->Clear();
        for(int i = 0; i < newmods->Count; i++) {
                this->mods->Add(newmods->Strings[i]);
        }                                            
}

void Configuration::getSettingsFileEntry(TStringList *settings) {
        settings->Add("[Conf]");
        settings->Add("Game = " + getGameName(this->gameid));
        if(!this->label.IsEmpty()) {
                settings->Add("Label = " + this->label);
        }
        if(!this->password.IsEmpty()) {
                settings->Add("Password = " + this->password);
        }
        if(this->mods->Count > 0) {
                settings->Add("Mods = " + this->createModLine());
        }
        if(this->addParameters->Count > 0 || this->nosplash || this->nomap) {
                settings->Add("Parameters = " + this->createParameterLine(false, false, false, false, false, false));
        }
        settings->Add("[\\Conf]");
}
