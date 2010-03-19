//---------------------------------------------------------------------------
#include <vcl.h>
#include <list>
#include <iostream.h>
#include <mmsystem.h>
#include <math.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma resource "wavefiles.res"
TForm1 *Form1;

int errorreports = 0;

typedef list<String> CustomStringList;

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

Sorter tableSorter = Sorter();

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

Sorter2 playerListSorter = Sorter2();

void addToErrorReport(String err, String msg) {
        if(err.SubString(1,6)== "Fehler") {
                errorreports++;
                Form1->StatusBar1->Panels->Items[2]->Text = "Errors: " + String(errorreports);
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
                int ping;
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
                CustomPlayerList playerlist;
                QueryAnswer queries[queryArrayLength];
                Server() {
                        this->watch = false;
                        this->index = -1;
                        this->ip = "";
                        this->gamespyport = 0;
                        this->timeouts = 0;
                        this->ping = 0;
                        this->clear();
                }
                   
                Server(String &i, int &p, int &ind) {
                        this->watch = false;
                        this->clear();
                        this->index = ind;
                        this->ip = i;
                        this->timeouts = 0;
                        this->ping = 0;
                        this->gamespyport = p;
                }

                void clear() {
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

String inputfile = "gslist-out.gsl";
String program_gslist = "gslist.exe";
String program_gslist_parameter = "-q -n opflashr -o 2";
Server ServerArray[128];
int numOfServers = 1;
int timeoutLimit = 10;
TStringList *ServerSortList = new TStringList;
TStringList *PlayerSortList = new TStringList;
TStringList *PlayerSortList2 = new TStringList;

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
                                        (ServerArray[j].mode == Form1->CheckBox1->Caption && Form1->CheckBox1->Checked) ||
                                        (ServerArray[j].mode == Form1->CheckBox2->Caption && Form1->CheckBox2->Checked) ||
                                        (ServerArray[j].mode == Form1->CheckBox3->Caption && Form1->CheckBox3->Checked) ||
                                        (ServerArray[j].mode == Form1->CheckBox4->Caption && Form1->CheckBox4->Checked) ||
                                        (ServerArray[j].mode == Form1->CheckBox5->Caption && Form1->CheckBox5->Checked) ||
                                        (ServerArray[j].mode == Form1->CheckBox8->Caption && Form1->CheckBox8->Checked)
                                ) && (
                                        (ServerArray[j].password == 1 && Form1->CheckBox6->Checked) ||
                                        (ServerArray[j].password == 0 && Form1->CheckBox7->Checked)
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
                                                        playerfilter = doPlayerFilter(ServerArray[j].playerlist, Form1->Edit4->Text); // );
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

void filterChanged() {
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
                                ServerSortList->AddObject(addLeadingZeros(ServerArray[j].ping), (TObject *) j);
                        }
                        inList++;
                } else if(abc == 0) {
                        hasNoName++;
                }
        }
        if(inList == 1) {
                setEmptyStringGrid();
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
                                Form1->StringGrid1->Cells[6][i] = String(ServerArray[j].ping);
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
                                Form1->StringGrid1->Cells[6][i] = String(ServerArray[j].ping);
                                ServerSortList->Delete(0);
                        }
                }
                Form1->StringGrid1->RowCount = inList;
        }
        Form1->StatusBar1->Panels->Items[1]->Text = "Online: " + String(numOfServers - hasNoName);
        if(selectedIndex > -1) {
                for(int k = 1; k < Form1->StringGrid1->RowCount; k++) {
                                if(Form1->StringGrid1->Cells[0][k] == String(selectedIndex)) {
                                        TGridRect myRect;
                                        myRect.Left = 0;
                                        myRect.Top = k;
                                        myRect.Right = 6;
                                        myRect.Bottom = k;
                                        Form1->StringGrid1->Selection = myRect;
                                        processPlayerList(selectedIndex);
                                        break;
                                } else {
                                        processPlayerList(-1);
                                }
                }
        } else {
                processPlayerList(-1);
        }
        return;
}

class BroadcastRotation {
        public:
                int current;
                bool IsReady;
                BroadcastRotation() {
                        this->reset();
                }
                void reset() {
                        this->current = -1;
                        this->IsReady = true;
                }
                int next() {
                        this->current = this->current + 1;
                        if(this->current >= numOfServers) {
                                this->current = -1;
                                Form1->Timer3->Enabled = false;
                                Form1->Timer1->Enabled = true;
                                filterChanged();
                                processPlayerList(-1);
                        }
                        int out = this->current;
                        return out;
                }
                void setReady() {
                        this->IsReady = true;
                        return;
                }
                bool isReady() {
                        return this->IsReady;
                }
};

