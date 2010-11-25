//---------------------------------------------------------------------------

#include <vcl.h>
#include <list.h>
#include <mmsystem.h>
#include <windows.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define SERVERSTATE_CREATING 2
#define SERVERSTATE_WAITING 6
#define SERVERSTATE_DEBRIEFING 9
#define SERVERSTATE_SETTINGUP 12
#define SERVERSTATE_BRIEFING 13
#define SERVERSTATE_PLAYING 14



TWINDOW_NOTIFICATIONS *WINDOW_NOTIFICATIONS;


/**
   Macro to retrieve the length of an array
 */

String alias = "OFPM_MP3PREVIEW";

template<typename T, int size>
int GetArrLength(T(&)[size]){return size;}

typedef list<String> CustomStringList;

int checkBool(bool in) {
        int out = 0;
        if(in) {
                out = 1;
        }
        return out;
}

class CustomNotification {
        public:
                String name;
                bool statusCreating;
                bool statusWaiting;
                bool statusSettingUp;
                bool statusBriefing;
                bool statusPlaying;
                bool statusDebriefing;

                bool withPassword;
                bool withoutPassword;

                int minPlayers;
                int maxPlayers;
                list<String> serverFilter;
                list<String> missionFilter;
                list<String> playerFilter;

                String soundFile;
                int playbackVolume;
                int playbackStart;
                int playbackEnd;
                TColor markingColor;
                bool set;

                CustomNotification () {
                        this->set = false;
                        this->statusCreating = false;
                }

                CustomNotification (String name, int filters, list<String> &mission,
                                    list<String> &server, list<String> &player, int minPlayers,
                                    int maxPlayers, String soundFile, int volume, int start, int end,
                                    String color) {
                        this->name = name;
                        this->withoutPassword = ((filters & 1) == 1);
                        filters = filters >> 1;
                        this->withPassword = ((filters & 1) == 1);
                        filters = filters >> 1;
                        this->statusDebriefing = ((filters & 1) == 1);
                        filters = filters >> 1;
                        this->statusPlaying = ((filters & 1) == 1);
                        filters = filters >> 1;
                        this->statusBriefing = ((filters & 1) == 1);
                        filters = filters >> 1;
                        this->statusSettingUp = ((filters & 1) == 1);
                        filters = filters >> 1;
                        this->statusWaiting = ((filters & 1) == 1);
                        filters = filters >> 1;
                        this->statusCreating = ((filters & 1) == 1);
                        this->missionFilter = mission;
                        this->serverFilter = server;
                        this->playerFilter = player;
                        this->soundFile = soundFile;
                        this->minPlayers = minPlayers;
                        this->maxPlayers = maxPlayers;
                        this->playbackVolume = volume;
                        this->playbackStart = start;
                        this->playbackEnd = end;
                        this->markingColor = StringToColor(color);
                        this->set = true;
                }

                CustomNotification (String name, bool statusC, bool statusW,
                        bool statusS, bool statusB, bool statusP, bool statusD,
                        bool statusWithPW, bool statusWithoutPW,
                        list<String> &mission, list<String> &server,
                        list<String> &player, int minPlayers, int maxPlayers,
                        String soundFile, int volume, int start, int end, String color) {
                        this->name = name;
                        this->withoutPassword = statusWithoutPW;
                        this->withPassword = statusWithPW;
                        this->statusDebriefing = statusD;
                        this->statusPlaying = statusP;
                        this->statusBriefing = statusB;
                        this->statusSettingUp = statusS;
                        this->statusWaiting = statusW;
                        this->statusCreating = statusC;
                        this->missionFilter = mission;
                        this->serverFilter = server;
                        this->playerFilter = player;
                        this->soundFile = soundFile;
                        this->minPlayers = minPlayers;
                        this->maxPlayers = maxPlayers;
                        this->playbackVolume = volume;
                        this->playbackStart = start;
                        this->playbackEnd = end;
                        this->markingColor = StringToColor(color);
                        this->set = true;
                }

