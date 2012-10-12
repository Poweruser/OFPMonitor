//---------------------------------------------------------------------------

#include "AudioTask.h"
#include "CustomNotification.h"
#include "StringSplitter.h"
#include <vcl.h>                                                          
#include <filectrl.hpp>
#include <mmsystem.h>
#include <windows.h>       
                                                            
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWINDOW_SETTINGS *WINDOW_SETTINGS;

#include "guiDBDefs.cpp"
#include "FileVersion.h"
#include "ConfigReader.h"

extern unsigned long resolv(char *host) ; 

void TWINDOW_SETTINGS::setModel(OFPMonitorModel *ofpm) {
        this->ofpm = ofpm;
}

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
   Refreshes the list box for the configurations in the settings window
 */

void TWINDOW_SETTINGS::updateConfList() {
        WINDOW_SETTINGS->LISTBOX_CONFIGURATIONS->Clear();
        int comboindex = WINDOW_SETTINGS->ComboBox2->Items->IndexOf(WINDOW_SETTINGS->ComboBox2->Text);
        if(comboindex >= 0) {
                Game *g = (Game*) (WINDOW_SETTINGS->ComboBox2->Items->Objects[comboindex]);

                if(g != NULL) {
                        for(int i = 0; i < g->getConfigurationsCount(); i++) {
                                Configuration *conf = g->getConfiguration(i);
                                if(conf != NULL) {
                                        WINDOW_SETTINGS->LISTBOX_CONFIGURATIONS->Items->AddObject(conf->createListEntry(), (TObject *) conf);
                                }
                        }
                }
        }
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
   Reads all folders within the game folder and displays them in the
   modfolder list box in the settings window
 */

void TWINDOW_SETTINGS::updateModFolderList(String ofpfolder) {
        WINDOW_SETTINGS->LISTBOX_MODFOLDERS_ALL->Clear();
        if(!ofpfolder.IsEmpty()) {
        	TSearchRec daten;
                if(0 == FindFirst((ofpfolder +"\\*").c_str(), faDirectory, daten)) {
                        try {
                                do {
                                        if(daten.Size == 0 && daten.Name != "." && daten.Name != "..") {
                                                WINDOW_SETTINGS->LISTBOX_MODFOLDERS_ALL->Items->Add(String(daten.Name));
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

String TWINDOW_SETTINGS::getGuiString(String ident) {
        String out = "";
        for (list<guiString>::iterator ci = guiStrings.begin(); ci != guiStrings.end(); ++ci) {
                if((*ci).identifier == ident) {
                        out = (*ci).value;
                        break;
                }
        }
        return out;
}

void TWINDOW_SETTINGS::refreshGamesModList() {
        TComboBox *box = this->ComboBox2;
        String last = box->Text;
        box->Items->Clear();
        for(int i = 0; i < GAMESTOTAL; i++) {
                Game *g = this->ofpm->getGame((OFPGames)i);
                if(g != NULL) {
                        if(g->isActive() && g->isValid()) {
                                box->Items->AddObject(g->getFullName(), (TObject *)g);
                        }
                }
        }

        if(box->Items->Count > 0) {
                int index = box->Items->IndexOf(last);
                if(index > -1) {
                        box->ItemIndex = index;
                } else {
                        box->ItemIndex = 0;
                }
                box->Enabled = true;
                WINDOW_SETTINGS->GROUPBOX_NEWCONFIGURATION->Enabled = true;
        } else {
                box->Enabled = false;
        }
        box->OnChange(WINDOW_SETTINGS);
}

void TWINDOW_SETTINGS::updateGames() {
        TComboBox *combobox;
        TCheckBox *checkbox;
        TEdit *edit;
        TLabel *label;
        TGroupBox *groupbox;
        for(int i = 0; i < GAMESTOTAL; i++) {
                Game *g = this->ofpm->getGame((OFPGames)i);
                if(i == OFPCWC) {
                        combobox = WINDOW_SETTINGS->COMBOBOX_OFPCWC_PROFILE;
                        checkbox = WINDOW_SETTINGS->CHECKBOX_OFPCWC;
                        edit = WINDOW_SETTINGS->EDIT_OFPCWC_EXECUTABLE;
                        label = WINDOW_SETTINGS->LABEL_OFPCWC_DETECTEDVERSION;
                        groupbox = WINDOW_SETTINGS->GROUPBOX_OFPCWC;
                } else if(i == OFPRES) {
                        combobox = WINDOW_SETTINGS->COMBOBOX_OFPRES_PROFILE;
                        checkbox = WINDOW_SETTINGS->CHECKBOX_OFPRES;
                        edit = WINDOW_SETTINGS->EDIT_OFPRES_EXECUTABLE;
                        label = WINDOW_SETTINGS->LABEL_OFPRES_DETECTEDVERSION;
                        groupbox = WINDOW_SETTINGS->GROUPBOX_OFPRES;
                } else if(i == ARMACWA) {
                        combobox = WINDOW_SETTINGS->COMBOBOX_ARMACWA_PROFILE;
                        checkbox = WINDOW_SETTINGS->CHECKBOX_ARMACWA;
                        edit = WINDOW_SETTINGS->EDIT_ARMACWA_EXECUTABLE;
                        label = WINDOW_SETTINGS->LABEL_ARMACWA_DETECTEDVERSION;
                        groupbox = WINDOW_SETTINGS->GROUPBOX_ARMACWA;
                }
                combobox->Items->Clear();
                edit->Text = "";
                label->Caption = "";
                groupbox->Visible = checkbox->Checked;
                if(g->isActive()) {
                        edit->Text = g->getGameExe();
                        if(!(g->getGameExe().IsEmpty())) {
                                label->Caption = WINDOW_SETTINGS->getGuiString("STRING_DETECTEDVERSION") + "  " + IntToStr(g->getFileVersion());
                        }
                        list<String> profiles = g->findPlayerProfiles();
                        String textToSet = "";
                        if(profiles.size() > 0) {
                                combobox->Enabled = true;
                                bool playerMatching = false;
                                for (list<String>::iterator ci = profiles.begin(); ci != profiles.end(); ++ci) {
                                        combobox->Items->Add(*ci);
                                        if((*ci) == g->getProfileName()) {
                                                playerMatching = true;
                                        }
                                }
                                if(!playerMatching) {
                                        g->detectPlayer("");
                                }
                                textToSet = g->getProfileName();
                        } else {
                                combobox->Enabled = false;
                                g->setProfileName("");
                                textToSet = WINDOW_SETTINGS->getGuiString("STRING_NOPROFILES");
                                combobox->Items->Add(textToSet);
                        }
                        combobox->ItemIndex = combobox->Items->IndexOf(textToSet);
                        checkbox->Checked = true;
                }
        }
        this->refreshGamesModList();
}


/**
   Applys a language file to the Gui
 */

void TWINDOW_SETTINGS::updateLanguage(String languagefile) {
        TStringList *file = new TStringList;
        String pathAndFile = this->ofpm->getWorkDir() + "\\" + languagefile;
        guiStrings.clear();
        guiStrings.push_back(guiString("STRING_YES","Yes"));
        guiStrings.push_back(guiString("STRING_NO","No"));
        guiStrings.push_back(guiString("STRING_NAME","Name"));
        guiStrings.push_back(guiString("STRING_ONLINE","Online:"));
        guiStrings.push_back(guiString("STRING_LISTED","Listed:"));
        guiStrings.push_back(guiString("STRING_ERRORS","Errors:"));
        guiStrings.push_back(guiString("STRING_NOPROFILES","No player profiles found!"));
        guiStrings.push_back(guiString("STRING_PLAYER_ALREADY_ON_SERVER","There's already a player with the same name on the server. Do you still want to start OFP?"));
        guiStrings.push_back(guiString("STRING_FROM","From:"));
        guiStrings.push_back(guiString("STRING_TO","To:"));
        guiStrings.push_back(guiString("STRING_PLAYBACKVOLUME","Volume:"));
        guiStrings.push_back(guiString("STRING_AUDIOFILE","MP3-File:"));
        guiStrings.push_back(guiString("STRING_MARKINGCOLOR","Marking color:"));
        guiStrings.push_back(guiString("STRING_MINIMUM","Min."));
        guiStrings.push_back(guiString("STRING_MAXIMUM","Max:"));
        guiStrings.push_back(guiString("STRING_CHAT_CONNECTINGTO","Connecting to:"));
        guiStrings.push_back(guiString("STRING_CHAT_CHANNEL","Channel:"));
        guiStrings.push_back(guiString("STRING_CHAT_DISCONNECTED","Disconnected."));
        guiStrings.push_back(guiString("STRING_CHAT_CONNECTING_FAILED","Connecting failed."));
        guiStrings.push_back(guiString("STRING_CHAT_JOINED","joined"));
        guiStrings.push_back(guiString("STRING_CHAT_LEFT","left"));
        guiStrings.push_back(guiString("STRING_CHAT_CLOSE","Close"));
        guiStrings.push_back(guiString("STRING_CHAT_CHATWITH","Chat with ..."));        
        guiStrings.push_back(guiString("STRING_CHAT_CONNECTIONLOST","Connection lost. Reconnecting ..."));
        guiStrings.push_back(guiString("STRING_DETECTEDVERSION","Detected file version: "));
        guiStrings.push_back(guiString("STRING_CHAT_LEFT","left"));
        guiStrings.push_back(guiString("STRING_BROWSE","Browse ..."));
        guiStrings.push_back(guiString("STRING_OFPEXECUTABLE","Executable"));
        guiStrings.push_back(guiString("STRING_PROFILE","Player name:"));
        guiStrings.push_back(guiString("STRING_UPDATE1","New version available:"));
        guiStrings.push_back(guiString("STRING_UPDATE2","Do you want to update now?"));
        guiStrings.push_back(guiString("STRING_UPDATE_ALREADYLATEST","You already have the latest version"));
        guiStrings.push_back(guiString("STRING_SERVERS_FAVORITE","Favorites"));
        guiStrings.push_back(guiString("STRING_SERVERS_WATCHED","Watched"));
        guiStrings.push_back(guiString("STRING_SERVERS_PERSISTENT","Persistent"));
        guiStrings.push_back(guiString("STRING_SERVERS_BLOCKED","Blocked"));
        guiStrings.push_back(guiString("STRING_SERVERS_ADDERROR","Could not resolve:"));
        guiStrings.push_back(guiString("STRING_PASSWORDDIALOG_TITLE", "Password required"));
        guiStrings.push_back(guiString("STRING_PASSWORDDIALOG_PROMPT", "This server is password-protected. Enter it here:"));


        if(FileExists(pathAndFile)) {
                String sign = "=";
                file->LoadFromFile(pathAndFile);
                String tmp;
                guiStrings.clear();
                list<String> val;
                for(int i = 0; i < file->Count; i++) {
                        Application->ProcessMessages();
                        val.clear();
                        tmp = file->Strings[i].Trim();
                        if(tmp.AnsiPos("BUTTON") == 1) {
                                val = getVarAndValue(tmp, sign);
                                for(int j = 0; j < GetArrLength(guiButton); j++) {
                                        if(guiButton[j]->Name == val.front()) {
                                                guiButton[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.AnsiPos("LABEL") == 1) {
                                val = getVarAndValue(tmp, sign);
                                for(int j = 0; j < GetArrLength(guiLabel); j++) {
                                        if(guiLabel[j]->Name == val.front()) {
                                                guiLabel[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.AnsiPos("CHECKBOX") == 1) {
                                val = getVarAndValue(tmp, sign);
                                for(int j = 0; j < GetArrLength(guiCheckBox); j++) {
                                        if(guiCheckBox[j]->Name == val.front()) {
                                                guiCheckBox[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.AnsiPos("GROUPBOX") == 1) {
                                val = getVarAndValue(tmp, sign);
                                for(int j = 0; j < GetArrLength(guiGroupBox); j++) {
                                        if(guiGroupBox[j]->Name == val.front()) {
                                                guiGroupBox[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.AnsiPos("MENUITEM") == 1) {
                                val = getVarAndValue(tmp, sign);
                                for(int j = 0; j < GetArrLength(guiMenuItem); j++) {
                                        if(guiMenuItem[j]->Name == val.front()) {
                                                guiMenuItem[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.AnsiPos("WINDOW") == 1) {
                                val = getVarAndValue(tmp, sign);
                                for(int j = 0; j < GetArrLength(guiForm); j++) {
                                        if(guiForm[j]->Name == val.front()) {
                                                guiForm[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.AnsiPos("RADIOBUTTON") == 1) {
                                val = getVarAndValue(tmp, sign);
                                for(int j = 0; j < GetArrLength(guiRadioButton); j++) {
                                        if(guiRadioButton[j]->Name == val.front()) {
                                                guiRadioButton[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        } else if(tmp.AnsiPos("TABSHEET") == 1) {
                                val = getVarAndValue(tmp, sign);
                                for(int j = 0; j < GetArrLength(guiTabSheet); j++) {
                                        if(guiTabSheet[j]->Name == val.front()) {
                                                guiTabSheet[j]->Caption = val.back();
                                                break;
                                        }
                                }
                        }
                        if(tmp.AnsiPos(sign)) {
                                val = getVarAndValue(tmp, sign);
                                String f = val.front();
                                String b = val.back();
                                guiStrings.push_back(guiString(f,b));
                        }
                }
                Form1->StringGrid1->Cells[0][0] = WINDOW_SETTINGS->getGuiString("STRING_ID");
                Form1->StringGrid1->Cells[1][0] = WINDOW_SETTINGS->getGuiString("STRING_NAME");
                Form1->StringGrid1->Cells[2][0] = WINDOW_SETTINGS->getGuiString("STRING_PLAYERS");
                Form1->StringGrid1->Cells[3][0] = WINDOW_SETTINGS->getGuiString("STRING_STATUS");
                Form1->StringGrid1->Cells[4][0] = WINDOW_SETTINGS->getGuiString("STRING_ISLAND");
                Form1->StringGrid1->Cells[5][0] = WINDOW_SETTINGS->getGuiString("STRING_MISSION");
                Form1->StringGrid1->Cells[6][0] = WINDOW_SETTINGS->getGuiString("STRING_PING");
                Form1->StringGrid2->Cells[0][0] = WINDOW_SETTINGS->getGuiString("STRING_NAME");
                Form1->StringGrid2->Cells[1][0] = WINDOW_SETTINGS->getGuiString("STRING_SCORE");
                Form1->StringGrid2->Cells[2][0] = WINDOW_SETTINGS->getGuiString("STRING_DEATHS");
                Form1->StringGrid2->Cells[3][0] = WINDOW_SETTINGS->getGuiString("STRING_TEAM");
                WINDOW_SETTINGS->StringGrid1->Cells[0][0] = WINDOW_SETTINGS->getGuiString("STRING_ID");
                WINDOW_SETTINGS->StringGrid1->Cells[1][0] = WINDOW_SETTINGS->getGuiString("STRING_ADDRESS");
                WINDOW_SETTINGS->StringGrid1->Cells[2][0] = WINDOW_SETTINGS->getGuiString("STRING_NAME");

                if(!WINDOW_SETTINGS->COMBOBOX_OFPRES_PROFILE->Enabled) {
                        WINDOW_SETTINGS->COMBOBOX_OFPRES_PROFILE->Text = WINDOW_SETTINGS->getGuiString("STRING_NOPROFILES");
                }
                if(!WINDOW_SETTINGS->COMBOBOX_OFPCWC_PROFILE->Enabled) {
                        WINDOW_SETTINGS->COMBOBOX_OFPCWC_PROFILE->Text = WINDOW_SETTINGS->getGuiString("STRING_NOPROFILES");
                }
                if(!WINDOW_SETTINGS->COMBOBOX_ARMACWA_PROFILE->Enabled) {
                        WINDOW_SETTINGS->COMBOBOX_ARMACWA_PROFILE->Text = WINDOW_SETTINGS->getGuiString("STRING_NOPROFILES");
                }
                WINDOW_SETTINGS->LABEL_FILTER_MISSIONNAME_BOX->Caption = Form1->LABEL_FILTER_MISSIONNAME->Caption;
                WINDOW_SETTINGS->LABEL_FILTER_SERVERNAME_BOX->Caption = Form1->LABEL_FILTER_SERVERNAME->Caption;
                WINDOW_SETTINGS->LABEL_FILTER_PLAYERNAME_BOX->Caption = Form1->LABEL_FILTER_PLAYERNAME->Caption;
                WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_CANCEL->Caption = WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_CANCEL->Caption;
                WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_EDIT->Caption = WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_EDIT->Caption;
                WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_OK->Caption = WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_OK->Caption;
                WINDOW_SETTINGS->BUTTON_NEWNOTIFICATION_ADD->Caption = WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_ADD->Caption;
                WINDOW_SETTINGS->BUTTON_NEWNOTIFICATION_CLEAR->Caption = WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_CLEAR->Caption;
                WINDOW_SETTINGS->BUTTON_NOTIFICATION_REMOVE->Caption = WINDOW_SETTINGS->BUTTON_CONFIGURATION_REMOVE->Caption;
                WINDOW_SETTINGS->CHECKBOX_FILTER_CREATING->Caption = Form1->CHECKBOX_FILTER_CREATING->Caption;
                WINDOW_SETTINGS->CHECKBOX_FILTER_WAITING->Caption = Form1->CHECKBOX_FILTER_WAITING->Caption;
                WINDOW_SETTINGS->CHECKBOX_FILTER_BRIEFING->Caption = Form1->CHECKBOX_FILTER_BRIEFING->Caption;
                WINDOW_SETTINGS->CHECKBOX_FILTER_SETTINGUP->Caption = Form1->CHECKBOX_FILTER_SETTINGUP->Caption;
                WINDOW_SETTINGS->CHECKBOX_FILTER_PLAYING->Caption = Form1->CHECKBOX_FILTER_PLAYING->Caption;
                WINDOW_SETTINGS->CHECKBOX_FILTER_DEBRIEFING->Caption = Form1->CHECKBOX_FILTER_DEBRIEFING->Caption;
                WINDOW_SETTINGS->CHECKBOX_FILTER_MINPLAYERS->Caption = WINDOW_SETTINGS->getGuiString("STRING_MINIMUM");
                WINDOW_SETTINGS->CHECKBOX_FILTER_MAXPLAYERS->Caption = WINDOW_SETTINGS->getGuiString("STRING_MAXIMUM");
                WINDOW_SETTINGS->BUTTON_BROWSE->Caption = WINDOW_SETTINGS->getGuiString("STRING_BROWSE");
                WINDOW_SETTINGS->BUTTON_OFPCWC_BROWSE->Caption = WINDOW_SETTINGS->getGuiString("STRING_BROWSE");
                WINDOW_SETTINGS->BUTTON_OFPRES_BROWSE->Caption = WINDOW_SETTINGS->getGuiString("STRING_BROWSE");
                WINDOW_SETTINGS->BUTTON_ARMACWA_BROWSE->Caption = WINDOW_SETTINGS->getGuiString("STRING_BROWSE");
                WINDOW_SETTINGS->LABEL_FILTER_PASSWORD->Caption = Form1->LABEL_FILTER_PASSWORD->Caption;
                WINDOW_SETTINGS->LABEL_FILTER_STATUS->Caption = Form1->LABEL_FILTER_STATUS->Caption;
                WINDOW_SETTINGS->LABEL_NOTIFICATION_NAME->Caption = WINDOW_SETTINGS->getGuiString("STRING_NAME");
                WINDOW_SETTINGS->LABEL_FILTER_PLAYERS->Caption = WINDOW_SETTINGS->getGuiString("STRING_PLAYERS");
                WINDOW_SETTINGS->CHECKBOX_FILTER_WITHOUTPASSWORD->Caption = Form1->CHECKBOX_FILTER_WITHOUTPASSWORD->Caption;
                WINDOW_SETTINGS->CHECKBOX_FILTER_WITHPASSWORD->Caption = Form1->CHECKBOX_FILTER_WITHPASSWORD->Caption;
                WINDOW_SETTINGS->LABEL_VOLUME->Caption = WINDOW_SETTINGS->getGuiString("STRING_PLAYBACKVOLUME");
                WINDOW_SETTINGS->LABEL_MARKINGCOLOR->Caption = WINDOW_SETTINGS->getGuiString("STRING_MARKINGCOLOR");
                WINDOW_SETTINGS->LABEL_AUDIOFILE->Caption = WINDOW_SETTINGS->getGuiString("STRING_AUDIOFILE");
                WINDOW_SETTINGS->LABEL_AUDIO_FROM->Caption = WINDOW_SETTINGS->getGuiString("STRING_FROM");
                WINDOW_SETTINGS->LABEL_AUDIO_TO->Caption = WINDOW_SETTINGS->getGuiString("STRING_TO");
                WINDOW_SETTINGS->LABEL_OFPCWC_EXECUTABLE->Caption = WINDOW_SETTINGS->getGuiString("STRING_OFPEXECUTABLE");
                WINDOW_SETTINGS->LABEL_OFPRES_EXECUTABLE->Caption = WINDOW_SETTINGS->getGuiString("STRING_OFPEXECUTABLE");
                WINDOW_SETTINGS->LABEL_ARMACWA_EXECUTABLE->Caption = WINDOW_SETTINGS->getGuiString("STRING_OFPEXECUTABLE");
                WINDOW_SETTINGS->LABEL_OFPCWC_PLAYERNAME->Caption = WINDOW_SETTINGS->getGuiString("STRING_PROFILE");
                WINDOW_SETTINGS->LABEL_OFPRES_PLAYERNAME->Caption = WINDOW_SETTINGS->getGuiString("STRING_PROFILE");
                WINDOW_SETTINGS->LABEL_ARMACWA_PLAYERNAME->Caption = WINDOW_SETTINGS->getGuiString("STRING_PROFILE");

        }
}


/**
   Searches for languages files
 */

void TWINDOW_SETTINGS::findLanguageFiles() {
        String flags[8] = { "chinese", "czech", "german",
                        "english", "french", "dutch",
                        "polish", "russian" };
        WINDOW_SETTINGS->ComboBox1->Clear();
        TSearchRec daten;
        if(0 == FindFirst(this->ofpm->getWorkDir() + "\\OFPM*.lang", faAnyFile, daten)) {
                try {
                        do {
                                for(int i = 0; i < 8; i++) {
                                        if(daten.Name.LowerCase().Pos(flags[i])) {
                                                WINDOW_SETTINGS->ComboBox1->ItemsEx->AddItem(daten.Name, i, i, -1, -1, NULL);
                                                break;
                                        }
                                }
                        } while(FindNext(daten) == 0);
                }__finally {
                        FindClose(daten);
                }
        }
}

void TWINDOW_SETTINGS::checkConfListState() {
        bool itemSelected = false;
        for(int i = 0; i < WINDOW_SETTINGS->LISTBOX_CONFIGURATIONS->Count; i++) {
                if(WINDOW_SETTINGS->LISTBOX_CONFIGURATIONS->Selected[i]) {
                        itemSelected = true;
                        break;
                }
        }
        bool limitReached = WINDOW_SETTINGS->LISTBOX_CONFIGURATIONS->Items->Count >= 50;
        WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_ADD->Enabled = !limitReached;
        WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_EDIT->Enabled = itemSelected;
        WINDOW_SETTINGS->BUTTON_CONFIGURATION_REMOVE->Enabled = itemSelected;
        WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_COPY->Enabled = itemSelected && !limitReached;
        WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_UP->Enabled = itemSelected;
        WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_DOWN->Enabled = itemSelected;
}

void TWINDOW_SETTINGS::exitEditMode() {
        WINDOW_SETTINGS->LISTBOX_CONFIGURATIONS->Enabled = true;
        WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_OK->Enabled = false;
        WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_CANCEL->Enabled = false;
        WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_OK->Visible = false;
        WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_CANCEL->Visible = false;
        WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_ADD->Visible = true;
        WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_ADD->Enabled = true;
        WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_CLEAR->Visible = true;
        WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_CLEAR->Enabled = true;
        WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_CLEAR->Click();
        this->checkConfListState();
}

void TWINDOW_SETTINGS::checkForAutoDetection(OFPGames id) {
        Game *g = this->ofpm->getGame(id);
        if(g != NULL) {
                if(g->isValid()) {
                        g->setActive(true);
                } else {
                        g->autodetect("");
                }
        }
}

void TWINDOW_SETTINGS::printPlaybackRange(AudioPosition start, AudioPosition end) {
        WINDOW_SETTINGS->EDIT_SONGSTART_MIN->Text = IntToStr(start.getMinutes());
        WINDOW_SETTINGS->EDIT_SONGSTART_SEC->Text = IntToStr(start.getSeconds());
        WINDOW_SETTINGS->EDIT_SONGSTART_MILL->Text = IntToStr(start.getMilliSeconds());
        WINDOW_SETTINGS->EDIT_SONGEND_MIN->Text = IntToStr(end.getMinutes());
        WINDOW_SETTINGS->EDIT_SONGEND_SEC->Text = IntToStr(end.getSeconds());
        WINDOW_SETTINGS->EDIT_SONGEND_MILL->Text = IntToStr(end.getMilliSeconds());
}

void TWINDOW_SETTINGS::printPlaybackPosition(AudioPosition current) {
        WINDOW_SETTINGS->LabelMilli->Caption = this->addLeadingZeros(current.getMilliSeconds(), 3);
        WINDOW_SETTINGS->LabelSeconds->Caption = this->addLeadingZeros(current.getSeconds(), 2) + ":";
        WINDOW_SETTINGS->LabelMinutes->Caption = this->addLeadingZeros(current.getMinutes(), 2) + ":";
}


void TWINDOW_SETTINGS::updateNotificationsList() {
        WINDOW_SETTINGS->LISTBOX_NOTIFICATIONS->Clear();
        for(int i = 0; i < this->ofpm->getNotificationCount(); i++) {
                CustomNotification* notif = this->ofpm->getNotification(i);
                if(notif != NULL) {
                        WINDOW_SETTINGS->LISTBOX_NOTIFICATIONS->Items->AddObject(notif->getName(), (TObject *) notif);
                }
        }
}
 

void TWINDOW_SETTINGS::checkNotificationListState() {
        WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_EDIT->Enabled = false;
        WINDOW_SETTINGS->BUTTON_NOTIFICATION_REMOVE->Enabled = false;
        for(int i = 0; i < WINDOW_SETTINGS->LISTBOX_NOTIFICATIONS->Count; i++) {
                if(WINDOW_SETTINGS->LISTBOX_NOTIFICATIONS->Selected[i]) {
                        WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_EDIT->Enabled = true;
                        WINDOW_SETTINGS->BUTTON_NOTIFICATION_REMOVE->Enabled = true;
                        break;
                }
        }
}

void TWINDOW_SETTINGS::updateChatSettings() {
        WINDOW_SETTINGS->COMBOBOX_CHAT_USERNAME->Clear();
        for(int i = 0; i < GAMESTOTAL; i++) {
                Game *g = this->ofpm->getGame((OFPGames)i);
                if(g != NULL) {
                        list<String> profiles = g->findPlayerProfiles();
                        for (list<String>::iterator ci = profiles.begin(); ci != profiles.end(); ++ci) {
                                if(WINDOW_SETTINGS->COMBOBOX_CHAT_USERNAME->Items->IndexOf(*ci) == -1) {
                                        WINDOW_SETTINGS->COMBOBOX_CHAT_USERNAME->Items->Add(*ci);
                                }
                        }
                }
        }
        String user = Form1->getChatUserName();
        if(!user.IsEmpty()) {
                WINDOW_SETTINGS->COMBOBOX_CHAT_USERNAME->Items->Add(user);
        }
        WINDOW_SETTINGS->COMBOBOX_CHAT_USERNAME->Text = Form1->getChatUserName();
        WINDOW_SETTINGS->EDIT_CHAT_IRCSERVER_ADDRESS->Text = Form1->getChatHost();
        WINDOW_SETTINGS->EDIT_CHAT_IRCSERVER_PORT->Text = Form1->getChatPort();
        WINDOW_SETTINGS->EDIT_CHAT_IRCSERVER_CHANNEL->Text = Form1->getChatChannel();
        WINDOW_SETTINGS->CHECKBOX_CHAT_AUTOCONNECT->Checked = Form1->getChatAutoConnect();
}

void TWINDOW_SETTINGS::exitEditNotificationMode() {
        WINDOW_SETTINGS->LISTBOX_NOTIFICATIONS->Enabled = true;
        WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_OK->Enabled = false;
        WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_CANCEL->Enabled = false;
        WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_OK->Visible = false;
        WINDOW_SETTINGS->BUTTON_EDITNOTIFICATION_CANCEL->Visible = false;
        WINDOW_SETTINGS->BUTTON_NEWNOTIFICATION_ADD->Visible = true;
        WINDOW_SETTINGS->BUTTON_NEWNOTIFICATION_ADD->Enabled = true;
        WINDOW_SETTINGS->BUTTON_NEWNOTIFICATION_CLEAR->Visible = true;
        WINDOW_SETTINGS->BUTTON_NEWNOTIFICATION_CLEAR->Enabled = true;
        WINDOW_SETTINGS->BUTTON_NEWNOTIFICATION_CLEAR->Click();
        this->checkNotificationListState();
}

void TWINDOW_SETTINGS::profileChanged(TComboBox *box, OFPGames gameid) {
        if(isValidGameID(gameid)) {
                Game *g = this->ofpm->getGame(gameid);
                if(g != NULL) {
                        if(box->Items->IndexOf(box->Text) == -1) {
                                box->ItemIndex = box->Items->IndexOf(g->getProfileName());
                        } else {
                                g->setProfileName(box->Text);
                        }
                }
        }
}

/**
   Converts an integer to a String and adds leading Zeros to the front until
   the String is @length characters long. Used to sort numbers alphabetically
   @i  number to convert
   @length  length of the String to return
   @return  the number with leading zeros as a String
 */

String TWINDOW_SETTINGS::addLeadingZeros(int number, int length) {
        String a = IntToStr(number);
        while (a.Length() < length) {
                a = "0" + a;
        }
        return a;
}

void TWINDOW_SETTINGS::setEmptyServerEditorList() {
        for(int i = 0; i < this->StringGrid1->ColCount; i++) {
                this->StringGrid1->Cells[i][1] = "";
        }
        this->StringGrid1->Objects[0][1] = NULL;
        this->StringGrid1->RowCount = 2;
}

void TWINDOW_SETTINGS::writeServerToStringGrid(int rowIndex, Server *srv) {
        this->StringGrid1->Cells[0][rowIndex] = " " + IntToStr(srv->getIndex());
        this->StringGrid1->Objects[0][rowIndex] = (TObject*) srv;
        this->StringGrid1->Cells[1][rowIndex] = srv->getAddress();
        this->StringGrid1->Cells[2][rowIndex] = srv->getName();
}

void TWINDOW_SETTINGS::updateServerEditorList() {
        list<Server*> allServers = this->ofpm->getAllMatchingServers(NULL);
        if(allServers.size() == 0) {
                this->setEmptyServerEditorList();
                this->BUTTON_SERVERS_REMOVE->Enabled = false;
        } else {
                TStringList *sortlist = new TStringList;
                sortlist->Sorted = true;
                sortlist->CaseSensitive = true;
                sortlist->Duplicates = dupAccept;

                for(list<Server*>::iterator ci = allServers.begin(); ci != allServers.end(); ++ci) {
                        Server *srv = *ci;
                        if(srv != NULL) {
                              sortlist->AddObject(this->addLeadingZeros(srv->getIndex(), 3), (TObject*) srv);
                        }
                }
                int rowIndex = 0;
                for(int i = 0; i < sortlist->Count; i++) {
                        rowIndex++;
                        this->writeServerToStringGrid(rowIndex, (Server*)(sortlist->Objects[i]));
                }
                sortlist->Clear();
                delete sortlist;
                StringGrid1->RowCount = max(1, rowIndex + 1);
                this->BUTTON_SERVERS_REMOVE->Enabled = true;
        }
}

String buildOpenDialogFilter(OFPGames gameid) {
        String filter = getFullGameNameByGameId(gameid) + "|";
        list<String> exes = getExesByGameId(gameid);
        while(exes.size() > 0) {
                filter += exes.front();
                exes.pop_front();
                if(exes.size() > 0) {
                        filter += ";";
                }
        }
        return filter;
}

String TWINDOW_SETTINGS::getFolder(String in) {
        String out = "";
        for(int i = in.Length() - 1; i >= 0; i--) {
                if(in.SubString(i,1) == "\\") {
                        out = in.SubString(0, i).Trim();
                        break;
                }
        }
        return out;
}

//---------------------------------------------------------------------------
__fastcall TWINDOW_SETTINGS::TWINDOW_SETTINGS(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::FormCreate(TObject *Sender)
{
        #include "guiDB.cpp"
        StringGrid1->ColWidths[0] = 24;
        StringGrid1->ColWidths[1] = 134;
        StringGrid1->ColWidths[2] = 216;
        for(int i = 3; i < 7; i++) {
                StringGrid1->ColWidths[i] = 24;
        }
        /*
        this->updateConfList();
        this->updateGames();
        */
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::OpenDialogGameFileCanClose(TObject *Sender,
      bool &CanClose)
{
        if(CanClose) {
                String exe = OpenDialogGameFile->FileName;
                String folder = this->getFolder(exe);
                this->ofpm->setGame((OFPGames)(OpenDialogGameFile->Tag), exe, "");
                this->updateGames();
                OpenDialogGameFile->InitialDir = "";
                OpenDialogGameFile->Tag = -1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_NEWCONFIGURATION_MOVERIGHTClick(TObject *Sender)
{
        for(int i = 0; i < LISTBOX_MODFOLDERS_ALL->Count; i++) {
                if(LISTBOX_MODFOLDERS_ALL->Selected[i]) {
                        LISTBOX_MODFOLDERS_SELECTED->Items->Add(LISTBOX_MODFOLDERS_ALL->Items->Strings[i]);
                        LISTBOX_MODFOLDERS_ALL->Items->Delete(i);
                        i--;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_NEWCONFIGURATION_MOVELEFTClick(TObject *Sender)
{
        for(int i = 0; i < LISTBOX_MODFOLDERS_SELECTED->Count; i++) {
                if(LISTBOX_MODFOLDERS_SELECTED->Selected[i]) {
                        LISTBOX_MODFOLDERS_ALL->Items->Add(LISTBOX_MODFOLDERS_SELECTED->Items->Strings[i]);
                        LISTBOX_MODFOLDERS_SELECTED->Items->Delete(i);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_NEWCONFIGURATION_UPClick(TObject *Sender)
{
        for(int i = 0; i < LISTBOX_MODFOLDERS_SELECTED->Count; i++) {
                if(LISTBOX_MODFOLDERS_SELECTED->Selected[i]) {
                        if(i > 0) {
                                LISTBOX_MODFOLDERS_SELECTED->Items->Exchange(i, i - 1);
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_NEWCONFIGURATION_DOWNClick(TObject *Sender)
{
        for(int i = 0; i < LISTBOX_MODFOLDERS_SELECTED->Count; i++) {
                if(LISTBOX_MODFOLDERS_SELECTED->Selected[i]) {
                        if(i < LISTBOX_MODFOLDERS_SELECTED->Count - 1) {
                                LISTBOX_MODFOLDERS_SELECTED->Items->Exchange(i, i + 1);
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_CONFIGURATION_REMOVEClick(TObject *Sender)
{
        int comboindex = ComboBox2->Items->IndexOf(ComboBox2->Text);
        Game *g = (Game*)(ComboBox2->Items->Objects[comboindex]);
        if(g != NULL) {
                for(int i = 0; i < LISTBOX_CONFIGURATIONS->Count; i++) {
                        if(LISTBOX_CONFIGURATIONS->Selected[i]) {
                                Configuration *conf = (Configuration*) (LISTBOX_CONFIGURATIONS->Items->Objects[i]);
                                if(conf != NULL) {
                                        g->deleteConfiguration(conf);
                                        LISTBOX_CONFIGURATIONS->Items->Delete(i);
                                }
                        }
                }
        }
        updateConfList();
        checkConfListState();
}
//---------------------------------------------------------------------------
        
void __fastcall TWINDOW_SETTINGS::BUTTON_NEWCONFIGURATION_ADDClick(TObject *Sender)
{
        int comboindex = ComboBox2->ItemIndex;
        Game *g = NULL;
        if(comboindex >= 0) {
                g = (Game*)(ComboBox2->Items->Objects[comboindex]);
        }
        if(g != NULL) {
                if(!EDIT_NEWCONFIGURATION_LABEL->Text.Trim().IsEmpty()) {
                        TStringList *mods = new TStringList;
                        for(int i = 0; i < LISTBOX_MODFOLDERS_SELECTED->Count; i++) {
                                mods->Add(LISTBOX_MODFOLDERS_SELECTED->Items->Strings[i]);
                        }
                        Configuration *c = new Configuration(g->getGameId(),
                                EDIT_NEWCONFIGURATION_LABEL->Text,
                                mods,
                                EDIT_NEWCONFIGURATION_PASSWORD->Text,
                                EDIT_NEWCONFIGURATION_PARAMETERS->Text,
                                CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked,
                                CHECKBOX_NEWCONFIGURATION_NOMAP->Checked);
                        g->addConfiguration(c);
                } else {
                        EDIT_NEWCONFIGURATION_LABEL->SetFocus();
                }
        }
        this->updateConfList();
        this->checkConfListState();
}
//---------------------------------------------------------------------------
          
void __fastcall TWINDOW_SETTINGS::BUTTON_NEWCONFIGURATION_CLEARClick(TObject *Sender)
{
        while(LISTBOX_MODFOLDERS_SELECTED->Count > 0) {
                LISTBOX_MODFOLDERS_ALL->Items->Add(LISTBOX_MODFOLDERS_SELECTED->Items->Strings[0]);
                LISTBOX_MODFOLDERS_SELECTED->Items->Delete(0);
        }
        EDIT_NEWCONFIGURATION_PASSWORD->Text = "";
        EDIT_NEWCONFIGURATION_PARAMETERS->Text = "";
        EDIT_NEWCONFIGURATION_LABEL->Text = "";
        CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked = true;
        CHECKBOX_NEWCONFIGURATION_NOMAP->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::FormClose(TObject *Sender, TCloseAction &Action)
{
        if(STOP->Visible) {
                STOP->Click();
        }
        try {
                int port = StrToInt(EDIT_CHAT_IRCSERVER_PORT->Text);
                Form1->setChat(EDIT_CHAT_IRCSERVER_ADDRESS->Text,
                port,
                EDIT_CHAT_IRCSERVER_CHANNEL->Text,
                COMBOBOX_CHAT_USERNAME->Text.TrimRight(),
                CHECKBOX_CHAT_AUTOCONNECT->Checked);
        } catch (...) {}
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_ESCAPE) {
                WINDOW_SETTINGS->Close();
        } else if(Key == VK_F2) {
                WINDOW_SETTINGS->CHECKBOX_NOTIFICATIONS_ACTIVE->Checked = !WINDOW_SETTINGS->CHECKBOX_NOTIFICATIONS_ACTIVE->Checked;
        }
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_SETTINGS::FormShow(TObject *Sender)
{
        exitEditMode();
        this->exitEditNotificationMode();
        updateChatSettings();
        updateServerEditorList();
        this->updateGames();
        this->findLanguageFiles();
        WINDOW_SETTINGS->ComboBox1->ItemIndex = WINDOW_SETTINGS->ComboBox1->Items->IndexOf(this->ofpm->getLanguageFile());
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_SETTINGS::BUTTON_EDITCONFIGURATION_EDITClick(TObject *Sender)
{
        BUTTON_NEWCONFIGURATION_CLEAR->Click();
        LISTBOX_CONFIGURATIONS->Enabled = false;
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
        BUTTON_EDITCONFIGURATION_COPY->Enabled = false;
        BUTTON_CONFIGURATION_REMOVE->Enabled = false;

        for(int i = 0; i < LISTBOX_CONFIGURATIONS->Count; i++) {
                if(LISTBOX_CONFIGURATIONS->Selected[i]) {
                        Configuration *conf = (Configuration*)(LISTBOX_CONFIGURATIONS->Items->Objects[i]);
                        if(conf != NULL) {
                                EDIT_NEWCONFIGURATION_LABEL->Text = conf->getLabel();
                                EDIT_NEWCONFIGURATION_PASSWORD->Text = conf->getPassword();

                        }
                        TStringList *mods = conf->getMods();
                        for(int j = 0; j < mods->Count; j++) {
                                LISTBOX_MODFOLDERS_SELECTED->Items->Add(mods->Strings[j]);
                                for(int k = 0; k < LISTBOX_MODFOLDERS_ALL->Count; k++) {
                                        if(mods->Strings[j] == LISTBOX_MODFOLDERS_ALL->Items->Strings[k]) {
                                                LISTBOX_MODFOLDERS_ALL->Items->Delete(k);
                                                break;
                                        }
                                }
                        }

                        CHECKBOX_NEWCONFIGURATION_NOMAP->Checked = conf->isNoSplashSet();
                        CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked = conf->isNoMapSet();
                        EDIT_NEWCONFIGURATION_PARAMETERS->Text = conf->createParameterLine(false, false, false, false, true, true);
                        break;
                }
        }

}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_SETTINGS::BUTTON_EDITCONFIGURATION_OKClick(TObject *Sender)
{
        for(int i = 0; i < LISTBOX_CONFIGURATIONS->Count; i++) {
                if(LISTBOX_CONFIGURATIONS->Selected[i]) {
                        Configuration *conf = (Configuration*)(LISTBOX_CONFIGURATIONS->Items->Objects[i]);
                        if(conf != NULL) {
                                TStringList *newmods = new TStringList;
                                for(int i = 0; i < LISTBOX_MODFOLDERS_SELECTED->Count; i++) {
                                        newmods->Add(LISTBOX_MODFOLDERS_SELECTED->Items->Strings[i]);
                                }
                                conf->setLabel(EDIT_NEWCONFIGURATION_LABEL->Text);
                                conf->setMods(newmods);
                                conf->setPassword(EDIT_NEWCONFIGURATION_PASSWORD->Text);
                                conf->setAddParameters(EDIT_NEWCONFIGURATION_PARAMETERS->Text);
                                delete newmods;
                                conf->setNoMap(CHECKBOX_NEWCONFIGURATION_NOMAP->Checked);
                                conf->setNoSplash(CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked);
                        }
                        break;
                }
        }
        this->updateConfList();
        this->exitEditMode();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_EDITCONFIGURATION_CANCELClick(
      TObject *Sender)
{
        exitEditMode();
}
//---------------------------------------------------------------------------


void __fastcall TWINDOW_SETTINGS::BUTTON_EDITCONFIGURATION_UPClick(TObject *Sender)
{
        int comboindex = ComboBox2->ItemIndex;
        Game *g = NULL;
        if(comboindex >= 0) {
                g = (Game*)(ComboBox2->Items->Objects[comboindex]);
        }
        if(g != NULL) {
                for(int i = 0; i < LISTBOX_CONFIGURATIONS->Count; i++) {
                        if(LISTBOX_CONFIGURATIONS->Selected[i]) {
                                if(i > 0) {
                                        LISTBOX_CONFIGURATIONS->Items->Exchange(i, i - 1);
                                        g->exchangeConfs(i, i - 1);
                                        break;
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_EDITCONFIGURATION_DOWNClick(TObject *Sender)
{
        int comboindex = ComboBox2->ItemIndex;
        Game *g = NULL;
        if(comboindex >= 0) {
                g = (Game*)(ComboBox2->Items->Objects[comboindex]);
        }
        if(g != NULL) {
                for(int i = 0; i < LISTBOX_CONFIGURATIONS->Count; i++) {
                        if(LISTBOX_CONFIGURATIONS->Selected[i]) {
                                if(i < LISTBOX_CONFIGURATIONS->Count - 1) {
                                        LISTBOX_CONFIGURATIONS->Items->Exchange(i, i + 1);
                                        g->exchangeConfs(i, i + 1);
                                        break;
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_EDITCONFIGURATION_COPYClick(
      TObject *Sender)
{
        int comboindex = ComboBox2->Items->IndexOf(ComboBox2->Text);
        Game *g = (Game*)(ComboBox2->Items->Objects[comboindex]);
        if(g != NULL) {
                for(int i = 0; i < LISTBOX_CONFIGURATIONS->Count; i++) {
                        if(LISTBOX_CONFIGURATIONS->Selected[i]) {
                                Configuration *conf = (Configuration*)(LISTBOX_CONFIGURATIONS->Items->Objects[i]);
                                Configuration *copy = conf->clone();
                                g->addConfiguration(copy);
                        }
                }
        }
        this->updateConfList();
        this->checkConfListState();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_OFPRES_BROWSEClick(TObject *Sender)
{
        if(!EDIT_OFPRES_EXECUTABLE->Text.IsEmpty()) {
                OpenDialogGameFile->InitialDir = getFolder(EDIT_OFPRES_EXECUTABLE->Text);
        }
        OpenDialogGameFile->Filter = buildOpenDialogFilter(OFPRES);
        OpenDialogGameFile->Tag = OFPRES;
        OpenDialogGameFile->Execute();
}

//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_OFPCWC_BROWSEClick(
      TObject *Sender)
{
        if(!EDIT_OFPCWC_EXECUTABLE->Text.IsEmpty()) {
                OpenDialogGameFile->InitialDir = getFolder(EDIT_OFPCWC_EXECUTABLE->Text);
        }
        OpenDialogGameFile->Filter = buildOpenDialogFilter(OFPCWC);
        OpenDialogGameFile->Tag = OFPCWC;
        OpenDialogGameFile->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_ARMACWA_BROWSEClick(
      TObject *Sender)
{
        if(!EDIT_ARMACWA_EXECUTABLE->Text.IsEmpty()) {
                OpenDialogGameFile->InitialDir = getFolder(EDIT_ARMACWA_EXECUTABLE->Text);
        }
        OpenDialogGameFile->Filter = buildOpenDialogFilter(ARMACWA);
        OpenDialogGameFile->Tag = ARMACWA;
        OpenDialogGameFile->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::ComboBox2Change(TObject *Sender)
{

        this->exitEditMode();

        this->updateConfList();
        this->checkConfListState();
        int comboindex = ComboBox2->Items->IndexOf(ComboBox2->Text);
        bool enable = (comboindex >= 0);
        if(enable) {
                Game *g = (Game*)(ComboBox2->Items->Objects[comboindex]);
                if(g != NULL) {
                        this->updateModFolderList(g->getGameFolder());
                }
        }
        GROUPBOX_CONFIGURATIONS->Enabled = enable;
        GROUPBOX_NEWCONFIGURATION->Enabled = enable;
        BUTTON_NEWCONFIGURATION_UP->Enabled = enable;
        BUTTON_NEWCONFIGURATION_DOWN->Enabled = enable;
        BUTTON_EDITCONFIGURATION_OK->Enabled = enable;
        BUTTON_NEWCONFIGURATION_ADD->Enabled = enable;
        BUTTON_NEWCONFIGURATION_CLEAR->Enabled = enable;
        BUTTON_EDITCONFIGURATION_CANCEL->Enabled = enable;
        BUTTON_NEWCONFIGURATION_MOVELEFT->Enabled = enable;
        BUTTON_NEWCONFIGURATION_MOVERIGHT->Enabled = enable;
        EDIT_NEWCONFIGURATION_LABEL->Enabled = enable;
        EDIT_NEWCONFIGURATION_PASSWORD->Enabled = enable;
        EDIT_NEWCONFIGURATION_PARAMETERS->Enabled = enable;
        CHECKBOX_NEWCONFIGURATION_NOSPLASH->Enabled = enable;
        CHECKBOX_NEWCONFIGURATION_NOMAP->Enabled = enable;
        LISTBOX_MODFOLDERS_ALL->Enabled = enable;
        LISTBOX_MODFOLDERS_SELECTED->Enabled = enable;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::COMBOBOX_OFPCWC_PROFILEChange(
      TObject *Sender)
{
        this->profileChanged(COMBOBOX_OFPCWC_PROFILE, OFPCWC);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::COMBOBOX_ARMACWA_PROFILEChange(
      TObject *Sender)
{
        this->profileChanged(COMBOBOX_ARMACWA_PROFILE, ARMACWA);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::COMBOBOX_OFPRES_PROFILEChange(TObject *Sender)
{
        this->profileChanged(COMBOBOX_OFPRES_PROFILE, OFPRES);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::CHECKBOX_OFPCWCClick(TObject *Sender)
{
        if(!CHECKBOX_OFPCWC->Checked) {
                this->ofpm->removeGame(OFPCWC);
        } else {
                this->checkForAutoDetection(OFPCWC);

        }
        this->updateGames();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::CHECKBOX_OFPRESClick(TObject *Sender)
{
        if(!CHECKBOX_OFPRES->Checked) {
                 this->ofpm->removeGame(OFPRES);
        } else {
                this->checkForAutoDetection(OFPRES);

        }
        this->updateGames();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::TABSHEET_MODSShow(TObject *Sender)
{
        this->refreshGamesModList();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_BROWSEClick(TObject *Sender)
{
        OpenDialogAudioFile->Execute();
        STOP->Click();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::OpenDialogAudioFileCanClose(TObject *Sender,
      bool &CanClose)
{
        String file = OpenDialogAudioFile->FileName;
        if(FileExists(file)) {
                EDIT_NOTIFICATION_FILE->Text = file;
                AudioTask *at = new AudioTask(file, this->ofpm->generateNewAudioAlias(), false);
                printPlaybackRange(at->getStartTime(), at->getEndTime());
                delete at;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_NOTIFICATION_FILEChange(TObject *Sender)
{
        LabelMilli->Visible = false;
        LabelSeconds->Visible = false;
        LabelMinutes->Visible = false;
        String file = EDIT_NOTIFICATION_FILE->Text;
        if(!FileExists(file) && !file.IsEmpty()) {
                EDIT_NOTIFICATION_FILE->Color = clRed;
        } else {
                EDIT_NOTIFICATION_FILE->Color = clWindow;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::CHECKBOX_FILTER_MINPLAYERSClick(
      TObject *Sender)
{
        EDIT_FILTER_MINPLAYERS->Enabled = CHECKBOX_FILTER_MINPLAYERS->Checked;
        UPDOWN_MINPLAYERS->Enabled = CHECKBOX_FILTER_MINPLAYERS->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::CHECKBOX_FILTER_MAXPLAYERSClick(
      TObject *Sender)
{
        EDIT_FILTER_MAXPLAYERS->Enabled = CHECKBOX_FILTER_MAXPLAYERS->Checked;
        UPDOWN_MAXPLAYERS->Enabled = CHECKBOX_FILTER_MAXPLAYERS->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_NEWNOTIFICATION_CLEARClick(
      TObject *Sender)
{
        MEMO_FILTER_MISSIONNAME->Clear();
        MEMO_FILTER_SERVERNAME->Clear();
        MEMO_FILTER_PLAYERNAME->Clear();
        CHECKBOX_FILTER_CREATING->Checked = false;
        CHECKBOX_FILTER_WAITING->Checked = false;
        CHECKBOX_FILTER_SETTINGUP->Checked = false;
        CHECKBOX_FILTER_BRIEFING->Checked = false;
        CHECKBOX_FILTER_PLAYING->Checked = false;
        CHECKBOX_FILTER_DEBRIEFING->Checked = false;
        CHECKBOX_FILTER_WITHPASSWORD->Checked = false;
        CHECKBOX_FILTER_WITHOUTPASSWORD->Checked = true;
        CHECKBOX_FILTER_MINPLAYERS->Checked = false;
        CHECKBOX_FILTER_MAXPLAYERS->Checked = false;
        CHECKBOX_REPEAT->Checked = false;
        UPDOWN_MINPLAYERS->Position = 0;
        UPDOWN_MAXPLAYERS->Position = 0;
        EDIT_NOTIFICATION_FILE->Text = "";
        EDIT_NOTIFICATION_NAME->Text = "";
        EDIT_SONGSTART_MIN->Text = "0";
        EDIT_SONGSTART_SEC->Text = "0";
        EDIT_SONGSTART_MILL->Text = "0";
        EDIT_SONGEND_MIN->Text = "0";
        EDIT_SONGEND_SEC->Text = "0";
        EDIT_SONGEND_MILL->Text = "0";
        TrackBar1->Position = 100;
        ColorBox1->Selected = clMaroon;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_EDITNOTIFICATION_EDITClick(
      TObject *Sender)
{
        LISTBOX_NOTIFICATIONS->Enabled = false;
        BUTTON_NEWNOTIFICATION_ADD->Visible = false;
        BUTTON_NEWNOTIFICATION_ADD->Enabled = false;
        BUTTON_NEWNOTIFICATION_CLEAR->Visible = false;
        BUTTON_NEWNOTIFICATION_CLEAR->Enabled = false;
        BUTTON_EDITNOTIFICATION_OK->Visible = true;
        BUTTON_EDITNOTIFICATION_OK->Enabled = true;
        BUTTON_EDITNOTIFICATION_CANCEL->Visible = true;
        BUTTON_EDITNOTIFICATION_CANCEL->Enabled = true;
        BUTTON_EDITNOTIFICATION_EDIT->Enabled = false;
        BUTTON_NOTIFICATION_REMOVE->Enabled = false;

        for(int i = 0; i < LISTBOX_NOTIFICATIONS->Count; i++) {
                if(LISTBOX_NOTIFICATIONS->Selected[i]) {
                        CustomNotification *notif = (CustomNotification*)(LISTBOX_NOTIFICATIONS->Items->Objects[i]);
                        if(notif != NULL) {
                                EDIT_NOTIFICATION_NAME->Text = notif->getName();
                                ColorBox1->Selected = notif->getMarkingColor();

                                AudioTask *task = notif->getAudioTask();
                                printPlaybackRange(task->getStartTime(), task->getEndTime());
                                CHECKBOX_REPEAT->Checked = task->isRepeatOn();
                                TrackBar1->Position = task->getVolume();
                                EDIT_NOTIFICATION_FILE->Text = task->getSoundFile();

                                ServerFilter *filter = notif->getFilter();

                                CHECKBOX_FILTER_BRIEFING->Checked = filter->briefing;
                                CHECKBOX_FILTER_CREATING->Checked = filter->creating;
                                CHECKBOX_FILTER_DEBRIEFING->Checked = filter->debriefing;
                                CHECKBOX_FILTER_MAXPLAYERS->Checked = (filter->maxPlayers > 0);
                                CHECKBOX_FILTER_MINPLAYERS->Checked = (filter->minPlayers > 0);
                                CHECKBOX_FILTER_PLAYING->Checked = filter->playing;
                                CHECKBOX_FILTER_SETTINGUP->Checked = filter->settingup;
                                CHECKBOX_FILTER_WAITING->Checked = filter->waiting;
                                CHECKBOX_FILTER_WITHOUTPASSWORD->Checked = filter->withoutPassword;
                                CHECKBOX_FILTER_WITHPASSWORD->Checked = filter->withPassword;
                                UPDOWN_MINPLAYERS->Position = max(filter->minPlayers, 0);
                                UPDOWN_MAXPLAYERS->Position = max(filter->maxPlayers, 0);
                                MEMO_FILTER_MISSIONNAME->Clear();
                                for (int m = 0; m < filter->missionNames->Count; m++) {
                                        MEMO_FILTER_MISSIONNAME->Lines->Add(filter->missionNames->Strings[m]);
                                }
                                MEMO_FILTER_SERVERNAME->Clear();
                                for (int m = 0; m < filter->serverNames->Count; m++) {
                                        MEMO_FILTER_SERVERNAME->Lines->Add(filter->serverNames->Strings[m]);
                                }
                                MEMO_FILTER_PLAYERNAME->Clear();
                                for (int m = 0; m < filter->playerNames->Count; m++) {
                                        MEMO_FILTER_PLAYERNAME->Lines->Add(filter->playerNames->Strings[m]);
                                }
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_EDITNOTIFICATION_OKClick(
      TObject *Sender)
{
        String notifName = EDIT_NOTIFICATION_NAME->Text;
        String audioFile = EDIT_NOTIFICATION_FILE->Text;
        if(!notifName.Trim().IsEmpty() && (FileExists(audioFile) || audioFile.Trim().IsEmpty())) {
                if(STOP->Visible) {
                        STOP->Click();
                }
                int listindex = LISTBOX_NOTIFICATIONS->ItemIndex;
                CustomNotification *notif = (CustomNotification*)(LISTBOX_NOTIFICATIONS->Items->Objects[listindex]);
                if(notif != NULL) {
                        ServerFilter *sf = notif->getFilter();
                        sf->missionNames->Clear();
                        for(int i = 0; i < MEMO_FILTER_MISSIONNAME->Lines->Count; i++) {
                                if(!MEMO_FILTER_MISSIONNAME->Lines->Strings[i].Trim().IsEmpty()) {
                                        sf->missionNames->Add(MEMO_FILTER_MISSIONNAME->Lines->Strings[i]);
                                }
                        }
                        sf->playerNames->Clear();
                        for(int i = 0; i < MEMO_FILTER_PLAYERNAME->Lines->Count; i++) {
                                if(!MEMO_FILTER_PLAYERNAME->Lines->Strings[i].Trim().IsEmpty()) {
                                        sf->playerNames->Add(MEMO_FILTER_PLAYERNAME->Lines->Strings[i]);
                                }
                        }
                        sf->serverNames->Clear();
                        for(int i = 0; i < MEMO_FILTER_SERVERNAME->Lines->Count; i++) {
                                if(!MEMO_FILTER_SERVERNAME->Lines->Strings[i].Trim().IsEmpty()) {
                                        sf->serverNames->Add(MEMO_FILTER_SERVERNAME->Lines->Strings[i]);
                                }
                        }
                        notif->setName(notifName);
                        sf->creating = CHECKBOX_FILTER_CREATING->Checked;
                        sf->waiting = CHECKBOX_FILTER_WAITING->Checked;
                        sf->settingup = CHECKBOX_FILTER_SETTINGUP->Checked;
                        sf->briefing = CHECKBOX_FILTER_BRIEFING->Checked;
                        sf->playing = CHECKBOX_FILTER_PLAYING->Checked;
                        sf->debriefing = CHECKBOX_FILTER_DEBRIEFING->Checked;
                        sf->withPassword = CHECKBOX_FILTER_WITHPASSWORD->Checked;
                        sf->withoutPassword = CHECKBOX_FILTER_WITHOUTPASSWORD->Checked;
                        if(CHECKBOX_FILTER_MINPLAYERS->Checked) {
                                sf->setMinPlayers(UPDOWN_MINPLAYERS->Position);
                        } else {
                                sf->setMinPlayers(0);
                        }
                        if(CHECKBOX_FILTER_MAXPLAYERS->Checked) {
                                sf->setMaxPlayers(UPDOWN_MAXPLAYERS->Position);
                        } else {
                                sf->setMaxPlayers(0);
                        }
                        AudioTask *at = notif->getAudioTask();
                        at->setFile(EDIT_NOTIFICATION_FILE->Text);
                        at->setRepeat(CHECKBOX_REPEAT->Checked);
                        at->setVolume(TrackBar1->Position);
                        int startPos = 0, endPos = 0;
                        try {
                                startPos =  StrToInt(EDIT_SONGSTART_MIN->Text)*60000 +
                                StrToInt(EDIT_SONGSTART_SEC->Text)*1000 +
                                StrToInt(EDIT_SONGSTART_MILL->Text);
                        } catch (...) {}
                        try {
                                endPos =    StrToInt(EDIT_SONGEND_MIN->Text)*60000 +
                                StrToInt(EDIT_SONGEND_SEC->Text)*1000 +
                                StrToInt(EDIT_SONGEND_MILL->Text);
                        } catch (...) {}
                        at->setPlayLength(startPos, endPos);
                        notif->setMarkingColor(ColorBox1->Selected);
                }
                updateNotificationsList();
                exitEditNotificationMode();
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_NEWNOTIFICATION_ADDClick(
      TObject *Sender)
{
        String notifName = EDIT_NOTIFICATION_NAME->Text;
        String audioName = EDIT_NOTIFICATION_FILE->Text;
        if(!notifName.Trim().IsEmpty() && (FileExists(audioName) || audioName.Trim().IsEmpty())) {
                if(STOP->Visible) {
                        STOP->Click();
                }
                TStringList *mission = new TStringList();
                TStringList *server = new TStringList();
                TStringList *player = new TStringList();
                for(int i = 0; i < MEMO_FILTER_MISSIONNAME->Lines->Count; i++) {
                        mission->Add(MEMO_FILTER_MISSIONNAME->Lines->Strings[i]);
                }
                for(int i = 0; i < MEMO_FILTER_SERVERNAME->Lines->Count; i++) {
                        server->Add(MEMO_FILTER_SERVERNAME->Lines->Strings[i]);
                }
                for(int i = 0; i < MEMO_FILTER_PLAYERNAME->Lines->Count; i++) {
                        player->Add(MEMO_FILTER_PLAYERNAME->Lines->Strings[i]);
                }
                int minP = 0, maxP = 0;
                if(CHECKBOX_FILTER_MINPLAYERS->Checked) {
                        minP = UPDOWN_MINPLAYERS->Position;
                }
                if(CHECKBOX_FILTER_MAXPLAYERS->Checked) {
                        maxP = UPDOWN_MAXPLAYERS->Position;
                }
                ServerFilter *sf = new ServerFilter(mission, server, player);
                sf->setMinPlayers(minP);
                sf->setMaxPlayers(maxP);
                sf->creating = CHECKBOX_FILTER_CREATING->Checked;
                sf->waiting = CHECKBOX_FILTER_WAITING->Checked;
                sf->settingup = CHECKBOX_FILTER_SETTINGUP->Checked;
                sf->briefing = CHECKBOX_FILTER_BRIEFING->Checked;
                sf->playing = CHECKBOX_FILTER_PLAYING->Checked;
                sf->debriefing = CHECKBOX_FILTER_DEBRIEFING->Checked;
                sf->withPassword = CHECKBOX_FILTER_WITHPASSWORD->Checked;
                sf->withoutPassword = CHECKBOX_FILTER_WITHOUTPASSWORD->Checked;

                AudioTask *at = new AudioTask(audioName, this->ofpm->generateNewAudioAlias(), CHECKBOX_REPEAT->Checked);
                at->setVolume(TrackBar1->Position);
                try {
                        at->setPlayLength(      StrToInt(EDIT_SONGSTART_MIN->Text)*60000 +
                                                StrToInt(WINDOW_SETTINGS->EDIT_SONGSTART_SEC->Text)*1000 +
                                                StrToInt(WINDOW_SETTINGS->EDIT_SONGSTART_MILL->Text),
                                                StrToInt(WINDOW_SETTINGS->EDIT_SONGEND_MIN->Text)*60000 +
                                                StrToInt(WINDOW_SETTINGS->EDIT_SONGEND_SEC->Text)*1000 +
                                                StrToInt(WINDOW_SETTINGS->EDIT_SONGEND_MILL->Text));
                } catch (...) {}
                CustomNotification *notif = new CustomNotification(notifName, sf, at, ColorToString(ColorBox1->Selected));
                this->ofpm->addNotification(notif);
                this->updateNotificationsList();
                this->checkNotificationListState();
        } else if(EDIT_NOTIFICATION_NAME->Text.Trim().IsEmpty()) {
                EDIT_NOTIFICATION_NAME->SetFocus();
        } else if(!FileExists(EDIT_NOTIFICATION_FILE->Text) && !EDIT_NOTIFICATION_FILE->Text.Trim().IsEmpty()) {
                EDIT_NOTIFICATION_FILE->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_NOTIFICATION_REMOVEClick(
      TObject *Sender)
{
        for(int i = 0; i < LISTBOX_NOTIFICATIONS->Count; i++) {
                if(LISTBOX_NOTIFICATIONS->Selected[i]) {
                        CustomNotification *notif = (CustomNotification*) (LISTBOX_NOTIFICATIONS->Items->Objects[i]);
                        if(notif != NULL) {
                                this->ofpm->removeNotification(notif);
                        }
                        LISTBOX_NOTIFICATIONS->Items->Delete(i);
                        break;
                }
        }
        this->updateNotificationsList();
        this->checkNotificationListState();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::TABSHEET_NOTIFICATIONSShow(TObject *Sender)
{
        this->exitEditNotificationMode();
        this->updateNotificationsList();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_EDITNOTIFICATION_CANCELClick(
      TObject *Sender)
{
        exitEditNotificationMode();        
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::PLAYClick(TObject *Sender)
{
        if(FileExists(EDIT_NOTIFICATION_FILE->Text)) {
                LabelMilli->Visible = true;
                LabelSeconds->Visible = true;
                LabelMinutes->Visible = true;
                PLAY->Visible = false;
                STOP->Visible = true;
                AudioTask *at = new AudioTask(EDIT_NOTIFICATION_FILE->Text, "OFPM_AUDIOPREVIEW", false);
                at->setDeleteOnEnd(true);
                at->setPlayLength(      StrToInt(EDIT_SONGSTART_MIN->Text)*60000 +
                                        StrToInt(WINDOW_SETTINGS->EDIT_SONGSTART_SEC->Text)*1000 +
                                        StrToInt(WINDOW_SETTINGS->EDIT_SONGSTART_MILL->Text),
                                        StrToInt(WINDOW_SETTINGS->EDIT_SONGEND_MIN->Text)*60000 +
                                        StrToInt(WINDOW_SETTINGS->EDIT_SONGEND_SEC->Text)*1000 +
                                        StrToInt(WINDOW_SETTINGS->EDIT_SONGEND_MILL->Text));
                at->setVolume(TrackBar1->Position);
                AudioPlayer *player = this->ofpm->getAudioPlayer();
                player->addAudioTask(at);
                Timer1->Enabled = true;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::TrackBar1Change(TObject *Sender)
{
        if(this->ofpm != NULL) {
                AudioPlayer *player = this->ofpm->getAudioPlayer();
                AudioTask *at = player->getTask("OFPM_AUDIOPREVIEW");
                if(at != NULL) {
                        at->setVolume(TrackBar1->Position);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::STOPClick(TObject *Sender)
{
        if(this->ofpm != NULL) {
                AudioPlayer *player = this->ofpm->getAudioPlayer();
                if(player != NULL) {
                        player->removeAudioTask("OFPM_AUDIOPREVIEW");
                        PLAY->Visible = true;
                        STOP->Visible = false;
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TWINDOW_SETTINGS::EDIT_FILTER_MINPLAYERSChange(TObject *Sender)
{
        try {
                int a = StrToInt(EDIT_FILTER_MINPLAYERS->Text);
                if(a < UPDOWN_MINPLAYERS->Min) {
                        EDIT_FILTER_MINPLAYERS->Text = UPDOWN_MINPLAYERS->Position;
                } else if(a > UPDOWN_MINPLAYERS->Max) {
                        EDIT_FILTER_MINPLAYERS->Text = UPDOWN_MINPLAYERS->Position;
                }
        } catch (...) {
                EDIT_FILTER_MINPLAYERS->Text = UPDOWN_MINPLAYERS->Position;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_FILTER_MAXPLAYERSChange(TObject *Sender)
{
        try {
                int a = StrToInt(EDIT_FILTER_MAXPLAYERS->Text);
                if(a < UPDOWN_MAXPLAYERS->Min) {
                        EDIT_FILTER_MAXPLAYERS->Text = UPDOWN_MAXPLAYERS->Position;
                } else if(a > UPDOWN_MAXPLAYERS->Max) {
                        EDIT_FILTER_MAXPLAYERS->Text = UPDOWN_MAXPLAYERS->Position;
                }
        } catch (...) {
                EDIT_FILTER_MAXPLAYERS->Text = UPDOWN_MAXPLAYERS->Position;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGEND_MILLChange(TObject *Sender)
{
        try {
                StrToInt(EDIT_SONGEND_MILL->Text);
        } catch (...) {
                EDIT_SONGEND_MILL->Text = "0";
        }        
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGSTART_MINChange(TObject *Sender)
{
        try {
                StrToInt(EDIT_SONGSTART_MIN->Text);
        } catch (...) {
                EDIT_SONGSTART_MIN->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGSTART_SECChange(TObject *Sender)
{
        try {
                StrToInt(EDIT_SONGSTART_SEC->Text);
        } catch (...) {
                EDIT_SONGSTART_SEC->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGSTART_MILLChange(TObject *Sender)
{
        try {
                StrToInt(EDIT_SONGSTART_MILL->Text);
        } catch (...) {
                EDIT_SONGSTART_MILL->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGEND_MINChange(TObject *Sender)
{
        try {
                StrToInt(EDIT_SONGEND_MIN->Text);
        } catch (...) {
                EDIT_SONGEND_MIN->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGEND_SECChange(TObject *Sender)
{
        try {
                StrToInt(EDIT_SONGEND_SEC->Text);
        } catch (...) {
                EDIT_SONGEND_SEC->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_NOTIFICATION_FILEKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_DELETE) {
                EDIT_NOTIFICATION_FILE->Text = "";
        }
}
//---------------------------------------------------------------------------


void __fastcall TWINDOW_SETTINGS::LISTBOX_NOTIFICATIONSClick(
      TObject *Sender)
{
        this->checkNotificationListState();        
}
//---------------------------------------------------------------------------
          
void __fastcall TWINDOW_SETTINGS::CHECKBOX_NOTIFICATIONS_ACTIVEClick(TObject *Sender)
{
        this->ofpm->setCustomNotifications(CHECKBOX_NOTIFICATIONS_ACTIVE->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_SETTINGS::UPDOWN_SERVERLIST_UPDATEClick(TObject *Sender, TUDBtnType Button)
{
        this->ofpm->setInterval(UPDOWN_SERVERLIST_UPDATE->Position);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::LISTBOX_CONFIGURATIONSClick(TObject *Sender)
{
        this->checkConfListState();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::CHECKBOX_ARMACWAClick(TObject *Sender)
{
        if(!CHECKBOX_ARMACWA->Checked) {
                 this->ofpm->removeGame(ARMACWA);
        } else {
                this->checkForAutoDetection(ARMACWA);
        }
        this->updateGames();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_CHAT_IRCSERVER_PORTChange(
      TObject *Sender)
{
        try {
                StrToInt(EDIT_CHAT_IRCSERVER_PORT->Text);
        } catch (...) {
                EDIT_CHAT_IRCSERVER_PORT->Text = Form1->getChatPort();
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_CHAT_SETDEFAULTClick(
      TObject *Sender)
{
        WINDOW_SETTINGS->EDIT_CHAT_IRCSERVER_ADDRESS->Text = DEFAULT_IRCSERVER_HOST;
        WINDOW_SETTINGS->EDIT_CHAT_IRCSERVER_PORT->Text = DEFAULT_IRCSERVER_PORT;
        WINDOW_SETTINGS->EDIT_CHAT_IRCSERVER_CHANNEL->Text = DEFAULT_IRCSERVER_CHANNEL;
        WINDOW_SETTINGS->CHECKBOX_CHAT_AUTOCONNECT->Checked = false;
}
//---------------------------------------------------------------------------


void __fastcall TWINDOW_SETTINGS::TRACKBAR_BANDWIDTHChange(TObject *Sender)
{
        this->ofpm->setBandwidthUsage(TRACKBAR_BANDWIDTH->Position);        
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::TABSHEET_GENERALShow(TObject *Sender)
{
        UPDOWN_SERVERLIST_UPDATE->Position = this->ofpm->getInterval();
        CHECKBOX_NOTIFICATIONS_ACTIVE->Checked = this->ofpm->areCustomNotificationsOn();
        CHECKBOX_UPDATE_CHECKATSTART->Checked = this->ofpm->isUpdateOnStartOn();
        TRACKBAR_BANDWIDTH->Position = (int)(this->ofpm->getBandwidthUsage());
        TRACKBAR_VOLUME->Position = this->ofpm->getVolume();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::CHECKBOX_UPDATE_CHECKATSTARTClick(
      TObject *Sender)
{
        this->ofpm->toggleUpdateOnStart(CHECKBOX_UPDATE_CHECKATSTART->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_UPDATEClick(TObject *Sender)
{
        WINDOW_UPDATE->checkForNewVersion(true);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::TABSHEET_SERVERSShow(TObject *Sender)
{
        this->updateServerEditorList();
        Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_SERVERS_ADDClick(TObject *Sender)
{
        String value;
        if(InputQuery(WINDOW_SETTINGS->getGuiString("STRING_SERVERS_ADD_TITLE"), WINDOW_SETTINGS->getGuiString("STRING_SERVERS_ADD_PROMPT"), value)) {
                if(!value.IsEmpty()) {
                        int defaultGameport = 2302;
                        Address *add = new Address();
                        if(add->readAddress(value, defaultGameport, false)) {
                                this->ofpm->addServer(add->getAddress());
                        } else {
                                int success = false;
                                struct in_addr addr;
                                StringSplitter ssp(value);
                                TStringList *url = ssp.split(":");
                                if(url->Count == 1) {
                                        url->Add(IntToStr(defaultGameport));
                                }
                                String ip = url->Strings[0];
                                addr.s_addr = resolv(ip.c_str());
                                if(addr.s_addr != INADDR_NONE) {
                                        ip = inet_ntoa(addr);
                                        if(ip != "62.157.140.133" && ip != "80.156.86.78") {
                                                success = true;
                                        }
                                }
                                if(success && add->readAddress(ip + ":" + url->Strings[1], defaultGameport, false)) {
                                        this->ofpm->addServer(add->getAddress());
                                } else {
                                        ShowMessage(WINDOW_SETTINGS->getGuiString("STRING_SERVERS_ADDERROR") + "  " + url->Strings[0]);
                                }
                        }
                        delete add;
                        updateServerEditorList();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::TRACKBAR_VOLUMEChange(TObject *Sender)
{
        this->ofpm->setVolume(TRACKBAR_VOLUME->Position);        
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::ComboBox1Change(TObject *Sender)
{
        String file = ComboBox1->ItemsEx->ComboItems[ComboBox1->ItemIndex]->Caption;
        if(FileExists(this->ofpm->getWorkDir() + "\\" + file)) {
                ComboBox1->Enabled = false;
                this->ofpm->setLanguageFile(file);
                updateLanguage(file);
                ComboBox1->Enabled = true;
                ComboBox1->SetFocus();
                this->updateGames();
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::StringGrid1DrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
        if(ACol > 2 && ACol < 7 && ARow > 0) {
                if(!(StringGrid1->Cells[0][ARow]).Trim().IsEmpty()) {
                        Server *srv = (Server*)(StringGrid1->Objects[0][ARow]);
                        if(srv != NULL) {
                                TColor mark = clNone;
                                if(ACol == 3 && srv->isFavorite()) {
                                        mark = clYellow;
                                } else if(ACol == 4 && srv->isWatched()) {
                                        mark = clBlue;
                                } else if(ACol == 5 && srv->isPersistent()) {
                                        mark = clGray;
                                } else if(ACol == 6 && srv->isBlocked()) {
                                        mark = clMaroon;
                                }
                                if(mark != clNone) {
                                        StringGrid1->Canvas->Brush->Color = mark;
                                        StringGrid1->Canvas->FillRect(Rect);
                                }
                        }
                }
        } else if(ACol > 2 && ACol < 7 && ARow == 0) {
                if(ACol == 3) {
                        ImageListPropertyIcons->Draw(StringGrid1->Canvas, Rect.Left + 4, Rect.Top + 2, 0, true);
                } else if(ACol == 4) {
                        ImageListPropertyIcons->Draw(StringGrid1->Canvas, Rect.Left + 4, Rect.Top + 2, 1, true);
                } else if(ACol == 5) {
                        ImageListPropertyIcons->Draw(StringGrid1->Canvas, Rect.Left + 4, Rect.Top + 2, 2, true);
                } else if(ACol == 6) {
                        ImageListPropertyIcons->Draw(StringGrid1->Canvas, Rect.Left + 4, Rect.Top + 2, 3, true);
                }

        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::StringGrid1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(Button == mbLeft) {
                int column = -1, row = -1;
                StringGrid1->MouseToCell(X, Y, column, row);
                if(column > 2 && column < 7 && row > 0) {
                        Server *srv = (Server*) (StringGrid1->Objects[0][row]);
                        if(srv != NULL) {
                                if(column == 3) {
                                        srv->setFavorite(!srv->isFavorite());
                                } else if(column == 4) {
                                        srv->setWatched(!srv->isWatched());
                                } else if(column == 5) {
                                        srv->setPersistent(!srv->isPersistent());
                                } else if(column == 6) {
                                        srv->setBlocked(!srv->isBlocked());
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_SERVERS_REMOVEClick(TObject *Sender)
{
        TGridRect sel = StringGrid1->Selection;
        if(sel.Top == sel.Bottom && sel.Top > 0) {
                Server *srv = (Server*) (StringGrid1->Objects[0][sel.Top]);
                if(srv != NULL) {
                        if(!this->ofpm->removeServer(srv->getGamespyAddress())) {
                                ShowMessage("failed");
                        }
                }
        }
        this->updateServerEditorList();
        StringGrid1->Selection = sel;
        StringGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::Timer1Timer(TObject *Sender)
{
        if(TABSHEET_SERVERS->Visible) {
                Timer1->Interval = 2000;
                WINDOW_SETTINGS->updateServerEditorList();
        } else {
                AudioPlayer *ap = this->ofpm->getAudioPlayer();
                if(ap->hasAlias("OFPM_AUDIOPREVIEW")) {
                        Timer1->Interval = 20;
                        AudioPosition aPos = ap->getCurrentPosition("OFPM_AUDIOPREVIEW");
                        printPlaybackPosition(aPos);
                } else {
                        printPlaybackPosition(AudioPosition(0));
                        STOP->Click();
                        Timer1->Enabled = false;
                }
        }
}
//---------------------------------------------------------------------------


