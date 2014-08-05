//---------------------------------------------------------------------------

#include "AudioTask.h"
#include "CustomNotification.h"
#include "StringSplitter.h"
#include <vcl.h>                                                          
                                                            
#pragma hdrstop

#include "Unit2.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWINDOW_SETTINGS *WINDOW_SETTINGS;

#include "FileVersion.h"
#include "ConfigReader.h"

enum OPENDIALOG_AUDIOFILE_TAG { ODAFT_Notifications, ODAFT_ChatSettings };

extern unsigned long resolv(char *host) ; 

void TWINDOW_SETTINGS::setModel(OFPMonitorModel *ofpm) {
        this->ofpm = ofpm;
}

void TWINDOW_SETTINGS::update(Observable *o) {
        if(o == this->languageDB) {
                this->updateGuiLanguage();
        }

}

void TWINDOW_SETTINGS::setLanguageDB(LanguageDB *languageDB) {
        this->languageDB = languageDB;
}

/**
   Refreshes the list box for the configurations in the settings window
 */

void TWINDOW_SETTINGS::updateConfList() {
        this->LISTBOX_CONFIGURATIONS->Clear();
        int comboindex = this->ComboBox2->Items->IndexOf(this->ComboBox2->Text);
        if(comboindex >= 0) {
                Game *g = (Game*) (this->ComboBox2->Items->Objects[comboindex]);

                if(g != NULL) {
                        for(int i = 0; i < g->getConfigurationsCount(); i++) {
                                Configuration *conf = g->getConfiguration(i);
                                if(conf != NULL) {
                                        this->LISTBOX_CONFIGURATIONS->Items->AddObject(conf->createListEntry(), (TObject *) conf);
                                }
                        }
                }
        }
}

