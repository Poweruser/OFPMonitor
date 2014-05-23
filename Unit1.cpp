//---------------------------------------------------------------------------

#include "QueryAnswer.h"                                                                    
#include "Address.h"
#include "Player.h"                                                                                                     
#include "Server.h"
#include "Message.h"
#include "ProcessFinder.h"
#include "ConfigReader.h"
#include "StringSplitter.h"
#include "OFPMonitorDefinitions.h"

#include <vcl.h>
#include <list.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CoolTrayIcon"
#pragma resource "wavefiles.res"
#pragma resource "*.dfm"

TForm1 *Form1;

void TForm1::update(Observable *o) {
        if(o == this->fontSettings) {
                TFont *f = this->fontSettings->getFont();
                this->updateFontOfGui(f);
                delete f;
        } else if(o == this->gameControl) {
                this->updateGameControlGui();
        } else if(o == this->serverFilter) {
                this->updateFilterOfGui();
        } else if(o == this->ofpm) {
                StatusBar1->Repaint();
        } else if(o == this->chat && this->chat != NULL) {
                MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = this->chat->isDisconnected();
                MENUITEM_MAINMENU_CHAT_DISCONNECT->Enabled = !this->chat->isDisconnected();
                MemoChatInput->Enabled = this->chat->isConnected();
                this->chat->writeUserList(StringGrid3);
                this->chat->writeConversations(TabControl1);
                if(this->chat->hasNewMessages()) {
                        this->TABSHEET_CHAT->ImageIndex = 4;
                }
                if(TabControl1->TabIndex >= 0) {
                        String conversation = TabControl1->Tabs->Strings[TabControl1->TabIndex];
                        this->chat->syncChat(conversation, this->MemoChatOutput);
                }
                TabControl1->Repaint();
                if(this->chat->isDisconnected()) {
                        TabControl1->TabIndex = 0;
                        this->chat->loadThisChat(this->chatSettings->getChannel(), MemoChatOutput, MemoChatInput);
                        MemoChatInput->Clear();
                }
        } else if(o == this->languageDB) {
                this->updateGuiLanguage();
        } else if(o == this->downloader) {
                if(!this->downloader->checkError()) {
                        TStringList *list = new TStringList;
                        this->downloader->getFile(list);
                        this->ofpm->parseMasterServerFile(list);
                        delete list;
                        this->downloader->RemoveObserver(this);
                        delete this->downloader;
                        this->downloader = NULL;
                }
        }
}

void TForm1::setFontSettings(FontSettings *font) {
        this->fontSettings = font;
}

void TForm1::setWindowSettings(WindowSettings *windowSettings) {
        this->windowSettings = windowSettings;
}

void TForm1::setChatSettings(ChatSettings *chatSettings) {
        this->chatSettings = chatSettings;
}

void TForm1::setModel(OFPMonitorModel *model) {
        this->ofpm = model;
}

void TForm1::setServerFilter(ServerFilter *serverFilter) {
        this->serverFilter = serverFilter;
}

void TForm1::setGameControl(GameControl *gameControl) {
        this->gameControl = gameControl;
}

void TForm1::setLanguageDB(LanguageDB *languageDB) {
        this->languageDB = languageDB;
}

void TForm1::updateGuiLanguage() {
        if(this->languageDB != NULL) {
                this->StringGrid1->Cells[0][0] = this->languageDB->getGuiString("STRING_ID");
                this->StringGrid1->Cells[1][0] = this->languageDB->getGuiString("STRING_NAME");
                this->StringGrid1->Cells[2][0] = this->languageDB->getGuiString("STRING_PLAYERS");
                this->StringGrid1->Cells[3][0] = this->languageDB->getGuiString("STRING_STATUS");
                this->StringGrid1->Cells[4][0] = this->languageDB->getGuiString("STRING_ISLAND");
                this->StringGrid1->Cells[5][0] = this->languageDB->getGuiString("STRING_MISSION");
                this->StringGrid1->Cells[6][0] = this->languageDB->getGuiString("STRING_PING");
                this->StringGrid2->Cells[0][0] = this->languageDB->getGuiString("STRING_NAME");
                this->StringGrid2->Cells[1][0] = this->languageDB->getGuiString("STRING_SCORE");
                this->StringGrid2->Cells[2][0] = this->languageDB->getGuiString("STRING_DEATHS");
                this->StringGrid2->Cells[3][0] = this->languageDB->getGuiString("STRING_TEAM");
                this->BUTTON_SERVERINFO_COPYADDRESS->Caption = this->languageDB->getGuiString(BUTTON_SERVERINFO_COPYADDRESS->Name);
                this->BUTTON_GAMECONTROL_REFRESH->Caption = this->languageDB->getGuiString(BUTTON_GAMECONTROL_REFRESH->Name);
                this->CHECKBOX_FILTER_PLAYING->Caption = this->languageDB->getGuiString(CHECKBOX_FILTER_PLAYING->Name);
                this->CHECKBOX_FILTER_WAITING->Caption = this->languageDB->getGuiString(CHECKBOX_FILTER_WAITING->Name);
                this->CHECKBOX_FILTER_CREATING->Caption = this->languageDB->getGuiString(CHECKBOX_FILTER_CREATING->Name);
                this->CHECKBOX_FILTER_BRIEFING->Caption = this->languageDB->getGuiString(CHECKBOX_FILTER_BRIEFING->Name);
                this->CHECKBOX_FILTER_SETTINGUP->Caption = this->languageDB->getGuiString(CHECKBOX_FILTER_SETTINGUP->Name);
                this->CHECKBOX_FILTER_DEBRIEFING->Caption = this->languageDB->getGuiString(CHECKBOX_FILTER_DEBRIEFING->Name);
                this->CHECKBOX_FILTER_WITHPASSWORD->Caption = this->languageDB->getGuiString(CHECKBOX_FILTER_WITHPASSWORD->Name);
                this->CHECKBOX_FILTER_WITHOUTPASSWORD->Caption = this->languageDB->getGuiString(CHECKBOX_FILTER_WITHOUTPASSWORD->Name);
                this->CHECKBOX_GAMECONTROL_AUTOGREENUP->Caption = this->languageDB->getGuiString(CHECKBOX_GAMECONTROL_AUTOGREENUP->Name);
                this->CHECKBOX_GAMECONTROL_RESTORE->Caption = this->languageDB->getGuiString(CHECKBOX_GAMECONTROL_RESTORE->Name);
                this->CHECKBOX_GAMECONTROL_RESTORE_PLAYING->Caption = this->languageDB->getGuiString(CHECKBOX_GAMECONTROL_RESTORE_PLAYING->Name);
                this->CHECKBOX_GAMECONTROL_RESTORE_WAITING->Caption = this->languageDB->getGuiString(CHECKBOX_GAMECONTROL_RESTORE_WAITING->Name);
                this->CHECKBOX_GAMECONTROL_RESTORE_CREATING->Caption = this->languageDB->getGuiString(CHECKBOX_GAMECONTROL_RESTORE_CREATING->Name);
                this->CHECKBOX_GAMECONTROL_RESTORE_BRIEFING->Caption = this->languageDB->getGuiString(CHECKBOX_GAMECONTROL_RESTORE_BRIEFING->Name);
                this->CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFING->Caption = this->languageDB->getGuiString(CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFING->Name);
                this->CHECKBOX_GAMECONTROL_AUTODETECT->Caption = this->languageDB->getGuiString(CHECKBOX_GAMECONTROL_AUTODETECT->Name);
                this->LABEL_FILTER_STATUS->Caption = this->languageDB->getGuiString(LABEL_FILTER_STATUS->Name);
                this->LABEL_FILTER_PASSWORD->Caption = this->languageDB->getGuiString(LABEL_FILTER_PASSWORD->Name);
                this->LABEL_FILTER_MINIMUMPLAYERS->Caption = this->languageDB->getGuiString(LABEL_FILTER_MINIMUMPLAYERS->Name);
                this->LABEL_FILTER_SERVERNAME->Caption = this->languageDB->getGuiString(LABEL_FILTER_SERVERNAME->Name);
                this->LABEL_FILTER_MISSIONNAME->Caption = this->languageDB->getGuiString(LABEL_FILTER_MISSIONNAME->Name);
                this->LABEL_FILTER_PLAYERNAME->Caption = this->languageDB->getGuiString(LABEL_FILTER_PLAYERNAME->Name);
                this->LABEL_SERVERINFO_IP->Caption = this->languageDB->getGuiString(LABEL_SERVERINFO_IP->Name);
                this->LABEL_SERVERINFO_PORT->Caption = this->languageDB->getGuiString(LABEL_SERVERINFO_PORT->Name);
                this->LABEL_SERVERINFO_PLATFORM->Caption = this->languageDB->getGuiString(LABEL_SERVERINFO_PLATFORM->Name);
                this->LABEL_SERVERINFO_PASSWORD->Caption = this->languageDB->getGuiString(LABEL_SERVERINFO_PASSWORD->Name);
                this->LABEL_SERVERINFO_VERSION->Caption = this->languageDB->getGuiString(LABEL_SERVERINFO_VERSION->Name);
                this->LABEL_SERVERINFO_EQMODREQ->Caption = this->languageDB->getGuiString(LABEL_SERVERINFO_EQMODREQ->Name);
                this->LABEL_GAMECONTROL_PROCESS->Caption = this->languageDB->getGuiString(LABEL_GAMECONTROL_PROCESS->Name);
                this->LABEL_GAMECONTROL_SERVER->Caption = this->languageDB->getGuiString(LABEL_GAMECONTROL_SERVER->Name);
                this->LABEL_GAMECONTROL_EXE->Caption = this->languageDB->getGuiString(LABEL_GAMECONTROL_EXE->Name);
                this->LABEL_GAMECONTROL_AUTOGREENUP_DELAY->Caption = this->languageDB->getGuiString(LABEL_GAMECONTROL_AUTOGREENUP_DELAY->Name);
                this->GROUPBOX_SERVERINFO->Caption = this->languageDB->getGuiString(GROUPBOX_SERVERINFO->Name);
                this->GROUPBOX_FILTERS->Caption = this->languageDB->getGuiString(GROUPBOX_FILTERS->Name);
                this->GROUPBOX_GAMECONTROL_PROCESS->Caption = this->languageDB->getGuiString(GROUPBOX_GAMECONTROL_PROCESS->Name);
                this->MENUITEM_MAINMENU_EXIT->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_EXIT->Name);
                this->MENUITEM_MAINMENU_SETTINGS->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_SETTINGS->Name);
                this->MENUITEM_MAINMENU_FONT->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_FONT->Name);
                this->MENUITEM_MAINMENU_GETNEWSERVERLIST->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_GETNEWSERVERLIST->Name);
                this->MENUITEM_MAINMENU_SERVERLIST_GAMESPY->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_SERVERLIST_GAMESPY->Name);
                this->MENUITEM_MAINMENU_SERVERLIST_POWERSERVER->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_SERVERLIST_POWERSERVER->Name);
                this->MENUITEM_POPUP_AUTOJOIN_SAMEMODS->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_AUTOJOIN_SAMEMODS->Name);
                this->MENUITEM_POPUP_JOIN->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_JOIN->Name);
                this->MENUITEM_POPUP_AUTOJOIN->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_AUTOJOIN->Name);
                this->MENUITEM_POPUP_AUTOJOINB->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_AUTOJOINB->Name);
                this->MENUITEM_POPUP_MODS->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_MODS->Name);
                this->MENUITEM_POPUP_WATCH->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_WATCH->Name);
                this->MENUITEM_POPUP_AUTOJOIN_NOMODS->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_AUTOJOIN_NOMODS->Name);
                this->MENUITEM_POPUP_JOIN_SAMEMODS->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_JOIN_SAMEMODS->Name);
                this->MENUITEM_MAINMENU_CHAT_CONNECT->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_CHAT_CONNECT->Name);
                this->MENUITEM_MAINMENU_CHAT_DISCONNECT->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_CHAT_DISCONNECT->Name);
                this->MENUITEM_MAINMENU_CHAT->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_CHAT->Name);
                this->MENUITEM_POPUP_JOIN_NOMODS->Caption = this->languageDB->getGuiString(MENUITEM_POPUP_JOIN_NOMODS->Name);
                this->MENUITEM_MAINMENU_LOCALGAME->Caption = this->languageDB->getGuiString(MENUITEM_MAINMENU_LOCALGAME->Name);
                this->TABSHEET_SERVERINFO->Caption = this->languageDB->getGuiString(TABSHEET_SERVERINFO->Name);
                this->TABSHEET_CHAT->Caption = this->languageDB->getGuiString(TABSHEET_CHAT->Name);
                this->TABSHEET_GAMECONTROL->Caption = this->languageDB->getGuiString(TABSHEET_GAMECONTROL->Name);
                this->RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCE->Caption = this->languageDB->getGuiString(RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCE->Name);
                this->RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEAT->Caption = this->languageDB->getGuiString(RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEAT->Name);
        }
}

