//---------------------------------------------------------------------------
#include <vcl.h>
#include <list>
#include <iostream.h>
#include <mmsystem.h>
#include <math.h>
#pragma hdrstop
#include ".\gamespy\msquery_header.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
#pragma resource "wavefiles.res"
#pragma resource "XP.res"
TForm1 *Form1;

typedef list<String> CustomStringList;

class Message {
        public:
                String content;
                String ip;
                int port;
                DWORD toa;

                Message(String ip, int port, String content, DWORD toa) {
                        this->ip = ip;
                        this->port = port;
                        this->content = content;
                        this->toa = toa;
                }
};


class FontSettings {
        public:
                String name;
                int size;
                int charset;
                TFontStyles style;
                FontSettings() {}
                FontSettings (  String name, int size, int charset,
                                bool bold, bool italic) {
                        if(!name.IsEmpty()) {
                                this->name = name;
                        } else {
                                this->name = Form1->Font->Name;
                        }
                        if(size == 0) {
                                this->size = Form1->Font->Size;
                        } else {
                                this->size = size;
                        }
                        this->charset = charset;
                        if(bold) {
                                this->style = this->style << fsBold;
                        }
                        if(italic) {
                                this->style = this->style << fsItalic;
                        }
                        this->update();
                }

                CustomStringList createFileEntry() {
                        CustomStringList output;
                        output.push_back("[FontSettings]");
                        output.push_back("Charset = " + String(this->charset));
                        output.push_back("Name = " + this->name);
                        output.push_back("Size = " + String(this->size));
                        output.push_back("Bold = " + this->checkBool(this->style.Contains(fsBold)));
                        output.push_back("Italic = " + this->checkBool(this->style.Contains(fsItalic)));
                        output.push_back("[\\FontSettings]");
                        return output;
                }

                String checkBool(bool in) {
                        if(in) {
                                return "1";
                        } else {
                                return "0";
                        }
                }

                void update() {
                        Form1->StringGrid1->Font->Charset = this->charset;
                        Form1->StringGrid1->Font->Name = this->name;
                        Form1->StringGrid1->Font->Size = this->size;
                        Form1->StringGrid1->Font->Style = this->style;
                        Form1->StringGrid1->DefaultRowHeight = this->size * 2.1f;
                        Form1->StringGrid2->Font->Charset = this->charset;
                        Form1->StringGrid2->Font->Name = this->name;
                        Form1->StringGrid2->Font->Size = this->size;
                        Form1->StringGrid2->Font->Style = this->style;
                        Form1->StringGrid2->DefaultRowHeight = this->size * 2.1f;
                        Form1->Label21->Font->Charset = this->charset;
                        Form1->FontDialog1->Font = Form1->StringGrid1->Font;
                        return;
                }
};



class WindowSettings {
        public:
                bool init;
                float ratioID;
                float ratioSN;
                float ratioPN;
                float ratioST;
                float ratioIS;
                float ratioMN;
                float ratioPI;
                float ratioPL;
                float ratioSC;
                float ratioDE;
                float ratioTE;
                
                WindowSettings() {
                        init = false;
                }

                float checkIfZero(float in, int grid) {
                        if(in - 0.001f < 0) {
                                if(grid == 1) {
                                        return ((((float)Form1->StringGrid1->Width / (float)Form1->StringGrid1->ColCount) -
                                                        (float)Form1->StringGrid1->GridLineWidth) / (float)Form1->StringGrid1->Width);
                                } else if(grid == 2) {
                                        return ((((float)Form1->StringGrid2->Width / (float)Form1->StringGrid2->ColCount) -
                                                        (float)Form1->StringGrid2->GridLineWidth) / (float)Form1->StringGrid2->Width);
                                }
                        } else {
                                return in;
                        }
                }

                WindowSettings( int top, int left, int height, int width, float ratioID, float ratioSN,
                                float ratioPN, float ratioST, float ratioIS,
                                float ratioMN, float ratioPI, float ratioPL,
                                float ratioSC, float ratioDE, float ratioTE) {
                        Form1->Position = poDesigned; 
                        Form1->Top = top;
                        Form1->Left = left;
                        if(height >= 526) {
                                Form1->Height = height;
                        }
                        if(width >= 666) {
                                Form1->Width = width;
                        }
                        if(top == 0 || left == 0) {

                        }
                        this->ratioID = checkIfZero(ratioID,1);
                        this->ratioSN = checkIfZero(ratioSN,1);
                        this->ratioPN = checkIfZero(ratioPN,1);
                        this->ratioST = checkIfZero(ratioST,1);
                        this->ratioIS = checkIfZero(ratioIS,1);
                        this->ratioMN = checkIfZero(ratioMN,1);
                        this->ratioPI = checkIfZero(ratioPI,1);
                        this->ratioPL = checkIfZero(ratioPL,2);
                        this->ratioSC = checkIfZero(ratioSC,2);
                        this->ratioDE = checkIfZero(ratioDE,2);
                        this->ratioTE = checkIfZero(ratioTE,2);
                        this->refresh();
                        this->init = true;
                }

                void refresh() {
                        Form1->StringGrid1->ColWidths[0] = (float)Form1->StringGrid1->Width * this->ratioID;
                        Form1->StringGrid1->ColWidths[1] = (float)Form1->StringGrid1->Width * this->ratioSN;
                        Form1->StringGrid1->ColWidths[2] = (float)Form1->StringGrid1->Width * this->ratioPN;
                        Form1->StringGrid1->ColWidths[3] = (float)Form1->StringGrid1->Width * this->ratioST;
                        Form1->StringGrid1->ColWidths[4] = (float)Form1->StringGrid1->Width * this->ratioIS;
                        Form1->StringGrid1->ColWidths[5] = (float)Form1->StringGrid1->Width * this->ratioMN;
                        Form1->StringGrid1->ColWidths[6] = (float)Form1->StringGrid1->Width * this->ratioPI;
                        Form1->StringGrid2->ColWidths[0] = (float)Form1->StringGrid2->Width * this->ratioPL;
                        Form1->StringGrid2->ColWidths[1] = (float)Form1->StringGrid2->Width * this->ratioSC;
                        Form1->StringGrid2->ColWidths[2] = (float)Form1->StringGrid2->Width * this->ratioDE;
                        Form1->StringGrid2->ColWidths[3] = (float)Form1->StringGrid2->Width * this->ratioTE;
                        return;
                }

                CustomStringList createFileEntry() {
                        CustomStringList output;
                        String tmp;
                        output.push_back("[WindowSettings]");
                        output.push_back("Top = " + String(Form1->Top));
                        output.push_back("Left = " + String(Form1->Left));
                        output.push_back("Height = " + String(Form1->Height));
                        output.push_back("Width = " + String(Form1->Width));
                        output.push_back("ratioID = " + tmp.sprintf("%.03f", ratioID));
                        output.push_back("ratioSN = " + tmp.sprintf("%.03f", ratioSN));
                        output.push_back("ratioPN = " + tmp.sprintf("%.03f", ratioPN));
                        output.push_back("ratioST = " + tmp.sprintf("%.03f", ratioST));
                        output.push_back("ratioIS = " + tmp.sprintf("%.03f", ratioIS));
                        output.push_back("ratioMN = " + tmp.sprintf("%.03f", ratioMN));
                        output.push_back("ratioPI = " + tmp.sprintf("%.03f", ratioPI));
                        output.push_back("ratioPL = " + tmp.sprintf("%.03f", ratioPL));
                        output.push_back("ratioSC = " + tmp.sprintf("%.03f", ratioSC));
                        output.push_back("ratioDE = " + tmp.sprintf("%.03f", ratioDE));
                        output.push_back("ratioTE = " + tmp.sprintf("%.03f", ratioTE));
                        output.push_back("[\\WindowSettings]");
                        return output;
                }