void TWINDOW_SETTINGS::updateGuiLanguage() {
        if(this->languageDB != NULL) {
                this->BUTTON_OFPRES_BROWSE->Caption = this->languageDB->getGuiString(BUTTON_OFPRES_BROWSE->Name);
                this->BUTTON_CONFIGURATION_REMOVE->Caption = this->languageDB->getGuiString(BUTTON_CONFIGURATION_REMOVE->Name);
                this->BUTTON_NEWCONFIGURATION_UP->Caption = this->languageDB->getGuiString(BUTTON_NEWCONFIGURATION_UP->Name);
                this->BUTTON_NEWCONFIGURATION_DOWN->Caption = this->languageDB->getGuiString(BUTTON_NEWCONFIGURATION_DOWN->Name);
                this->BUTTON_NEWCONFIGURATION_ADD->Caption = this->languageDB->getGuiString(BUTTON_NEWCONFIGURATION_ADD->Name);
                this->BUTTON_NEWCONFIGURATION_CLEAR->Caption = this->languageDB->getGuiString(BUTTON_NEWCONFIGURATION_CLEAR->Name);
                this->BUTTON_EDITCONFIGURATION_EDIT->Caption = this->languageDB->getGuiString(BUTTON_EDITCONFIGURATION_EDIT->Name);
                this->BUTTON_EDITCONFIGURATION_OK->Caption = this->languageDB->getGuiString(BUTTON_EDITCONFIGURATION_OK->Name);
                this->BUTTON_EDITCONFIGURATION_CANCEL->Caption = this->languageDB->getGuiString(BUTTON_EDITCONFIGURATION_CANCEL->Name);
                this->BUTTON_EDITCONFIGURATION_UP->Caption = this->languageDB->getGuiString(BUTTON_EDITCONFIGURATION_UP->Name);
                this->BUTTON_EDITCONFIGURATION_DOWN->Caption = this->languageDB->getGuiString(BUTTON_EDITCONFIGURATION_DOWN->Name);
                this->BUTTON_EDITCONFIGURATION_COPY->Caption = this->languageDB->getGuiString(BUTTON_EDITCONFIGURATION_COPY->Name);
                this->BUTTON_CHAT_SETDEFAULT->Caption = this->languageDB->getGuiString(BUTTON_CHAT_SETDEFAULT->Name);
                this->BUTTON_CHATSETTINGS_BROWSEAUDIOFILE->Caption = this->languageDB->getGuiString(BUTTON_CHATSETTINGS_BROWSEAUDIOFILE->Name);
                this->BUTTON_CHATSETTINGS_CLEARAUDIOFILE->Caption = this->languageDB->getGuiString(BUTTON_CHATSETTINGS_CLEARAUDIOFILE->Name);
                this->BUTTON_UPDATE->Caption = this->languageDB->getGuiString(BUTTON_UPDATE->Name);
                this->BUTTON_SERVERS_ADD->Caption = this->languageDB->getGuiString(BUTTON_SERVERS_ADD->Name);
                this->BUTTON_SERVERS_REMOVE->Caption = this->languageDB->getGuiString(BUTTON_SERVERS_REMOVE->Name);
                this->BUTTON_SERVERS_EXPORT->Caption = this->languageDB->getGuiString(BUTTON_SERVERS_EXPORT->Name);
                this->BUTTON_MASTERSERVERS_ADD->Caption = this->languageDB->getGuiString(BUTTON_MASTERSERVERS_ADD->Name);
                this->BUTTON_MASTERSERVERS_REMOVE->Caption = this->languageDB->getGuiString(BUTTON_MASTERSERVERS_REMOVE->Name);
                this->CHECKBOX_NEWCONFIGURATION_NOSPLASH->Caption = this->languageDB->getGuiString(CHECKBOX_NEWCONFIGURATION_NOSPLASH->Name);
                this->CHECKBOX_NEWCONFIGURATION_NOMAP->Caption = this->languageDB->getGuiString(CHECKBOX_NEWCONFIGURATION_NOMAP->Name);
                this->CHECKBOX_REPEAT->Caption = this->languageDB->getGuiString(CHECKBOX_REPEAT->Name);
                this->CHECKBOX_NOTIFICATIONS_ACTIVE->Caption = this->languageDB->getGuiString(CHECKBOX_NOTIFICATIONS_ACTIVE->Name);
                this->CHECKBOX_CHAT_AUTOCONNECT->Caption = this->languageDB->getGuiString(CHECKBOX_CHAT_AUTOCONNECT->Name);
                this->CHECKBOX_CHATSETTINGS_BALLONHINT->Caption = this->languageDB->getGuiString(CHECKBOX_CHATSETTINGS_BALLONHINT->Name);
                this->CHECKBOX_CHATSETTINGS_AUDIONOTIFICATION->Caption = this->languageDB->getGuiString(CHECKBOX_CHATSETTINGS_AUDIONOTIFICATION->Name);
                this->CHECKBOX_UPDATE_CHECKATSTART->Caption = this->languageDB->getGuiString(CHECKBOX_UPDATE_CHECKATSTART->Name);
                this->CHECKBOX_MASTERSERVERS_UPDATEONSTART->Caption = this->languageDB->getGuiString(CHECKBOX_MASTERSERVERS_UPDATEONSTART->Name);
                this->LABEL_SERVERLIST_INTERVAL->Caption = this->languageDB->getGuiString(LABEL_SERVERLIST_INTERVAL->Name);
                this->LABEL_NEWCONFIGURATION_MODFOLDERS->Caption = this->languageDB->getGuiString(LABEL_NEWCONFIGURATION_MODFOLDERS->Name);
                this->LABEL_NEWCONFIGURATION_LABEL->Caption = this->languageDB->getGuiString(LABEL_NEWCONFIGURATION_LABEL->Name);
                this->LABEL_NEWCONFIGURATION_PASSWORD->Caption = this->languageDB->getGuiString(LABEL_NEWCONFIGURATION_PASSWORD->Name);
                this->LABEL_NEWCONFIGURATION_ADDITIONALPARAMETERS->Caption = this->languageDB->getGuiString(LABEL_NEWCONFIGURATION_ADDITIONALPARAMETERS->Name);
                this->LABEL_CHAT_USERNAME->Caption = this->languageDB->getGuiString(LABEL_CHAT_USERNAME->Name);
                this->LABEL_CHAT_IRCSERVER_ADDRESS->Caption = this->languageDB->getGuiString(LABEL_CHAT_IRCSERVER_ADDRESS->Name);
                this->LABEL_CHAT_IRCSERVER_PORT->Caption = this->languageDB->getGuiString(LABEL_CHAT_IRCSERVER_PORT->Name);
                this->LABEL_CHAT_IRCSERVER_CHANNEL->Caption = this->languageDB->getGuiString(LABEL_CHAT_IRCSERVER_CHANNEL->Name);
                this->LABEL_BANDWIDTH_HIGH->Caption = this->languageDB->getGuiString(LABEL_BANDWIDTH_HIGH->Name);
                this->LABEL_BANDWIDTH_MODERATE->Caption = this->languageDB->getGuiString(LABEL_BANDWIDTH_MODERATE->Name);
                this->LABEL_BANDWIDTH_LOW->Caption = this->languageDB->getGuiString(LABEL_BANDWIDTH_LOW->Name);
                this->LABEL_BANDWIDTH_VERYLOW->Caption = this->languageDB->getGuiString(LABEL_BANDWIDTH_VERYLOW->Name);
                this->GROUPBOX_SERVERLIST->Caption = this->languageDB->getGuiString(GROUPBOX_SERVERLIST->Name);
                this->GROUPBOX_LANGUAGE->Caption = this->languageDB->getGuiString(GROUPBOX_LANGUAGE->Name);
                this->GROUPBOX_NEWCONFIGURATION->Caption = this->languageDB->getGuiString(GROUPBOX_NEWCONFIGURATION->Name);
                this->GROUPBOX_NOTIFICATIONS_FILTERS->Caption = this->languageDB->getGuiString(GROUPBOX_NOTIFICATIONS_FILTERS->Name);
                this->GROUPBOX_CONFIGURATIONS->Caption = this->languageDB->getGuiString(GROUPBOX_CONFIGURATIONS->Name);
                this->GROUPBOX_NOTIFICATIONS->Caption = this->languageDB->getGuiString(GROUPBOX_NOTIFICATIONS->Name);
                this->GROUPBOX_CHATSETTINGS_GENERAL->Caption = this->languageDB->getGuiString(GROUPBOX_CHATSETTINGS_GENERAL->Name);
                this->GROUPBOX_CHATSETTINGS_SERVER->Caption = this->languageDB->getGuiString(GROUPBOX_CHATSETTINGS_SERVER->Name);
                this->GROUPBOX_CHATSETTINGS_NOTIFICATIONS->Caption = this->languageDB->getGuiString(GROUPBOX_CHATSETTINGS_NOTIFICATIONS->Name);
                this->GROUPBOX_BANDWIDTHCONSUMPTION->Caption = this->languageDB->getGuiString(GROUPBOX_BANDWIDTHCONSUMPTION->Name);
                this->GROUPBOX_UPDATE->Caption = this->languageDB->getGuiString(GROUPBOX_UPDATE->Name);
                this->GROUPBOX_VOLUME->Caption = this->languageDB->getGuiString(GROUPBOX_VOLUME->Name);
                this->GROUPBOX_MASTERSERVERS->Caption = this->languageDB->getGuiString(GROUPBOX_MASTERSERVERS->Name);
                this->Caption = this->languageDB->getGuiString(this->Name);
                this->TABSHEET_GENERAL->Caption = this->languageDB->getGuiString(this->TABSHEET_GENERAL->Name);
                this->TABSHEET_GAMES->Caption = this->languageDB->getGuiString(this->TABSHEET_GAMES->Name);
                this->TABSHEET_MODS->Caption = this->languageDB->getGuiString(this->TABSHEET_MODS->Name);
                this->TABSHEET_NOTIFICATIONS->Caption = this->languageDB->getGuiString(this->TABSHEET_NOTIFICATIONS->Name);
                this->TABSHEET_CHATSETTINGS->Caption = this->languageDB->getGuiString(this->TABSHEET_CHATSETTINGS->Name);
                this->TABSHEET_SERVERS->Caption = this->languageDB->getGuiString(this->TABSHEET_SERVERS->Name);
                this->TABSHEET_MASTERSERVERS->Caption = this->languageDB->getGuiString(this->TABSHEET_MASTERSERVERS->Name);
                this->StringGrid1->Cells[0][0] = this->languageDB->getGuiString("STRING_ID");
                this->StringGrid1->Cells[1][0] = this->languageDB->getGuiString("STRING_ADDRESS");
                this->StringGrid1->Cells[2][0] = this->languageDB->getGuiString("STRING_NAME");
                if(!this->COMBOBOX_OFPRES_PROFILE->Enabled) {
                        this->COMBOBOX_OFPRES_PROFILE->Text = this->languageDB->getGuiString("STRING_NOPROFILES");
                }
                if(!this->COMBOBOX_OFPCWC_PROFILE->Enabled) {
                        this->COMBOBOX_OFPCWC_PROFILE->Text = this->languageDB->getGuiString("STRING_NOPROFILES");
                }
                if(!this->COMBOBOX_ARMACWA_PROFILE->Enabled) {
                        this->COMBOBOX_ARMACWA_PROFILE->Text = this->languageDB->getGuiString("STRING_NOPROFILES");
                }
                this->LABEL_FILTER_MISSIONNAME_BOX->Caption = this->languageDB->getGuiString("LABEL_FILTER_MISSIONNAME");
                this->LABEL_FILTER_SERVERNAME_BOX->Caption = this->languageDB->getGuiString("LABEL_FILTER_SERVERNAME");
                this->LABEL_FILTER_PLAYERNAME_BOX->Caption = this->languageDB->getGuiString("LABEL_FILTER_PLAYERNAME");
                this->BUTTON_EDITNOTIFICATION_CANCEL->Caption = this->languageDB->getGuiString("BUTTON_EDITCONFIGURATION_CANCEL");
                this->BUTTON_EDITNOTIFICATION_EDIT->Caption = this->languageDB->getGuiString("BUTTON_EDITCONFIGURATION_EDIT");
                this->BUTTON_EDITNOTIFICATION_OK->Caption = this->languageDB->getGuiString("BUTTON_EDITCONFIGURATION_OK");
                this->BUTTON_NEWNOTIFICATION_ADD->Caption = this->languageDB->getGuiString("BUTTON_NEWCONFIGURATION_ADD");
                this->BUTTON_NEWNOTIFICATION_CLEAR->Caption = this->languageDB->getGuiString("BUTTON_NEWCONFIGURATION_CLEAR");
                this->BUTTON_NOTIFICATION_REMOVE->Caption = this->languageDB->getGuiString("BUTTON_CONFIGURATION_REMOVE");
                this->CHECKBOX_FILTER_CREATING->Caption = this->languageDB->getGuiString("CHECKBOX_FILTER_CREATING");
                this->CHECKBOX_FILTER_WAITING->Caption = this->languageDB->getGuiString("CHECKBOX_FILTER_WAITING");
                this->CHECKBOX_FILTER_BRIEFING->Caption = this->languageDB->getGuiString("CHECKBOX_FILTER_BRIEFING");
                this->CHECKBOX_FILTER_SETTINGUP->Caption = this->languageDB->getGuiString("CHECKBOX_FILTER_SETTINGUP");
                this->CHECKBOX_FILTER_PLAYING->Caption = this->languageDB->getGuiString("CHECKBOX_FILTER_PLAYING");
                this->CHECKBOX_FILTER_DEBRIEFING->Caption = this->languageDB->getGuiString("CHECKBOX_FILTER_DEBRIEFING");
                this->CHECKBOX_FILTER_MINPLAYERS->Caption = this->languageDB->getGuiString("STRING_MINIMUM");
                this->CHECKBOX_FILTER_MAXPLAYERS->Caption = this->languageDB->getGuiString("STRING_MAXIMUM");
                this->BUTTON_BROWSE->Caption = this->languageDB->getGuiString("STRING_BROWSE");
                this->BUTTON_OFPCWC_BROWSE->Caption = this->languageDB->getGuiString("STRING_BROWSE");
                this->BUTTON_OFPRES_BROWSE->Caption = this->languageDB->getGuiString("STRING_BROWSE");
                this->BUTTON_ARMACWA_BROWSE->Caption = this->languageDB->getGuiString("STRING_BROWSE");
                this->LABEL_FILTER_PASSWORD->Caption = this->languageDB->getGuiString("LABEL_FILTER_PASSWORD");
                this->LABEL_FILTER_STATUS->Caption = this->languageDB->getGuiString("LABEL_FILTER_STATUS");
                this->LABEL_NOTIFICATION_NAME->Caption = this->languageDB->getGuiString("STRING_NAME");
                this->LABEL_FILTER_PLAYERS->Caption = this->languageDB->getGuiString("STRING_PLAYERS");
                this->CHECKBOX_FILTER_WITHOUTPASSWORD->Caption = this->languageDB->getGuiString("CHECKBOX_FILTER_WITHOUTPASSWORD");
                this->CHECKBOX_FILTER_WITHPASSWORD->Caption = this->languageDB->getGuiString("CHECKBOX_FILTER_WITHPASSWORD");
                this->LABEL_VOLUME->Caption = this->languageDB->getGuiString("STRING_PLAYBACKVOLUME");
                this->LABEL_MARKINGCOLOR->Caption = this->languageDB->getGuiString("STRING_MARKINGCOLOR");
                this->LABEL_AUDIOFILE->Caption = this->languageDB->getGuiString("STRING_AUDIOFILE");
                this->LABEL_AUDIO_FROM->Caption = this->languageDB->getGuiString("STRING_FROM");
                this->LABEL_AUDIO_TO->Caption = this->languageDB->getGuiString("STRING_TO");
                this->LABEL_OFPCWC_EXECUTABLE->Caption = this->languageDB->getGuiString("STRING_OFPEXECUTABLE");
                this->LABEL_OFPRES_EXECUTABLE->Caption = this->languageDB->getGuiString("STRING_OFPEXECUTABLE");
                this->LABEL_ARMACWA_EXECUTABLE->Caption = this->languageDB->getGuiString("STRING_OFPEXECUTABLE");
                this->LABEL_OFPCWC_PLAYERNAME->Caption = this->languageDB->getGuiString("STRING_PROFILE");
                this->LABEL_OFPRES_PLAYERNAME->Caption = this->languageDB->getGuiString("STRING_PROFILE");
                this->LABEL_ARMACWA_PLAYERNAME->Caption = this->languageDB->getGuiString("STRING_PROFILE");
        }
}