float TForm1::checkIfTableRatioZero(float in, TStringGrid *grid) {
        if(in - 0.001f < 0) {
                return ((((float)grid->Width / (float)grid->ColCount) - (float)grid->GridLineWidth) / (float)grid->Width);
        }
        return in;
}

/**
   Returns the time differents between two timestamps (in seconds)
   Return format h:mm:ss

 */

String TForm1::calcElapsedTime(long a, long b) {
        String out = "";
        long diff = b - a;
        int sec = diff % 60;
        diff = diff - sec;
        int min = (diff % 3600) / 60;
        diff = diff - (60 * min);
        int hour = diff / 3600;
        out = IntToStr(hour) + ":";
        if(min < 10) { out += "0"; }
        out += IntToStr(min) + ":";
        if(sec < 10) { out += "0"; }
        out += IntToStr(sec);
        return out;
}

void TForm1::updateFontOfGui(TFont *font) {
        this->StringGrid1->Font->Charset = font->Charset;
        this->StringGrid1->Font->Name = font->Name;
        this->StringGrid1->Font->Size = font->Size;
        this->StringGrid1->Font->Style = font->Style;
        this->StringGrid1->DefaultRowHeight = font->Size * 2.1f;
        this->StringGrid2->Font->Charset = font->Charset;
        this->StringGrid2->Font->Name = font->Name;
        this->StringGrid2->Font->Size = font->Size;
        this->StringGrid2->Font->Style = font->Style;
        this->StringGrid2->DefaultRowHeight = font->Size * 2.1f;
        this->Font->Charset = font->Charset;
        this->Panel2->Font->Charset = font->Charset;
        this->Panel2->Font->Name = font->Name;
        this->Panel2->Font->Size = font->Size;
        this->Panel2->Font->Style = font->Style;
        this->MemoChatInput->Constraints->MaxHeight = 3 * font->Size * 2.0f;
        this->MemoChatInput->Height = this->MemoChatInput->Constraints->MaxHeight;
        WINDOW_SETTINGS->Font->Charset = font->Charset;
        WINDOW_LOCALGAME->Font->Charset = font->Charset;
        WINDOW_UPDATE->Font->Charset = font->Charset;
}

void TForm1::updateMainMenuSettings() {
        this->MENUITEM_MAINMENU_SERVERLIST_GAMESPY->Checked = this->ofpm->isQueryOfGamespySet();
        this->MENUITEM_MAINMENU_SERVERLIST_POWERSERVER->Checked = this->ofpm->isQueryOfPowerserverSet();
}

void TForm1::updateFilterOfGui() {
        this->Edit3->Text = IntToStr(this->serverFilter->minPlayers);
        this->UpDown1->Position = this->serverFilter->minPlayers;
        this->Edit2->Text = this->serverFilter->getServerName();
        this->Edit1->Text = this->serverFilter->getMissionName();
        this->Edit4->Text = this->serverFilter->getPlayerName();
        this->CHECKBOX_FILTER_CREATING->Checked = this->serverFilter->creating;
        this->CHECKBOX_FILTER_WAITING->Checked = this->serverFilter->waiting;
        this->CHECKBOX_FILTER_SETTINGUP->Checked = this->serverFilter->settingup;
        this->CHECKBOX_FILTER_BRIEFING->Checked = this->serverFilter->briefing;
        this->CHECKBOX_FILTER_PLAYING->Checked = this->serverFilter->playing;
        this->CHECKBOX_FILTER_DEBRIEFING->Checked = this->serverFilter->debriefing;
        this->CHECKBOX_FILTER_WITHPASSWORD->Checked = this->serverFilter->withPassword;
        this->CHECKBOX_FILTER_WITHOUTPASSWORD->Checked = this->serverFilter->withoutPassword;
}

void TForm1::writeServerToStringGrid(int rowIndex, int serverID) {
        Server *srv = this->ofpm->getServerByID(serverID);
        if(srv != NULL) {
                this->StringGrid1->Cells[0][rowIndex] = " " + IntToStr(srv->getServerID());
                this->StringGrid1->Objects[0][rowIndex] = (TObject*) srv->getServerID();
                this->StringGrid1->Cells[1][rowIndex] = srv->getName();
                        /*
                          Because of some unknown reason, the maximum number of players,
                          reported by the server in a query, is 2 higher than it should be
                        */
                this->StringGrid1->Cells[2][rowIndex] = IntToStr(srv->getPlayerNum()) + " / " + IntToStr(srv->getMaxPlayerNum() - 2);
                String gs = this->getGameState(srv->getGameState());
                long Stime = srv->getStatusTime();
                if(Stime > 0) {
                        gs += " " + this->calcElapsedTime(Stime, time(0));
                }
                this->StringGrid1->Cells[3][rowIndex] = gs;
                this->StringGrid1->Cells[4][rowIndex] = srv->getIsland();
                this->StringGrid1->Cells[5][rowIndex] = srv->getMission();
                String pingField = IntToStr(srv->getPing());
                if(srv->hasTimedOut()) {
                        pingField = " --- ";
                }
                this->StringGrid1->Cells[6][rowIndex] = pingField;
                if(srv->getServerID() == this->selectedServerID) {
                        TGridRect myRect;
                        myRect.Left = 0;
                        myRect.Top = rowIndex;
                        myRect.Right = StringGrid1->ColCount - 1;
                        myRect.Bottom = rowIndex;
                        this->StringGrid1->Selection = myRect;
                }
        }
}

void TForm1::writePlayerToStringGrid(int rowIndex, Player *p) {
        this->StringGrid2->Cells[0][rowIndex] = p->name;
        this->StringGrid2->Cells[1][rowIndex] = p->score;
        this->StringGrid2->Cells[2][rowIndex] = p->deaths;
        this->StringGrid2->Cells[3][rowIndex] = p->team;
}

/**
   Returns the localized string of the server state
   2: Creating
   6: Waiting
   7: ??????? (is ignored by OFPMonitor, happens sometimes before BRIEFING,
      sometimes between DEBRIEFING and WAITING/CREATING; 'Loading Files' maybe?
   9: Debriefing
   12: Setting up
   13: Briefing
   14: Playing
 */