                void updateGrid1() {
                        this->ratioID = (float)Form1->StringGrid1->ColWidths[0] / (float)Form1->StringGrid1->Width;
                        this->ratioSN = (float)Form1->StringGrid1->ColWidths[1] / (float)Form1->StringGrid1->Width;
                        this->ratioPN = (float)Form1->StringGrid1->ColWidths[2] / (float)Form1->StringGrid1->Width;
                        this->ratioST = (float)Form1->StringGrid1->ColWidths[3] / (float)Form1->StringGrid1->Width;
                        this->ratioIS = (float)Form1->StringGrid1->ColWidths[4] / (float)Form1->StringGrid1->Width;
                        this->ratioMN = (float)Form1->StringGrid1->ColWidths[5] / (float)Form1->StringGrid1->Width;
                        this->ratioPI = (float)Form1->StringGrid1->ColWidths[6] / (float)Form1->StringGrid1->Width;
                        return;
                }
                void updateGrid2() {
                        this->ratioPL = (float)Form1->StringGrid2->ColWidths[0] / (float)Form1->StringGrid2->Width;
                        this->ratioSC = (float)Form1->StringGrid2->ColWidths[1] / (float)Form1->StringGrid2->Width;
                        this->ratioDE = (float)Form1->StringGrid2->ColWidths[2] / (float)Form1->StringGrid2->Width;
                        this->ratioTE = (float)Form1->StringGrid2->ColWidths[3] / (float)Form1->StringGrid2->Width;
                        return;
                }
};

class QueryAnswer {
        public:
                String id;
                String part;
                bool final;
                CustomStringList content;

                QueryAnswer () {
                        this->clear();
                }

                void clear() {
                        this->id = "";
                        this->part = "";
                        this->final = false;
                        this->content.clear();
                }
};


class Sorter {
        public:
                bool normal;
                bool id;
                bool name;
                bool players;
                bool status;
                bool island;
                bool mission;
                bool ping;

                Sorter() {
                        disableAll();
                        setPlayers();
                        normal = false;
                }

                void reset() {
                        disableAll();
                        setPlayers();
                        normal = false;
                }

                void disableAll() {
                        id = false;
                        name = false;
                        players = false;
                        ping = false;
                        status = false;
                        island = false;
                        mission = false;
                        normal = true;
                }

                void setId() {
                        if(id) {
                                normal = !normal;
                        } else {
                                disableAll();
                                id = true;
                        }
                }
                void setName() {
                        if(name) {
                                normal = !normal;
                        } else {
                                disableAll();
                                name = true;
                        }
                }
                void setPlayers() {
                        if(players) {
                                normal = !normal;
                        } else {
                                disableAll();
                                players = true;
                        }
                }
                void setStatus() {
                        if(status) {
                                normal = !normal;
                        } else {
                                disableAll();
                                status = true;
                        }
                }
                void setIsland() {
                        if(island) {
                                normal = !normal;
                        } else {
                                disableAll();
                                island = true;
                        }
                }
                void setMission() {
                        if(mission) {
                                normal = !normal;
                        } else {
                                disableAll();
                                mission = true;
                        }
                }
                void setPing() {
                        if(ping) {
                                normal = !normal;
                        } else {
                                disableAll();
                                ping = true;
                        }
                }
};



class Sorter2 {
        public:
                bool normal;
                bool name;
                bool score;
                bool deaths;
                bool team;

                Sorter2() {
                        disableAll();
                        setName();
                }

                void disableAll() {
                        normal = true;
                        name = false;
                        score = false;
                        deaths = false;
                        team = false;
                }
                void setName() {
                        if(name) {
                                normal = !normal;
                        } else {
                                disableAll();
                                name = true;
                        }
                }
                void setScore() {
                        if(score) {
                                normal = !normal;
                        } else {
                                disableAll();
                                score = true;
                        }
                }
                void setDeaths() {
                        if(deaths) {
                                normal = !normal;
                        } else {
                                disableAll();
                                deaths = true;
                        }
                }
                void setTeam() {
                        if(team) {
                                normal = !normal;
                        } else {
                                disableAll();
                                team = true;
                        }
                }
};

class Player {
        public:
                String name;
                String team;
                int deaths;
                int score;

                Player() {
                        this->deaths = 0;
                        this->score = 0;
                        this->team = "";
                        this->name = "";
                }
                Player(String &n, String &t, int &s, int &d) {
                        this->name = n;
                        this->team = t;
                        this->score = s;
                        this->deaths = d;
                }
};

typedef list<Player> CustomPlayerList;
const unsigned int queryArrayLength = 10;

class Server {
        public:
                int index;
                int gamespyport;
                int gameport;
                list<int> ping;
                DWORD messageSent;
                int timeouts;
                String ip;
                String timeleft;
                int players;
                int maxplayers;
                String mission;
                String name;
                String mode;
                String island;
                String platform;
                String param1;
                String param2;
                String mod;
                int queryid;
                String impl;
                int password;
                int actver;
                int reqver;
                int equalMod;
                bool watch;
                bool loseATurn;
                CustomPlayerList playerlist;
                QueryAnswer queries[queryArrayLength];
                Server() {
                        this->watch = false;
                        this->index = -1;
                        this->ip = "";
                        this->gamespyport = 0;
                        this->timeouts = 0;
                        this->ping.clear();
                        this->clear();
                }

                Server(String &i, int &p, int &ind) {
                        this->watch = false;
                        this->clear();
                        this->index = ind;
                        this->ip = i;
                        this->timeouts = 0;
                        this->ping.clear();
                        this->gamespyport = p;
                }

                void clear() {
                        this->loseATurn = false;
                        this->gameport = 0;
                        this->timeleft = "";
                        this->players = 0;
                        this->maxplayers = 0;
                        this->mission = "";
                        this->name = "";
                        this->mode = "";
                        this->impl = "";
                        this->param1 = "";
                        this->param2 = "";
                        this->island = "";
                        this->actver = 0;
                        this->reqver = 0;
                        this->platform = "";
                        this->password = -1;
                        this->mod = "";
                        this->equalMod = 0;
                        this->messageSent = 0;
                        this->queryid = 0;
                        this->playerlist.clear();

                }
};


Server ServerArray[1024];
int numOfServers = 0;


Sorter tableSorter = Sorter();
Sorter2 playerListSorter = Sorter2();
WindowSettings windowsettings;
FontSettings fontsettings;
int timeoutLimit = 10;
TStringList *ServerSortList = new TStringList;
TStringList *PlayerSortList = new TStringList;
TStringList *PlayerSortList2 = new TStringList;