/**
   Reads all folders within the game folder and displays them in the
   modfolder list box in the settings window
 */

void TWINDOW_SETTINGS::updateModFolderList(String ofpfolder) {
        this->LISTBOX_MODFOLDERS_ALL->Clear();
        if(!ofpfolder.IsEmpty()) {
        	TSearchRec daten;
                if(0 == FindFirst((ofpfolder +"\\*").c_str(), faDirectory, daten)) {
                        try {
                                do {
                                        if(daten.Size == 0 && daten.Name != "." && daten.Name != "..") {
                                                this->LISTBOX_MODFOLDERS_ALL->Items->Add(String(daten.Name));
                                        }
                                } while(FindNext(daten) == 0);
                        }__finally
                        {
                                FindClose(daten);
                        }
                }
        }
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
                this->GROUPBOX_NEWCONFIGURATION->Enabled = true;
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
                        combobox = this->COMBOBOX_OFPCWC_PROFILE;
                        checkbox = this->CHECKBOX_OFPCWC;
                        edit = this->EDIT_OFPCWC_EXECUTABLE;
                        label = this->LABEL_OFPCWC_DETECTEDVERSION;
                        groupbox = this->GROUPBOX_OFPCWC;
                } else if(i == OFPRES) {
                        combobox = this->COMBOBOX_OFPRES_PROFILE;
                        checkbox = this->CHECKBOX_OFPRES;
                        edit = this->EDIT_OFPRES_EXECUTABLE;
                        label = this->LABEL_OFPRES_DETECTEDVERSION;
                        groupbox = this->GROUPBOX_OFPRES;
                } else if(i == ARMACWA) {
                        combobox = this->COMBOBOX_ARMACWA_PROFILE;
                        checkbox = this->CHECKBOX_ARMACWA;
                        edit = this->EDIT_ARMACWA_EXECUTABLE;
                        label = this->LABEL_ARMACWA_DETECTEDVERSION;
                        groupbox = this->GROUPBOX_ARMACWA;
                }
                combobox->Items->Clear();
                edit->Text = "";
                label->Caption = "";
                groupbox->Visible = checkbox->Checked;
                if(g->isActive()) {
                        edit->Text = g->getGameExe();
                        if(!(g->getGameExe().IsEmpty())) {
                                label->Caption = this->languageDB->getGuiString("STRING_DETECTEDVERSION") + "  " + IntToStr(g->getFileVersion());
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
                                textToSet = this->languageDB->getGuiString("STRING_NOPROFILES");
                                combobox->Items->Add(textToSet);
                        }
                        combobox->ItemIndex = combobox->Items->IndexOf(textToSet);
                        checkbox->Checked = true;
                }
        }
        this->refreshGamesModList();
}