BroadcastRotation serverCycle = BroadcastRotation();

String getGameState (int i) {
        String out = IntToStr(i);
        if(i == 2) {
                out = "Creating";
        } else if(i == 6) {
                out = "Waiting";
        } else if(i == 9) {
                out = "Debriefing";
        } else if(i == 12) {
                out = "Setting up";
        } else if(i == 13) {
                out = "Briefing";
        } else if(i == 14) {
                out = "Playing";
        }
        //DEBUG
        if(out.Length() < 7){
                addToErrorReport("Fehler 7", "Unbekannter Spielstatus: " + out);
        }
        return out;
}

CustomStringList getAddress(String address) {
        list<String> a;
        for(int i = 0; i < address.Length(); i++) {
                if(address.SubString(i,1) == ":") {
                        a.push_back(address.SubString(0,i - 1));
                        a.push_back(address.SubString(i + 1, address.Length() - i));
                        break;
                }
        }
        return a;
}

void readFile() {
        TStringList *TempList = new TStringList;
        TempList->Sorted = true;
        TempList->Duplicates = dupIgnore;
        bool read = false;

        //DEBUG
        int debug = 0;
        while (!read) {
                debug++;
                if(debug > 50) {
                        addToErrorReport("Fehler 3","Datei konnte nach 50 Versuchen nicht gelesen werden");
                        break;
                }
                try {
                       TempList->LoadFromFile(inputfile);
                       read = true;
                } catch (...) {
                        Sleep(200);
                }
        }
        numOfServers = TempList->Count;
        for(int i = 0; i < TempList->Count && i < 128; i++) {
                if(TempList->Strings[i].Length() > 8) {
                        CustomStringList a = getAddress(TempList->Strings[i]);
                        String ip = a.front();
                        int port =  StrToInt(a.back());
                        a.clear();
                        ServerArray[i] = Server(ip, port, i);
                }
        }
        Form1->StatusBar1->Panels->Items[0]->Text = "Listed: " + String(numOfServers);
        Form1->StatusBar1->Panels->Items[1]->Text = "Online: ";
        delete TempList;
        //DEBUG
        addToErrorReport("Hinweis 1","Serverliste gelesen: "+ String(numOfServers));
        return;
}