int errorreports = 0;




void addToErrorReport(String err, String msg) {
        if(err.SubString(1,6)== "Fehler") {
                errorreports++;
                Form1->StatusBar1->Panels->Items[2]->Text = Form2->getGuiString("STRING_ERRORS") + " " + String(errorreports);
        }
        TStringList *error = new TStringList;
        if(FileExists("errorreport.txt")) {
                error->LoadFromFile("errorreport.txt");
        }
        if(error->Count > 500) {
                error->Delete(error->Count - 1);
                error->Delete(error->Count - 1);
                error->Delete(error->Count - 1);
        }
        error->Insert(0,msg);
        error->Insert(0,err);
        error->Insert(0,"============================");
        error->SaveToFile("errorreport.txt");
        return;
}

void TForm1::setWindowSettings(int top,int left,int height, int width, float ratioID,float ratioSN,
                                float ratioPN,float ratioST,float ratioIS,
                                float ratioMN,float ratioPI,float ratioPL,
                                float ratioSC,float ratioDE,float ratioTE) {
        windowsettings = WindowSettings(top,left,height,width,ratioID,ratioSN,
                                ratioPN,ratioST,ratioIS,
                                ratioMN,ratioPI,ratioPL,
                                ratioSC,ratioDE,ratioTE);
}

void TForm1::setFont(String name, int size, int charset,
                        bool bold, bool italic) {
        fontsettings = FontSettings(name, size, charset, bold, italic);
}

void updateTimeoutLimit() {
        timeoutLimit = ceil(10000 / Form1->Timer1->Interval);
        return;
}

void sendUdpMessage(int index, String ip, int port, String msg) {
        char buffer[256];
        int len;
        strcpy(buffer,msg.c_str());
        len=strlen(buffer);
        Form1->NMUDP1->RemotePort = port;
        Form1->NMUDP1->RemoteHost = ip;
        Form1->NMUDP1->SendBuffer(buffer,256,len);
        if(ServerArray[index].messageSent == 0) {
                ServerArray[index].messageSent = timeGetTime();
        } else {
                int tmp = ServerArray[index].timeouts;
                if(tmp < timeoutLimit) {
                        ServerArray[index].timeouts = tmp + 1;
                } else {
                        ServerArray[index].clear();
                }
        }
        return;
}