/**
   Searches for languages files
 */

void TWINDOW_SETTINGS::findLanguageFiles() {
        String flags[9] = { "chinese", "czech", "german",
                        "english", "french", "dutch",
                        "polish", "russian", "spanish" };
        this->ComboBox1->Clear();
        TSearchRec daten;
        if(0 == FindFirst(this->ofpm->getWorkDir() + "\\OFPM*.lang", faAnyFile, daten)) {
                try {
                        do {
                                for(int i = 0; i < 9; i++) {
                                        if(daten.Name.LowerCase().Pos(flags[i])) {
                                                this->ComboBox1->ItemsEx->AddItem(daten.Name, i, i, -1, -1, NULL);
                                                break;
                                        }
                                }
                        } while(FindNext(daten) == 0);
                  }
                  __finally {
                        FindClose(daten);
                  }
        }
}

void TWINDOW_SETTINGS::checkConfListState() {
        bool itemSelected = false;
        for(int i = 0; i < this->LISTBOX_CONFIGURATIONS->Count; i++) {
                if(this->LISTBOX_CONFIGURATIONS->Selected[i]) {
                        itemSelected = true;
                        break;
                }
        }
        bool limitReached = this->LISTBOX_CONFIGURATIONS->Items->Count >= 50;
        this->BUTTON_NEWCONFIGURATION_ADD->Enabled = !limitReached;
        this->BUTTON_EDITCONFIGURATION_EDIT->Enabled = itemSelected;
        this->BUTTON_CONFIGURATION_REMOVE->Enabled = itemSelected;
        this->BUTTON_EDITCONFIGURATION_COPY->Enabled = itemSelected && !limitReached;
        this->BUTTON_EDITCONFIGURATION_UP->Enabled = itemSelected;
        this->BUTTON_EDITCONFIGURATION_DOWN->Enabled = itemSelected;
}

void TWINDOW_SETTINGS::exitEditMode() {
        this->LISTBOX_CONFIGURATIONS->Enabled = true;
        this->BUTTON_EDITCONFIGURATION_OK->Enabled = false;
        this->BUTTON_EDITCONFIGURATION_CANCEL->Enabled = false;
        this->BUTTON_EDITCONFIGURATION_OK->Visible = false;
        this->BUTTON_EDITCONFIGURATION_CANCEL->Visible = false;
        this->BUTTON_NEWCONFIGURATION_ADD->Visible = true;
        this->BUTTON_NEWCONFIGURATION_ADD->Enabled = true;
        this->BUTTON_NEWCONFIGURATION_CLEAR->Visible = true;
        this->BUTTON_NEWCONFIGURATION_CLEAR->Enabled = true;
        this->BUTTON_NEWCONFIGURATION_CLEAR->Click();
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
        this->EDIT_SONGSTART_MIN->Text = IntToStr(start.getMinutes());
        this->EDIT_SONGSTART_SEC->Text = IntToStr(start.getSeconds());
        this->EDIT_SONGSTART_MILL->Text = IntToStr(start.getMilliSeconds());
        this->EDIT_SONGEND_MIN->Text = IntToStr(end.getMinutes());
        this->EDIT_SONGEND_SEC->Text = IntToStr(end.getSeconds());
        this->EDIT_SONGEND_MILL->Text = IntToStr(end.getMilliSeconds());
}