                TStringList* createFileEntry() {
                        TStringList *output = new TStringList;
                        int filters = 0;
                        if(this->statusCreating) { filters = filters + 1; }
                        filters = filters << 1;
                        if(this->statusWaiting) { filters = filters + 1; }
                        filters = filters << 1;
                        if(this->statusSettingUp) { filters = filters + 1; }
                        filters = filters << 1;
                        if(this->statusBriefing) { filters = filters + 1; }
                        filters = filters << 1;
                        if(this->statusPlaying) { filters = filters + 1; }
                        filters = filters << 1;
                        if(this->statusDebriefing) { filters = filters + 1; }
                        filters = filters << 1;
                        if(this->withPassword) { filters = filters + 1; }
                        filters = filters << 1;
                        if(this->withoutPassword) { filters = filters + 1; }
                        output->Add("[CustomNotification]");
                        output->Add("name = " + this->name);
                        output->Add("statusFilter = " + String(filters));

                        String mission = "";
                        if(this->missionFilter.size() > 0) {
                                do {
                                        mission += this->missionFilter.front();
                                        this->missionFilter.pop_front();
                                        if(this->missionFilter.size() > 0) {
                                                mission += ";";
                                        }
                                } while (this->missionFilter.size() > 0);
                        }
                        String server = "";
                        if(this->serverFilter.size() > 0) {
                                do {
                                        server += this->serverFilter.front();
                                        this->serverFilter.pop_front();
                                        if(this->serverFilter.size() > 0) {
                                                server += ";";
                                        }
                                } while (this->serverFilter.size() > 0);
                        }
                        String player = "";
                        if(this->playerFilter.size() > 0) {
                                do {
                                        player += this->playerFilter.front();
                                        this->playerFilter.pop_front();
                                        if(this->playerFilter.size() > 0) {
                                                player += ";";
                                        }
                                } while (this->playerFilter.size() > 0);
                        }
                        output->Add("missionFilter = " + mission);
                        output->Add("serverFilter = " + server);
                        output->Add("playerFilter = " + player);
                        if(this->minPlayers >= 0) {
                                output->Add("minimumPlayers = " + String(this->minPlayers));
                        }
                        if(this->maxPlayers >= 0) {
                                output->Add("maximumPlayers = " + String(this->maxPlayers));
                        }
                        output->Add("markingColor = " + ColorToString(this->markingColor));
                        output->Add("soundFile = " + this->soundFile);
                        output->Add("playbackVolume = " + String(this->playbackVolume));
                        output->Add("playbackStart = " + String(this->playbackStart));
                        output->Add("playbackEnd = " + String(this->playbackEnd));
                        output->Add("[\\CustomNotification]");

                        return output;
                }
};

CustomNotification CustomNotify[32];



class SongPosition {
     public:
        int milli;
        int sec;
        int min;
        SongPosition() {}
        void setMilli(int milli) {
                this->milli = milli;
        }
        void setSec(int sec) {
                this->sec = sec;
        }
        void setMin(int min) {
                this->min = min;
        }
};


SongPosition calcSongPosition(int position) {
        SongPosition out;
        out.setMilli(position % 1000);
        out.setSec(((position - out.milli)/1000) % 60);
        out.setMin((((position - out.milli)/1000) - out.sec) / 60);
        return out;
}

void printPlaybackRange(int start, int end) {
        SongPosition s = calcSongPosition(start);
        SongPosition e = calcSongPosition(end);
        WINDOW_NOTIFICATIONS->Edit5->Text = IntToStr(s.min);
        WINDOW_NOTIFICATIONS->Edit6->Text = IntToStr(s.sec);
        WINDOW_NOTIFICATIONS->Edit7->Text = IntToStr(s.milli);
        WINDOW_NOTIFICATIONS->Edit8->Text = IntToStr(e.min);
        WINDOW_NOTIFICATIONS->Edit9->Text = IntToStr(e.sec);
        WINDOW_NOTIFICATIONS->Edit10->Text = IntToStr(e.milli);
}


TStringList* TWINDOW_NOTIFICATIONS::getFileEntry() {
        TStringList *entry = new TStringList;

        for(int i = 0; i < GetArrLength(CustomNotify); i++) {
                if(CustomNotify[i].set) {
                        TStringList *part = CustomNotify[i].createFileEntry();
                        while(part->Count > 0) {
                                entry->Add(part->Strings[0]);
                                part->Delete(0);
                        }
                        delete part;
                }
        }
        
        return entry;
}

void TWINDOW_NOTIFICATIONS::addCustomNotification(String name, int filters, list<String> &mission,
                                    list<String> &server, list<String> &player, int minPlayers,
                                    int maxPlayers, String soundFile, int volume, int start, int end,
                                    String color) {
        for(int i = 0; i < GetArrLength(CustomNotify); i++) {
                if(!CustomNotify[i].set) {
                        CustomNotify[i] = CustomNotification(name, filters,
                                    mission, server, player,
                                    minPlayers, maxPlayers,
                                    soundFile, volume, start, end, color);
                        break;
                }
        }
}