bool doNameFilter(String c, String d) {
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

bool doPlayerFilter(CustomPlayerList l, String s) {
        bool out = false;
        for (CustomPlayerList::iterator ci = l.begin(); ci != l.end(); ++ci) {
                Player p = *ci;
                if(doNameFilter(p.name, s)) {
                        out = true;
                        break;
                }
        }
        return out;
}

int checkFilters(int j) {
        int out = 0;
        if(ServerArray[j].name.Length() > 0 && ServerArray[j].timeouts < timeoutLimit) {
                out = 1;
                if(ServerArray[j].players >= Form1->UpDown1->Position) {
                        if(
                                (
                                        (ServerArray[j].mode == Form1->CHECKBOX_FILTER_PLAYING->Caption && Form1->CHECKBOX_FILTER_PLAYING->Checked) ||
                                        (ServerArray[j].mode == Form1->CHECKBOX_FILTER_WAITING->Caption && Form1->CHECKBOX_FILTER_WAITING->Checked) ||
                                        (ServerArray[j].mode == Form1->CHECKBOX_FILTER_CREATING->Caption && Form1->CHECKBOX_FILTER_CREATING->Checked) ||
                                        (ServerArray[j].mode == Form1->CHECKBOX_FILTER_BRIEFING->Caption && Form1->CHECKBOX_FILTER_BRIEFING->Checked) ||
                                        (ServerArray[j].mode == Form1->CHECKBOX_FILTER_DEBRIEFING->Caption && Form1->CHECKBOX_FILTER_DEBRIEFING->Checked) ||
                                        (ServerArray[j].mode == Form1->CHECKBOX_FILTER_SETTINGUP->Caption && Form1->CHECKBOX_FILTER_SETTINGUP->Checked)
                                ) && (
                                        (ServerArray[j].password == 1 && Form1->CHECKBOX_FILTER_WITHPASSWORD->Checked) ||
                                        (ServerArray[j].password == 0 && Form1->CHECKBOX_FILTER_WITHOUTPASSWORD->Checked)
                                )
                        ) {
                                bool missionfilter = true;
                                if(Form1->Edit1->Text.Trim().Length() > 0) {
                                        missionfilter = doNameFilter(ServerArray[j].mission,Form1->Edit1->Text);
                                }
                                if(missionfilter) {
                                        bool namefilter = true;
                                        if(Form1->Edit2->Text.Trim().Length() > 0) {
                                                namefilter = doNameFilter(ServerArray[j].name,Form1->Edit2->Text);
                                        }
                                        if(namefilter) {
                                                bool playerfilter = true;
                                                if(Form1->Edit4->Text.Trim().Length() > 0) {
                                                        playerfilter = doPlayerFilter(ServerArray[j].playerlist, Form1->Edit4->Text);
                                                }
                                                if(playerfilter) {
                                                        out = 2;
                                                }
                                        }
                                }
                        }
                }
        }
        return out;
}

void setEmptyStringGrid() {
        Form1->StringGrid1->RowCount = 2;
        for(int i = 0; i < Form1->StringGrid1->ColCount; i++) {
                Form1->StringGrid1->Cells[i][1] = "";
        }
        return;
}

String addLeadingZeros(int i) {
        String a = String(i);
        while (a.Length() < 4) {
                a = "0" + a;
        }
        return a;
}

void setEmptyPlayerList() {
        Form1->StringGrid2->RowCount = 2;
        Form1->StringGrid2->Cells[0][1] = "";
        Form1->StringGrid2->Cells[1][1] = "";
        Form1->StringGrid2->Cells[2][1] = "";
        Form1->StringGrid2->Cells[3][1] = "";
        return;
}

void processPlayerList(int index) {
        PlayerSortList->Clear();
        PlayerSortList2->Clear();
        int row = Form1->StringGrid1->Selection.BottomRight.Y;
        try {
                if(index == -1) {
                        index = StrToInt(Form1->StringGrid1->Cells[0][row]);
                }
                int counter = ServerArray[index].playerlist.size();
                for (CustomPlayerList::iterator ci = ServerArray[index].playerlist.begin(); ci != ServerArray[index].playerlist.end(); ++ci) {
                        counter--;
                        if(counter < 0) {
                                break;
                        }
                        if(playerListSorter.name) {
                                PlayerSortList->AddObject(ci->name, (TObject *) &(*ci));
                        } else if(playerListSorter.score) {
                                if(ci->score >= 0) {
                                        PlayerSortList->AddObject(addLeadingZeros(ci->score), (TObject*) &(*ci));
                                } else {
                                        PlayerSortList2->AddObject(addLeadingZeros(ci->score), (TObject*) &(*ci));
                                }
                        } else if(playerListSorter.deaths) {
                                PlayerSortList->AddObject(addLeadingZeros(ci->deaths), (TObject*) &(*ci));
                        } else if(playerListSorter.team) {
                                PlayerSortList->AddObject(ci->team, (TObject*) &(*ci));
                        }
                }
                //DEBUG
                if(counter < 0) {
                        addToErrorReport("Fehler 1","");
                }
        } catch (...) {}
        if(PlayerSortList->Count == 0) {
                setEmptyPlayerList();
        } else {
                int z = PlayerSortList->Count;
                int x = PlayerSortList2->Count;

                //DEBUG
                if(x > 50 || z > 50) {
                        addToErrorReport("Fehler 2","Fehler in processPlayerList(int index).\nindex: " + String(index) + "  " + ServerArray[index].name +"\nListe1: " + String(z) + "  Liste2: " + String(x));
                        return;
                }


                Form1->StringGrid2->RowCount = z + x + 1;
                if(playerListSorter.normal) {
                        for(int i = 1 + x; i <= z + x; i++) {
                                Player *p = (Player *) PlayerSortList->Objects[0];
                                Form1->StringGrid2->Cells[0][i] = p->name;
                                Form1->StringGrid2->Cells[1][i] = p->score;
                                Form1->StringGrid2->Cells[2][i] = p->deaths;
                                Form1->StringGrid2->Cells[3][i] = p->team;
                                PlayerSortList->Delete(0);
                        }
                        for(int i = x; i >= 1; i--) {
                                Player *q = (Player *) PlayerSortList2->Objects[0];
                                Form1->StringGrid2->Cells[0][i] = q->name;
                                Form1->StringGrid2->Cells[1][i] = q->score;
                                Form1->StringGrid2->Cells[2][i] = q->deaths;
                                Form1->StringGrid2->Cells[3][i] = q->team;
                                PlayerSortList2->Delete(0);
                        }
                } else {
                        for(int i = z; i >= 1; i--) {
                                Player *p = (Player *) PlayerSortList->Objects[0];
                                Form1->StringGrid2->Cells[0][i] = p->name;
                                Form1->StringGrid2->Cells[1][i] = p->score;
                                Form1->StringGrid2->Cells[2][i] = p->deaths;
                                Form1->StringGrid2->Cells[3][i] = p->team;
                                PlayerSortList->Delete(0);
                        }
                        for(int i = z + 1; i <= z + x; i++) {
                                Player *q = (Player *) PlayerSortList2->Objects[0];
                                Form1->StringGrid2->Cells[0][i] = q->name;
                                Form1->StringGrid2->Cells[1][i] = q->score;
                                Form1->StringGrid2->Cells[2][i] = q->deaths;
                                Form1->StringGrid2->Cells[3][i] = q->team;
                                PlayerSortList2->Delete(0);
                        } 
                }
        }
        return;
}

void updateServerInfoBox(int index) {
        if(index >= 0 && index < numOfServers) {
                Form1->Label2->Caption = ServerArray[index].ip;
                Form1->Label4->Caption = ServerArray[index].gameport;
                Form1->Label9->Caption = ServerArray[index].platform;
                //Form1->Label18->Caption = ServerArray[index].impl;
                Form1->Label21->Caption = ServerArray[index].name;
                Form1->BUTTON_SERVERINFO_COPYADDRESS->Enabled = true;
                int a = ServerArray[index].password;
                if(a == 0) {
                        Form1->Label11->Caption = Form2->getGuiString("STRING_NO");
                } else if(a == 1) {
                        Form1->Label11->Caption = Form2->getGuiString("STRING_YES");
                }
                Form1->Label13->Caption = ServerArray[index].actver;
        } else {
                Form1->BUTTON_SERVERINFO_COPYADDRESS->Enabled = false;
                Form1->Label2->Caption = "";
                Form1->Label4->Caption = "";
                Form1->Label9->Caption = "";
                //Form1->Label18->Caption = "";
                Form1->Label21->Caption = "";
                Form1->Label11->Caption = "";
                Form1->Label13->Caption = "";
        }
        return;
}


int averagePing(list<int> &pings) {
        int sum = 0;
        int i = 0;
        for (list<int>::iterator ci = pings.begin(); ci != pings.end(); ++ci) {
                sum += *ci;
                i++;
        }
        if(i == 0) {
                return 0;
        } else {
                return (sum / i);
        }
}

bool filterChanging = false;
void filterChanged(bool userinput) {
        if(filterChanging) {
                return;
        }
        filterChanging = true;
        if(userinput) {
                Form2->setSettingsChanged();
        }
        int row = Form1->StringGrid1->Selection.BottomRight.Y;
        int selectedIndex;
        try {
                selectedIndex = StrToInt(Form1->StringGrid1->Cells[0][row]);
        } catch (...) {
                selectedIndex = -1;
        }
        ServerSortList->Clear();
        int inList = 1;
        int hasNoName = 0;
        for (int j = 0; j < numOfServers; j++) {
                int abc = checkFilters(j);
                if(abc == 2) {
                        if(tableSorter.id) {
                                ServerSortList->AddObject(addLeadingZeros(ServerArray[j].index),(TObject *) j);
                        } else if(tableSorter.name) {
                                ServerSortList->AddObject(ServerArray[j].name,(TObject *) j);
                        } else if(tableSorter.players) {
                                ServerSortList->AddObject(addLeadingZeros(ServerArray[j].players),(TObject *) j);
                        } else if(tableSorter.status) {
                                ServerSortList->AddObject(ServerArray[j].mode, (TObject *) j);
                        } else if(tableSorter.island) {
                                ServerSortList->AddObject(ServerArray[j].island, (TObject *) j);
                        } else if(tableSorter.mission) {
                                ServerSortList->AddObject(ServerArray[j].mission, (TObject *) j);
                        } else if(tableSorter.ping) {
                                ServerSortList->AddObject(addLeadingZeros(averagePing(ServerArray[j].ping)), (TObject *) j);
                        }
                        inList++;
                } else if(abc == 0) {
                        hasNoName++;
                }
        }
        bool found = false;

        if(inList == 1) {
                setEmptyStringGrid();
                setEmptyPlayerList();
                updateServerInfoBox(-1);
        } else {
                if(tableSorter.normal) {
                        for(int i = 1; i < inList; i++) {
                                TObject *t = ServerSortList->Objects[0];
                                int j = (int)t;
                                Form1->StringGrid1->Cells[0][i] = " " + String(ServerArray[j].index);
                                Form1->StringGrid1->Cells[1][i] = ServerArray[j].name;
                                Form1->StringGrid1->Cells[2][i] = String(ServerArray[j].players) + " / " + String(ServerArray[j].maxplayers);
                                Form1->StringGrid1->Cells[3][i] = ServerArray[j].mode;
                                Form1->StringGrid1->Cells[4][i] = ServerArray[j].island;
                                Form1->StringGrid1->Cells[5][i] = ServerArray[j].mission;
                                Form1->StringGrid1->Cells[6][i] = String(averagePing(ServerArray[j].ping));
                                ServerSortList->Delete(0);
                        }
                } else {
                        for(int i = inList - 1; i >= 1; i--) {
                                TObject *t = ServerSortList->Objects[0];
                                int j = (int)t;
                                Form1->StringGrid1->Cells[0][i] = " " + String(ServerArray[j].index);
                                Form1->StringGrid1->Cells[1][i] = ServerArray[j].name;
                                Form1->StringGrid1->Cells[2][i] = String(ServerArray[j].players) + " / " + String(ServerArray[j].maxplayers);
                                Form1->StringGrid1->Cells[3][i] = ServerArray[j].mode;
                                Form1->StringGrid1->Cells[4][i] = ServerArray[j].island;
                                Form1->StringGrid1->Cells[5][i] = ServerArray[j].mission;
                                Form1->StringGrid1->Cells[6][i] = String(averagePing(ServerArray[j].ping));
                                ServerSortList->Delete(0);
                        }
                }
                Form1->StringGrid1->RowCount = inList;
                Form1->StatusBar1->Panels->Items[0]->Text = Form2->getGuiString("STRING_LISTED") + " " + String(numOfServers);
                Form1->StatusBar1->Panels->Items[1]->Text = Form2->getGuiString("STRING_ONLINE") + " " + String(numOfServers - hasNoName);
                if(selectedIndex > -1) {
                        for(int k = 1; k < Form1->StringGrid1->RowCount; k++) {
                                if((Form1->StringGrid1->Cells[0][k]).Trim() == String(selectedIndex).Trim()) {
                                        found = true;
                                        TGridRect myRect;
                                        myRect.Left = 0;
                                        myRect.Top = k;
                                        myRect.Right = 6;
                                        myRect.Bottom = k;
                                        Form1->StringGrid1->Selection = myRect;
                                        break;
                                }
                        }
                        if(found) {
                                processPlayerList(selectedIndex);
                                updateServerInfoBox(selectedIndex);
                        }
                }

        }
        if(found) {
                Form1->TrayIcon1->Hint = ServerArray[selectedIndex].name + "     " + ServerArray[selectedIndex].mode + "     " +  String(ServerArray[selectedIndex].players) + " Players";
        } else {
                Form1->TrayIcon1->Hint = "OFPMonitor";
        }
        filterChanging = false;
        return;
}

class BroadcastRotation {
        public:
                int current;
                bool receivingFirstTime;
                bool loseTurnValue;
                bool IsReady;
                BroadcastRotation() {
                        this->reset();
                }
                void reset() {
                        this->current = -1;
                        this->IsReady = true;
                        this->receivingFirstTime = true;
                        this->loseTurnValue = false;
                }
                int next() {
                        bool temp = false;
                        do {
                                if(temp) {
                                        ServerArray[this->current].loseATurn = false;
                                }
                                this->current = this->current + 1;
                                if(this->current >= numOfServers) {
                                        this->current = -1;
                                        this->receivingFirstTime = false;
                                        Form1->Timer3->Enabled = false;
                                        Form1->Timer1->Enabled = true;
                                        filterChanged(false);
                                        processPlayerList(-1);
                                        break;
                                }
                                temp = true;
                        } while ( ServerArray[this->current].loseATurn );
                        int out = this->current;
                        return out;
                }
                void setReady() {
                        this->IsReady = true;
                        return;
                }
                bool loseTurn() {
                        this->loseTurnValue = !this->loseTurnValue;
                        return this->loseTurnValue;
                }
                bool isReady() {
                        return this->IsReady;
                }
};

BroadcastRotation serverCycle = BroadcastRotation();

String getGameState (int i, String old) {
        String out = IntToStr(i);
        if(i == 2) {
                out = Form1->CHECKBOX_FILTER_CREATING->Caption;
        } else if(i == 6) {
                out = Form1->CHECKBOX_FILTER_WAITING->Caption;
        } else if(i == 9) {
                out = Form1->CHECKBOX_FILTER_DEBRIEFING->Caption;
        } else if(i == 12) {
                out = Form1->CHECKBOX_FILTER_SETTINGUP->Caption;
        } else if(i == 13) {
                out = Form1->CHECKBOX_FILTER_BRIEFING->Caption;
        } else if(i == 14) {
                out = Form1->CHECKBOX_FILTER_PLAYING->Caption;
        } else {
                addToErrorReport("Fehler 13, status",out);
        }
        return out;
}

CustomStringList getAddress(String address) {
        CustomStringList a;
        for(int i = 0; i < address.Length(); i++) {
                if(address.SubString(i,1) == ":") {
                        a.push_back(address.SubString(0,i - 1));
                        a.push_back(address.SubString(i + 1, address.Length() - i));
                        break;
                }
        }
        return a;
}

void readServerList(TStringList *in) {
        Form1->StatusBar1->Panels->Items[0]->Text = "";
        Form1->StatusBar1->Panels->Items[1]->Text = "";
        numOfServers = 0;
        for(int i = 0; i < in->Count && i < sizeof(ServerArray); i++) {
                if(in->Strings[i].Length() > 8) {
                        CustomStringList a = getAddress(in->Strings[i]);
                        String ip = a.front();
                        int port =  StrToInt(a.back());
                        a.clear();
                        ServerArray[i] = Server(ip, port, i);
                        numOfServers++;
                }
        }
        return;
}



CustomStringList TForm1::splitUpMessage(String msg, String split) {
        CustomStringList a;
        int start = 1;
        if(split == "\\") {
                start = 2;
        }
        int last = start;
        for(int i = start; i < msg.Length(); i++) {
                if(msg.SubString(i,split.Length()) == split) {
                        a.push_back(msg.SubString(last, i - last));
                        last = i + split.Length();
                }
        }
        a.push_back(msg.SubString(last, (msg.Length() + 1) - last));
        return a;
}

void mergeLists(CustomStringList &a, CustomStringList &b) {
        while(b.size() > 0) {
                String tmp = b.front();
                a.push_back(tmp);
                b.pop_front();
        }
        return;
}


void checkServerStatus(int i, String newStatus) {
        if(ServerArray[i].watch) {
                int j = 0;
                if(newStatus == Form1->CHECKBOX_FILTER_CREATING->Caption) {
                        j = 1;
                } else if(newStatus == Form1->CHECKBOX_FILTER_WAITING->Caption) {
                        j = 2;
                } else if(newStatus == Form1->CHECKBOX_FILTER_BRIEFING->Caption) {
                        j = 3;
                } else if(newStatus == Form1->CHECKBOX_FILTER_PLAYING->Caption) {
                        j = 4;
                } else if(newStatus == Form1->CHECKBOX_FILTER_DEBRIEFING->Caption) {
                        j = 5;
                }
                if(j > 0) {
                        PlaySound(PChar(j), NULL, SND_RESOURCE | SND_ASYNC);
                }
        }
        return;
}



bool readInfoPacket(int &i, String &msg, String ip, int &port) {
        bool out = false;
        CustomStringList a = Form1->splitUpMessage(msg,"\\");
        if(a.size() <= 1) {
                return false;
        }
        String idstring = a.back();
        a.pop_back();
        String querystring = a.back();
        bool final = false;
        a.pop_back();
        if(querystring == "queryid" && a.size()%2 == 0) {
                CustomStringList b = Form1->splitUpMessage(idstring,".");
                if(b.size() == 2) {
                        int id = StrToInt(b.front());
                        int part = StrToInt(b.back());
                        CustomStringList tmp;
                        tmp.push_front(a.back());
                        a.pop_back();
                        if(a.back() == "final") {
                                final = true;
                        }
                        mergeLists(a,tmp);
                        if(     (part == 1 && ServerArray[i].queryid < id) ||
                                (part > 1 && ServerArray[i].queryid == id)      ) {
                                        if(part == 1) {
                                                out = true;
                                                int num = a.size();
                                                for(int k = 0; k < num; k++) {
                                                        String t = a.back();
                                                        tmp.push_front(t);
                                                        a.pop_back();
                                                        if(a.back() == "hostname") {
                                                                String hostname = tmp.front();
                                                                for(int l = 0; l < numOfServers; l++) {
                                                                        if((hostname == ServerArray[l].name && ip != ServerArray[l].ip) || (id == ServerArray[l].queryid)) {
                                                                                return false;
                                                                        }
                                                                }
                                                                break;
                                                        }
                                                }
                                                mergeLists(a, tmp);
                                                ServerArray[i].queryid = id;
                                        } else {
                                                out = false;
                                        }
                                        ServerArray[i].queries[part - 1].clear();
                                        ServerArray[i].queries[part - 1].id = id;
                                        ServerArray[i].queries[part - 1].final = final;
                                        ServerArray[i].queries[part - 1].part = part;
                                        mergeLists(ServerArray[i].queries[part - 1].content,a);
                        } else {
                                return false;
                        }
                }
        } else {
                return false;
        }
        CustomStringList answer;
        bool success = false;
        if(final) {
                bool correct = true;
                int endingIndex = -1;
                for(int j = 0; j < queryArrayLength && correct; j++) {
                        correct = (ServerArray[i].queryid == ServerArray[i].queries[j].id);
                        if(ServerArray[i].queries[j].final) {
                                endingIndex = j;
                                break;
                        }
                }
                if(correct && endingIndex > -1) {
                        for(int j = 0; j <= endingIndex; j++) {
                                mergeLists(answer,ServerArray[i].queries[j].content);
                                success = true;
                        }
                } else {
                        //DEBUG
                        addToErrorReport("Fehler 5, queries dont match",msg);
                        return false;
                }
        }
        bool players = false;
                if(ServerArray[i].ip == ip && ServerArray[i].gamespyport == port && success) {
                        bool once = true;
                        int counter = answer.size();
                        for (CustomStringList::iterator ci = answer.begin(); ci != answer.end(); ++ci) {
                                counter--;
                                if(counter < 0) {
                                        break;
                                }
                                String tmp = *ci;
                                if(tmp == "final") {
                                        break;
                                }
                                if(tmp.SubString(1,7) == "player_") {
                                        if(once) {
                                                while(!ServerArray[i].playerlist.empty()) {
                                                        Player *t = &(ServerArray[i].playerlist.front());
                                                        delete t;
                                                        ServerArray[i].playerlist.pop_front();
                                                }
                                                once = false;
                                        }
                                        players = true;
                                }
                                if(!players) {
                                        if(tmp == "hostname") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].name = *ci;
                                        } else if (tmp == "hostport") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].gameport = StrToInt(*ci);
                                        } else if (tmp == "mapname") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].island = *ci;
                                        } else if (tmp == "gametype") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].mission = *ci;
                                        } else if (tmp == "numplayers") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].players = StrToInt(*ci);
                                                if(once && ServerArray[i].players == 0) {
                                                        while(!ServerArray[i].playerlist.empty()) {
                                                                Player *t = &(ServerArray[i].playerlist.front());
                                                                delete t;
                                                                ServerArray[i].playerlist.pop_front();
                                                        }
                                                        once = false;
                                                }
                                        } else if (tmp == "maxplayers") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].maxplayers = StrToInt(*ci) - 2;
                                        } else if (tmp == "timeleft") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].timeleft = *ci;
                                        } else if (tmp == "param1") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].param1 = *ci;
                                        } else if (tmp == "param2") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].param2 = *ci;
                                        } else if (tmp == "actver") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].actver = StrToInt(*ci);
                                        } else if (tmp == "reqver") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].reqver = StrToInt(*ci);
                                        } else if (tmp == "mod") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].mod = *ci;
                                        } else if (tmp == "equalMod") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].equalMod = StrToInt(*ci);
                                        } else if (tmp == "password") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].password = StrToInt(*ci);
                                        } else if (tmp == "gstate") {
                                                ++ci;
                                                counter--;
                                                String oldStatus = ServerArray[i].mode;
                                                String newStatus = getGameState(StrToInt(*ci), oldStatus);
                                                if(ServerArray[i].mode != newStatus) {
                                                        ServerArray[i].mode = newStatus;
                                                        checkServerStatus(i, newStatus);
                                                }
                                        } else if (tmp == "platform") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].platform = *ci;
                                        } else if (tmp == "impl") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].impl = *ci;
                                        }
                                } else {

                                        if(tmp.SubString(1,7) == "player_") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].playerlist.push_back(Player());
                                                ServerArray[i].playerlist.back().name = *ci;
                                        } else if(tmp.SubString(1,5) == "team_") {
                                                ++ci;
                                                counter--;
                                                ServerArray[i].playerlist.back().team = *ci;
                                        } else if(tmp.SubString(1,6) == "score_") {
                                                ++ci;
                                                counter--;
                                                try {
                                                        ServerArray[i].playerlist.back().score = StrToInt(*ci);
                                                } catch (...) {
                                                        ServerArray[i].playerlist.back().score = 0;
                                                }
                                        } else if(tmp.SubString(1,7) == "deaths_") {
                                                ++ci;
                                                counter--;
                                                try {
                                                        ServerArray[i].playerlist.back().deaths = StrToInt(*ci);
                                                } catch (...) {
                                                        ServerArray[i].playerlist.back().score = 0;
                                                }
                                        }
                                }
                        }
                        //DEBUG
                        if(counter < 0) {
                                addToErrorReport("Fehler 6",msg);
                        }
                }
        return out;
}