CustomStringList TForm1::splitUpMessage(String msg, String split) {
        list<String> a;
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
                if(newStatus == "Creating") {
                        j = 1;
                } else if(newStatus == "Waiting") {
                        j = 2;
                } else if(newStatus == "Briefing") {
                        j = 3;
                } else if(newStatus == "Playing") {
                        j = 4;
                } else if(newStatus == "Debriefing") {
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
                        addToErrorReport("Fehler 5, queries passen nicht zusammen",msg);
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

                                                String newStatus = getGameState(StrToInt(*ci));
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
                Form1->Visible = true;
                Form1->Caption = Application->Title;
                StringGrid1->Cells[0][0]="ID";
                StringGrid1->Cells[1][0]="Name";
                StringGrid1->Cells[2][0]="Players";
                StringGrid1->Cells[3][0]="Status";
                StringGrid1->Cells[4][0]="Island";
                StringGrid1->Cells[5][0]="Mission";
                StringGrid1->Cells[6][0]="Ping";
                StringGrid2->Cells[0][0]="Name";
                StringGrid2->Cells[1][0]="Score";
                StringGrid2->Cells[2][0]="Deaths";
                StringGrid2->Cells[3][0]="Team";
                if(!FileExists(inputfile)) {
                        if(FileExists(program_gslist)) {
                                SHELLEXECUTEINFO ShellInfo;
                                memset(&ShellInfo, 0, sizeof(ShellInfo));
                                ShellInfo.cbSize = sizeof(ShellInfo);
                                ShellInfo.hwnd = Handle;
                                ShellInfo.lpVerb = "open";
                                ShellInfo.lpFile = PChar(program_gslist.c_str());
                                ShellInfo.nShow = SW_HIDE;
                                ShellInfo.lpDirectory = NULL;
                                ShellInfo.lpParameters = PChar(program_gslist_parameter.c_str());
                                ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                                if (ShellExecuteEx(&ShellInfo)) {
                                        WaitForSingleObject(ShellInfo.hProcess, INFINITE);
                                }
                        }
                }
                readFile();
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
                Form2->init();
                updateTimeoutLimit();
                if(!Form2->getExe().IsEmpty() && !Form2->getExeFolder().IsEmpty()) {
                        PopupMenu1->Items->Items[0]->Enabled = true;
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
                for(int j = 0; j < numOfServers; j++) {
                        if(ServerArray[j].index == -1) {
                                break;
                        }
                        if(ServerArray[j].ip == FromIP && ServerArray[j].gamespyport == Port) {
                                if(readInfoPacket(j, buf, FromIP, Port)) {
                                        if(ServerArray[j].messageSent > 1) {
                                                ServerArray[j].ping = i - ServerArray[j].messageSent;
                                                ServerArray[j].messageSent = 0;
                                                ServerArray[j].timeouts = 0;
                                        }
                                }
                                break;
                        }
                }
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
                        Label2->Caption = ServerArray[index].ip;
                        Label4->Caption = ServerArray[index].gameport;
                        Label9->Caption = ServerArray[index].platform;
                        Label18->Caption = ServerArray[index].impl;
                        int a = ServerArray[index].password;
                        if(a == 0) {
                                Label11->Caption = "No";
                        } else if(a == 1) {
                                Label11->Caption = "Yes";
                        }
                        Label13->Caption = ServerArray[index].actver;
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
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Timer3->Enabled = false;
        Timer1->Enabled = false;
        setEmptyStringGrid();
        setEmptyPlayerList();
        serverCycle.reset();
        tableSorter.reset();
        int j = 0;
        int i = ServerArray[j].index;
        while(i > -1) {
                ServerArray[j] = Server();
                j++;
                i = ServerArray[j].index;
        }
        if(FileExists(program_gslist)) {
                SHELLEXECUTEINFO ShellInfo;
                memset(&ShellInfo, 0, sizeof(ShellInfo));
                ShellInfo.cbSize = sizeof(ShellInfo);
                ShellInfo.hwnd = Handle;
                ShellInfo.lpVerb = "open";
                ShellInfo.lpFile = PChar(program_gslist.c_str());
                ShellInfo.nShow = SW_HIDE;
                ShellInfo.lpDirectory = NULL;
                ShellInfo.lpParameters = PChar(program_gslist_parameter.c_str());
                ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                bool res = ShellExecuteEx(&ShellInfo);
                if (res) {
                        WaitForSingleObject(ShellInfo.hProcess, INFINITE);
                }
        }
        readFile();
        Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        Timer1->Enabled = false;
        Timer3->Enabled = false;
        delete ServerSortList;
        delete PlayerSortList;
        delete PlayerSortList2;
        Form2->writeSettingToFile();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
        String msg = Label2->Caption + ":" + Label4->Caption;;
        copyToClipBoard(msg);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox4Click(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox5Click(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NMUDP1DataSend(TObject *Sender)
{
        serverCycle.setReady();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
        if(serverCycle.isReady()) {
                int a = serverCycle.next();
                if(a >= 0) {
                        sendUdpMessage(a, ServerArray[a].ip,ServerArray[a].gamespyport,"\\info\\rules\\players\\");
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox6Click(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox7Click(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(Button == 0 && Y < StringGrid1->DefaultRowHeight) {
                if(X < 635) {
                        if(X < 30) {
                                tableSorter.setId();
                        } else if(X < 227) {
                                tableSorter.setName();
                        } else if(X < 281) {
                                tableSorter.setPlayers();
                        } else if(X < 350) {
                                tableSorter.setStatus();
                        } else if(X < 409) {
                                tableSorter.setIsland();
                        } else if(X < 593) {
                                tableSorter.setMission();
                        } else if(X < 635) {
                                tableSorter.setPing();
                        }
                        filterChanged();
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
                                Label2->Caption = ServerArray[index].ip;
                                Label4->Caption = ServerArray[index].gameport;
                                Label9->Caption = ServerArray[index].platform;
                                Label18->Caption = ServerArray[index].impl;
                                int a = ServerArray[index].password;
                                if(a == 0) {
                                        Label11->Caption = "No";
                                } else if(a == 1) {
                                        Label11->Caption = "Yes";
                                }
                                Label13->Caption = ServerArray[index].actver;

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
                                PopupMenu1->Popup(Form1->Left + StringGrid1->Left + X + 5,Form1->Top + StringGrid1->Top + Y + StringGrid1->DefaultRowHeight + 7);
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
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit2Change(TObject *Sender)
{
        filterChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(Button == 0 && Y < 16) {
                if(X < 254) {
                        if(X < 101) {
                                playerListSorter.setName();
                        } else if(X < 140) {
                                playerListSorter.setScore();
                        } else if(X < 184) {
                                playerListSorter.setDeaths();
                        } else if(X < 260) {
                                playerListSorter.setTeam();
                        }
                        processPlayerList(-1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit4Change(TObject *Sender)
{
        filterChanged();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        Form2->ShowModal();
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
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox8Click(TObject *Sender)
{
        filterChanged();
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
                                a.Right = 634;
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