void TWINDOW_NOTIFICATIONS::checkNotifications(int index, String servername, int players, int status,
                                String missionname, bool passworded,
                                list<String> playerlist) {

        for(int i = 0; i < GetArrLength(CustomNotify); i++) {
                if(     passworded && CustomNotify[i].withPassword ||
                        !passworded && CustomNotify[i].withoutPassword) {
                        if(     (CustomNotify[i].minPlayers <= players ||
                                 CustomNotify[i].minPlayers < 0) &&
                                (CustomNotify[i].maxPlayers >= players ||
                                 CustomNotify[i].maxPlayers < 0)) {
                                if(     CustomNotify[i].statusCreating && status == SERVERSTATE_CREATING ||
                                        CustomNotify[i].statusWaiting && status == SERVERSTATE_WAITING ||
                                        CustomNotify[i].statusBriefing && status == SERVERSTATE_BRIEFING ||
                                        CustomNotify[i].statusSettingUp && status == SERVERSTATE_SETTINGUP ||
                                        CustomNotify[i].statusPlaying && status == SERVERSTATE_PLAYING ||
                                        CustomNotify[i].statusDebriefing && status == SERVERSTATE_DEBRIEFING) {
                                        bool servertest = false;
                                        bool missiontest = false;
                                        bool playertest = false;
                                        if(CustomNotify[i].serverFilter.size() > 0) {
                                                for (list<String>::iterator ci = CustomNotify[i].serverFilter.begin(); ci != CustomNotify[i].serverFilter.end(); ++ci) {
                                                        if(Form1->doNameFilter(servername,*ci)) {
                                                                servertest = true;
                                                                break;
                                                        }
                                                }
                                        } else { servertest = true; }
                                        if(CustomNotify[i].missionFilter.size() > 0) {

                                                for (list<String>::iterator ci = CustomNotify[i].missionFilter.begin(); ci != CustomNotify[i].missionFilter.end(); ++ci) {
                                                        if(Form1->doNameFilter(missionname,*ci)) {
                                                                missiontest = true;
                                                                break;
                                                        }
                                                }
                                        } else { missiontest = true; }
                                        if(CustomNotify[i].playerFilter.size() > 0) {
                                                for (list<String>::iterator ci = playerlist.begin(); ci != playerlist.end(); ++ci) {
                                                        for (list<String>::iterator di = CustomNotify[i].playerFilter.begin(); di != CustomNotify[i].playerFilter.end(); ++di) {
                                                                if(Form1->doNameFilter(*ci,*di)) {
                                                                        playertest = true;
                                                                        break;
                                                                }
                                                        }
                                                }
                                        } else { playertest = true; }
                                        if(servertest && missiontest && playertest) {
                                                Form1->createMP3Job(i, index, CustomNotify[i].soundFile,"MP3_" + String(index) + "_" + String(i), CustomNotify[i].playbackVolume*10, CustomNotify[i].playbackStart, CustomNotify[i].playbackEnd, CustomNotify[i].markingColor);
                                        } else { Form1->stopMP3Job("MP3_" + String(index) + "_" + String(i)); }
                                } else { Form1->stopMP3Job("MP3_" + String(index) + "_" + String(i)); }
                        } else { Form1->stopMP3Job("MP3_" + String(index) + "_" + String(i)); }
                } else { Form1->stopMP3Job("MP3_" + String(index) + "_" + String(i)); }
        }
        return;
}


void updateNotificationsList() {
        WINDOW_NOTIFICATIONS->ListBox1->Clear();
        for(int i = 0; i < GetArrLength(CustomNotify); i++) {
                if(CustomNotify[i].set) {
                        WINDOW_NOTIFICATIONS->ListBox1->Items->AddObject(CustomNotify[i].name, (TObject *) i);
                }
        }
        return;
}
 

void checkNotificationListState() {
        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_EDIT->Enabled = false;
        WINDOW_NOTIFICATIONS->BUTTON_NOTIFICATION_REMOVE->Enabled = false;
        for(int i = 0; i < WINDOW_NOTIFICATIONS->ListBox1->Count; i++) {
                if(WINDOW_NOTIFICATIONS->ListBox1->Selected[i]) {
                        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_EDIT->Enabled = true;
                        WINDOW_NOTIFICATIONS->BUTTON_NOTIFICATION_REMOVE->Enabled = true;
                        break;
                }
        }
        return;
}