void TWINDOW_SETTINGS::printPlaybackPosition(AudioPosition current) {
        this->LabelMilli->Caption = this->addLeadingZeros(current.getMilliSeconds(), 3);
        this->LabelSeconds->Caption = this->addLeadingZeros(current.getSeconds(), 2) + ":";
        this->LabelMinutes->Caption = this->addLeadingZeros(current.getMinutes(), 2) + ":";
}


void TWINDOW_SETTINGS::updateNotificationsList() {
        this->LISTBOX_NOTIFICATIONS->Clear();
        for(int i = 0; i < this->ofpm->getNotificationCount(); i++) {
                CustomNotification* notif = this->ofpm->getNotification(i);
                if(notif != NULL) {
                        this->LISTBOX_NOTIFICATIONS->Items->AddObject(notif->getName(), (TObject *) notif);
                }
        }
}
 

void TWINDOW_SETTINGS::checkNotificationListState() {
        this->BUTTON_EDITNOTIFICATION_EDIT->Enabled = false;
        this->BUTTON_NOTIFICATION_REMOVE->Enabled = false;
        for(int i = 0; i < this->LISTBOX_NOTIFICATIONS->Count; i++) {
                if(this->LISTBOX_NOTIFICATIONS->Selected[i]) {
                        this->BUTTON_EDITNOTIFICATION_EDIT->Enabled = true;
                        this->BUTTON_NOTIFICATION_REMOVE->Enabled = true;
                        break;
                }
        }
}

void TWINDOW_SETTINGS::updateChatSettings() {
        this->COMBOBOX_CHAT_USERNAME->Clear();
        for(int i = 0; i < GAMESTOTAL; i++) {
                Game *g = this->ofpm->getGame((OFPGames)i);
                if(g != NULL) {
                        list<String> profiles = g->findPlayerProfiles();
                        for (list<String>::iterator ci = profiles.begin(); ci != profiles.end(); ++ci) {
                                if(this->COMBOBOX_CHAT_USERNAME->Items->IndexOf(*ci) == -1) {
                                        this->COMBOBOX_CHAT_USERNAME->Items->Add(*ci);
                                }
                        }
                }
        }
        String user = this->chatSettings->getUserName();
        if(!user.IsEmpty()) {
                this->COMBOBOX_CHAT_USERNAME->Items->Add(user);
        }
        this->COMBOBOX_CHAT_USERNAME->Text = this->chatSettings->getUserName();
        this->EDIT_CHAT_IRCSERVER_ADDRESS->Text = this->chatSettings->getHost();
        this->EDIT_CHAT_IRCSERVER_PORT->Text = this->chatSettings->getPort();
        this->EDIT_CHAT_IRCSERVER_CHANNEL->Text = this->chatSettings->getChannel();
        this->CHECKBOX_CHAT_AUTOCONNECT->Checked = this->chatSettings->isAutoConnectOn();
        this->CHECKBOX_CHATSETTINGS_BALLONHINT->Checked = this->chatSettings->isBallonHintOn();
        this->CHECKBOX_CHATSETTINGS_AUDIONOTIFICATION->Checked = this->chatSettings->isAudioNotificationOn();
        String file = this->chatSettings->getNotificationSoundFile();
        if(file.IsEmpty()) {
                this->LABEL_CHATSETTINGS_SELECTEDAUDIOFILE->Caption = this->languageDB->getGuiString("STRING_NO_FILE_SELECTED");
        } else {
                this->LABEL_CHATSETTINGS_SELECTEDAUDIOFILE->Caption = this->chatSettings->getNotificationSoundFile();
        }
}

