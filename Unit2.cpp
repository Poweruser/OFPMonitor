//---------------------------------------------------------------------------

#include <vcl.h>
#include <list.h>
#include <filectrl.hpp>
#include <io.h>
#include <windows.h>
#include <Registry.hpp>

#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

#include "guiDBDefs.cpp"


const int confAmount = 50;

/**
   Macro to retrieve the length of an array
 */

template<typename T, int size>
int GetArrLength(T(&)[size]){return size;}

/**
   Returns the number of game configurations the user has set
 */

int TForm2::getConfAmount() {
        return confAmount;
}

/**
   Represents an game configuration, which the user can use to join an server
 */

class Configuration {
        public:
		bool set;
                String label;
                list<String> mods;
                String password;
                list<String> addParameters;

                Configuration(String l, list<String> &m, String pw, String aP, bool ns, bool nm) {
                        this->set = true;
                        this->label = l;
                        this->mods = m;
                        this->password = pw;
                        this->addParameters = Form1->splitUpMessage(aP," ");
                        if(nm) {
                                this->addParameters.push_back("-nomap");
                        }
                        if(ns) {
                                this->addParameters.push_back("-nosplash");
                        }
                }

		Configuration () {
			this->set = false;
		}
                TStringList* createFileEntry() {
                        TStringList *output = new TStringList;
                        output->Add("[Conf]");
                        if(!this->label.IsEmpty()) {
                                output->Add("Label = " + this->label);
                        }
                        if(!this->password.IsEmpty()) {
                                output->Add("Password = " + this->password);
                        }
                        if(this->mods.size() > 0) {
                                output->Add("Mods = " + this->createModLine());
                        }
                        if(this->addParameters.size() > 0) {
                                output->Add("Parameters = " + this->createParameterLine());
                        }
                        output->Add("[\\Conf]");
                        return output;
                }
                String createStartLine(String ip, int port, String player) {
                        String out = "" ;
                        out += " " + this->createParameterLine();
                        out += " -connect=" + ip;
                        out += " -port=" + String(port);
                        String ml = this->createModLine();
                        if(!player.IsEmpty()) {
                                out += " \"-name=" + player + "\"";
                        }
                        if(!ml.IsEmpty()) {
                                out += " \"-mod="+ this->createModLine() +"\"";
                        }
                        return out;
                }
                String createListEntry() {
                        String out = "";
                        if(this->set) {
                                if(!this->label.Trim().IsEmpty()) {
                                        out += this->label + "  ";
                                }
                                if(this->password.Length() > 0) {
                                        out += "pw:" + this->password + "  ";
                                }
                                out += this->createModLine();
                        }
                        return out;
                }

                String createModLine () {
                        String modline = "";
                        unsigned int i = 0;
                        for (list<String>::iterator ci = this->mods.begin(); ci != this->mods.end(); ++ci) {
                                i++;
                                modline += *ci;
                                if(i < this->mods.size()) {
                                        modline += ";";
                                }
                        }
                        return modline;
                }

                String createParameterLine() {
                        String paraline = "";
                        unsigned int j = 0;
                        for (list<String>::iterator cj = this->addParameters.begin(); cj != this->addParameters.end(); ++cj) {
                                j++;
                                paraline += *cj;
                                if(j < this->addParameters.size()) {
                                        paraline += " ";
                                }
                        }
                        return paraline;
                }
};

/**
   Converts an bool to its binary representation
 */

String checkBool(bool in) {
        if(in) {
                return "1";
        } else {
                return "0";
        }
}

/**
   Converts the binary representation of true and false (1 and 0) to a bool
 */

bool checkBool2(String in) {
        return (in == "1");
}

/**
   Stores the general program settings
 */

class Settings {
        public:
                bool changed;
                String workdir;
                String exe;
                String folder;
                String player;
                int interval;
                Configuration startupConfs[confAmount];
                String file;
                String languagefile;
                TStringList *watched;

                Settings() {
                        this->watched = new TStringList;
                        this->watched->Sorted = true;
                        this->watched->Duplicates = dupIgnore;
                        this->workdir = GetCurrentDir();
                        this->interval = 1;
                        this->file = this->workdir + "\\OFPMonitor.ini";
                        this->languagefile = "Default";
                        this->changed = false;
                }

                Configuration pSgetConf(int i) {
                        return this->startupConfs[i];
                }
                void pSdeleteConf(int i) {
                        this->startupConfs[i].set = false;
                        for(int j = i + 1; j < confAmount; j++) {
                                this->startupConfs[j - 1] = (this->startupConfs[j]);
                        }
                        this->startupConfs[confAmount - 1].set = false;
                        this->changed = true;
                }
                void pSaddConf(Configuration c) {
                        for(int i = 0; i < confAmount; i++) {
                                if(!this->startupConfs[i].set) {
                                        this->startupConfs[i] = c;
                                        break;
                                }
                        }
                        this->changed = true;
                }

                void setInterval(int i) {
                        this->interval = i;
                        Form1->Timer1->Interval = i * 1000;
                        this->changed = true;
                }