void exitEditNotificationMode() {
        WINDOW_NOTIFICATIONS->ListBox1->Enabled = true;
        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_OK->Enabled = false;
        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_CANCEL->Enabled = false;
        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_OK->Visible = false;
        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_CANCEL->Visible = false;
        WINDOW_NOTIFICATIONS->BUTTON_NEWNOTIFICATION_ADD->Visible = true;
        WINDOW_NOTIFICATIONS->BUTTON_NEWNOTIFICATION_ADD->Enabled = true;
        WINDOW_NOTIFICATIONS->BUTTON_NEWNOTIFICATION_CLEAR->Visible = true;
        WINDOW_NOTIFICATIONS->BUTTON_NEWNOTIFICATION_CLEAR->Enabled = true;
        WINDOW_NOTIFICATIONS->BUTTON_NEWNOTIFICATION_CLEAR->Click();
        checkNotificationListState();
        return;
}

void updateLanguage() {
        WINDOW_NOTIFICATIONS->LABEL_FILTER_MISSIONNAME_BOX->Caption = Form1->LABEL_FILTER_MISSIONNAME->Caption;
        WINDOW_NOTIFICATIONS->LABEL_FILTER_SERVERNAME_BOX->Caption = Form1->LABEL_FILTER_SERVERNAME->Caption;
        WINDOW_NOTIFICATIONS->LABEL_FILTER_PLAYERNAME_BOX->Caption = Form1->LABEL_FILTER_PLAYERNAME->Caption;
        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_CANCEL->Caption = WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_CANCEL->Caption;
        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_EDIT->Caption = WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_EDIT->Caption;
        WINDOW_NOTIFICATIONS->BUTTON_EDITNOTIFICATION_OK->Caption = WINDOW_SETTINGS->BUTTON_EDITCONFIGURATION_OK->Caption;
        WINDOW_NOTIFICATIONS->BUTTON_NEWNOTIFICATION_ADD->Caption = WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_ADD->Caption;
        WINDOW_NOTIFICATIONS->BUTTON_NEWNOTIFICATION_CLEAR->Caption = WINDOW_SETTINGS->BUTTON_NEWCONFIGURATION_CLEAR->Caption;
        WINDOW_NOTIFICATIONS->BUTTON_NOTIFICATION_REMOVE->Caption = WINDOW_SETTINGS->BUTTON_CONFIGURATION_REMOVE->Caption;
        WINDOW_NOTIFICATIONS->CHECKBOX_FILTER_CREATING->Caption = Form1->CHECKBOX_FILTER_CREATING->Caption;
        WINDOW_NOTIFICATIONS->CHECKBOX_FILTER_WAITING->Caption = Form1->CHECKBOX_FILTER_WAITING->Caption;
        WINDOW_NOTIFICATIONS->CHECKBOX_FILTER_BRIEFING->Caption = Form1->CHECKBOX_FILTER_BRIEFING->Caption;
        WINDOW_NOTIFICATIONS->CHECKBOX_FILTER_SETTINGUP->Caption = Form1->CHECKBOX_FILTER_SETTINGUP->Caption;
        WINDOW_NOTIFICATIONS->CHECKBOX_FILTER_PLAYING->Caption = Form1->CHECKBOX_FILTER_PLAYING->Caption;
        WINDOW_NOTIFICATIONS->CHECKBOX_FILTER_DEBRIEFING->Caption = Form1->CHECKBOX_FILTER_DEBRIEFING->Caption;
        WINDOW_NOTIFICATIONS->BUTTON_BROWSE->Caption = WINDOW_SETTINGS->BUTTON_OFPEXECUTABLE_BROWSE->Caption;
        WINDOW_NOTIFICATIONS->LABEL_FILTER_PASSWORD->Caption = Form1->LABEL_FILTER_PASSWORD->Caption;
        WINDOW_NOTIFICATIONS->LABEL_FILTER_STATUS->Caption = Form1->LABEL_FILTER_STATUS->Caption;
        WINDOW_NOTIFICATIONS->LABEL_NOTIFICATION_NAME->Caption = WINDOW_SETTINGS->getGuiString("STRING_NAME");
        WINDOW_NOTIFICATIONS->LABEL_FILTER_PLAYERS->Caption = WINDOW_SETTINGS->getGuiString("STRING_PLAYERS");
        WINDOW_NOTIFICATIONS->CHECKBOX_FILTER_WITHOUTPASSWORD->Caption = Form1->CHECKBOX_FILTER_WITHOUTPASSWORD->Caption;
        WINDOW_NOTIFICATIONS->CHECKBOX_FILTER_WITHPASSWORD->Caption = Form1->CHECKBOX_FILTER_WITHPASSWORD->Caption;
        WINDOW_NOTIFICATIONS->LABEL_VOLUME->Caption = WINDOW_SETTINGS->getGuiString("STRING_PLAYBACKVOLUME");
        WINDOW_NOTIFICATIONS->LABEL_MARKINGCOLOR->Caption = WINDOW_SETTINGS->getGuiString("STRING_MARKINGCOLOR");
        WINDOW_NOTIFICATIONS->LABEL_AUDIOFILE->Caption = WINDOW_SETTINGS->getGuiString("STRING_AUDIOFILE");
        WINDOW_NOTIFICATIONS->LABEL_AUDIO_FROM->Caption = WINDOW_SETTINGS->getGuiString("STRING_FROM");
        WINDOW_NOTIFICATIONS->LABEL_AUDIO_TO->Caption = WINDOW_SETTINGS->getGuiString("STRING_TO");
        return;
}
      