class MessageReader {
        public:
                bool working;
                list<Message> messageList;

                MessageReader() {
                        this->working = false;
                }

                void newMessage(Message m) {
                        this->messageList.push_back(m);
                }



                void checkForNewMessages() {
                        if(this->working) {
                                return;
                        }
                        this->working = true;
                        while(this->messageList.size() > 0) {
                                Message m = this->messageList.front();
                                for(int j = 0; j < numOfServers; j++) {
                                        if(ServerArray[j].index == -1) {
                                                break;
                                        }
                                        if(ServerArray[j].ip == m.ip && ServerArray[j].gamespyport == m.port) {
                                                if(readInfoPacket(j, m.content, m.ip, m.port)) {
                                                        if(!ServerArray[j].loseATurn && ServerArray[j].players == 0) {
                                                                if(serverCycle.receivingFirstTime) {
                                                                        ServerArray[j].loseATurn = serverCycle.loseTurn();
                                                                } else {
                                                                        ServerArray[j].loseATurn = true;
                                                                }
                                                        }
                                                        if(ServerArray[j].messageSent > 1) {
                                                                int curr = m.toa - ServerArray[j].messageSent;
                                                                if(ServerArray[j].ping.size() > 4) {
                                                                        ServerArray[j].ping.pop_front();
                                                                };
                                                                ServerArray[j].ping.push_back(curr);
                                                                ServerArray[j].messageSent = 0;
                                                                ServerArray[j].timeouts = 0;
                                                        }
                                                }
                                                break;
                                        }
                                }
                                this->messageList.pop_front();
                        }
                        this->working = false;
                }
};