String TForm1::getGameState (int i) {
        String out = IntToStr(i);
        switch (i) {
                case SERVERSTATE_CREATING:
                        out = this->CHECKBOX_FILTER_CREATING->Caption;
                        break;
                case SERVERSTATE_WAITING:
                        out = this->CHECKBOX_FILTER_WAITING->Caption;
                        break;
                case SERVERSTATE_DEBRIEFING:
                        out = this->CHECKBOX_FILTER_DEBRIEFING->Caption;
                        break;
                case SERVERSTATE_SETTINGUP:
                        out = this->CHECKBOX_FILTER_SETTINGUP->Caption;
                        break;
                case SERVERSTATE_BRIEFING:
                        out = this->CHECKBOX_FILTER_BRIEFING->Caption;
                        break;
                case SERVERSTATE_PLAYING:
                        out = this->CHECKBOX_FILTER_PLAYING->Caption;
                        break;
        }
        return out;
}


/**
   Checks if  c  contains  d
   @c  the String to check
   @d  the String to look for
   @return  'true' is c does contain d, otherwise 'false'
 */

bool TForm1::doNameFilter(String c, String d) {
        bool out = false;
        String a = c.LowerCase();
        String b = d.LowerCase();
        for(int z = 0; z <= ((a.Length() - b.Length()) + 1); z++) {
                if(a.SubString(z,b.Length()) == b) {
                        out = true;
                        break;
                }
        }
        return out;
}

/**
   Empties the Server table
 */

void TForm1::setEmptyServerList() {
        for(int i = 0; i < this->StringGrid1->ColCount; i++) {
                this->StringGrid1->Cells[i][1] = "";
        }
        this->StringGrid1->RowCount = 2;
}

/**
   Converts an integer to a String and adds leading Zeros to the front until
   the String is @length characters long. Used to sort numbers alphabetically
   @i  number to convert
   @length  length of the String to return
   @return  the number with leading zeros as a String
 */

String TForm1::addLeadingZeros(int number, int length) {
        String a = IntToStr(number);
        while (a.Length() < length) {
                a = "0" + a;
        }
        return a;
}

/**
   Empties the Player table
 */

void TForm1::setEmptyPlayerList() {
        this->StringGrid2->RowCount = 2;
        for(int i = 0; i < this->StringGrid2->ColCount; i++) {
                this->StringGrid2->Cells[i][1] = "";
        }
}

/**
   Performs the update of the Player table. Reads the index of the currently
   selected row in the server table, gets the player list and sorts it
   with the help of a TStringList

   @index  index (positive number) of the server , negativ number if the index
           couldnt be found   
 */

void TForm1::processPlayerList(int serverID) {
        TStringList *plist = new TStringList;
        plist->Sorted = true;
        plist->CaseSensitive = true;
        plist->Duplicates = dupAccept;
        TStringList *plistNegScore = new TStringList;
        plistNegScore->Sorted = true;
        plistNegScore->CaseSensitive = true;
        plistNegScore->Duplicates = dupAccept;
        Server *selected = this->ofpm->getServerByID(serverID);
        if(selected == NULL) {
                int row = this->StringGrid1->Selection.BottomRight.Y;
                selected = this->ofpm->getServerByID((int) (this->StringGrid1->Objects[0][row]));
        }
        if(selected != NULL) {
                int availablePlayers = selected->getPlayerNumOfPlayerList();
                int realPlayers = selected->getPlayerNum();
                for(int i = 0; i < availablePlayers && i < realPlayers; i++) {
                        Player *p = selected->getPlayer(i);
                        if(p != NULL) {
                                if(this->playerTableSorter->isNameSet()) {
                                        plist->AddObject(p->name, (TObject*) p);
                                } else if(this->playerTableSorter->isScoreSet()) {
                                        if(p->score >= 0) {
                                                plist->AddObject(this->addLeadingZeros(p->score, 6), (TObject*) p);
                                        } else {
                                                plistNegScore->AddObject(this->addLeadingZeros(p->score, 6), (TObject*) p);
                                        }
                                } else if(this->playerTableSorter->isDeathsSet()) {
                                        plist->AddObject(this->addLeadingZeros(p->deaths, 4), (TObject*) p);
                                } else if(this->playerTableSorter->isTeamSet()) {
                                        plist->AddObject(p->team, (TObject*) p);
                                }
                        }
                }
        }
        if((plist->Count + plistNegScore->Count) == 0) {
                this->setEmptyPlayerList();

        } else {
                int z = plist->Count;
                int x = plistNegScore->Count;
                if(this->playerTableSorter->isNormalOrder()) {
                        for(int i = 1 + x; i <= z + x; i++) {
                                Player *p = (Player*) plist->Objects[0];
                                this->writePlayerToStringGrid(i, p);
                                plist->Delete(0);
                        }
                        for(int i = x; i >= 1; i--) {
                                Player *q = (Player*) plistNegScore->Objects[0];
                                this->writePlayerToStringGrid(i, q);
                                plistNegScore->Delete(0);
                        }
                } else {
                        for(int i = z; i >= 1; i--) {
                                Player *p = (Player*) plist->Objects[0];
                                this->writePlayerToStringGrid(i, p);
                                plist->Delete(0);
                        }
                        for(int i = z + 1; i <= z + x; i++) {
                                Player *q = (Player*) plistNegScore->Objects[0];
                                this->writePlayerToStringGrid(i, q);
                                plistNegScore->Delete(0);
                        }
                }
                this->StringGrid2->RowCount = z + x + 1;
        }
        delete (plist);
        delete (plistNegScore);
}

/**
   Updates the Server Info part of the GUI

   @index  the index of the server
 */

void TForm1::updateServerInfoBox(int serverID) {
        Server *srv = this->ofpm->getServerByID(serverID);
        if(srv != NULL) {
                if(srv->isOnline()) {
                        this->LABEL_SERVERINFO_IP_VALUE->Caption = srv->getIP();
                        this->LABEL_SERVERINFO_PORT_VALUE->Caption = IntToStr(srv->getGamePort());
                        this->LABEL_SERVERINFO_PLATFORM_VALUE->Caption = srv->getPlatform();
                        this->LABEL_SERVERINFO_NAME->Caption = srv->getName();
                        this->BUTTON_SERVERINFO_COPYADDRESS->Enabled = true;
                        if(srv->hasPassword()) {
                                this->LABEL_SERVERINFO_PASSWORD_VALUE->Caption = this->languageDB->getGuiString("STRING_YES");
                        } else {
                                this->LABEL_SERVERINFO_PASSWORD_VALUE->Caption = this->languageDB->getGuiString("STRING_NO");
                        }
                        if(srv->requiresEqualMod()) {
                                this->LABEL_SERVERINFO_EQMODREQ_VALUE->Caption = this->languageDB->getGuiString("STRING_YES");
                        } else {
                                this->LABEL_SERVERINFO_EQMODREQ_VALUE->Caption = this->languageDB->getGuiString("STRING_NO");
                        }
                        this->LABEL_SERVERINFO_VERSION_VALUE->Caption = IntToStr(srv->getRequiredVersion()) + " / " + IntToStr(srv->getActualVersion());
                        return;
                }
        }
        this->BUTTON_SERVERINFO_COPYADDRESS->Enabled = false;
        this->LABEL_SERVERINFO_NAME->Caption = " ";
        this->LABEL_SERVERINFO_IP_VALUE->Caption = " ";
        this->LABEL_SERVERINFO_PORT_VALUE->Caption = " ";
        this->LABEL_SERVERINFO_VERSION_VALUE->Caption = " ";
        this->LABEL_SERVERINFO_PLATFORM_VALUE->Caption = " ";
        this->LABEL_SERVERINFO_PASSWORD_VALUE->Caption = " ";
        this->LABEL_SERVERINFO_EQMODREQ_VALUE->Caption = " ";
}

/**
   Performs the update of the GUI

   @userinput  'true' if the update was triggered
               by the user (e.g. changing filter rules)

 */