void TWINDOW_NOTIFICATIONS::updateFontSettings(int charset) {
        WINDOW_NOTIFICATIONS->Font->Charset = charset;
        return;
}
        
//---------------------------------------------------------------------------
__fastcall TWINDOW_NOTIFICATIONS::TWINDOW_NOTIFICATIONS(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::BUTTON_BROWSEClick(TObject *Sender)
{
        OpenDialog1->Execute();
        STOP->Click();        
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_NOTIFICATIONS::OpenDialog1CanClose(TObject *Sender,
      bool &CanClose)
{
        Edit1->Tag = -1;
        Edit1->Text = "";
        Edit1->Text = OpenDialog1->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_NOTIFICATIONS::Edit1Change(TObject *Sender)
{
        LabelMilli->Visible = false;
        LabelSeconds->Visible = false;
        LabelMinutes->Visible = false;
        if(!FileExists(Edit1->Text) && !Edit1->Text.IsEmpty()) {
                Edit1->Color = clRed;
        } else {
                Edit1->Color = clWindow;
                if(FileExists(Edit1->Text)) {
                        if(Edit1->Tag > -1) {
                                printPlaybackRange(CustomNotify[Edit1->Tag].playbackStart, CustomNotify[Edit1->Tag].playbackEnd);
                        } else {
                                mciSendString(("open \"" + Edit1->Text + "\" alias LengthCheck").c_str(),0,0,0);
                                mciSendString("set LengthCheck time format milliseconds",0,0,0);
                                char text[128];
                                mciSendString("status LengthCheck length", text, 128, 0);
                                printPlaybackRange(0, StrToInt(text));
                                mciSendString("close LengthCheck", 0, 0, 0);
                        }
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_NOTIFICATIONS::CHECKBOX_FILTER_MINPLAYERSClick(TObject *Sender)
{
        Edit2->Enabled = CHECKBOX_FILTER_MINPLAYERS->Checked;
        UpDown1->Enabled = CHECKBOX_FILTER_MINPLAYERS->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_NOTIFICATIONS::CHECKBOX_FILTER_MAXPLAYERSClick(TObject *Sender)
{
        Edit3->Enabled = CHECKBOX_FILTER_MAXPLAYERS->Checked;
        UpDown2->Enabled = CHECKBOX_FILTER_MAXPLAYERS->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::BUTTON_NEWNOTIFICATION_CLEARClick(TObject *Sender)
{
        Memo1->Clear();
        Memo2->Clear();
        Memo3->Clear();
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
        UpDown1->Position = 0;
        UpDown2->Position = 0;
        Edit1->Text = "";
        Edit4->Text = "";
        Edit5->Text = "0";
        Edit6->Text = "0";
        Edit7->Text = "0";
        Edit8->Text = "0";
        Edit9->Text = "0";
        Edit10->Text = "0";
        TrackBar1->Position = 100;
        ColorBox1->Selected = clMaroon;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::BUTTON_EDITNOTIFICATION_EDITClick(TObject *Sender)
{
        ListBox1->Enabled = false;
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

        for(int i = 0; i < ListBox1->Count; i++) {
                if(ListBox1->Selected[i]) {
                        TObject *t = ListBox1->Items->Objects[i];
                        int j = (int) t;
                        CustomNotification cN = CustomNotify[j];
                        Edit4->Text = cN.name;
                        CHECKBOX_FILTER_BRIEFING->Checked = cN.statusBriefing;
                        CHECKBOX_FILTER_CREATING->Checked = cN.statusCreating;
                        CHECKBOX_FILTER_DEBRIEFING->Checked = cN.statusDebriefing;
                        CHECKBOX_FILTER_MAXPLAYERS->Checked = (cN.maxPlayers > 0);
                        CHECKBOX_FILTER_MINPLAYERS->Checked = (cN.minPlayers > 0);
                        CHECKBOX_FILTER_PLAYING->Checked = cN.statusPlaying;
                        CHECKBOX_FILTER_SETTINGUP->Checked = cN.statusSettingUp;
                        CHECKBOX_FILTER_WAITING->Checked = cN.statusWaiting;
                        CHECKBOX_FILTER_WITHOUTPASSWORD->Checked = cN.withoutPassword;
                        CHECKBOX_FILTER_WITHPASSWORD->Checked = cN.withPassword;

                        UpDown1->Position = max(cN.minPlayers, 0);
                        CHECKBOX_FILTER_MINPLAYERS->Checked = (cN.minPlayers >= 0);
                        UpDown2->Position = max(cN.maxPlayers, 0);
                        CHECKBOX_FILTER_MAXPLAYERS->Checked = (cN.maxPlayers >= 0);
                        Memo1->Clear();
                        for (list<String>::iterator ci = cN.missionFilter.begin(); ci != cN.missionFilter.end(); ++ci) {
                                Memo1->Lines->Add(*ci);
                        }
                        Memo2->Clear();
                        for (list<String>::iterator ci = cN.serverFilter.begin(); ci != cN.serverFilter.end(); ++ci) {
                                Memo2->Lines->Add(*ci);
                        }
                        Memo3->Clear();
                        for (list<String>::iterator ci = cN.playerFilter.begin(); ci != cN.playerFilter.end(); ++ci) {
                                Memo3->Lines->Add(*ci);
                        }
                        Edit1->Tag = j;
                        Edit1->Text = cN.soundFile;
                        ColorBox1->Selected = cN.markingColor;
                        TrackBar1->Position = cN.playbackVolume;
                        break;
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_NOTIFICATIONS::BUTTON_EDITNOTIFICATION_OKClick(TObject *Sender)
{
    if(!Edit4->Text.Trim().IsEmpty() && (FileExists(Edit1->Text) || Edit1->Text.Trim().IsEmpty())) {
        if(STOP->Visible) {
                STOP->Click();
        }
        list<String> mission;
        for(int i = 0; i < Memo1->Lines->Count; i++) {
                if(!Memo1->Lines->Strings[i].Trim().IsEmpty()) {
                        mission.push_back(Memo1->Lines->Strings[i]);
                }
        }
        list<String> server;
        for(int i = 0; i < Memo2->Lines->Count; i++) {
                if(!Memo2->Lines->Strings[i].Trim().IsEmpty()) {
                        server.push_back(Memo2->Lines->Strings[i]);
                }
        }
        list<String> player;
        for(int i = 0; i < Memo3->Lines->Count; i++) {
                if(!Memo3->Lines->Strings[i].Trim().IsEmpty()) {
                        player.push_back(Memo3->Lines->Strings[i]);
                }
        }
        for(int i = 0; i < ListBox1->Count; i++) {
                if(ListBox1->Selected[i]) {
                        TObject *t = ListBox1->Items->Objects[i];
                        int j = (int) t;
                        CustomNotify[j].name = Edit4->Text;
                        CustomNotify[j].missionFilter = mission;
                        CustomNotify[j].serverFilter = server;
                        CustomNotify[j].playerFilter = player;
                        CustomNotify[j].statusCreating = CHECKBOX_FILTER_CREATING->Checked;
                        CustomNotify[j].statusWaiting = CHECKBOX_FILTER_WAITING->Checked;
                        CustomNotify[j].statusSettingUp = CHECKBOX_FILTER_SETTINGUP->Checked;
                        CustomNotify[j].statusBriefing = CHECKBOX_FILTER_BRIEFING->Checked;
                        CustomNotify[j].statusPlaying = CHECKBOX_FILTER_PLAYING->Checked;
                        CustomNotify[j].statusDebriefing = CHECKBOX_FILTER_DEBRIEFING->Checked;
                        CustomNotify[j].withPassword = CHECKBOX_FILTER_WITHPASSWORD->Checked;
                        CustomNotify[j].withoutPassword = CHECKBOX_FILTER_WITHOUTPASSWORD->Checked;
                        if(CHECKBOX_FILTER_MINPLAYERS->Checked) {
                                CustomNotify[j].minPlayers = UpDown1->Position;
                        } else {
                                CustomNotify[j].minPlayers = -1;
                        }
                        if(CHECKBOX_FILTER_MAXPLAYERS->Checked) {
                                CustomNotify[j].maxPlayers = UpDown2->Position;
                        } else {
                                CustomNotify[j].maxPlayers = -1;
                        }
                        CustomNotify[j].soundFile = Edit1->Text;
                        CustomNotify[j].playbackVolume = TrackBar1->Position;
                        CustomNotify[i].playbackStart =
                                                StrToInt(Edit5->Text)*60000 +
                                                StrToInt(Edit6->Text)*1000 +
                                                StrToInt(Edit7->Text);
                        CustomNotify[j].playbackEnd =
                                                StrToInt(Edit8->Text)*60000 +
                                                StrToInt(Edit9->Text)*1000 +
                                                StrToInt(Edit10->Text);
                        CustomNotify[j].markingColor = ColorBox1->Selected;
                        break;
                }
        }
        updateNotificationsList();
        WINDOW_SETTINGS->setSettingsChanged();
        exitEditNotificationMode();
    }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::BUTTON_NEWNOTIFICATION_ADDClick(TObject *Sender)
{
        if(!Edit4->Text.Trim().IsEmpty() && (FileExists(Edit1->Text) || Edit1->Text.Trim().IsEmpty())) {
                if(STOP->Visible) {
                        STOP->Click();
                }
                list<String> mission, server, player;
                for(int i = 0; i < Memo1->Lines->Count; i++) {
                        mission.push_back(Memo1->Lines->Strings[i]);
                }
                for(int i = 0; i < Memo2->Lines->Count; i++) {
                        server.push_back(Memo2->Lines->Strings[i]);
                }
                for(int i = 0; i < Memo3->Lines->Count; i++) {
                        player.push_back(Memo3->Lines->Strings[i]);
                }
                int minP = -1, maxP = -1;
                if(CHECKBOX_FILTER_MINPLAYERS->Checked) {
                        minP = UpDown1->Position;
                }
                if(CHECKBOX_FILTER_MAXPLAYERS->Checked) {
                        maxP = UpDown2->Position;
                }
                CustomNotification newCN = CustomNotification(Edit4->Text,
                        CHECKBOX_FILTER_CREATING->Checked, CHECKBOX_FILTER_WAITING->Checked,
                        CHECKBOX_FILTER_SETTINGUP->Checked, CHECKBOX_FILTER_BRIEFING->Checked,
                        CHECKBOX_FILTER_PLAYING->Checked, CHECKBOX_FILTER_DEBRIEFING->Checked,
                        CHECKBOX_FILTER_WITHPASSWORD->Checked, CHECKBOX_FILTER_WITHOUTPASSWORD->Checked,
                        mission, server, player, minP, maxP,
                        Edit1->Text, TrackBar1->Position,
                                StrToInt(Edit5->Text)*60000 +
                                StrToInt(WINDOW_NOTIFICATIONS->Edit6->Text)*1000 +
                                StrToInt(WINDOW_NOTIFICATIONS->Edit7->Text),
                                StrToInt(WINDOW_NOTIFICATIONS->Edit8->Text)*60000 +
                                StrToInt(WINDOW_NOTIFICATIONS->Edit9->Text)*1000 +
                                StrToInt(WINDOW_NOTIFICATIONS->Edit10->Text),
                        ColorToString(ColorBox1->Selected));

                for(int i = 0; i < GetArrLength(CustomNotify); i++) {
                        if(!CustomNotify[i].set) {
                                CustomNotify[i] = newCN;
                                break;
                        }
                }
                if(ListBox1->Items->Count >= GetArrLength(CustomNotify)) {
                        BUTTON_NEWNOTIFICATION_ADD->Enabled = false;
                }
                updateNotificationsList();
                WINDOW_SETTINGS->setSettingsChanged();
                checkNotificationListState();
        } else if(Edit4->Text.Trim().IsEmpty()) {
                Edit4->SetFocus();
        } else if(!FileExists(Edit1->Text) && !Edit1->Text.Trim().IsEmpty()) {
                Edit1->SetFocus();
        }
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_NOTIFICATIONS::BUTTON_NOTIFICATION_REMOVEClick(TObject *Sender)
{
        for(int i = 0; i < ListBox1->Count; i++) {
                if(ListBox1->Selected[i]) {
                        TObject *t = ListBox1->Items->Objects[i];
                        int j = (int) t;
                        CustomNotify[j] = CustomNotification();
                        ListBox1->Items->Delete(i);
                }
        }
        if(ListBox1->Items->Count < GetArrLength(CustomNotify)) {
                BUTTON_NEWNOTIFICATION_ADD->Enabled = true;
        }
        updateNotificationsList();
        checkNotificationListState();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::FormShow(TObject *Sender)
{
        exitEditNotificationMode();
        updateNotificationsList();
        checkNotificationListState();
        updateLanguage();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::ListBox1Click(TObject *Sender)
{
        checkNotificationListState();        
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_NOTIFICATIONS::BUTTON_EDITNOTIFICATION_CANCELClick(
      TObject *Sender)
{
        exitEditNotificationMode();
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::PLAYClick(TObject *Sender)
{
        if(FileExists(Edit1->Text)) {
                LabelMilli->Visible = true;
                LabelSeconds->Visible = true;
                LabelMinutes->Visible = true;
                PLAY->Visible = false;
                STOP->Visible = true;
                Form1->createMP3Job(-1, -1, Edit1->Text,alias,TrackBar1->Position*10,
                        StrToInt(Edit5->Text)*60000 +
                        StrToInt(Edit6->Text)*1000 +
                        StrToInt(Edit7->Text),
                        StrToInt(Edit8->Text)*60000 +
                        StrToInt(Edit9->Text)*1000 +
                        StrToInt(Edit10->Text), clBlack);
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_ESCAPE) {
                WINDOW_NOTIFICATIONS->Close();
        }                
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_NOTIFICATIONS::TrackBar1Change(TObject *Sender)
{
     //   char text[128];
     //   mciSendString(("setaudio " + alias + " volume to " + String(TrackBar1->Position)*10).c_str(), text, 24,0);
        mciSendString(("setaudio " + alias + " volume to " + String(TrackBar1->Position)*10).c_str(), 0, 0,0);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::STOPClick(TObject *Sender)
{
        Form1->stopMP3Job(alias);
        PLAY->Visible = true;
        STOP->Visible = false;        
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::Edit2Change(TObject *Sender)
{
        try {
                int a = StrToInt(Edit2->Text);
                if(a < UpDown1->Min) {
                        Edit2->Text = UpDown1->Position;
                } else if(a > UpDown1->Max) {
                        Edit2->Text = UpDown1->Position;
                }
        } catch (...) {
                Edit2->Text = UpDown1->Position;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::Edit3Change(TObject *Sender)
{
        try {
                int a = StrToInt(Edit3->Text);
                if(a < UpDown2->Min) {
                        Edit3->Text = UpDown2->Position;
                } else if(a > UpDown2->Max) {
                        Edit3->Text = UpDown2->Position;
                }
        } catch (...) {
                Edit3->Text = UpDown2->Position;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::FormClose(TObject *Sender, TCloseAction &Action)
{
        if(STOP->Visible) {
                STOP->Click();
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::Edit10Change(TObject *Sender)
{
        try {
                StrToInt(Edit10->Text);
        } catch (...) {
                Edit10->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::Edit5Change(TObject *Sender)
{
        try {
                StrToInt(Edit5->Text);
        } catch (...) {
                Edit5->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::Edit6Change(TObject *Sender)
{
        try {
                StrToInt(Edit6->Text);
        } catch (...) {
                Edit6->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::Edit7Change(TObject *Sender)
{
        try {
                StrToInt(Edit7->Text);
        } catch (...) {
                Edit7->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::Edit8Change(TObject *Sender)
{
        try {
                StrToInt(Edit8->Text);
        } catch (...) {
                Edit8->Text = "0";
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_NOTIFICATIONS::Edit9Change(TObject *Sender)
{
        try {
                StrToInt(Edit9->Text);
        } catch (...) {
                Edit9->Text = "0";
        }
}
//---------------------------------------------------------------------------