                void writeToFile(list<String> &servers, list<String> &watchedServers, list<String> &font, list<String> &window) {
                        if(this->changed) {
                                TStringList *file = new TStringList;
                                file->Add("[General]");
                                file->Add("Exe = " + String(this->exe));
                                file->Add("LastPlayer = " + this->player);
                                file->Add("LangFile = " + this->languagefile);
                                file->Add("Interval = " + String(this->interval));
                                file->Add("[\\General]");
                                for(int i = 0; i < confAmount; i++) {
                                        if(this->startupConfs[i].set) {
                                                TStringList *entry = this->startupConfs[i].createFileEntry();
                                                while (entry->Count > 0) {
                                                        file->Add(entry->Strings[0]);
                                                        entry->Delete(0);
                                                }
                                                delete entry;
                                        }
                                }
                                file->Add("[Filters]");
                                file->Add("Playing = " + checkBool(Form1->CHECKBOX_FILTER_PLAYING->Checked));
                                file->Add("Waiting= " + checkBool(Form1->CHECKBOX_FILTER_WAITING->Checked));
                                file->Add("Creating = " + checkBool(Form1->CHECKBOX_FILTER_CREATING->Checked));
                                file->Add("Settingup = " + checkBool(Form1->CHECKBOX_FILTER_SETTINGUP->Checked));
                                file->Add("Briefing = " + checkBool(Form1->CHECKBOX_FILTER_BRIEFING->Checked));
                                file->Add("Debriefing = " + checkBool(Form1->CHECKBOX_FILTER_DEBRIEFING->Checked));
                                file->Add("WithPW = " + checkBool(Form1->CHECKBOX_FILTER_WITHPASSWORD->Checked));
                                file->Add("WithoutPW = " + checkBool(Form1->CHECKBOX_FILTER_WITHOUTPASSWORD->Checked));
                                file->Add("minPlayers = " + IntToStr(Form1->UpDown1->Position));
                                file->Add("ServerName = " + Form1->Edit2->Text);
                                file->Add("MissionName = " + Form1->Edit1->Text);
                                file->Add("PlayerName = " + Form1->Edit4->Text);
                                file->Add("[\\Filters]");
                                String tmp;
                                while(font.size() > 0) {
                                        tmp = font.front();
                                        file->Add(tmp);
                                        font.pop_front();
                                }
                                while(window.size() > 0) {
                                        tmp = window.front();
                                        file->Add(tmp);
                                        window.pop_front();
                                }
                                if (servers.size() > 0) {
                                        file->Add("[Servers]");
                                        if(watchedServers.size() > 0) {
                                                file->Add("[Watch]");
                                                while(watchedServers.size() > 0) {
                                                        tmp = watchedServers.front();
                                                        file->Add(tmp);
                                                        watchedServers.pop_front();
                                                }
                                                file->Add("[\\Watch]");
                                        }
                                        while(servers.size() > 0) {
                                                tmp = servers.front();
                                                file->Add(tmp);
                                                servers.pop_front();
                                        }
                                        file->Add("[\\Servers]");
                                }
                                file->SaveToFile(this->file);
                                delete file;
                        }
                }
};
Settings programSettings = Settings();

void TForm2::writeSettingToFile(list<String> servers, list<String> watchedServers, list<String> font, list<String> window) {
        programSettings.writeToFile(servers, watchedServers, font, window);
}

void TForm2::setSettingsChanged() {
        programSettings.changed = true;
}

boolean TForm2::isOFPResistance() {
        return ((programSettings.folder + "FLASHPOINTRESISTANCE.EXE") == programSettings.exe);
}

String TForm2::getConfListEntry(int i) {
        return programSettings.startupConfs[i].createListEntry();
}

String TForm2::getConfStartLine(int i, String ip, int port) {
        return programSettings.startupConfs[i].createStartLine(ip, port, programSettings.player);
}

String TForm2::getConfModLine(int i) {
        return programSettings.startupConfs[i].createModLine();
}

TStringList* TForm2::getWatchedList() {
        return programSettings.watched;
}

/**
   Returns the currently set game exe file
 */

String TForm2::getExe() {
        return programSettings.exe;
}

/**
   Returns the game folder
 */

String TForm2::getExeFolder() {
        return programSettings.folder;
}

/**
   Refreshes the list box for the configurations in the settings window
 */

void updateConfList() {
        Form2->ListBox1->Clear();
        for(int i = 0; i < confAmount; i++) {
                if(programSettings.startupConfs[i].set) {
                        Form2->ListBox1->Items->AddObject(programSettings.startupConfs[i].createListEntry(), (TObject *) i);
                }
        }
        return;
}

/**
   Returns the value of a String with the format "XYZ = VALUE"
 */