MessageReader messageReader = MessageReader();

void copyToClipBoard (String msg) {
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
        return;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        windowsettings = WindowSettings(0,0,0,0,0.0f, 0.0f,0.0f, 0.0f,
                                0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f);
        numOfServers = 0;
        Form1->Caption = Application->Title;
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
        ServerSortList->Sorted = true;
        ServerSortList->CaseSensitive = true;
        ServerSortList->Duplicates = dupAccept;
        PlayerSortList->Sorted = true;
        PlayerSortList->CaseSensitive = true;
        PlayerSortList->Duplicates = dupAccept;
        PlayerSortList2->Sorted = true;
        PlayerSortList2->CaseSensitive = true;
        PlayerSortList2->Duplicates = dupAccept;
        Timer3->Enabled = true;
        TStringList *TempList = Form2->init();
        readServerList(TempList);
        updateTimeoutLimit();
        if(!Form2->getExe().IsEmpty() && !Form2->getExeFolder().IsEmpty()) {
                PopupMenu1->Items->Items[0]->Enabled = true;
        }
        Form1->Visible = true;
        if(numOfServers == 0) {
                MENUITEM_MAINMENU_GETNEWSERVERLIST->Click();
        }
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NMUDP1DataReceived(TComponent *Sender,
      int NumberBytes, AnsiString FromIP, int Port)
{
        DWORD i = timeGetTime();
        char buffer[2048];
        int len;
        NMUDP1->ReadBuffer(buffer,2048,len);
        buffer[len]=0;
        String buf = String(buffer);
        free(buffer);
        messageReader.newMessage(Message(FromIP,Port,buf,i));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
        String z = (StringGrid1->Cells[0][ARow]).Trim();
        if(!z.IsEmpty()) {
                try {
                        int index = StrToInt(z);
                        processPlayerList(index);
                        updateServerInfoBox(index);
                } catch (...) {
                }
        } else {
                setEmptyPlayerList();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        Application->ProcessMessages();
        Timer3->Enabled = true;
        Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        Timer1->Enabled = false;
        Timer3->Enabled = false;
        delete ServerSortList;
        delete PlayerSortList;
        delete PlayerSortList2;
        CustomStringList servers;
        for(int i = 0; i < sizeof(ServerArray); i++) {
                if(ServerArray[i].index == -1) {
                        break;
                }
                servers.push_back(ServerArray[i].ip + ":" + String(ServerArray[i].gamespyport));
        }
        Form2->writeSettingToFile(servers, fontsettings.createFileEntry(), windowsettings.createFileEntry());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BUTTON_SERVERINFO_COPYADDRESSClick(TObject *Sender)
{
        copyToClipBoard(Label2->Caption + ":" + Label4->Caption);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_PLAYINGClick(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_WAITINGClick(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_CREATINGClick(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_BRIEFINGClick(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_DEBRIEFINGClick(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NMUDP1DataSend(TObject *Sender)
{
        serverCycle.setReady();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
        messageReader.checkForNewMessages();
        if(serverCycle.isReady()) {
                int a = serverCycle.next();
                if(a >= 0) {
                        sendUdpMessage(a, ServerArray[a].ip,ServerArray[a].gamespyport,"\\info\\rules\\players\\");
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_WITHPASSWORDClick(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_WITHOUTPASSWORDClick(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        int col0, col1, col2, col3, col4, col5, col6;
        col0 = StringGrid1->ColWidths[0] + StringGrid1->GridLineWidth;
        col1 = col0 + StringGrid1->ColWidths[1] + StringGrid1->GridLineWidth;
        col2 = col1 + StringGrid1->ColWidths[2] + StringGrid1->GridLineWidth;
        col3 = col2 + StringGrid1->ColWidths[3] + StringGrid1->GridLineWidth;
        col4 = col3 + StringGrid1->ColWidths[4] + StringGrid1->GridLineWidth;
        col5 = col4 + StringGrid1->ColWidths[5] + StringGrid1->GridLineWidth;
        col6 = col5 + StringGrid1->ColWidths[6] + StringGrid1->GridLineWidth;

        if(Button == 0 && Y < StringGrid1->DefaultRowHeight) {
                if(X < col6) {
                        if(X < col0) {
                                tableSorter.setId();
                        } else if(X < col1) {
                                tableSorter.setName();
                        } else if(X < col2) {
                                tableSorter.setPlayers();
                        } else if(X < col3) {
                                tableSorter.setStatus();
                        } else if(X < col4) {
                                tableSorter.setIsland();
                        } else if(X < col5) {
                                tableSorter.setMission();
                        } else if(X < col6) {
                                tableSorter.setPing();
                        }
                        filterChanged(false);
                        Form2->setSettingsChanged();
                }
        } else if(Button == 1 && Y >= StringGrid1->DefaultRowHeight) {
                int c = ((Y - StringGrid1->DefaultRowHeight) / (StringGrid1->DefaultRowHeight + 1)) + 1;
                if(StringGrid1->RowCount > c) {
                        try {
                                int index = StrToInt(StringGrid1->Cells[0][c + (StringGrid1->TopRow - 1)]);
                                TGridRect myRect;
                                myRect.Left = 0;
                                myRect.Top = c + (StringGrid1->TopRow - 1);
                                myRect.Right = StringGrid1->ColCount - 1;
                                myRect.Bottom = c + (StringGrid1->TopRow - 1);
                                Form1->StringGrid1->Selection = myRect;
                                processPlayerList(index);
                                updateServerInfoBox(index);
                                CustomStringList t = splitUpMessage(ServerArray[index].mod,";");
                                PopupMenu1->Items->Items[2]->Checked = ServerArray[index].watch;
                                PopupMenu1->Items->Items[2]->Tag = index;
                                PopupMenu1->Items->Items[2]->OnClick = ClickWatchButton;
                                int i = 0;
                                for (CustomStringList::iterator ci = t.begin(); ci != t.end(); ++ci) {
                                        TMenuItem *m = PopupMenu1->Items->Items[1]->Items[i];
                                        m->Caption = *ci;
                                        m->Visible = true;
                                        i++;
                                }
                                for(; i < PopupMenu1->Items->Items[1]->Count; i++) {
                                        TMenuItem *m = PopupMenu1->Items->Items[1]->Items[i];
                                        m->Visible = false;
                                }
                                PopupMenu1->Popup(Form1->Left + StringGrid1->Left + X + 5,Form1->Top + StringGrid1->Top + Y + StringGrid1->DefaultRowHeight + 25);
                        } catch (...) {}
                }
        }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit3Change(TObject *Sender)
{
        try {
                int a = StrToInt(Edit3->Text);
                if(a < UpDown1->Min) {
                        Edit3->Text = UpDown1->Position;
                } else if(a > UpDown1->Max) {
                        Edit3->Text = UpDown1->Position;
                }
        } catch (...) {
                Edit3->Text = UpDown1->Position;
        }
        filterChanged(true);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit2Change(TObject *Sender)
{
        filterChanged(true);
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
                                playerListSorter.setName();
                        } else if(X < col1) {
                                playerListSorter.setScore();
                        } else if(X < col2) {
                                playerListSorter.setDeaths();
                        } else if(X < col3) {
                                playerListSorter.setTeam();
                        }
                        processPlayerList(-1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit4Change(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PopupMenu1Popup(TObject *Sender)
{
        for(int i = 0; i < Form2->getConfAmount() || i < PopupMenu1->Items->Items[0]->Count; i++) {
                String s = Form2->getConfListEntry(i);
                if(!s.IsEmpty()) {
                        TMenuItem *a;
                        if(i < PopupMenu1->Items->Items[0]->Count) {
                                a = PopupMenu1->Items->Items[0]->Items[i];
                        } else {
                                a = new TMenuItem(this);
                                PopupMenu1->Items->Items[0]->Add(a);
                        }
                        a->Tag = i;
                        a->Caption = s;
                        a->Visible = true;
                        a->OnClick = ClickMyButton;
                } else {
                        if(i < PopupMenu1->Items->Items[0]->Count) {
                                PopupMenu1->Items->Items[0]->Items[i]->Visible = false;
                        }
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClickMyButton(TObject *Sender)
{
        TMenuItem *a = (TMenuItem *) Sender;
        ShellExecute(Handle, "open", PChar(Form2->getExe().c_str()), PChar(Form2->getConfStartLine(a->Tag,Label2->Caption,StrToInt(Label4->Caption)).c_str()), PChar(Form2->getExeFolder().c_str()), SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClickWatchButton(TObject *Sender)
{
        TMenuItem *a = (TMenuItem *) Sender;
        int index = a->Tag;
        a->Checked = !(a->Checked);
        ServerArray[index].watch = a->Checked;
        StringGrid1->Refresh();
        checkServerStatus(index, ServerArray[index].mode);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CHECKBOX_FILTER_SETTINGUPClick(TObject *Sender)
{
        filterChanged(true);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_ESCAPE) {
                Form1->Close();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        if(ACol == StringGrid1->ColCount - 1) {
                try {
                        int zelle = ARow;
                        int index = StrToInt((StringGrid1->Cells[0][zelle]).Trim());
                        if(ServerArray[index].watch) {
                                TRect a;
                                a.Top = ((zelle - (StringGrid1->TopRow - 1)) * StringGrid1->DefaultRowHeight) + (zelle - (StringGrid1->TopRow - 1));
                                a.Bottom = ((zelle + 1 - (StringGrid1->TopRow - 1)) * StringGrid1->DefaultRowHeight) + (zelle - (StringGrid1->TopRow - 1));
                                a.Left = 1;
                                int tmp = 0;
                                for(int i = 0; i < StringGrid1->ColCount; i++) {
                                        tmp += StringGrid1->ColWidths[i] + StringGrid1->GridLineWidth;
                                }
                                a.Right = tmp;
                                StringGrid1->Canvas->Brush->Color = clBlue;
                                StringGrid1->Canvas->FrameRect(a);
                                a.Top = a.Top + 1;
                                a.Bottom = a.Bottom - 1;
                                a.Left = a.Left + 1;
                                a.Right = a.Right - 1;
                                StringGrid1->Canvas->FrameRect(a);
                                a.Top = a.Top + 1;
                                a.Bottom = a.Bottom - 1;
                                a.Left = a.Left + 1;
                                a.Right = a.Right - 1;
                                StringGrid1->Canvas->FrameRect(a);
                        }
                } catch (...) {}
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_SETTINGSClick(TObject *Sender)
{
        Form2->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_EXITClick(TObject *Sender)
{
        Form1->Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_GETNEWSERVERLISTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_GETNEWSERVERLIST->Enabled = false;
        Timer3->Enabled = false;
        Timer1->Enabled = false;
        setEmptyStringGrid();
        setEmptyPlayerList();
        updateServerInfoBox(-1);
        serverCycle.reset();
        tableSorter.reset();
        TStringList *CurrentList = new TStringList;
        CurrentList->Sorted = true;
        CurrentList->Duplicates = dupIgnore;
        int j = 0;
        numOfServers = 0;
        int i = ServerArray[j].index;
        while(i > -1) {
                if(ServerArray[j].name.Length() > 0) {
                        CurrentList->Add((ServerArray[j].ip + ":" + String(ServerArray[j].gamespyport)).Trim());
                }
                ServerArray[j] = Server();
                j++;
                i = ServerArray[j].index;
        }

        scandelay *= 1000;
        dnsdb(NULL);
        gslist_step_1(gamestr, filter);
        peer.sin_addr.s_addr = msip;
        peer.sin_port        = htons(msport);
        peer.sin_family      = AF_INET;

        buff = (unsigned char *) malloc(BUFFSZ + 1);
        if(!buff) std_err();
        dynsz = BUFFSZ;
        multigamename = gamestr;
        multigamenamep = strchr((char *)gamestr, ',');
        if(multigamenamep) {
                *multigamenamep = 0;
        }
        sd = gslist_step_2(&peer, buff, secure, gamestr, validate, filter, &enctypex_data);
        ipport = gslist_step_3(sd, validate, &enctypex_data, &len, &buff, &dynsz);
        itsok = gslist_step_4(secure, buff, &enctypex_data, &ipport, &len);
        ipbuffer = ipport;
    	while(len >= 6) {
        	ipc = myinetntoa(ipport->ip);
        	if(!enctypex_query[0]) {
                	String s;
                	s.sprintf("%15s:%d", ipc, ntohs(ipport->port));
                        CurrentList->Add(s.Trim());
        	}
        	ipport++;
        	len -= 6;
    	}
        readServerList(CurrentList);
        delete CurrentList;
        Form2->setSettingsChanged();
        Timer1->Enabled = true;
        MENUITEM_MAINMENU_GETNEWSERVERLIST->Enabled = true;       
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_FONTClick(TObject *Sender)
{
        FontDialog1->Font = StringGrid1->Font;
        FontDialog1->Execute();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FontDialog1Apply(TObject *Sender, HWND Wnd)
{
        fontsettings.name = FontDialog1->Font->Name;
        fontsettings.size = FontDialog1->Font->Size;
        fontsettings.charset = FontDialog1->Font->Charset;
        fontsettings.style = FontDialog1->Font->Style;
        fontsettings.update();
        Form2->setSettingsChanged();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
        StringGrid2->Width = Form1->Width - (StringGrid2->Left + 10);
        StringGrid1->Width = Form1->Width - (StringGrid1->Left + 10);
        StringGrid1->Height = Form1->Height - (StringGrid1->Top + StatusBar1->Height + 45);
        if(windowsettings.init) {
                windowsettings.refresh();
        }
        Form2->setSettingsChanged();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        windowsettings.updateGrid1();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        windowsettings.updateGrid2();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FontDialog1Close(TObject *Sender)
{
        StringGrid1->Font = FontDialog1->Font;        
}
//---------------------------------------------------------------------------