void TForm1::filterChanged(bool userinput) {
        if(filterChanging) {
                return;
        }
        filterChanging = true;

        if(this->selectedServerID == NULL_SERVERID) {
                int row = this->StringGrid1->Selection.BottomRight.Y;
                String z = this->StringGrid1->Cells[0][row];
                if(!z.IsEmpty()) {
                        this->setSelectedServer((int) (this->StringGrid1->Objects[0][row]));
                }
        }

        TStringList *alist = new TStringList;
        alist->Sorted = true;
        alist->CaseSensitive = true;
        alist->Duplicates = dupAccept;
        TStringList *slist = new TStringList;
        slist->Sorted = true;
        slist->CaseSensitive = true;
        slist->Duplicates = dupAccept;
        TStringList *flist = new TStringList;
        flist->Sorted = true;
        flist->CaseSensitive = true;
        flist->Duplicates = dupAccept;
        TStringList *sortList;
        list<int> matches;
        String totalServerCount = "", onlineServerCount = "";
        if(this->ofpm != NULL) {
                matches = this->ofpm->getAllMatchingServers(this->serverFilter);
                totalServerCount = IntToStr(this->ofpm->getTotalServerCount());
                onlineServerCount = IntToStr(this->ofpm->getOnlineServerCount());
        }
        for (list<int>::iterator si = matches.begin(); si != matches.end(); ++si) {
                int serverID = *si;
                Server *srv = this->ofpm->getServerByID(serverID);
                if(srv == NULL) {
                        continue;
                }
                if(srv->isFavorite()) {
                        sortList = flist;
                } else if(srv->isAutoJoin()) {
                        sortList = alist;
                } else {
                        sortList = slist;
                }

                if(this->serverTableSorter->isIdSet()) {
                        sortList->AddObject(this->addLeadingZeros(srv->getServerID(), 3), (TObject*) srv->getServerID());
                } else if(this->serverTableSorter->isNameSet()) {
                        sortList->AddObject(srv->getName(), (TObject*) srv);
                } else if(this->serverTableSorter->isPlayersSet()) {
                        sortList->AddObject(this->addLeadingZeros(srv->getPlayerNum(), 3), (TObject*) srv->getServerID());
                } else if(this->serverTableSorter->isStatusSet()) {
                        sortList->AddObject(srv->getGameState(), (TObject*) srv->getServerID());
                } else if(this->serverTableSorter->isIslandSet()) {
                        sortList->AddObject(srv->getIsland(), (TObject*) srv->getServerID());
                } else if(this->serverTableSorter->isMissionSet()) {
                        sortList->AddObject(srv->getMission(), (TObject*) srv->getServerID());
                } else if(this->serverTableSorter->isPingSet()) {
                        sortList->AddObject(this->addLeadingZeros(srv->getPing(), 5), (TObject*) srv->getServerID());
                }
        }
        this->StatusBar1->Panels->Items[0]->Text = this->languageDB->getGuiString("STRING_LISTED") + " " + totalServerCount;
        this->StatusBar1->Panels->Items[1]->Text = this->languageDB->getGuiString("STRING_ONLINE") + " " + onlineServerCount;
        if(matches.size() == 0) {
                this->setEmptyServerList();
                this->setEmptyPlayerList();
                this->updateServerInfoBox(NULL);
        } else {
                int rowIndex = 0;
                TStringList *array[3];
                array[0] = alist;
                array[1] = flist;
                array[2] = slist;
                for(int j = 0; j < 3; j++) {
                        for(int i = 0; i < array[j]->Count; i++) {
                                rowIndex++;
                                TObject *serverID = array[j]->Objects[i];
                                if(!this->serverTableSorter->isNormalOrder()) {
                                        serverID = array[j]->Objects[array[j]->Count - (i + 1)];
                                }
                                this->writeServerToStringGrid(rowIndex, (int)serverID);
                        }
                }
                this->StringGrid1->RowCount = max(1, rowIndex + 1);
                Server *srv = this->ofpm->getServerByID(this->selectedServerID);
                if(srv != NULL) {
                        processPlayerList(this->selectedServerID);
                        updateServerInfoBox(this->selectedServerID);
                        this->CoolTrayIcon1->Hint = srv->getName() + "     " + getGameState(srv->getGameState()) + "     " +  String(srv->getPlayerNum()) + " " + this->languageDB->getGuiString("STRING_PLAYERS");
                } else {
                        this->CoolTrayIcon1->Hint = "OFPMonitor";
                }

        }
        delete alist;
        delete flist;
        delete slist;
        filterChanging = false;
}


/**
   Copys a String to the clipboard of the OS
 */

void TForm1::copyToClipBoard (String msg) {
	if (OpenClipboard(NULL) != 0) {
		EmptyClipboard();
                HGLOBAL hClipboardData;
                hClipboardData = GlobalAlloc(GMEM_DDESHARE, msg.Length()+1);
                char * pchData;
                pchData = (char*)GlobalLock(hClipboardData);
                strcpy(pchData, LPCSTR(msg.c_str()));
                GlobalUnlock(hClipboardData);
                SetClipboardData(CF_TEXT,hClipboardData);
                CloseClipboard();
        }
}

void TForm1::updateGameControlGui() {
        bool foundProcess = false;
        for(int i = 0; i < this->ComboBox1->Items->Count; i++) {
                ProcessInfo *proc = (ProcessInfo *) this->ComboBox1->Items->Objects[i];
                if(proc != NULL) {
                        if(this->gameControl->matchesProcess(*proc)) {
                                this->ComboBox1->ItemIndex = i;
                                this->ComboBox1Change(ComboBox1);
                                foundProcess = true;
                                break;
                        }
                }
        }
        if(!foundProcess) {
                if(gameControl->verifyProcess()) {
                        this->BUTTON_GAMECONTROL_REFRESH->Click();
                        return;
                }
                this->ComboBox1->ItemIndex = -1;
                this->ComboBox1Change(ComboBox1);
                Label9->Caption = "";
        }
        int selSrv = NULL_SERVERID;
        bool foundServer;
        if(this->ComboBox2->ItemIndex > -1) {
                selSrv = (int) (this->ComboBox2->Items->Objects[this->ComboBox2->ItemIndex]);
        }
        if(!(foundServer = this->gameControl->matchesServer(selSrv))) {
                for(int i = 0; i < this->ComboBox2->Items->Count; i++) {
                        Server *srv = this->ofpm->getServerByID((int) (this->ComboBox2->Items->Objects[i]));
                        if(srv != NULL) {
                                if(this->gameControl->matchesServer(srv->getServerID())) {
                                        this->ComboBox2->ItemIndex = i;
                                        this->ComboBox2Change(ComboBox2);
                                        foundServer = true;
                                        break;
                                }
                        }
                }
        }
        if(!foundServer) {
                if(this->gameControl->verifyServer()) {
                        this->BUTTON_GAMECONTROL_REFRESH->Click();
                        return;
                }
                this->ComboBox2->ItemIndex = -1;
                this->ComboBox2Change(ComboBox2);
        }
        if(foundProcess && foundServer && (this->gameControl->isAutoGreenOn() || this->gameControl->isRestoreGameOn())) {
                TABSHEET_GAMECONTROL->ImageIndex = 1;
        } else {
                TABSHEET_GAMECONTROL->ImageIndex = 0;
        }
        PageControl1->Repaint();
        this->CHECKBOX_GAMECONTROL_AUTODETECT->Checked = this->gameControl->isAutoDetectOn();
        this->CHECKBOX_GAMECONTROL_AUTOGREENUP->Checked = this->gameControl->isAutoGreenOn();
        this->CHECKBOX_GAMECONTROL_RESTORE->Checked = this->gameControl->isRestoreGameOn();
        bool repeatedGreenUp = this->gameControl->getGreenUpRepeat();
        this->RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCE->Checked = !repeatedGreenUp;
        this->RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEAT->Checked = repeatedGreenUp;
        this->CHECKBOX_GAMECONTROL_RESTORE_CREATING->Checked = this->gameControl->restoreOnCreating;
        this->CHECKBOX_GAMECONTROL_RESTORE_WAITING->Checked = this->gameControl->restoreOnWaiting;
        this->CHECKBOX_GAMECONTROL_RESTORE_BRIEFING->Checked = this->gameControl->restoreOnBriefing;
        this->CHECKBOX_GAMECONTROL_RESTORE_PLAYING->Checked = this->gameControl->restoreOnPlaying;
        this->CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFING->Checked = this->gameControl->restoreOnDebriefing;
        this->UpDown2->Position = this->gameControl->getGreenUpDelay();
        this->ComboBox1->Enabled = !(this->ComboBox1->Items->Count == 0);
        this->ComboBox2->Enabled = !(this->ComboBox2->Items->Count == 0);
}


void TForm1::updateWindowSettingsPosition() {
        this->windowSettings->setLeft(this->Left);
        this->windowSettings->setTop(this->Top);
        this->windowSettings->setHeight(this->Height);
        this->windowSettings->setWidth(this->Width);
        this->windowSettings->setDevider(this->PageControl1->Height);
}

void TForm1::applyWindowSettings() {
        this->Position = poDesigned;
        this->Top = this->windowSettings->getTop();
        this->Left = this->windowSettings->getLeft();

        if(this->windowSettings->getHeight() >= this->Constraints->MinHeight) {
                this->Height = this->windowSettings->getHeight();
        }
        if(this->windowSettings->getWidth() >= this->Constraints->MinWidth) {
                this->Width = this->windowSettings->getWidth();
        }
        if(this->windowSettings->getDevider() < this->PageControl1->Constraints->MinHeight ||
                this->windowSettings->getDevider() > this->ClientHeight - (
                        this->StringGrid1->Constraints->MinHeight +
                        this->StatusBar1->Height +
                        this->Splitter1->Height)) {
                this->PageControl1->Height = this->PageControl1->Constraints->MinHeight;
        } else {
                this->PageControl1->Height = this->windowSettings->getDevider();
        }
        this->applyWindowSettingsRatios();
        this->setAlwaysOnTop(this->windowSettings->isAlwaysOnTopSet());
}

void TForm1::applyWindowSettingsRatios() {
        for(int i = 0; i < this->StringGrid1->ColCount; i++) {
                this->StringGrid1->ColWidths[i] = (float)this->StringGrid1->Width *
                        this->windowSettings->checkIfZero(this->windowSettings->getRatioServerTable(i), this->StringGrid1);
        }
        for(int i = 0; i < this->StringGrid2->ColCount; i++) {
                this->StringGrid2->ColWidths[i] = (float)this->StringGrid2->Width *
                        this->windowSettings->checkIfZero(this->windowSettings->getRatioPlayerTable(i), this->StringGrid2);
        }
}

void TForm1::setSelectedServer(int serverID) {
        if(this->selectedServerID >= 0) {
                Server *srv = this->ofpm->getServerByID(this->selectedServerID);
                if(srv != NULL) {
                        srv->setSelectedToDisplay(false);
                }
        }
        this->selectedServerID = serverID;
        if(this->selectedServerID >= 0) {
                Server *srv = this->ofpm->getServerByID(this->selectedServerID);
                if(srv != NULL) {
                        srv->setSelectedToDisplay(true);
                }
        }
}

bool TForm1::getServerPasswordDialog(String &password) {
        String caption = this->languageDB->getGuiString("STRING_PASSWORDDIALOG_TITLE");
        Server *srv = this->ofpm->getServerByID(this->selectedServerID);
        String text = "";
        if(srv != NULL) {
                text = srv->getName() + "\n\n";
        }
        text += this->languageDB->getGuiString("STRING_PASSWORDDIALOG_PROMPT");
        return InputQuery(caption, text, password);
}