String getValue(String in) {
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

/**
   Splits a String with 'diff' as seperator and returns the two parts in a list
 */

list<String> getVarAndValue(String in, String diff) {
        list<String> out;
        String tmp = in.Trim();
        for(int i = 0; i < tmp.Length(); i++) {
                if(tmp.SubString(i,diff.Length()) == diff) {
                        out.push_front(tmp.SubString(1, i - 1).Trim());
                        out.push_back(tmp.SubString(i + diff.Length(), tmp.Length() - (i + diff.Length() -1)).Trim());
                        break;
                }
        }
        return out;
}

/**
   Returns the folder of the game exe file
 */

String getFolder(String in) {
        String out = "";
        for(int i = in.Length() - 1; i >= 0; i--) {
                if(in.SubString(i,1) == "\\") {
                        out = in.SubString(0, i).Trim();
                        break;
                }
        }
        return out;
}

/**
   Reads a String from the OS registry. 'a' holds a list of keys to visit in order,
   'key' is the object which content is to read inside the last key
 */

String GetRegistryValue(void * root, list<String> a, String key) {
        String S = "";
        TRegistry *Registry = new TRegistry(KEY_READ);
        try
        {
                Registry->RootKey = root;
                while (a.size() > 0) {
                        Registry->OpenKey(a.front(),false);
                        a.pop_front();
                }
                S = Registry->ReadString(key);
        }
        __finally {
                delete Registry;
        }
        return S;
}

/**
   Reads all folders within the game folder and displays them in the
   modfolder list box in the settings window
 */

void updateModFolderList(String ofpfolder) {
        if(!ofpfolder.IsEmpty()) {
                Form2->ListBox2->Clear();
        	TSearchRec daten;
                if(0 == FindFirst((ofpfolder +"\\*").c_str(), faDirectory, daten)) {
                        try {
                                do {
                                        if(daten.Size == 0 && daten.Name != "." && daten.Name != "..") {
                                                Form2->ListBox2->Items->Add(String(daten.Name));
                                        }
                                } while(FindNext(daten) == 0);
                        }__finally
                        {
                                FindClose(daten);
                        }
                }
        }
}

/**
   Returns a String of the current set language for an identifier 
 */

String TForm2::getGuiString(String ident) {
        String out = "";
        for (list<guiString>::iterator ci = guiStrings.begin(); ci != guiStrings.end(); ++ci) {
                if((*ci).identifier == ident) {
                        out = (*ci).value;
                        break;
                }
        }
        return out;
}

/**
   Reads all player profile folders in OFP's \Users folder and lists them in the
   player name combobox in the settings window
 */

bool updateProfileList(String ofpfolder) {
        bool success = false;
        if(!ofpfolder.IsEmpty()) {
                Form2->COMBOBOX_PROFILE->Clear();
        	TSearchRec daten;
                if(0 == FindFirst((ofpfolder +"\\Users\\*").c_str(), faDirectory, daten)) {
                        try {
                                do {
                                        if(     daten.Size == 0 &&
                                                daten.Name != "." &&
                                                daten.Name != ".." &&
                                                FileExists(ofpfolder + "\\Users\\" + daten.Name + "\\UserInfo.cfg")) {
                                                        Form2->COMBOBOX_PROFILE->Items->Add(String(daten.Name));
                                                        success = true;
                                        }
                                } while(FindNext(daten) == 0);
                        }__finally
                        {
                                FindClose(daten);
                        }
                }
        }
        Form2->COMBOBOX_PROFILE->Enabled = success;
        if(!success) {
                Form2->COMBOBOX_PROFILE->Text = Form2->getGuiString("STRING_NOPROFILES");
        }
        return success;
}

bool refreshProfiles(String folder, String player) {
        if(updateProfileList(folder)) {
                list<String> b;
                b.push_back("Software");
                b.push_back("Codemasters");
                b.push_back("Operation Flashpoint");
                String registryPlayer = GetRegistryValue(HKEY_CURRENT_USER, b, "Player Name");
                bool lp = false, rp = false;
                for(int k = 0; k < Form2->COMBOBOX_PROFILE->Items->Count; k++) {
                        if(Form2->COMBOBOX_PROFILE->Items->Strings[k] == player) {
                                lp = true;
                        }
                        if(Form2->COMBOBOX_PROFILE->Items->Strings[k] == registryPlayer) {
                                rp = true;
                        }
                }
                if(lp) {
                        Form2->COMBOBOX_PROFILE->Text = player;
                } else if(rp) {
                        Form2->COMBOBOX_PROFILE->Text = registryPlayer;
                } else {
                        Form2->COMBOBOX_PROFILE->Text = Form2->COMBOBOX_PROFILE->Items->Strings[0];
                }
                programSettings.player = Form2->COMBOBOX_PROFILE->Text;
                return true;
        } else {
                return false;
        }
}

void checkIfExeAndPlayerIsSet(String folder, String player) {
        if(refreshProfiles(folder,player) &&
           !Form2->getExe().IsEmpty() &&
           !Form2->getExeFolder().IsEmpty()) {
                        Form1->MENUITEM_POPUP_JOIN->Enabled = true;
                        Form1->MENUITEM_POPUP_AUTOJOIN->Enabled = true;
                        Form1->MENUITEM_POPUP_AUTOJOINB->Enabled = true;
        } else {
                        Form1->MENUITEM_POPUP_JOIN->Enabled = false;
                        Form1->MENUITEM_POPUP_AUTOJOIN->Enabled = false;
                        Form1->MENUITEM_POPUP_AUTOJOINB->Enabled = false;
        }
}

/**
   Applys a language file to the Gui
 */

void updateLanguage(String languagefile) {
        TStringList *file = new TStringList;
        String pathAndFile = programSettings.workdir + "\\" + languagefile;
        guiStrings.push_back(guiString("STRING_YES","Yes"));
        guiStrings.push_back(guiString("STRING_NO","No"));
        guiStrings.push_back(guiString("STRING_ONLINE","Online:"));
        guiStrings.push_back(guiString("STRING_LISTED","Listed:"));
        guiStrings.push_back(guiString("STRING_ERRORS","Errors:"));
        guiStrings.push_back(guiString("STRING_NOPROFILES","No player profiles found!"));
        if(FileExists(pathAndFile)) {
                file->LoadFromFile(pathAndFile);
                String tmp;
                guiStrings.clear();
                list<String> val;
                for(int i = 0; i < file->Count; i++) {
                        val.clear();
                        tmp = file->Strings[i].Trim();
                        if(tmp.SubString(1,6) == "BUTTON") {
                                val = getVarAndValue(tmp, "=");
                                for(int j = 0; j < GetArrLength(guiButton); j++) {
                                        if(guiButton[j]->Name == val.front()) {
                                                guiButton[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.SubString(1,5) == "LABEL") {
                                val = getVarAndValue(tmp, "=");
                                for(int j = 0; j < GetArrLength(guiLabel); j++) {
                                        if(guiLabel[j]->Name == val.front()) {
                                                guiLabel[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.SubString(1,8) == "CHECKBOX") {
                                val = getVarAndValue(tmp, "=");
                                for(int j = 0; j < GetArrLength(guiCheckBox); j++) {
                                        if(guiCheckBox[j]->Name == val.front()) {
                                                guiCheckBox[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.SubString(1,8) == "GROUPBOX") {
                                val = getVarAndValue(tmp, "=");
                                for(int j = 0; j < GetArrLength(guiGroupBox); j++) {
                                        if(guiGroupBox[j]->Name == val.front()) {
                                                guiGroupBox[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.SubString(1,8) == "MENUITEM") {
                                val = getVarAndValue(tmp, "=");
                                for(int j = 0; j < GetArrLength(guiMenuItem); j++) {
                                        if(guiMenuItem[j]->Name == val.front()) {
                                                guiMenuItem[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.SubString(1,15) == "SETTINGS_WINDOW") {
                                val = getVarAndValue(tmp, "=");
                                for(int j = 0; j < GetArrLength(guiForm); j++) {
                                        if(guiForm[j]->Hint == val.front()) {
                                                guiForm[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.SubString(1,6) == "STRING") {
                                val = getVarAndValue(tmp, "=");
                                String f = val.front();
                                String b = val.back();
                                guiStrings.push_back(guiString(f,b));
                        }
                }
                Form1->StringGrid1->Cells[0][0] = Form2->getGuiString("STRING_ID");
                Form1->StringGrid1->Cells[1][0] = Form2->getGuiString("STRING_NAME");
                Form1->StringGrid1->Cells[2][0] = Form2->getGuiString("STRING_PLAYERS");
                Form1->StringGrid1->Cells[3][0] = Form2->getGuiString("STRING_STATUS");
                Form1->StringGrid1->Cells[4][0] = Form2->getGuiString("STRING_ISLAND");
                Form1->StringGrid1->Cells[5][0] = Form2->getGuiString("STRING_MISSION");
                Form1->StringGrid1->Cells[6][0] = Form2->getGuiString("STRING_PING");
                Form1->StringGrid2->Cells[0][0] = Form2->getGuiString("STRING_NAME");
                Form1->StringGrid2->Cells[1][0] = Form2->getGuiString("STRING_SCORE");
                Form1->StringGrid2->Cells[2][0] = Form2->getGuiString("STRING_DEATHS");
                Form1->StringGrid2->Cells[3][0] = Form2->getGuiString("STRING_TEAM");
                if(!Form2->COMBOBOX_PROFILE->Enabled) {
                        Form2->COMBOBOX_PROFILE->Text = Form2->getGuiString("STRING_NOPROFILES");
                }
        }
        return;
}

/**
   Reads the programs config file
 */

list<String> readConfigFile() {
        String exe = "";
        String interval = "";
        String folder = "";
        String player = "";
        String langfile = "";
        list<String> ipList;
        if(FileExists(programSettings.file)) {
                TStringList *file = new TStringList;
                file->LoadFromFile(programSettings.file);
                for(int i = 0; i < file->Count; i++) {
                        String tmp = file->Strings[i].Trim();
                        if(tmp.SubString(1,9) == "[General]") {
                                i++;
                                tmp = file->Strings[i].Trim();
                                while(tmp.SubString(1,10) != "[\\General]" && i < file->Count - 1) {
                                        if((tmp.SubString(1,3) == "Exe")) {
                                                String val = getValue(tmp);
                                                if(FileExists(val)) {
                                                        exe = val;
                                                        folder = getFolder(exe);
                                                }
                                        } else if((tmp.SubString(1,10) == "LastPlayer")) {
                                                player = getValue(tmp);
                                        } else if((tmp.SubString(1,8) == "Interval")) {
                                                interval = getValue(tmp);
                                        } else if((tmp.SubString(1,8) == "LangFile")) {
                                                langfile = getValue(tmp);
                                        }
                                        i++;
                                        tmp = file->Strings[i].Trim();
                                }
                        } else if((tmp.SubString(1,6) == "[Conf]")) {
                                Configuration c = Configuration();
                                c.set = true;
                                i++;
                                tmp = file->Strings[i].Trim();
                                while((tmp.SubString(1,7) != "[\\Conf]") && i < file->Count - 1) {
                                        if((tmp.SubString(1,8) == "Password")) {
                                                c.password = getValue(tmp);
                                        } else if((tmp.SubString(1,4) == "Mods")) {
                                                c.mods = Form1->splitUpMessage(getValue(tmp), ";");
                                        } else if((tmp.SubString(1,10) == "Parameters")) {
                                                c.addParameters = Form1->splitUpMessage(getValue(tmp), " ");
                                        } else if((tmp.SubString(1,5) == "Label")) {
                                                c.label = getValue(tmp);
                                        }
                                        i++;
                                        tmp = file->Strings[i].Trim();
                                }
                                programSettings.pSaddConf(c);
                        } else if((tmp.SubString(1,9) == "[Servers]")) {
                                i++;
                                tmp = file->Strings[i].Trim();
                                while((tmp.SubString(1,10) != "[\\Servers]") && i < file->Count - 1) {
                                        if(tmp.SubString(1,7) == "[Watch]") {
                                                i++;
                                                tmp = file->Strings[i].Trim();
                                                programSettings.watched->Clear();
                                                while(tmp.SubString(1,8) != "[\\Watch]" && i < file->Count -1 ) {
                                                        if(tmp.Length() > 8) {
                                                                programSettings.watched->Add(tmp.Trim());
                                                                ipList.push_back(tmp.Trim());
                                                        }
                                                        i++;
                                                        tmp = file->Strings[i].Trim();
                                                }
                                        } else if(tmp.Length() > 8) {
                                                ipList.push_back(tmp.Trim());
                                        }
                                        i++;
                                        tmp = file->Strings[i].Trim();
                                }
                        } else if((tmp.SubString(1,9) == "[Filters]")) {
                                i++;
                                tmp = file->Strings[i].Trim();
                                while((tmp.SubString(1,10) != "[\\Filters]") && i < file->Count - 1) {
                                        if((tmp.SubString(1,7) == "Playing")) {
                                                Form1->CHECKBOX_FILTER_PLAYING->Checked = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,7) == "Waiting")) {
                                                Form1->CHECKBOX_FILTER_WAITING->Checked = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,8) == "Creating")) {
                                                Form1->CHECKBOX_FILTER_CREATING->Checked = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,9) == "Settingup")) {
                                                Form1->CHECKBOX_FILTER_SETTINGUP->Checked = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,8) == "Briefing")) {
                                                Form1->CHECKBOX_FILTER_BRIEFING->Checked = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,10) == "Debriefing")) {
                                                Form1->CHECKBOX_FILTER_DEBRIEFING->Checked = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,6) == "WithPW")) {
                                                Form1->CHECKBOX_FILTER_WITHPASSWORD->Checked = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,9) == "WithoutPW")) {
                                                Form1->CHECKBOX_FILTER_WITHOUTPASSWORD->Checked = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,10) == "minPlayers")) {
                                                try {
                                                        int i = StrToInt(getValue(tmp));
                                                        Form1->UpDown1->Position = i;
                                                } catch (...) {}
                                        } else if((tmp.SubString(1,10) == "ServerName")) {
                                                Form1->Edit2->Text = getValue(tmp);
                                        } else if((tmp.SubString(1,11) == "MissionName")) {
                                                Form1->Edit1->Text = getValue(tmp);
                                        } else if((tmp.SubString(1,10) == "PlayerName")) {
                                                Form1->Edit4->Text = getValue(tmp);
                                        }
                                        i++;
                                        tmp = file->Strings[i].Trim();
                                }
                        } else if((tmp.SubString(1,14) == "[FontSettings]")) {
                                i++;
                                tmp = file->Strings[i].Trim();
                                int charset = 0;
                                String name = "";
                                int size = 0;
                                bool bold = false, italic = false;
                                while((tmp.SubString(1,15) != "[\\FontSettings]") && i < file->Count - 1) {
                                        if((tmp.SubString(1,4) == "Name")) {
                                                name = getValue(tmp);
                                        } else if((tmp.SubString(1,7) == "Charset")) {
                                                try {
                                                        charset = StrToInt(getValue(tmp));
                                                } catch (...) {}
                                        } else if((tmp.SubString(1,4) == "Size")) {
                                                try {
                                                        size = StrToInt(getValue(tmp));
                                                } catch (...) {}
                                        } else if((tmp.SubString(1,4) == "Bold")) {
                                                bold = checkBool2(getValue(tmp));
                                        } else if((tmp.SubString(1,6) == "Italic")) {
                                                italic = checkBool2(getValue(tmp));
                                        }
                                        i++;
                                        tmp = file->Strings[i].Trim();
                                }
                                Form1->setFont(name, size, charset,bold,italic);
                        } else if((tmp.SubString(1,16) == "[WindowSettings]")) {
                                i++;
                                tmp = file->Strings[i].Trim();
                                int     top = 0,
                                        left = 0,
                                        width = 0,
                                        height = 0,
                                        devider = 0;
                                float   ratioID = 0.0f,
                                        ratioSN = 0.0f,
                                        ratioPN = 0.0f,
                                        ratioST = 0.0f,
                                        ratioIS = 0.0f,
                                        ratioMN = 0.0f,
                                        ratioPI = 0.0f,
                                        ratioPL = 0.0f,
                                        ratioSC = 0.0f,
                                        ratioDE = 0.0f,
                                        ratioTE = 0.0f;
                                        
                                while((tmp.SubString(1,17) != "[\\WindowSettings]") && i < file->Count - 1) {
                                        if((tmp.SubString(1,4) == "Left")) {
                                                try {   left = StrToInt(getValue(tmp));  }catch(...) {}
                                        } else if((tmp.SubString(1,3) == "Top")) {
                                                try {   top = StrToInt(getValue(tmp));  }catch(...) {}
                                        } else if((tmp.SubString(1,5) == "Width")) {
                                                try {   width = StrToInt(getValue(tmp));  }catch(...) {}
                                        } else if((tmp.SubString(1,6) == "Height")) {
                                                try {   height = StrToInt(getValue(tmp));  }catch(...) {}
                                        } else if((tmp.SubString(1,7) == "ratioID")) {
                                                try {   ratioID = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if((tmp.SubString(1,7) == "ratioSN")) {
                                                try {   ratioSN = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if((tmp.SubString(1,7) == "ratioPN")) {
                                                try {   ratioPN = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if((tmp.SubString(1,7) == "ratioST")) {
                                                try {   ratioST = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if((tmp.SubString(1,7) == "ratioIS")) {
                                                try {   ratioIS = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if(tmp.SubString(1,7) == "ratioMN") {
                                                try {   ratioMN = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if(tmp.SubString(1,7) == "ratioPI") {
                                                try {   ratioPI = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if(tmp.SubString(1,7) == "ratioPL") {
                                                try {   ratioPL = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if(tmp.SubString(1,7) == "ratioSC") {
                                                try {   ratioSC = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if(tmp.SubString(1,7) == "ratioDE") {
                                                try {   ratioDE = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if(tmp.SubString(1,7) == "ratioTE") {
                                                try {   ratioTE = atof(getValue(tmp).c_str());  }catch(...) {}
                                        } else if(tmp.SubString(1,7) == "devider") {
                                                try {   devider = atof(getValue(tmp).c_str());  }catch(...) {}
                                        }
                                        i++;
                                        tmp = file->Strings[i].Trim();
                                }


                                Form1->setWindowSettings(top,left,height,width,ratioID,
                                        ratioSN,
                                        ratioPN,
                                        ratioST,
                                        ratioIS,
                                        ratioMN,
                                        ratioPI,
                                        ratioPL,
                                        ratioSC,
                                        ratioDE,
                                        ratioTE,
                                        devider);

                        }
                }
                delete file;
        }
        if(!player.IsEmpty()) {
                programSettings.player = player;
        };
        if(folder.IsEmpty()) {
                list<String> a;
                a.push_back("SOFTWARE");
                a.push_back("Codemasters");
                a.push_back("Operation Flashpoint");
                folder = GetRegistryValue(HKEY_LOCAL_MACHINE, a, "Main");
        }
        if(exe.IsEmpty() && !folder.IsEmpty()) {
                if(FileExists(folder + "\\FlashpointResistance.exe")) {
                        exe = folder + "\\FlashpointResistance.exe";
                }
        }

        if(!exe.IsEmpty()) {
                programSettings.exe = exe;
                Form2->Edit1->Text = programSettings.exe;
        }
        if(!folder.IsEmpty()) {
                programSettings.folder = folder;
                updateModFolderList(programSettings.folder);
        } else {
                Form2->BUTTON_NEWCONFIGURATION_ADD->Enabled = false;
                Form2->GROUPBOX_NEWCONFIGURATION->Enabled = false;
        }



        if(!langfile.IsEmpty()) {
                if(FileExists(GetCurrentDir() + "\\" + langfile)) {
                        programSettings.languagefile = langfile;
                }
        }
        try {
                int a = StrToInt(interval);
                programSettings.setInterval(a);
                Form2->UpDown1->Position = a;
        }catch (...) {
                programSettings.setInterval(2);
                Form2->UpDown1->Position = 2;
        }
        Form2->Edit5->Text = String(Form2->UpDown1->Position);
        programSettings.changed = false;
        return ipList;
}

/**
   Searches for languages files
 */

void findLanguageFiles() {
                Form2->ComboBox1->Clear();
               	TSearchRec daten;
                if(0 == FindFirst("OFPM*.lang", faAnyFile, daten)) {
                        try {
                                do {
                                        Form2->ComboBox1->Items->Add(daten.Name);
                                } while(FindNext(daten) == 0);
                        }__finally
                        {
                                FindClose(daten);
                        }
                }
                return;
}


     /*
String extractString(String a, String b) {
        String out = a;
        for(int i = 1; i <= a.Length() - b.Length() + 1; i++) {
                if(a.SubString(i, b.Length()) == b) {
                        out  = a.SubString(1, i - 1);
                        out += a.SubString(i + b.Length(), a.Length() - (b.Length() + i - 1));
                        break;
                }
        }
        return out;
}
       */
void checkConfListState() {
        Form2->BUTTON_EDITCONFIGURATION_EDIT->Enabled = false;
        Form2->BUTTON_CONFIGURATION_REMOVE->Enabled = false;
        Form2->BUTTON_EDITCONFIGURATION_UP->Enabled = true;
        Form2->BUTTON_EDITCONFIGURATION_DOWN->Enabled = true;
        for(int i = 0; i < Form2->ListBox1->Count; i++) {
                if(Form2->ListBox1->Selected[i]) {
                        Form2->BUTTON_EDITCONFIGURATION_EDIT->Enabled = true;
                        Form2->BUTTON_CONFIGURATION_REMOVE->Enabled = true;
                        break;
                }
        }
        return;
}

void exitEditMode() {
        Form2->ListBox1->Enabled = true;
        Form2->BUTTON_EDITCONFIGURATION_OK->Enabled = false;
        Form2->BUTTON_EDITCONFIGURATION_CANCEL->Enabled = false;
        Form2->BUTTON_EDITCONFIGURATION_OK->Visible = false;
        Form2->BUTTON_EDITCONFIGURATION_CANCEL->Visible = false;
        Form2->BUTTON_NEWCONFIGURATION_ADD->Visible = true;
        Form2->BUTTON_NEWCONFIGURATION_ADD->Enabled = true;
        Form2->BUTTON_NEWCONFIGURATION_CLEAR->Visible = true;
        Form2->BUTTON_NEWCONFIGURATION_CLEAR->Enabled = true;
        Form2->BUTTON_NEWCONFIGURATION_CLEAR->Click();
        checkConfListState();
        return;
}

String TForm2::getCurrentPlayerName() {
        if(!Form2->COMBOBOX_PROFILE->Enabled) {
                return "";
        } else {
                return Form2->COMBOBOX_PROFILE->Text;
        }
}

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BUTTON_OFPEXECUTABLE_BROWSEClick(TObject *Sender)
{
        if(!Edit1->Text.IsEmpty()) {
                OpenDialog1->InitialDir = getFolder(programSettings.exe);
        }
        OpenDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
        #include "guiDB.cpp"
        findLanguageFiles();
        list<String> ipList = readConfigFile();
        updateLanguage(programSettings.languagefile);
        checkIfExeAndPlayerIsSet(programSettings.folder, programSettings.player);
        Form1->Visible = true;
        Form1->readServerList(ipList);
        updateConfList();
        Form2->ComboBox1->Text = programSettings.languagefile;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::OpenDialog1CanClose(TObject *Sender,
      bool &CanClose)
{
        if(CanClose) {
                programSettings.exe = OpenDialog1->FileName;
                programSettings.folder = getFolder(programSettings.exe);
                Edit1->Text = programSettings.exe;
                updateModFolderList(programSettings.folder);
                checkIfExeAndPlayerIsSet(programSettings.folder, programSettings.player);
                Form2->setSettingsChanged();
                OpenDialog1->InitialDir = "";
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button7Click(TObject *Sender)
{
        for(int i = 0; i < ListBox2->Count; i++) {
                if(ListBox2->Selected[i]) {
                        ListBox3->Items->Add(ListBox2->Items->Strings[i]);
                        ListBox2->Items->Delete(i);
                        i--;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button6Click(TObject *Sender)
{
        for(int i = 0; i < ListBox3->Count; i++) {
                if(ListBox3->Selected[i]) {
                        ListBox2->Items->Add(ListBox3->Items->Strings[i]);
                        ListBox3->Items->Delete(i);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BUTTON_NEWCONFIGURATION_UPClick(TObject *Sender)
{
        for(int i = 0; i < ListBox3->Count; i++) {
                if(ListBox3->Selected[i]) {
                        if(i > 0) {
                                ListBox3->Items->Exchange(i, i - 1);
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BUTTON_NEWCONFIGURATION_DOWNClick(TObject *Sender)
{
        for(int i = 0; i < ListBox3->Count; i++) {
                if(ListBox3->Selected[i]) {
                        if(i < ListBox3->Count - 1) {
                                ListBox3->Items->Exchange(i, i + 1);
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BUTTON_CONFIGURATION_REMOVEClick(TObject *Sender)
{
        for(int i = 0; i < ListBox1->Count; i++) {
                if(ListBox1->Selected[i]) {
                        TObject *t = ListBox1->Items->Objects[i];
                        int j = (int) t;
                        programSettings.pSdeleteConf(j);
                        ListBox1->Items->Delete(i);
                }
        }
        if(ListBox1->Items->Count < confAmount) {
                BUTTON_NEWCONFIGURATION_ADD->Enabled = true;
        }
        updateConfList();
        checkConfListState();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::BUTTON_NEWCONFIGURATION_ADDClick(TObject *Sender)
{
                list<String> a;
                for(int i = 0; i < ListBox3->Count; i++) {
                        a.push_back(ListBox3->Items->Strings[i]);
                }
                Configuration newC = Configuration(Edit6->Text, a, Edit3->Text, Edit4->Text, CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked, CHECKBOX_NEWCONFIGURATION_NOMAP->Checked);
                programSettings.pSaddConf(newC);
                if(ListBox1->Items->Count >= confAmount) {
                        BUTTON_NEWCONFIGURATION_ADD->Enabled = false;
                }
                updateConfList();
                Form2->setSettingsChanged();
                checkConfListState();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Edit5Change(TObject *Sender)
{
        try {
                int a = StrToInt(Edit5->Text);
                if(a < UpDown1->Min) {
                        Edit5->Text = UpDown1->Position;
                } else if(a > UpDown1->Max) {
                        Edit5->Text = UpDown1->Position;
                }
        } catch (...) {
                Edit5->Text = UpDown1->Position;
        }
        programSettings.setInterval(UpDown1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
        programSettings.setInterval(UpDown1->Position);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::BUTTON_NEWCONFIGURATION_CLEARClick(TObject *Sender)
{
        while(ListBox3->Count > 0) {
                ListBox2->Items->Add(ListBox3->Items->Strings[0]);
                ListBox3->Items->Delete(0);
        }
        Edit3->Text = "";
        Edit4->Text = "";
        Edit6->Text = "";
        CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked = true;
        CHECKBOX_NEWCONFIGURATION_NOMAP->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
        checkIfExeAndPlayerIsSet(programSettings.folder, programSettings.player);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_ESCAPE) {
                Form2->Close();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
        updateModFolderList(programSettings.folder);
        exitEditMode();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{
        if(FileExists(programSettings.workdir + "\\" + ComboBox1->Text)) {
                programSettings.languagefile = ComboBox1->Text;
                updateLanguage(programSettings.languagefile);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BUTTON_EDITCONFIGURATION_EDITClick(TObject *Sender)
{
        BUTTON_NEWCONFIGURATION_CLEAR->Click();
        ListBox1->Enabled = false;
        BUTTON_NEWCONFIGURATION_ADD->Visible = false;
        BUTTON_NEWCONFIGURATION_ADD->Enabled = false;
        BUTTON_NEWCONFIGURATION_CLEAR->Visible = false;
        BUTTON_NEWCONFIGURATION_CLEAR->Enabled = false;
        BUTTON_EDITCONFIGURATION_OK->Visible = true;
        BUTTON_EDITCONFIGURATION_OK->Enabled = true;
        BUTTON_EDITCONFIGURATION_CANCEL->Visible = true;
        BUTTON_EDITCONFIGURATION_CANCEL->Enabled = true;
        BUTTON_EDITCONFIGURATION_EDIT->Enabled = false;
        BUTTON_EDITCONFIGURATION_UP->Enabled = false;
        BUTTON_EDITCONFIGURATION_DOWN->Enabled = false;
        BUTTON_CONFIGURATION_REMOVE->Enabled = false;

        for(int i = 0; i < ListBox1->Count; i++) {
                if(ListBox1->Selected[i]) {
                        TObject *t = ListBox1->Items->Objects[i];
                        int j = (int) t;
                        Configuration edit = programSettings.startupConfs[j];
                        Edit6->Text = edit.label;
                        Edit3->Text = edit.password;
                        for (list<String>::iterator ci = edit.mods.begin(); ci != edit.mods.end(); ++ci) {
                                ListBox3->Items->Add(*ci);
                                for(int k = 0; k < ListBox2->Count; k++) {
                                        if(*ci == ListBox2->Items->Strings[k]) {
                                                ListBox2->Items->Delete(k);
                                                break;
                                        }
                                }
                        }
                        CHECKBOX_NEWCONFIGURATION_NOMAP->Checked = false;
                        CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked = false;
                        String line = "";
                        for (list<String>::iterator di = edit.addParameters.begin(); di != edit.addParameters.end(); ++di) {
                                String tmp = *di;
                                String nomap = "-nomap";
                                String nosplash = "-nosplash";
                                if((nomap == tmp) || nosplash == tmp) {
                                        if(nomap == tmp) {
                                                CHECKBOX_NEWCONFIGURATION_NOMAP->Checked = true;
                                        }
                                        if(nosplash == tmp) {
                                                CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked = true;
                                        }
                                } else {
                                        if(line.Length() > 0) {
                                                line += " ";
                                        }
                                        line += tmp;
                                }

                        }
                        Edit4->Text = line;
                        break;
                }
        }

}
//---------------------------------------------------------------------------
void __fastcall TForm2::BUTTON_EDITCONFIGURATION_OKClick(TObject *Sender)
{
        list<String> a;
        for(int i = 0; i < ListBox3->Count; i++) {
                a.push_back(ListBox3->Items->Strings[i]);
        }
        for(int i = 0; i < ListBox1->Count; i++) {
                if(ListBox1->Selected[i]) {
                        TObject *t = ListBox1->Items->Objects[i];
                        int j = (int) t;
                        programSettings.startupConfs[j].label = Edit6->Text;
                        programSettings.startupConfs[j].mods = a;
                        programSettings.startupConfs[j].password = Edit3->Text;
                        programSettings.startupConfs[j].addParameters = Form1->splitUpMessage(Edit4->Text," ");
                        if(CHECKBOX_NEWCONFIGURATION_NOMAP->Checked) {
                                programSettings.startupConfs[j].addParameters.push_back("-nomap");
                        }
                        if(CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked) {
                                programSettings.startupConfs[j].addParameters.push_back("-nosplash");
                        }
                        break;
                }
        }
        updateConfList();
        Form2->setSettingsChanged();
        exitEditMode();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ListBox1Click(TObject *Sender)
{
        checkConfListState();              
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BUTTON_EDITCONFIGURATION_CANCELClick(
      TObject *Sender)
{
        exitEditMode();
}
//---------------------------------------------------------------------------



void __fastcall TForm2::COMBOBOX_PROFILEChange(TObject *Sender)
{
        String tmp = COMBOBOX_PROFILE->Text;
        bool found = false;
        for(int i = 0; i < COMBOBOX_PROFILE->Items->Count; i++) {
                if(COMBOBOX_PROFILE->Items->Strings[i] == tmp) {
                        found = true;
                        break;
                }
        }
        if(!found) {
                COMBOBOX_PROFILE->Text = programSettings.player;
        } else {
                programSettings.player = COMBOBOX_PROFILE->Text;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BUTTON_EDITCONFIGURATION_UPClick(TObject *Sender)
{
        for(int i = 0; i < ListBox1->Count; i++) {
                if(ListBox1->Selected[i]) {
                        if(i > 0) {
                                ListBox1->Items->Exchange(i, i - 1);
                                Configuration tmp = programSettings.startupConfs[i];
                                programSettings.startupConfs[i] = programSettings.startupConfs[i - 1];
                                programSettings.startupConfs[i - 1] = tmp;

                                TObject *t = ListBox1->Items->Objects[i];
                                ListBox1->Items->Objects[i] = ListBox1->Items->Objects[i - 1];
                                ListBox1->Items->Objects[i - 1] = t;
                                Form2->setSettingsChanged();
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BUTTON_EDITCONFIGURATION_DOWNClick(TObject *Sender)
{
        for(int i = 0; i < ListBox1->Count; i++) {
                if(ListBox1->Selected[i]) {
                        if(i < ListBox1->Count - 1) {
                                ListBox1->Items->Exchange(i, i + 1);
                                Configuration tmp = programSettings.startupConfs[i];
                                programSettings.startupConfs[i] = programSettings.startupConfs[i + 1];
                                programSettings.startupConfs[i + 1] = tmp;
                                TObject *t = ListBox1->Items->Objects[i];
                                ListBox1->Items->Objects[i] = ListBox1->Items->Objects[i + 1];
                                ListBox1->Items->Objects[i + 1] = t;
                                Form2->setSettingsChanged();
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------