void TWINDOW_SETTINGS::exitEditNotificationMode() {
        this->LISTBOX_NOTIFICATIONS->Enabled = true;
        this->BUTTON_EDITNOTIFICATION_OK->Enabled = false;
        this->BUTTON_EDITNOTIFICATION_CANCEL->Enabled = false;
        this->BUTTON_EDITNOTIFICATION_OK->Visible = false;
        this->BUTTON_EDITNOTIFICATION_CANCEL->Visible = false;
        this->BUTTON_NEWNOTIFICATION_ADD->Visible = true;
        this->BUTTON_NEWNOTIFICATION_ADD->Enabled = true;
        this->BUTTON_NEWNOTIFICATION_CLEAR->Visible = true;
        this->BUTTON_NEWNOTIFICATION_CLEAR->Enabled = true;
        this->BUTTON_NEWNOTIFICATION_CLEAR->Click();
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

void TWINDOW_SETTINGS::writeServerToStringGrid(int rowIndex, int serverID) {
        Server *srv = this->ofpm->getServerByID(serverID);
        if(srv != NULL) {
                this->StringGrid1->Cells[0][rowIndex] = " " + IntToStr(srv->getServerID());
                this->StringGrid1->Objects[0][rowIndex] = (TObject*) srv->getServerID();
                this->StringGrid1->Cells[1][rowIndex] = srv->getAddress();
                this->StringGrid1->Cells[2][rowIndex] = srv->getName();
        }
}

void TWINDOW_SETTINGS::updateServerEditorList() {
        list<int> allServers = this->ofpm->getAllMatchingServers(NULL);
        if(allServers.size() == 0) {
                this->setEmptyServerEditorList();
                this->BUTTON_SERVERS_REMOVE->Enabled = false;
        } else {
                TStringList *sortlist = new TStringList;
                sortlist->Sorted = true;
                sortlist->CaseSensitive = true;
                sortlist->Duplicates = dupAccept;

                for(list<int>::iterator ci = allServers.begin(); ci != allServers.end(); ++ci) {
                        int serverID = *ci;
                        Server *srv = this->ofpm->getServerByID(serverID);
                        if(srv != NULL) {
                                if(this->serverEditorTableSorter->isIDSet()) {
                                        sortlist->AddObject(this->addLeadingZeros(srv->getServerID(), 3), (TObject*) srv->getServerID());
                                } else if(this->serverEditorTableSorter->isIPSet()) {
                                        sortlist->AddObject(srv->getAddress(), (TObject*) srv->getServerID());
                                } else if(this->serverEditorTableSorter->isNameSet()) {
                                        sortlist->AddObject(srv->getName(), (TObject*) srv->getServerID());
                                } else if(this->serverEditorTableSorter->isFavoritesSet()) {
                                        sortlist->AddObject(IntToStr(srv->isFavorite()), (TObject*) srv->getServerID());
                                } else if(this->serverEditorTableSorter->isWatchedSet()) {
                                        sortlist->AddObject(IntToStr(srv->isWatched()), (TObject*) srv->getServerID());
                                } else if(this->serverEditorTableSorter->isPersistentSet()) {
                                        sortlist->AddObject(IntToStr(srv->isPersistent()), (TObject*) srv->getServerID());
                                } else if(this->serverEditorTableSorter->isBlockedSet()) {
                                        sortlist->AddObject(IntToStr(srv->isBlocked()), (TObject*) srv->getServerID());
                                }
                        }
                }
                int rowIndex = 0;
                for(int i = 0; i < sortlist->Count; i++) {
                        rowIndex++;
                        TObject *serverID = sortlist->Objects[i];
                        if(!this->serverEditorTableSorter->isNormalOrder()) {
                                serverID = sortlist->Objects[sortlist->Count - (i + 1)];
                        }
                        this->writeServerToStringGrid(rowIndex, (int) serverID);
                }
                sortlist->Clear();
                delete sortlist;
                StringGrid1->RowCount = max(1, rowIndex + 1);
                StringGrid1->Repaint();
                this->BUTTON_SERVERS_REMOVE->Enabled = true;
        }
}

void TWINDOW_SETTINGS::setChatSettings(ChatSettings *chatSettings) {
        this->chatSettings = chatSettings;
}

String buildOpenDialogFilter(OFPGames gameid) {
        String filter = getFullGameNameByGameId(gameid) + "|";
        list<String> exes = getExesByGameId(gameid, true);
        while(exes.size() > 0) {
                filter += exes.front();
                exes.pop_front();
                if(exes.size() > 0) {
                        filter += ";";
                }
        }
        return filter;
}

//---------------------------------------------------------------------------
__fastcall TWINDOW_SETTINGS::TWINDOW_SETTINGS(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::FormCreate(TObject *Sender)
{
        StringGrid1->ColWidths[0] = 24;
        StringGrid1->ColWidths[1] = 134;
        StringGrid1->ColWidths[2] = 216;
        for(int i = 3; i < 7; i++) {
                StringGrid1->ColWidths[i] = 24;
        }
        this->serverEditorTableSorter = new ServerEditorTableSorter();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::OpenDialogGameFileCanClose(TObject *Sender,
      bool &CanClose)
{
        if(CanClose) {
                String exe = OpenDialogGameFile->FileName;
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

        int port = StrToIntDef(EDIT_CHAT_IRCSERVER_PORT->Text, -1);
        if(port > 0 && port < 65536) {
                this->chatSettings->setSettings(EDIT_CHAT_IRCSERVER_ADDRESS->Text,
                                                port,
                                                EDIT_CHAT_IRCSERVER_CHANNEL->Text,
                                                COMBOBOX_CHAT_USERNAME->Text.TrimRight(),
                                                CHECKBOX_CHAT_AUTOCONNECT->Checked);
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_ESCAPE) {
                this->Close();
        } else if(Key == VK_F2) {
                this->CHECKBOX_NOTIFICATIONS_ACTIVE->Checked = !this->CHECKBOX_NOTIFICATIONS_ACTIVE->Checked;
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
        this->ComboBox1->ItemIndex = this->ComboBox1->Items->IndexOf(this->ofpm->getLanguageFile());
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

                        CHECKBOX_NEWCONFIGURATION_NOMAP->Checked = conf->isNoMapSet();
                        CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked = conf->isNoSplashSet();
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
                                conf->setNoMap(CHECKBOX_NEWCONFIGURATION_NOMAP->Checked);
                                conf->setNoSplash(CHECKBOX_NEWCONFIGURATION_NOSPLASH->Checked);
                                conf->setAddParameters(EDIT_NEWCONFIGURATION_PARAMETERS->Text);
                                delete newmods;                                                
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
                OpenDialogGameFile->InitialDir = ExtractFilePath(EDIT_OFPRES_EXECUTABLE->Text);
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
                OpenDialogGameFile->InitialDir = ExtractFilePath(EDIT_OFPCWC_EXECUTABLE->Text);
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
                OpenDialogGameFile->InitialDir = ExtractFilePath(EDIT_ARMACWA_EXECUTABLE->Text);
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
        OpenDialogAudioFile->Tag = ODAFT_Notifications;
        OpenDialogAudioFile->Execute();
        STOP->Click();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::OpenDialogAudioFileCanClose(TObject *Sender,
      bool &CanClose)
{
        String file = OpenDialogAudioFile->FileName;
        if(FileExists(file)) {
                if(OpenDialogAudioFile->Tag == ODAFT_Notifications) {
                        EDIT_NOTIFICATION_FILE->Text = file;
                        AudioTask *at = new AudioTask(file, this->ofpm->generateNewAudioAlias(), false);
                        printPlaybackRange(at->getStartTime(), at->getEndTime());
                        delete at;
                } else if(OpenDialogAudioFile->Tag == ODAFT_ChatSettings) {
                        this->chatSettings->setNotificationSoundFile(file);
                        LABEL_CHATSETTINGS_SELECTEDAUDIOFILE->Caption = file;
                }
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
                        int min = StrToIntDef(EDIT_SONGSTART_MIN->Text, -1);
                        int sec = StrToIntDef(EDIT_SONGSTART_SEC->Text, -1);
                        int mil = StrToIntDef(EDIT_SONGSTART_MILL->Text, -1);
                        if(min > -1 && sec > -1 && mil > -1) {
                                startPos = min*60000 + sec*1000 + mil;
                        }
                        min = StrToIntDef(EDIT_SONGEND_MIN->Text, -1);
                        sec = StrToIntDef(EDIT_SONGEND_SEC->Text, -1);
                        mil = StrToIntDef(EDIT_SONGEND_MILL->Text, -1);
                        if(min > -1 && sec > -1 && mil > -1) {
                                endPos = min*60000 + sec*1000 + mil;
                        }
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
                int Smin = StrToIntDef(this->EDIT_SONGSTART_MIN->Text, -1);
                int Ssec = StrToIntDef(this->EDIT_SONGSTART_SEC->Text, -1);
                int Smil = StrToIntDef(this->EDIT_SONGSTART_MILL->Text, -1);
                int Emin = StrToIntDef(this->EDIT_SONGEND_MIN->Text, -1);
                int Esec = StrToIntDef(this->EDIT_SONGEND_SEC->Text, -1);
                int Emil = StrToIntDef(this->EDIT_SONGEND_MILL->Text, -1);
                if(Smin > -1 && Ssec > -1 && Smil > -1 &&
                   Emin > -1 && Esec > -1 && Emil > -1) {
                        at->setPlayLength(Smin*60000 + Ssec*1000 + Smil,
                                          Emin*60000 + Esec*1000 + Emil);
                }
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
                int Smin = StrToIntDef(this->EDIT_SONGSTART_MIN->Text, -1);
                int Ssec = StrToIntDef(this->EDIT_SONGSTART_SEC->Text, -1);
                int Smil = StrToIntDef(this->EDIT_SONGSTART_MILL->Text, -1);
                int Emin = StrToIntDef(this->EDIT_SONGEND_MIN->Text, -1);
                int Esec = StrToIntDef(this->EDIT_SONGEND_SEC->Text, -1);
                int Emil = StrToIntDef(this->EDIT_SONGEND_MILL->Text, -1);
                if(Smin > -1 && Ssec > -1 && Smil > -1 &&
                   Emin > -1 && Esec > -1 && Emil > -1) {
                        at->setPlayLength(Smin*60000 + Ssec*1000 + Smil,
                                          Emin*60000 + Esec*1000 + Emil);
                }
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
        int a = StrToIntDef(EDIT_FILTER_MINPLAYERS->Text, UPDOWN_MINPLAYERS->Position);
        if(a < UPDOWN_MINPLAYERS->Min) {
                EDIT_FILTER_MINPLAYERS->Text = UPDOWN_MINPLAYERS->Position;
        } else if(a > UPDOWN_MINPLAYERS->Max) {
                EDIT_FILTER_MINPLAYERS->Text = UPDOWN_MINPLAYERS->Position;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_FILTER_MAXPLAYERSChange(TObject *Sender)
{
        int a = StrToIntDef(EDIT_FILTER_MAXPLAYERS->Text, UPDOWN_MAXPLAYERS->Position);
        if(a < UPDOWN_MAXPLAYERS->Min) {
                EDIT_FILTER_MAXPLAYERS->Text = UPDOWN_MAXPLAYERS->Position;
        } else if(a > UPDOWN_MAXPLAYERS->Max) {
                EDIT_FILTER_MAXPLAYERS->Text = UPDOWN_MAXPLAYERS->Position;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGEND_MILLChange(TObject *Sender)
{
        if(StrToIntDef(EDIT_SONGEND_MILL->Text, -1) < 0) {
                EDIT_SONGEND_MILL->Text = "0";
        }        
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGSTART_MINChange(TObject *Sender)
{
        if(StrToIntDef(EDIT_SONGSTART_MIN->Text, -1) < 0) {
                EDIT_SONGSTART_MIN->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGSTART_SECChange(TObject *Sender)
{
        if(StrToIntDef(EDIT_SONGSTART_SEC->Text, -1) < 0) {
                EDIT_SONGSTART_SEC->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGSTART_MILLChange(TObject *Sender)
{
        if(StrToIntDef(EDIT_SONGSTART_MILL->Text, -1) < 0) {
                EDIT_SONGSTART_MILL->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGEND_MINChange(TObject *Sender)
{
        if(StrToIntDef(EDIT_SONGEND_MIN->Text, -1) < 0) {
                EDIT_SONGEND_MIN->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::EDIT_SONGEND_SECChange(TObject *Sender)
{
        if(StrToIntDef(EDIT_SONGEND_SEC->Text, -1) < 0) {
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
        if(StrToIntDef(EDIT_CHAT_IRCSERVER_PORT->Text, -1) < 0) {
                EDIT_CHAT_IRCSERVER_PORT->Text = IntToStr(this->chatSettings->getPort());
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_CHAT_SETDEFAULTClick(
      TObject *Sender)
{
        if(this->chatSettings != NULL) {
                this->chatSettings->setDefault();
        }
        this->updateChatSettings();
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
        CHECKBOX_UPDATE_CHECKATSTART->Checked = this->ofpm->isUpdateOnStartSet();
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
        if(InputQuery(this->languageDB->getGuiString("STRING_SERVERS_ADD_TITLE"), this->languageDB->getGuiString("STRING_SERVERS_ADD_PROMPT"), value)) {
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
                                        ShowMessage(this->languageDB->getGuiString("STRING_SERVERS_ADDERROR") + "  " + url->Strings[0]);
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
                        int serverID = (int)(StringGrid1->Objects[0][ARow]);
                        Server *srv = this->ofpm->getServerByID(serverID);
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
                        int serverID = (int)(StringGrid1->Objects[0][row]);
                        Server *srv = this->ofpm->getServerByID(serverID);
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
                } else if(column > -1 && column < 7 && row == 0) {
                        if(column == 0) {
                                this->serverEditorTableSorter->setID();
                        } else if(column == 1) {
                                this->serverEditorTableSorter->setIP();
                        } else if(column == 2) {
                                this->serverEditorTableSorter->setName();
                        } else if(column == 3) {
                                this->serverEditorTableSorter->setFavorites();
                        } else if(column == 4) {
                                this->serverEditorTableSorter->setWatched();
                        } else if(column == 5) {
                                this->serverEditorTableSorter->setPersistent();
                        } else if(column == 6) {
                                this->serverEditorTableSorter->setBlocked();
                        }
                        this->updateServerEditorList();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_SERVERS_REMOVEClick(TObject *Sender)
{
        TGridRect sel = StringGrid1->Selection;
        if(sel.Top == sel.Bottom && sel.Top > 0) {
                int serverID = (int)(StringGrid1->Objects[0][sel.Top]);
                Server *srv = this->ofpm->getServerByID(serverID);
                if(srv != NULL) {
                        this->ofpm->removeServer(srv->getGamespyAddress());
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
                this->updateServerEditorList();
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


void __fastcall TWINDOW_SETTINGS::FormDestroy(TObject *Sender)
{
        delete this->serverEditorTableSorter;
}
//---------------------------------------------------------------------------



void __fastcall TWINDOW_SETTINGS::BUTTON_MASTERSERVERS_ADDClick(TObject *Sender)
{
        String title = this->languageDB->getGuiString("STRING_MASTERSERVERS_DIALOGTITLE");
        String message = this->languageDB->getGuiString("STRING_MASTERSERVERS_DIALOGPROMPT");
        AnsiString input = InputBox(title, message, "");
        if(!input.IsEmpty()) {
                this->ofpm->addMasterServer(input);
        }
        this->updateMasterServerSettings();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::TABSHEET_MASTERSERVERSShow(
      TObject *Sender)
{
        this->updateMasterServerSettings();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::CHECKBOX_MASTERSERVERS_UPDATEONSTARTClick(
      TObject *Sender)
{
        this->ofpm->setUpdateOfMasterServersOnStart(CHECKBOX_MASTERSERVERS_UPDATEONSTART->Checked);
}
//---------------------------------------------------------------------------

void TWINDOW_SETTINGS::updateMasterServerSettings() {
        CHECKBOX_MASTERSERVERS_UPDATEONSTART->Checked = this->ofpm->isUpdateOfMasterServersOnStartSet();
        TStringList *ms = new TStringList;
        this->ofpm->getMasterServers(ms);
        LISTBOX_MASTERSERVERS->Clear();
        for(int i = 0; i < ms->Count; i++) {
                LISTBOX_MASTERSERVERS->Items->Add(ms->Strings[i]);
        }
        BUTTON_MASTERSERVERS_REMOVE->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_MASTERSERVERS_REMOVEClick(
      TObject *Sender)
{
        for(int i = 0; i < LISTBOX_MASTERSERVERS->Count; i++) {
                if(LISTBOX_MASTERSERVERS->Selected[i]) {
                        this->ofpm->removeMasterServer(LISTBOX_MASTERSERVERS->Items->Strings[i]);
                        break;
                }
        }
        this->updateMasterServerSettings();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::LISTBOX_MASTERSERVERSClick(
      TObject *Sender)
{
        for(int i = 0; i < LISTBOX_MASTERSERVERS->Count; i++) {
                if(LISTBOX_MASTERSERVERS->Selected[i]) {
                        BUTTON_MASTERSERVERS_REMOVE->Enabled = true;
                        return;
                }
        }
        BUTTON_MASTERSERVERS_REMOVE->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_SERVERS_EXPORTClick(TObject *Sender)
{
        SaveDialog1->InitialDir = this->ofpm->getWorkDir();
        SaveDialog1->FileName = "hosts.txt";
        SaveDialog1->Filter = "Any file|*.*";
        SaveDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::SaveDialog1CanClose(TObject *Sender,
      bool &CanClose)
{
        String selectedFile = SaveDialog1->FileName;
        TStringList *toSave = new TStringList;
        if(FileExists(selectedFile)) {
                String prompt = this->languageDB->getGuiString("STRING_EXPORT_DIALOGPROMPT");
                String title = this->languageDB->getGuiString("STRING_EXPORT_DIALOGTITLE");
                String replace = this->languageDB->getGuiString("STRING_EXPORT_DIALOGREPLACE");
                String merge = this->languageDB->getGuiString("STRING_EXPORT_DIALOGMERGE");
                String message = prompt + "\n\n ";
                message += replace + "\n ";
                message += merge;
                int result = Application->MessageBox(message.c_str(), title.c_str(), MB_YESNOCANCEL | MB_ICONQUESTION);
                if(result == IDNO) {
                        toSave->LoadFromFile(selectedFile);
                } else if(result == IDCANCEL) {
                        delete toSave;
                        return;
                }
        }
        list<int> servers = this->ofpm->getAllMatchingServers(NULL);
        for(list<int>::iterator ci = servers.begin(); ci != servers.end(); ++ci) {
                int serverID = *ci;
                Server *srv = this->ofpm->getServerByID(serverID);
                if(srv != NULL) {
                        String address = srv->getAddress();
                        int index = toSave->IndexOf(address);
                        if(index < 0) {
                                toSave->Add(address);
                        }
                }
        }
        toSave->SaveToFile(selectedFile);
        delete toSave;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_CHATSETTINGS_BROWSEAUDIOFILEClick(
      TObject *Sender)
{
        OpenDialogAudioFile->Tag = ODAFT_ChatSettings;
        OpenDialogAudioFile->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TWINDOW_SETTINGS::CHECKBOX_CHATSETTINGS_BALLONHINTClick(
      TObject *Sender)
{
        this->chatSettings->setBallonHint(CHECKBOX_CHATSETTINGS_BALLONHINT->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::BUTTON_CHATSETTINGS_CLEARAUDIOFILEClick(
      TObject *Sender)
{
        this->chatSettings->setNotificationSoundFile("");
        this->updateChatSettings();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::CHECKBOX_CHATSETTINGS_AUDIONOTIFICATIONClick(
      TObject *Sender)
{
        this->chatSettings->setAudioNotification(CHECKBOX_CHATSETTINGS_AUDIONOTIFICATION->Checked);        
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_SETTINGS::TABSHEET_CHATSETTINGSShow(
      TObject *Sender)
{
        updateChatSettings();
}
//---------------------------------------------------------------------------