void TForm1::setAlwaysOnTop(bool active) {
        this->windowSettings->setAlwaysOnTop(active);
        if(active) {
                SetWindowPos(this->Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE |SWP_NOOWNERZORDER);
        } else {
                SetWindowPos(this->Handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE|SWP_NOOWNERZORDER);
        }
        StatusBar1->Repaint();
}

void TForm1::toggleAlwaysOnTop() {
        this->setAlwaysOnTop(!this->windowSettings->isAlwaysOnTopSet());
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Application->OnMinimize = OnMinimize;
        this->Caption = Application->Title;
        StringGrid1->Cells[0][0] = "ID";
        StringGrid1->Cells[1][0] = "Name";
        StringGrid1->Cells[2][0] = "Players";
        StringGrid1->Cells[3][0] = "Status";
        StringGrid1->Cells[4][0] = "Island";
        StringGrid1->Cells[5][0] = "Mission";
        StringGrid1->Cells[6][0] = "Ping";
        StringGrid2->Cells[0][0] = "Name";
        StringGrid2->Cells[1][0] = "Score";
        StringGrid2->Cells[2][0] = "Deaths";
        StringGrid2->Cells[3][0] = "Team";
        this->serverTableSorter = new ServerTableSorter();
        this->playerTableSorter = new PlayerTableSorter();
        this->filterChanging = false;
        this->chat = NULL;
        this->chatThreadHandle = NULL;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
        String z = (StringGrid1->Cells[0][ARow]).Trim();
        TObject *to = (StringGrid1->Objects[0][ARow]);
        if(!z.IsEmpty()) {
                int serverID = (int)to;
                this->setSelectedServer(serverID);
                if(serverID >= 0) {
                        this->processPlayerList(serverID);
                        this->updateServerInfoBox(serverID);
                }
        } else {
                this->setSelectedServer(NULL_SERVERID);
                this->setEmptyPlayerList();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        int i = Timer1->Tag;
        i++;
        Timer1->Tag = i;
        Application->ProcessMessages();
        if(this->ofpm != NULL) {
                this->ofpm->ProcessMessages();
                if(i >= this->ofpm->getInterval()) {
                        this->ofpm->queryServers();
                        Timer1->Tag = 0;
                }
                MENUITEM_MAINMENU_GETNEWSERVERLIST->Enabled = this->ofpm->isGameSpyUpdateDone();
        }
        this->filterChanged(false);
        if(this->gameControl != NULL) {
                this->gameControl->ProcessMessages();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        this->Enabled = false;
        Timer1->Enabled = false;
        if(this->chatThreadHandle != NULL) {
                TerminateThread(this->chatThreadHandle, 0);
        }
        if(this->chat != NULL) {
                this->chat->disconnect();
                delete this->chat;
                this->chat = NULL;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BUTTON_SERVERINFO_COPYADDRESSClick(TObject *Sender)
{
        this->copyToClipBoard(LABEL_SERVERINFO_IP_VALUE->Caption + ":" + LABEL_SERVERINFO_PORT_VALUE->Caption);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_PLAYINGClick(TObject *Sender)
{
        this->serverFilter->playing = CHECKBOX_FILTER_PLAYING->Checked;
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_WAITINGClick(TObject *Sender)
{
        this->serverFilter->waiting = CHECKBOX_FILTER_WAITING->Checked;
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_CREATINGClick(TObject *Sender)
{
        this->serverFilter->creating = CHECKBOX_FILTER_CREATING->Checked;
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_BRIEFINGClick(TObject *Sender)
{
        this->serverFilter->briefing = CHECKBOX_FILTER_BRIEFING->Checked;
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_DEBRIEFINGClick(TObject *Sender)
{
        this->serverFilter->debriefing = CHECKBOX_FILTER_DEBRIEFING->Checked;
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_WITHPASSWORDClick(TObject *Sender)
{
        this->serverFilter->withPassword = CHECKBOX_FILTER_WITHPASSWORD->Checked;
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_WITHOUTPASSWORDClick(TObject *Sender)
{
        this->serverFilter->withoutPassword = CHECKBOX_FILTER_WITHOUTPASSWORD->Checked;
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
        this->serverFilter->setMissionName(Edit1->Text);
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(Button == mbLeft && Y < StringGrid1->DefaultRowHeight) {
                int col0, col1, col2, col3, col4, col5, col6;
                col0 = StringGrid1->ColWidths[0] + StringGrid1->GridLineWidth;
                col1 = col0 + StringGrid1->ColWidths[1] + StringGrid1->GridLineWidth;
                col2 = col1 + StringGrid1->ColWidths[2] + StringGrid1->GridLineWidth;
                col3 = col2 + StringGrid1->ColWidths[3] + StringGrid1->GridLineWidth;
                col4 = col3 + StringGrid1->ColWidths[4] + StringGrid1->GridLineWidth;
                col5 = col4 + StringGrid1->ColWidths[5] + StringGrid1->GridLineWidth;
                col6 = col5 + StringGrid1->ColWidths[6] + StringGrid1->GridLineWidth;

                if(X < col6) {
                        if(X < col0) {
                                this->serverTableSorter->setId();
                        } else if(X < col1) {
                                this->serverTableSorter->setName();
                        } else if(X < col2) {
                                this->serverTableSorter->setPlayers();
                        } else if(X < col3) {
                                this->serverTableSorter->setStatus();
                        } else if(X < col4) {
                                this->serverTableSorter->setIsland();
                        } else if(X < col5) {
                                this->serverTableSorter->setMission();
                        } else if(X < col6) {
                                this->serverTableSorter->setPing();
                        }
                        this->filterChanged(false);
                }
        } else if(Button == mbRight && Y >= StringGrid1->DefaultRowHeight) {
                int c = ((Y - StringGrid1->DefaultRowHeight) / (StringGrid1->DefaultRowHeight + 1)) + 1;
                if(StringGrid1->RowCount > c) {
                                int serverID = (int)(StringGrid1->Objects[0][c + (StringGrid1->TopRow - 1)]);
                                TGridRect myRect;
                                myRect.Left = 0;
                                myRect.Top = c + (StringGrid1->TopRow - 1);
                                myRect.Right = StringGrid1->ColCount - 1;
                                myRect.Bottom = c + (StringGrid1->TopRow - 1);
                                this->StringGrid1->Selection = myRect;
                                Server *srv = this->ofpm->getServerByID(serverID);
                                if(srv != NULL) {
                                        this->setSelectedServer(srv->getServerID());
                                        this->selectedServerIDForPopUp = srv->getServerID();
                                        processPlayerList(srv->getServerID());
                                        updateServerInfoBox(srv->getServerID());
                                        StringSplitter ssp(srv->getMod());
                                        ssp.setKeepEmptyParts(false);
                                        TStringList *mods = ssp.split(";");
                                        MENUITEM_POPUP_AUTOJOIN->Visible = srv->isStatePlaying() && !srv->isAutoJoin();
                                        MENUITEM_POPUP_AUTOJOINB->Visible = srv->isAutoJoin();
                                        MENUITEM_POPUP_AUTOJOINB->Checked = srv->isAutoJoin();
                                        MENUITEM_POPUP_WATCH->Checked = srv->isWatched();

                                        while(mods->Count > MENUITEM_POPUP_MODS->Count) {
                                                TMenuItem *m = new TMenuItem(this);
                                                m->Visible = false;
                                                MENUITEM_POPUP_MODS->Add(m);
                                        }

                                        int items = 0;
                                        for(int i = 0; i < mods->Count; i++) {
                                                TMenuItem *m = MENUITEM_POPUP_MODS->Items[i];
                                                m->Caption = mods->Strings[i];
                                                m->Visible = true;
                                                items++;
                                        }
                                        MENUITEM_POPUP_MODS->Enabled = (items > 0);
                                        for(; items < MENUITEM_POPUP_MODS->Count; items++) {
                                                TMenuItem *m = MENUITEM_POPUP_MODS->Items[items];
                                                m->Visible = false;
                                        }
                                        PopupMenu1->Popup(this->Left + StringGrid1->Left + X + 5,this->Top + StringGrid1->Top + Y + StringGrid1->DefaultRowHeight + 25);
                                }
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit2Change(TObject *Sender)
{
        this->serverFilter->setServerName(Edit2->Text);
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        int col0, col1, col2, col3, col4, col5, col6;
        col0 = StringGrid2->ColWidths[0] + StringGrid2->GridLineWidth;
        col1 = col0 + StringGrid2->ColWidths[1] + StringGrid2->GridLineWidth;
        col2 = col1 + StringGrid2->ColWidths[2] + StringGrid2->GridLineWidth;
        col3 = col2 + StringGrid2->ColWidths[3] + StringGrid2->GridLineWidth;

        if(Button == 0 && Y < StringGrid2->DefaultRowHeight) {
                if(X < col3) {
                        if(X < col0) {
                                playerTableSorter->setName();
                        } else if(X < col1) {
                                playerTableSorter->setScore();
                        } else if(X < col2) {
                                playerTableSorter->setDeaths();
                        } else if(X < col3) {
                                playerTableSorter->setTeam();
                        }
                        processPlayerList(NULL);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit4Change(TObject *Sender)
{
        this->serverFilter->setPlayerName(Edit4->Text);
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PopupMenu1Popup(TObject *Sender)
{
        int serverID = this->selectedServerIDForPopUp;
        Server *srv = this->ofpm->getServerByID(serverID);
        int additionalItems = 2;

        TMenuItem *join;
        TMenuItem *autojoin;

        int i;
        for(i = 0; i < additionalItems; i++) {
                join = MENUITEM_POPUP_JOIN->Items[i];
                autojoin = MENUITEM_POPUP_AUTOJOIN->Items[i];
                join->Tag = i - additionalItems;
                autojoin->Tag = i - additionalItems;
                if(i == 0) {
                        join->OnClick = ClickJoinButton;
                        autojoin->OnClick = ClickAutoJoinConfButton;
                        if(srv != NULL) {
                                join->Enabled = !(srv->requiresEqualMod() && srv->hasMods());
                        } else {
                                join->Enabled = false;
                        }
                        autojoin->Enabled = join->Enabled;
                        join->Visible = true;
                        autojoin->Visible = true;
                } else if(i == 1) {
                        join->OnClick = ClickJoinButton;
                        autojoin->OnClick = ClickAutoJoinConfButton;
                        if(srv != NULL) {
                                join->Visible = srv->requiresEqualMod() && srv->hasMods();
                        } else {
                                join->Visible = false;
                        }
                        autojoin->Visible = join->Visible;
                }
        }
        Game *game = this->ofpm->getMatchingGame(serverID);
        bool validGame = (game != NULL);
        MENUITEM_POPUP_JOIN->Enabled = validGame;
        MENUITEM_POPUP_AUTOJOIN->Enabled = validGame;
        MENUITEM_POPUP_AUTOJOINB->Enabled = validGame;
        if(validGame) {
                for(i = additionalItems; i - additionalItems < game->getConfigurationsCount() || i < MENUITEM_POPUP_JOIN->Count; i++) {
                        bool handled = false;
                        int counter = i - additionalItems;
                        Configuration *conf = game->getConfiguration(counter);
                        if(conf != NULL) {
                                String s = conf->createListEntry();
                                if(!s.IsEmpty()) {
                                        if(i < MENUITEM_POPUP_JOIN->Count) {
                                                join = MENUITEM_POPUP_JOIN->Items[i];
                                        } else {
                                                join = new TMenuItem(this);
                                                MENUITEM_POPUP_JOIN->Add(join);
                                        }
                                        if(i < MENUITEM_POPUP_AUTOJOIN->Count) {
                                                autojoin = MENUITEM_POPUP_AUTOJOIN->Items[i];
                                        } else {
                                                autojoin = new TMenuItem(this);
                                                MENUITEM_POPUP_AUTOJOIN->Add(autojoin);
                                        }
                                        join->Tag = (int)conf;
                                        join->Caption = s;
                                        join->Visible = true;
                                        join->OnClick = ClickJoinButton;

                                        autojoin->Tag = (int)conf;
                                        autojoin->Caption = s;
                                        autojoin->Visible = true;
                                        autojoin->OnClick = ClickAutoJoinConfButton;

                                        if(srv != NULL) {
                                                join->Enabled = !srv->requiresEqualMod() || (srv->requiresEqualMod() && srv->doesModMatch(conf->createModLine()));
                                        } else {
                                                join->Enabled = false;
                                        }
                                        autojoin->Enabled = join->Enabled;
                                        handled = true;
                                }
                        }
                        if(!handled) {
                                if(i < MENUITEM_POPUP_JOIN->Count) {
                                        MENUITEM_POPUP_JOIN->Items[i]->Visible = false;
                                        MENUITEM_POPUP_AUTOJOIN->Items[i]->Visible = false;
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClickJoinButton(TObject *Sender)
{
        this->ofpm->disableAutoJoin();
        Server *srv = this->ofpm->getServerByID(this->selectedServerIDForPopUp);
        Game *game = this->ofpm->getMatchingGame(this->selectedServerIDForPopUp);
        int tag = ((TMenuItem*)Sender)->Tag;
        if(srv != NULL && game != NULL) {
                bool startGame = true;
                bool found = srv->isPlayerOnServer(game->getProfileName(), true);
                if(found) {
                        int msgBoxRes = MessageBoxA(NULL, this->languageDB->getGuiString("STRING_PLAYER_ALREADY_ON_SERVER").c_str(),
                                    "", MB_YESNO | MB_ICONQUESTION);
                        startGame = (msgBoxRes == IDYES);
                }
                if(startGame) {
                        String confLine = "";
                        bool inputOk = true;
                        String password = "";
                        if(tag < 0) {       
                                if(srv->hasPassword()) {
                                        inputOk = this->getServerPasswordDialog(password);
                                }
                                if(inputOk) {
                                        if(tag == -1) {
                                                confLine = game->createDefaultStartLine(srv->getIP(), srv->getGamePort(), srv->getMod(), password);
                                        } else if(tag == -2) {
                                                confLine = game->createDefaultStartLine(srv->getIP(), srv->getGamePort(), "", password);
                                        }
                                }
                        } else {
                                Configuration *conf = (Configuration*)tag;
                                if(srv->hasPassword() && conf->getPassword().IsEmpty()) {
                                        inputOk =  this->getServerPasswordDialog(password);
                                }
                                if(inputOk) {
                                        confLine = conf->createStartLine(srv->getIP(), srv->getGamePort(), game->getProfileName(), srv->hasPassword(), password);
                                }
                        }
                        if(!confLine.IsEmpty()) {
                                this->ofpm->startTheGame(game, confLine);
                        }
                }
        }
}
//---------------------------------------------------------------------------
  void __fastcall TForm1::ClickAutoJoinConfButton(TObject *Sender)
{
        this->ofpm->disableAutoJoin();
        int tag = ((TMenuItem*)Sender)->Tag;
        Server *srv = this->ofpm->getServerByID(this->selectedServerIDForPopUp);
        Game *game = this->ofpm->getMatchingGame(this->selectedServerIDForPopUp);
        if(game != NULL && srv != NULL) {
                String autoJoinLine = "";
                bool inputOk = true;
                String password = "";
                if(tag < 0) {
                        if(srv->hasPassword()) {
                                inputOk = this->getServerPasswordDialog(password);
                        }
                        if(inputOk) {
                                if(tag == -1) {
                                        autoJoinLine = game->createDefaultStartLine(srv->getIP(), srv->getGamePort(), srv->getMod(), password);
                                } else if(tag == -2) {
                                        autoJoinLine = game->createDefaultStartLine(srv->getIP(), srv->getGamePort(), "", password);
                                }
                        }
                } else {
                        Configuration *conf = (Configuration*)tag;
                        if(srv->hasPassword() && conf->getPassword().IsEmpty()) {
                                inputOk = this->getServerPasswordDialog(password);
                        }
                        if(inputOk) {
                                autoJoinLine = conf->createStartLine(srv->getIP(), srv->getGamePort(), game->getProfileName(), srv->hasPassword(), password);
                        }
                }
                if(!autoJoinLine.IsEmpty()) {
                        srv->setAutoJoin(true, autoJoinLine);
                }
        }
        StringGrid1->Refresh();
        this->filterChanged(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClickWatchButton(TObject *Sender)
{
        Server *srv = this->ofpm->getServerByID(this->selectedServerIDForPopUp);
        if(srv != NULL) {
                TMenuItem *a = (TMenuItem *) Sender;
                a->Checked = !(a->Checked);
                srv->setWatched(a->Checked);
                if(srv->isWatched()) {
                        StatusChange *sc = new StatusChange(srv->getGamespyAddress(), 0, srv->getGameState());
                        this->ofpm->playAudioServerStatus(sc);
                        delete sc;
                }
        }
        StringGrid1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_SETTINGUPClick(TObject *Sender)
{
        this->serverFilter->settingup = CHECKBOX_FILTER_SETTINGUP->Checked;
        this->filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_ESCAPE) {
                this->Close();
        } else if(Key == VK_F13) {
                CoolTrayIcon1->ShowMainForm();
        } else if(Key == VK_F2) {
                if(this->ofpm != NULL) {
                        this->ofpm->setCustomNotifications(!this->ofpm->areCustomNotificationsOn());
                }
        } else if(Key == VK_F3) {
                toggleAlwaysOnTop();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        if(ACol > 0 && ARow > 0 && !(StringGrid1->Cells[0][ARow]).Trim().IsEmpty()) {
                Server *srv = this->ofpm->getServerByID((int)(StringGrid1->Objects[0][ARow]));
                if(srv != NULL) {
                        TColor mark = clNone;
                        if(this->ofpm != NULL) {
                                mark = this->ofpm->getMarkingColor(srv->getServerID());
                        }
                        if(     mark != clNone ||
                                srv->isWatched() ||
                                srv->isAutoJoin() ||
                                srv->isFavorite()) {
                                StringGrid1->Canvas->Font->Color = clWhite;
                                if(mark != clNone) {
                                        StringGrid1->Canvas->Brush->Color = mark;
                                } else if(srv->isWatched()) {
                                        StringGrid1->Canvas->Brush->Color = clBlue;
                                } else if(srv->isAutoJoin()) {
                                        StringGrid1->Canvas->Brush->Color = clRed;
                                } else if(srv->isFavorite()) {
                                        StringGrid1->Canvas->Font->Color = clBlack;
                                        StringGrid1->Canvas->Brush->Color = clYellow;
                                }
                                StringGrid1->Canvas->FillRect(Rect);
                                Rect.Left = Rect.Left + 2;
                                DrawText(StringGrid1->Canvas->Handle, StringGrid1->Cells[ACol][ARow].c_str(),
                                        -1, &Rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
                        }
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_SETTINGSClick(TObject *Sender)
{
        WINDOW_SETTINGS->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_EXITClick(TObject *Sender)
{
        this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_FONTClick(TObject *Sender)
{
        FontDialog1->Font = StringGrid1->Font;
        if(FontDialog1->Execute()) {
                this->fontSettings->setFont(FontDialog1->Font);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
        StringGrid2->Width = TABSHEET_SERVERINFO->PageControl->Pages[0]->Width - (GROUPBOX_SERVERINFO->Width + 5);
        StringGrid1->Width = this->ClientWidth;
        PageControl1->Height = this->ClientHeight - (StatusBar1->Height + StringGrid1->Height + Splitter1->Height);
        this->applyWindowSettingsRatios();
        StatusBar1->Realign();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FontDialog1Apply(TObject *Sender, HWND Wnd)
{
        this->fontSettings->setFont(FontDialog1->Font);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_POPUP_AUTOJOINBClick(TObject *Sender)
{
        if(this->ofpm != NULL) {
                this->ofpm->disableAutoJoin();
        }
        StringGrid1->Refresh();
        filterChanged(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
        int X = StringGrid1->ColWidths[0] + StringGrid1->ColWidths[1];
        int Y = (StringGrid1->DefaultRowHeight + 1) * (StringGrid1->Selection.Top - StringGrid1->TopRow + 1) + (StringGrid1->DefaultRowHeight/2);
        this->StringGrid1MouseDown(Sender, mbRight, TShiftState(), X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Splitter1Moved(TObject *Sender)
{
        Application->ProcessMessages();
        this->windowSettings->setDevider(this->PageControl1->Height);
        this->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Info1Click(TObject *Sender)
{
        WINDOW_INFO->ShowModal();
}
//---------------------------------------------------------------------------

DWORD WINAPI chatThread (LPVOID lpdwThreadParam__ ) {
        Chat *chat = (Chat*) lpdwThreadParam__;
        chat->connect("", true);
        while(chat->isConnectionLost()) {
                chat->reconnect();
        }
        if(chat->isConnectingFailed()) {
                chat->disconnect();
        }
        return 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_CONNECTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = false;
        MemoChatInput->Clear();
        MemoChatOutput->Clear();
        this->PageControl1->ActivePage = this->TABSHEET_CHAT;
        if(this->chat != NULL) {
                if(this->chat->isDisconnected()) {
                        if(this->chatThreadHandle != NULL) {
                                TerminateThread(this->chatThreadHandle, 0);
                        }
                        delete (this->chat);
                        this->chat = NULL;
                }
        }
        if(this->chat == NULL) {
                this->chat = new Chat(this->chatSettings, this->languageDB);
                this->chat->SetObserver(this);
                this->chatThreadHandle = CreateThread(0, 0, chatThread, this->chat, 0, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_DISCONNECTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_CHAT_DISCONNECT->Enabled = false;
        if(this->chat != NULL) {
                this->chat->disconnect();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MemoChatInputChange(TObject *Sender)
{
        while(MemoChatInput->Lines->Count > 3) {
                int start = MemoChatInput->SelStart;
                int length = MemoChatInput->SelLength;
                MemoChatInput->Lines->Delete(MemoChatInput->Lines->Count - 1);
                MemoChatInput->SelStart = start;
                MemoChatInput->SelLength = length;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(Shift.Contains(ssAlt) && Button == mbLeft) {
                int col = -1, row = -1;
                StringGrid3->MouseToCell(X, Y, col, row);
                if(col >= 0 && row >= 0) {
                        String userToBlock = StringGrid3->Cells[col][row];
                        if(!userToBlock.IsEmpty()) {
                                if(this->chat != NULL) {
                                        this->chat->toggleBlockedClient(userToBlock);
                                        StringGrid3->Repaint();
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid3DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        StringGrid3->Canvas->Font->Color = clBlack;
        StringGrid3->Canvas->Brush->Color = clWindow;
        String clientName = StringGrid3->Cells[ACol][ARow];
        if(!clientName.IsEmpty() && this->chat != NULL) {
                String ownName = this->chat->getUserNameInUse();
                if(this->chat->isClientBlocked(clientName) && ownName != clientName) {
                        StringGrid3->Canvas->Font->Color = clWhite;
                        StringGrid3->Canvas->Brush->Color = clBlack;
                }
        }
        StringGrid3->Canvas->FillRect(Rect);
        Rect.Left = Rect.Left + 2;
        DrawText(StringGrid3->Canvas->Handle, StringGrid3->Cells[ACol][ARow].c_str(),
                -1, &Rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OnMinimize(TObject *Sender)
{
        CoolTrayIcon1->HideMainForm();
}
void __fastcall TForm1::CoolTrayIcon1Click(TObject *Sender)
{
        CoolTrayIcon1->ShowMainForm();
        CoolTrayIcon1->HideBalloonHint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TABSHEET_CHATShow(TObject *Sender)
{
        TABSHEET_CHAT->Highlighted = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MemoChatInputKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_RETURN) {
                String input = "";
                for(int i = 0; i < this->MemoChatInput->Lines->Count; i++) {
                        input += this->MemoChatInput->Lines->Strings[i];
                }
                MemoChatInput->Clear();
                if(!input.Trim().IsEmpty()) {
                        String caption;
                        if(TabControl1->TabIndex == -1) {
                                caption = this->chatSettings->getChannel();
                        } else {
                                caption = TabControl1->Tabs->Strings[TabControl1->TabIndex];
                        }
                        if(this->chat->isConnected()) {
                                this->chat->userSendsMessage(caption, input);
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_LOCALGAMEClick(TObject *Sender)
{
        WINDOW_LOCALGAME->ShowModal();
}
//---------------------------------------------------------------------------
                          
void __fastcall TForm1::TabControl1DrawTab(TCustomTabControl *Control,
      int TabIndex, const TRect &Rect, bool Active)
{
        TRect r = Rect;
        r.Left += 4;
        String caption = TabControl1->Tabs->Strings[TabIndex];
        if(this->chat != NULL) {
                if(TabIndex != TabControl1->TabIndex) {
                        if(this->chat->hasConversationNewMessages(caption)) {
                                Control->Canvas->Font->Color = clWhite;
                                Control->Canvas->Brush->Color = clBlue;
                                Control->Canvas->FillRect(Rect);
                        }
                }
        }
        DrawText(Control->Canvas->Handle, caption.c_str(),
                -1, &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabControl1Change(TObject *Sender)
{
        if(TabControl1->Tabs->Count == 1) {
                TabControl1->TabIndex = 0;
        }
        int ind = TabControl1->TabIndex;
        if(ind > -1) {
                String caption = TabControl1->Tabs->Strings[ind];
                if(this->chat != NULL) {
                        this->chat->loadThisChat(caption, this->MemoChatOutput, this->MemoChatInput);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabControl1Changing(TObject *Sender,
      bool &AllowChange)
{
        if(TabControl1->Tabs->Count == 1) {
                TabControl1->TabIndex = 0;
        }
        int ind = TabControl1->TabIndex;
        if(ind > -1) {
                String caption = TabControl1->Tabs->Strings[ind];
                if(this->chat != NULL) {
                        this->chat->saveCurrentInput(caption, this->MemoChatInput);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid3ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
        Openchat1->Visible = false;
        Openchat1->Caption = this->languageDB->getGuiString("STRING_CHAT_CHATWITH");
        Openchat1->Hint = "";
        if(this->chat != NULL) {
                if(this->chat->isConnected()) {
                        String ownName = this->chat->getUserNameInUse();
                        int col = -1, row = -1;
                        StringGrid3->MouseToCell(MousePos.x, MousePos.y, col, row);
                        if(col >= 0 && row >= 0) {
                                String name = StringGrid3->Cells[0][row];
                                if(!name.IsEmpty() && name != ownName) {
                                        Openchat1->Hint = name;
                                        Openchat1->Visible = true;
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Openchat1Click(TObject *Sender)
{
        String name = Openchat1->Hint;
        if(!name.IsEmpty()) {
                if(this->chat != NULL) {
                        this->chat->openConversation(name);
                }
                for(int j = 0; j < TabControl1->Tabs->Count; j++) {
                        if(TabControl1->Tabs->Strings[j] == name) {
                                TabControl1->TabIndex = j;
                                TabControl1Change(this);
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabControl1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
        Close1->Visible = false;
        int index = TabControl1->IndexOfTabAt(MousePos.x, MousePos.y);
        if(index >= 0) {
                String name = TabControl1->Tabs->Strings[index];
                if(name.Pos("#") == 1) {
                        Close1->Hint = "";
                } else {
                        Close1->Caption = this->languageDB->getGuiString("STRING_CHAT_CLOSE");
                        Close1->Hint = name;
                        Close1->Visible = true;
                        TPoint p = TabControl1->ClientToScreen(MousePos);
                        PopupMenuChat2->Popup(p.x, p.y);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Close1Click(TObject *Sender)
{
        String name = Close1->Hint;
        if(!name.IsEmpty()) {
                if(this->chat != NULL) {
                        this->chat->closeConversation(name);
                        if(this->TabControl1->Tabs->Count > 0) {
                                this->TabControl1->TabIndex = 0;
                                this->TabControl1Change(this);
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCEClick(TObject *Sender)
{
        this->gameControl->setGreenUpRepeat(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEATClick(TObject *Sender)
{
        this->gameControl->setGreenUpRepeat(true);
}
//---------------------------------------------------------------------------
                   
void __fastcall TForm1::CHECKBOX_GAMECONTROL_AUTOGREENUPClick(TObject *Sender)
{
        this->gameControl->enableAutoGreenUp(CHECKBOX_GAMECONTROL_AUTOGREENUP->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTOREClick(TObject *Sender)
{
        this->gameControl->enableRestoreGame(CHECKBOX_GAMECONTROL_RESTORE->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
        if(ComboBox1->ItemIndex > -1) {
                ProcessInfo *p = (ProcessInfo*) ComboBox1->Items->Objects[ComboBox1->ItemIndex];
                if(p != NULL) {
                        Label9->Caption = p->moduleName;
                        this->gameControl->setProcess(p);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox2Change(TObject *Sender)
{
        if(ComboBox2->ItemIndex > -1) {
                Server *srv = this->ofpm->getServerByID((int) (ComboBox2->Items->Objects[ComboBox2->ItemIndex]));
                if(srv != NULL) {
                        this->gameControl->setServer(srv->getServerID());
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TABSHEET_GAMECONTROLShow(TObject *Sender)
{
        BUTTON_GAMECONTROL_REFRESH->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_CREATINGClick(TObject *Sender)
{
        this->gameControl->restoreOnCreating = CHECKBOX_GAMECONTROL_RESTORE_CREATING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_WAITINGClick(TObject *Sender)
{
        this->gameControl->restoreOnWaiting = CHECKBOX_GAMECONTROL_RESTORE_WAITING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_BRIEFINGClick(TObject *Sender)
{
        this->gameControl->restoreOnBriefing = CHECKBOX_GAMECONTROL_RESTORE_BRIEFING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_PLAYINGClick(TObject *Sender)
{
        this->gameControl->restoreOnPlaying = CHECKBOX_GAMECONTROL_RESTORE_PLAYING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFINGClick(TObject *Sender)
{
        this->gameControl->restoreOnDebriefing = CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown2ChangingEx(TObject *Sender,
      bool &AllowChange, short NewValue, TUpDownDirection Direction)
{
        this->gameControl->setGreenUpDelay(NewValue);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CHECKBOX_GAMECONTROL_AUTODETECTClick(
      TObject *Sender)
{
        this->gameControl->setAutoDetect(CHECKBOX_GAMECONTROL_AUTODETECT->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BUTTON_GAMECONTROL_REFRESHClick(TObject *Sender)
{
        for(int i = 0; i < ComboBox1->Items->Count; i++) {
                ProcessInfo *pi = (ProcessInfo*) ComboBox1->Items->Objects[i];
                delete pi;
        }
        ComboBox1->Clear();
        ProcessFinder *pf = new ProcessFinder();
        TStringList *s = new TStringList();
        s->Sorted = true;
        s->Duplicates = dupIgnore;
        TStringList *m = new TStringList();
        if(this->ofpm != NULL) {
                this->ofpm->getAllAppTitlesOfGames(s);
                this->ofpm->getAllExesOfGames(m);
        }
        if(pf->enumerate(s, m)) {
                for (list<ProcessInfo>::iterator proc = pf->output.begin(); proc != pf->output.end(); ++proc) {
                        ProcessInfo *p = new ProcessInfo((*proc).pid, (*proc).hWindow, (*proc).title, (*proc).moduleName);
                        ComboBox1->Items->AddObject(p->title + "  |  " + IntToStr(p->pid), (TObject*) p);
                        if(this->gameControl->matchesProcess(*p)) {
                                ComboBox1->ItemIndex = ComboBox1->Items->Count - 1;
                        }
                }
        }
        delete pf;
        delete s;
        delete m;
        ComboBox2->Clear();
        ServerFilter *sf = new ServerFilter();
        list<int> servers = this->ofpm->getAllMatchingServers(sf);
        delete sf;

        for (list<int>::iterator si = servers.begin(); si != servers.end(); ++si) {
                int serverID = *si;
                Server *srv = this->ofpm->getServerByID(serverID);
                if(srv != NULL) {
                        if(srv->isOnline()) {
                                ComboBox2->Items->AddObject(srv->getName(), (TObject*) (srv->getServerID()));
                                if(this->gameControl->matchesServer(srv->getServerID())) {
                                        ComboBox2->ItemIndex = ComboBox2->Items->Count - 1;
                                }
                        }
                }
        }
        this->updateGameControlGui();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
        if(this->ofpm != NULL) {
                this->updateMainMenuSettings();
                if(!this->ofpm->getTotalServerCount()) {
                        this->ofpm->queryGameSpyList();
                }
                this->ofpm->queryServers();
                if(this->ofpm->isUpdateOnStartSet()) {
                        WINDOW_UPDATE->checkForNewVersion(false);
                }
                if(this->ofpm->isUpdateOfMasterServersOnStartSet()) {
                        this->downloader = new HttpsDownloader("https://raw.githubusercontent.com/wiki/poweruser/ofpmonitor/masterservers.txt");
                        this->downloader->SetObserver(this);
                        this->downloader->start();
                }
        }
        this->updateFilterOfGui();
        if(this->chatSettings->isAutoConnectOn()) {
                this->MENUITEM_MAINMENU_CHAT_CONNECT->Click();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        for(int i = 0; i < this->StringGrid1->ColCount; i++) {
                this->windowSettings->setRatioServerTable(i, (float)this->StringGrid1->ColWidths[i] / (float)this->StringGrid1->Width);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        for(int i = 0; i < this->StringGrid2->ColCount; i++) {
                this->windowSettings->setRatioPlayerTable(i, (float)this->StringGrid2->ColWidths[i] / (float)this->StringGrid2->Width);
        }     
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormConstrainedResize(TObject *Sender,
      int &MinWidth, int &MinHeight, int &MaxWidth, int &MaxHeight)
{
        this->updateWindowSettingsPosition();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown1ChangingEx(TObject *Sender,
      bool &AllowChange, short NewValue, TUpDownDirection Direction)
{
        bool withinRange = (NewValue >= UpDown1->Min) && (NewValue <= UpDown1->Max);
        AllowChange = withinRange;
        if(withinRange) {
                this->serverFilter->minPlayers = StrToInt(NewValue);
                this->filterChanged(true);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StatusBar1DrawPanel(TStatusBar *StatusBar,
      TStatusPanel *Panel, const TRect &Rect)
{
        StatusBar1->Canvas->Brush->Color = StatusBar1->Color;
        StatusBar1->Canvas->FillRect(Rect);
        if(Panel->ID == 2) {
                if(this->ofpm != NULL) {
                        int volume = this->ofpm->getVolume();
                        if(volume) {
                                volume = (volume / 34) + 1;
                        }
                        ImageListVolume->Draw(StatusBar1->Canvas, Rect.Left + 2, Rect.Top + 2, volume, true);
                }
        } else if(Panel->ID == 3) {
                if(this->ofpm != NULL) {
                        int image = this->ofpm->areCustomNotificationsOn();
                        ImageListNotification->Draw(StatusBar1->Canvas, Rect.Left + 2, Rect.Top + 2, image, true);
                }
        } else if(Panel->ID == 4) {
                if(this->ofpm != NULL) {
                        int level = (int) (this->ofpm->getBandwidthUsage());
                        ImageListBandwidth->Draw(StatusBar1->Canvas, Rect.Left + 2, Rect.Top + 2, level, true);
                }
        } else if(Panel->ID == 5) {
                if(this->windowSettings != NULL) {
                        int pinned = this->windowSettings->isAlwaysOnTopSet();
                        ImageListPinned->Draw(StatusBar1->Canvas, Rect.Left + 2, Rect.Top + 2, pinned, true);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StatusBar1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(Button == mbLeft) {
                int border = StatusBar1->BorderWidth;
                int left = border;
                if(Y > border && Y < border + StatusBar1->Height) {
                        for(int i = 0; i < StatusBar1->Panels->Count; i++) {
                                if(X < left) { break; }
                                if(X > left &&
                                   X < left + StatusBar1->Panels->Items[i]->Width) {
                                        if(i == 3) {
                                                if(this->ofpm != NULL) {
                                                        this->ofpm->setCustomNotifications(!this->ofpm->areCustomNotificationsOn());
                                                }
                                        } else if(i == 5) {
                                                this->toggleAlwaysOnTop();
                                        }
                                }
                                left += (StatusBar1->Panels->Items[i]->Width + border);
                        }
                }
                StatusBar1->Repaint();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
        delete this->serverTableSorter;
        delete this->playerTableSorter;
}
//---------------------------------------------------------------------------






void __fastcall TForm1::PageControl1DrawTab(TCustomTabControl *Control,
      int TabIndex, const TRect &Rect, bool Active)
{
        int imageId = PageControl1->Pages[TabIndex]->ImageIndex;
        String caption = PageControl1->Pages[TabIndex]->Caption;
        TRect r = Rect;
        r.Left += 26;
        r.Top += 3;

        bool newMsg = false;
        if(this->chat != NULL) {
                if(this->chat->hasNewMessages()) {
                        newMsg = true;
                        this->TABSHEET_CHAT->ImageIndex = 4;
                }
        }
        if(!newMsg) {
                this->TABSHEET_CHAT->ImageIndex = 2;
        }
        if(TabIndex == TABSHEET_CHAT->PageIndex && !Active) {
                if(newMsg) {
                        Control->Canvas->Font->Color = clWhite;
                        Control->Canvas->Brush->Color = clBlue;
                        Control->Canvas->FillRect(Rect);
                }
        }
        ImageListTabIcons->Draw(PageControl1->Canvas, Rect.Left + 4, Rect.Top + 3, imageId, true);
        DrawText(Control->Canvas->Handle, caption.c_str(),
                -1, &r, DT_LEFT | DT_SINGLELINE );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_GETNEWSERVERLISTClick(TObject *Sender)
{
        if(this->ofpm->isGameSpyUpdateDone()) {
                MENUITEM_MAINMENU_GETNEWSERVERLIST->Enabled = false;
                this->ofpm->queryGameSpyList();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_SERVERLIST_GAMESPYClick(TObject *Sender)
{
        this->ofpm->setQueryOfGamespy(MENUITEM_MAINMENU_SERVERLIST_GAMESPY->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_SERVERLIST_POWERSERVERClick(
      TObject *Sender)
{
        this->ofpm->setQueryOfPowerserver(MENUITEM_MAINMENU_SERVERLIST_POWERSERVER->Checked);
}
//---------------------------------------------------------------------------

