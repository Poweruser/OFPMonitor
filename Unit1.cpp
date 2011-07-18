//---------------------------------------------------------------------------
#include <vcl.h>                                                     
#include <list.h>                                         
#include <iostream.h>
#include <mmsystem.h>
#include <math.h>
#pragma hdrstop
#include ".\gamespy\msquery_header.h"
#include "irc/irc.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CoolTrayIcon"
#pragma resource "*.dfm"
#pragma resource "wavefiles.res"
                
TForm1 *Form1;
#include "OFPMonitor.h"
using namespace OFPMonitor_Unit1;

/**                                                                                          
   Represents an internet address with IP and port
 */

class Address {
        public:
                String ip;
                int port;
                Address() {
                        this->ip = "";
                        this->port = 0;
                }

                Address(String ip, int port) {
                        this->ip = ip;
                        this->port = port;
                }
};

/**
   Stores the current Font configuration
 */

class FontSettings {
        public:
                String name;
                int size;
                int charset;
                TFontStyles style;
                FontSettings() {}

                /**
                   Constructor

                   @name  name of the font
                   @size  font size
                   @charset  the charset being used
                   @bold  bold option
                   @italic  italic option
                */

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

                /**
                   Creates the section about the font settings that will be
                   written to the configuration file of the program
                */

                list<String> createFileEntry() {
                        list<String> output;
                        output.push_back("[FontSettings]");
                        output.push_back("Charset = " + String(this->charset));
                        output.push_back("Name = " + this->name);
                        output.push_back("Size = " + String(this->size));
                        output.push_back("Bold = " + this->checkBool(this->style.Contains(fsBold)));
                        output.push_back("Italic = " + this->checkBool(this->style.Contains(fsItalic)));
                        output.push_back("[\\FontSettings]");
                        return output;
                }

                /**
                   Converts bool to its binary representation

                   @in   true: option is set
                         false: option is not set
                   @return  1 for true
                            0 for false
                */

                String checkBool(bool in) {
                        if(in) {
                                return "1";
                        } else {
                                return "0";
                        }
                }

                /**
                   Applies the font settings to the GUI
                */

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
                        Form1->Font->Charset = this->charset;
                        Form1->Panel2->Font->Charset = this->charset;
                        Form1->Panel2->Font->Name = this->name;
                        Form1->Panel2->Font->Size = this->size;
                        Form1->Panel2->Font->Style = this->style;
                        Form1->MemoChatInput->Constraints->MaxHeight = 3 * this->size * 2.0f;
                        Form1->MemoChatInput->Height = Form1->MemoChatInput->Constraints->MaxHeight;
                        WINDOW_SETTINGS->Font->Charset = this->charset;
                        WINDOW_LOCALGAME->Font->Charset = this->charset;
                }
};

/**
   Stores the current column width ratios of the Server and Player tables
*/

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

                /**
                   Constructor
                 */

                WindowSettings() {
                        init = false;
                }

                /**
                   If no stored information has been read before
                   (e.g. no config file), a default ratio will be returned:
                   'table width' / '# of columns'

                   @in  the ratio value to check
                   @grid  the stringgrid the column is part of
                          1: Server table
                          2: Player table
                */

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

                /**
                   Constructor
                   Input are the values read from the config file

                   @top  Top position of the window
                   @left  Left position of the window
                   @height  Height of the window
                   @width  Width of the window
                   @ratioID  ratio of the ID column
                   @ratioSN  ratio of the Server name column
                   @ratioPN  ratio of the Player number column
                   @ratioST  ratio of the Status column
                   @ratioIS  ratio of the Island column
                   @ratioMN  ratio of the Mission column
                   @ratioPI  ratio of the Ping column
                   @ratioPL  ratio of the Player name column
                   @ratioSC  ratio of the Score column
                   @ratioDE  ratio of the Deaths column
                   @ratioTE  ratio of the Team column
                   @devider  Height of the upper gui part
                 */
                 
                WindowSettings( int top, int left, int height, int width, float ratioID, float ratioSN,
                                float ratioPN, float ratioST, float ratioIS,
                                float ratioMN, float ratioPI, float ratioPL,
                                float ratioSC, float ratioDE, float ratioTE,
                                int devider) {
                        Form1->Position = poDesigned; 
                        Form1->Top = top;
                        Form1->Left = left;

                        if(height >= Form1->Constraints->MinHeight) {
                                Form1->Height = height;
                        }
                        if(width >= Form1->Constraints->MinWidth) {
                                Form1->Width = width;
                        }
                        if(devider < Form1->PageControl1->Constraints->MinHeight ||
                           devider > Form1->ClientHeight - (    Form1->StringGrid1->Constraints->MinHeight +
                                                                Form1->StatusBar1->Height +
                                                                Form1->Splitter1->Height)) {
                                Form1->PageControl1->Height = Form1->PageControl1->Constraints->MinHeight;
                        } else {
                                Form1->PageControl1->Height = devider;
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

                /**
                   Applies the current ratio values to the Stringtable columns
                 */

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
                }

                /**
                   Creates the section about the window settings that will be
                   written to the configuration file of the program
                */

                list<String> createFileEntry() {
                        list<String> output;
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
                        output.push_back("devider = " + String(Form1->PageControl1->Height));
                        output.push_back("[\\WindowSettings]");
                        return output;
                }

                /**
                   Calculates the current ratio values of the Stringgrid columns
                   This method is called after the user has changed a column width
                 */

                void updateGrid1() {
                        this->ratioID = (float)Form1->StringGrid1->ColWidths[0] / (float)Form1->StringGrid1->Width;
                        this->ratioSN = (float)Form1->StringGrid1->ColWidths[1] / (float)Form1->StringGrid1->Width;
                        this->ratioPN = (float)Form1->StringGrid1->ColWidths[2] / (float)Form1->StringGrid1->Width;
                        this->ratioST = (float)Form1->StringGrid1->ColWidths[3] / (float)Form1->StringGrid1->Width;
                        this->ratioIS = (float)Form1->StringGrid1->ColWidths[4] / (float)Form1->StringGrid1->Width;
                        this->ratioMN = (float)Form1->StringGrid1->ColWidths[5] / (float)Form1->StringGrid1->Width;
                        this->ratioPI = (float)Form1->StringGrid1->ColWidths[6] / (float)Form1->StringGrid1->Width;
                }

                /**
                   Calculates the current ratio values of the Stringgrid columns
                   This method is called after the user has changed a column width
                 */

                void updateGrid2() {
                        this->ratioPL = (float)Form1->StringGrid2->ColWidths[0] / (float)Form1->StringGrid2->Width;
                        this->ratioSC = (float)Form1->StringGrid2->ColWidths[1] / (float)Form1->StringGrid2->Width;
                        this->ratioDE = (float)Form1->StringGrid2->ColWidths[2] / (float)Form1->StringGrid2->Width;
                        this->ratioTE = (float)Form1->StringGrid2->ColWidths[3] / (float)Form1->StringGrid2->Width;
                }
};

/**
   After a query answer has been validated, its query details are read
   and stored in this object
*/

class QueryAnswer {
        public:
                String id;
                String part;
                bool final;
                list<String> content;

                /**
                   Constructor
                 */

                QueryAnswer () {
                        this->clear();
                }

                /**
                   Clears all object attributes
                 */

                void clear() {
                        this->id = "";
                        this->part = "";
                        this->final = false;
                        this->content.clear();
                }
};

/**
   This object keeps track of how the Server table is currently sorted
 */

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

                /**
                   Constructor
                 */

                Sorter() {
                        disableAll();
                        setPlayers();
                        normal = false;
                }

                /**
                   resets the attributes to default
                 */

                void reset() {
                        disableAll();
                        setPlayers();
                        normal = false;
                }

                /**
                   Sets all attributes false
                   'false' means that the table is not sorted after this column
                   'true' means that it is sorted after this column
                 */

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

                /**
                   The table will be sorted after IDs
                 */

                void setId() {
                        if(id) {
                                normal = !normal;
                        } else {
                                disableAll();
                                id = true;
                        }
                }

                /**
                   The table will be sorted alphabetically after Server names
                 */

                void setName() {
                        if(name) {
                                normal = !normal;
                        } else {
                                disableAll();
                                name = true;
                        }
                }

                /**
                   The table will be sorted after the number of players
                 */

                void setPlayers() {
                        if(players) {
                                normal = !normal;
                        } else {
                                disableAll();
                                players = true;
                        }
                }

                /**
                   The table will be sorted alphabetically after the server status
                 */

                void setStatus() {
                        if(status) {
                                normal = !normal;
                        } else {
                                disableAll();
                                status = true;
                        }
                }

                /**
                   The table will be sorted alphabetically after island names
                 */

                void setIsland() {
                        if(island) {
                                normal = !normal;
                        } else {
                                disableAll();
                                island = true;
                        }
                }

                /**
                   The table will be sorted alphabetically after mission names
                 */

                void setMission() {
                        if(mission) {
                                normal = !normal;
                        } else {
                                disableAll();
                                mission = true;
                        }
                }

                /**
                   The table will be sorted after pings
                 */

                void setPing() {
                        if(ping) {
                                normal = !normal;
                        } else {
                                disableAll();
                                ping = true;
                        }
                }
};

/**
   This object keeps track of how the Player table is currently sorted
 */

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

                /**
                   Sets all attributes false
                   'false' means that the table is not sorted after this column
                   'true' means that it is sorted after this column
                 */

                void disableAll() {
                        normal = true;
                        name = false;
                        score = false;
                        deaths = false;
                        team = false;
                }

                /**
                   The table will be sorted alphabetically after Player names
                 */

                void setName() {
                        if(name) {
                                normal = !normal;
                        } else {
                                disableAll();
                                name = true;
                        }
                }

                /**
                   The table will be sorted after scores
                 */

                void setScore() {
                        if(score) {
                                normal = !normal;
                        } else {
                                disableAll();
                                score = true;
                        }
                }

                /**
                   The table will be sorted after deaths
                 */

                void setDeaths() {
                        if(deaths) {
                                normal = !normal;
                        } else {
                                disableAll();
                                deaths = true;
                        }
                }

                /**
                   The table will be sorted alphabetically after Team names
                 */

                void setTeam() {
                        if(team) {
                                normal = !normal;
                        } else {
                                disableAll();
                                team = true;
                        }
                }
};

/**
   Object which holds all data of one player on a server
 */

class Player {
        public:
                String name;
                String team;
                int deaths;
                int score;

                /**
                   Default Constructor of a blank Player object
                 */

                Player() {
                        this->deaths = 0;
                        this->score = 0;
                        this->team = "";
                        this->name = "";
                }

                /**
                   Constructor

                   @n  player name
                   @t  team name
                   @s  score
                   @d  deaths

                 */
                Player(String &n, String &t, int &s, int &d) {
                        this->name = n;
                        this->team = t;
                        this->score = s;
                        this->deaths = d;
                }
};

typedef list<Player> CustomPlayerList;

int errorreports = 0;

/**
   Add an entry to the error report file

   @err  Type of error
   @msg  Additional debug output
 */

void addToErrorReport(String err, String msg) {
        if(err.SubString(1,6)== "Fehler" || err == "Exception InvalidInteger") {
                errorreports++;
                Form1->StatusBar1->Panels->Items[2]->Text = WINDOW_SETTINGS->getGuiString("STRING_ERRORS") + " " + String(errorreports);
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
        delete(error);
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

String getGameState (int i) {
        String out = IntToStr(i);
        if(i == SERVERSTATE_CREATING) {
                out = Form1->CHECKBOX_FILTER_CREATING->Caption;
        } else if(i == SERVERSTATE_WAITING) {
                out = Form1->CHECKBOX_FILTER_WAITING->Caption;
        } else if(i == SERVERSTATE_DEBRIEFING) {
                out = Form1->CHECKBOX_FILTER_DEBRIEFING->Caption;
        } else if(i == SERVERSTATE_SETTINGUP) {
                out = Form1->CHECKBOX_FILTER_SETTINGUP->Caption;
        } else if(i == SERVERSTATE_BRIEFING) {
                out = Form1->CHECKBOX_FILTER_BRIEFING->Caption;
        } else if(i == SERVERSTATE_PLAYING) {
                out = Form1->CHECKBOX_FILTER_PLAYING->Caption;
        }
        return out;
}


/**
   Representation of one server

 */

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
                long gametime;
                int players;
                int maxplayers;
                String mission;
                String name;
                int gamestate;
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
                bool autojoin;
                String autojoinConf;
                CustomPlayerList playerlist;
                QueryAnswer queries[queryArrayLength];
                int notificationRuleIndex;
                int missedQueryTurns;
                int emptyServerCounter;


                /**
                   Default Constructor of a blank server
                 */

                Server() {
                        this->watch = false;
                        this->index = -1;
                        this->ip = "";
                        this->gamespyport = 0;
                        this->timeouts = 0;
                        this->ping.clear();
                        this->clear();
                }

                /**
                   Constructor

                   @i  the server's ip
                   @p  the server's gamespy port
                   @ind  the server's index in the ServerArray
                 */

                Server(String i, int p, int ind) {
                        this->watch = false;
                        this->clear();
                        this->index = ind;
                        this->ip = i;
                        this->timeouts = 0;
                        this->ping.clear();
                        this->gamespyport = p;
                }

                /**
                   Clears all attributes, used to make servers invalid.
                   e.g. when they go offline
                 */

                void clear() {
                        this->autojoin = false;
                        this->autojoinConf = "";
                        this->gameport = 0;
                        this->timeleft = "";
                        this->gametime = 0;
                        this->players = 0;
                        this->maxplayers = 0;
                        this->mission = "";
                        this->name = "";
                        this->gamestate = 0;
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
                        this->notificationRuleIndex = -1;
                        this->missedQueryTurns = 0;
                        this->emptyServerCounter = 0;
                }
};


Server ServerArray[SERVERARRAY_LENGTH];
int numOfServers = 0;

Sorter tableSorter = Sorter();
Sorter2 playerListSorter = Sorter2();
WindowSettings windowsettings;
FontSettings fontsettings;
int timeoutLimit = 10;
TStringList *ServerSortList = new TStringList;
TStringList *PlayerSortList = new TStringList;
TStringList *PlayerSortList2 = new TStringList;

/**
   Gives Unit2, which loades the config file, access to the object
   storing the window settings of Form1
 */

void TForm1::setWindowSettings(int top,int left,int height, int width, float ratioID,float ratioSN,
                                float ratioPN,float ratioST,float ratioIS,
                                float ratioMN,float ratioPI,float ratioPL,
                                float ratioSC,float ratioDE,float ratioTE,
                                int devider) {
        windowsettings = WindowSettings(top,left,height,width,ratioID,ratioSN,
                                ratioPN,ratioST,ratioIS,
                                ratioMN,ratioPI,ratioPL,
                                ratioSC,ratioDE,ratioTE,
                                devider);
}

/**
   Gives Unit2, which loades the config file, access to the object
   storing the font settings
 */


void TForm1::setFont(String name, int size, int charset,
                        bool bold, bool italic) {
        fontsettings = FontSettings(name, size, charset, bold, italic);
}

/**
   Updates the Timer in Form1 when the config file is read, and/or the user sets
   a new timeout value in the settings window
 */

void updateTimeoutLimit() {
        timeoutLimit = ceil(10000 / Form1->Timer1->Interval);
}

/**
   Wrapping method around the Udp socket to send messages easier.
   The time of sending is stored in the corresponding server object
 */

void sendUdpMessage(int index, String ip, int port, String msg) {
        Form1->IdUDPServer1->Send(ip, port, msg);
        //Form1->Memo1->Lines->Add("sende: "+ ip + ":" + String(port)); 
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
    Checks if a name of the Players in list  l  contains the String s
    @return  result of the check. 'true' if at least
             one player name contains s, otherwise 'false'
 */

bool doPlayerFilter(CustomPlayerList l, String s) {
        bool out = false;
        for (CustomPlayerList::iterator ci = l.begin(); ci != l.end(); ++ci) {
                Player p = *ci;
                if(Form1->doNameFilter(p.name, s)) {
                        out = true;
                        break;
                }
        }
        return out;
}

/**
   Performs the checking of filter options that are available to the user
   Status checkboxes, password checkboxes, server, mission and player names

   @j  index of the server to check
   @return  number coded result of the check
            0 means: Server is offline/not set
            1 means: Server is online but does not pass the filter check
            2 means: Server is online and passes the filter check
            3 means: Server is marked for autojoin when game ends

 */

int checkFilters(int j) {
        int out = 0;
        if(ServerArray[j].autojoin) {
                out = 3;
        } else if(ServerArray[j].name.Length() > 0 && ServerArray[j].timeouts < timeoutLimit) {
                out = 1;
                if(ServerArray[j].players >= Form1->UpDown1->Position) {
                          
                        if(
                                (
                                        (ServerArray[j].gamestate == SERVERSTATE_PLAYING && Form1->CHECKBOX_FILTER_PLAYING->Checked) ||
                                        (ServerArray[j].gamestate == SERVERSTATE_WAITING && Form1->CHECKBOX_FILTER_WAITING->Checked) ||
                                        (ServerArray[j].gamestate == SERVERSTATE_CREATING && Form1->CHECKBOX_FILTER_CREATING->Checked) ||
                                        (ServerArray[j].gamestate == SERVERSTATE_BRIEFING && Form1->CHECKBOX_FILTER_BRIEFING->Checked) ||
                                        (ServerArray[j].gamestate == SERVERSTATE_DEBRIEFING && Form1->CHECKBOX_FILTER_DEBRIEFING->Checked) ||
                                        (ServerArray[j].gamestate == SERVERSTATE_SETTINGUP && Form1->CHECKBOX_FILTER_SETTINGUP->Checked)
                                ) && (
                                        (ServerArray[j].password == 1 && Form1->CHECKBOX_FILTER_WITHPASSWORD->Checked) ||
                                        (ServerArray[j].password == 0 && Form1->CHECKBOX_FILTER_WITHOUTPASSWORD->Checked)
                                )
                        ) {
                                bool missionfilter = true;
                                if(Form1->Edit1->Text.Trim().Length() > 0) {
                                        missionfilter = Form1->doNameFilter(ServerArray[j].mission,Form1->Edit1->Text);
                                }
                                if(missionfilter) {
                                        bool namefilter = true;
                                        if(Form1->Edit2->Text.Trim().Length() > 0) {
                                                namefilter = Form1->doNameFilter(ServerArray[j].name,Form1->Edit2->Text);
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

/**
   Empties the Server table
 */

void setEmptyStringGrid() {
        Form1->StringGrid1->RowCount = 2;
        for(int i = 0; i < Form1->StringGrid1->ColCount; i++) {
                Form1->StringGrid1->Cells[i][1] = "";
        }
}

/**
   Converts an integer to a String and adds "0"s to the front until the
   String is four characters long. Used to sort numbers alphabetically
   @i  number to convert
   @return  the number with leading zeros as a String
 */

String addLeadingZeros(int i) {
        String a = String(i);
        while (a.Length() < 4) {
                a = "0" + a;
        }
        return a;
}

/**
   Empties the Player table
 */

void setEmptyPlayerList() {
        Form1->StringGrid2->RowCount = 2;
        for(int i = 0; i < Form1->StringGrid2->ColCount; i++) {
                Form1->StringGrid2->Cells[i][1] = "";
        }
}

/**
   Performs the update of the Player table. Reads the index of the currently
   selected row in the server table, gets the player list and sorts it
   with the help of a TStringList

   @index  index (positive number) of the server , negativ number if the index
           couldnt be found   
 */

void processPlayerList(int index) {
        PlayerSortList->Clear();
        PlayerSortList2->Clear();
        int row = Form1->StringGrid1->Selection.BottomRight.Y;
        try {
                if(index < 0) {
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
        } catch (...) { }
        if(PlayerSortList->Count == 0) {
                setEmptyPlayerList();
        } else {
                int z = PlayerSortList->Count;
                int x = PlayerSortList2->Count;

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
}

/**
   Updates the Server Info part of the GUI

   @index  the index of the server
 */

void updateServerInfoBox(int index) {
        if(index >= 0 && index < numOfServers) {
                Form1->LABEL_SERVERINFO_IP_VALUE->Caption = ServerArray[index].ip;
                Form1->LABEL_SERVERINFO_PORT_VALUE->Caption = ServerArray[index].gamespyport - 1;
                Form1->LABEL_SERVERINFO_PLATFORM_VALUE->Caption = ServerArray[index].platform;
                Form1->LABEL_SERVERINFO_NAME->Caption = ServerArray[index].name;
                Form1->BUTTON_SERVERINFO_COPYADDRESS->Enabled = true;
                if(ServerArray[index].password) {
                        Form1->LABEL_SERVERINFO_PASSWORD_VALUE->Caption = WINDOW_SETTINGS->getGuiString("STRING_YES");
                } else {
                        Form1->LABEL_SERVERINFO_PASSWORD_VALUE->Caption = WINDOW_SETTINGS->getGuiString("STRING_NO");
                }
                if(ServerArray[index].equalMod) {
                        Form1->LABEL_SERVERINFO_EQMODREQ_VALUE->Caption = WINDOW_SETTINGS->getGuiString("STRING_YES");
                } else {
                        Form1->LABEL_SERVERINFO_EQMODREQ_VALUE->Caption = WINDOW_SETTINGS->getGuiString("STRING_NO");
                }
                                Form1->LABEL_SERVERINFO_VERSION_VALUE->Caption = IntToStr(ServerArray[index].reqver) + " / " + IntToStr(ServerArray[index].actver);
        } else {
                Form1->BUTTON_SERVERINFO_COPYADDRESS->Enabled = false;
                Form1->LABEL_SERVERINFO_NAME->Caption = " ";
                Form1->LABEL_SERVERINFO_IP_VALUE->Caption = " ";
                Form1->LABEL_SERVERINFO_PORT_VALUE->Caption = " ";
                Form1->LABEL_SERVERINFO_VERSION_VALUE->Caption = " ";
                Form1->LABEL_SERVERINFO_PLATFORM_VALUE->Caption = " ";
                Form1->LABEL_SERVERINFO_PASSWORD_VALUE->Caption = " ";
                Form1->LABEL_SERVERINFO_EQMODREQ_VALUE->Caption = " ";
        }
}

/**
   Calculates the average over a number of recorded pings

   @pings  list containing the pings
   @return  the average over all listed pings
 */

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

/**
   Returns the time differents between two timestamps (in seconds)
   Return format h:mm:ss

 */

String calcElapsedTime(long a, long b) {
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



bool filterChanging = false;

/**
   Performs the update of the GUI

   @userinput  'true' if the update was triggered
               by the user (e.g. changing filter rules)

 */
void filterChanged(bool userinput) {
        if(filterChanging) {
                return;
        }
        filterChanging = true;
        if(userinput) {
                WINDOW_SETTINGS->setSettingsChanged();
        }
        int row = Form1->StringGrid1->Selection.BottomRight.Y;
        int selectedIndex;
        try {
                AnsiString& cellValue = Form1->StringGrid1->Cells[0][row];
                if (cellValue.Length() > 0) {
                        selectedIndex = StrToInt(Form1->StringGrid1->Cells[0][row]);
                } else {
                        selectedIndex = -1;
                }
        } catch (...) {
                selectedIndex = -1;
        }
        ServerSortList->Clear();
        int inList = 1;
        int hasNoName = 0;
        int autojoin = -1;
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
                                ServerSortList->AddObject(ServerArray[j].gamestate, (TObject *) j);
                        } else if(tableSorter.island) {
                                ServerSortList->AddObject(ServerArray[j].island, (TObject *) j);
                        } else if(tableSorter.mission) {
                                ServerSortList->AddObject(ServerArray[j].mission, (TObject *) j);
                        } else if(tableSorter.ping) {
                                ServerSortList->AddObject(addLeadingZeros(averagePing(ServerArray[j].ping)), (TObject *) j);
                        }
                        inList++;
                } else if(abc == 3) {
                        inList++;
                        autojoin = j;
                } else if(abc == 0) {
                        hasNoName++;
                }
        }
        bool found = false;
        Form1->StatusBar1->Panels->Items[0]->Text = WINDOW_SETTINGS->getGuiString("STRING_LISTED") + " " + String(numOfServers);
        Form1->StatusBar1->Panels->Items[1]->Text = WINDOW_SETTINGS->getGuiString("STRING_ONLINE") + " " + String(numOfServers - hasNoName);
        if(inList == 1) {
                setEmptyStringGrid();
                setEmptyPlayerList();
                updateServerInfoBox(-1);
        } else {
                for(int i = 1; i < inList; i++) {
                        int k = i;
                        int j = 0;
                        if(autojoin < 0) {
                                TObject *t = ServerSortList->Objects[0];
                                j = (int)t;
                                if(!tableSorter.normal) {
                                        if(autojoin < -1) {
                                                k = abs(inList - i + 1);
                                        } else {
                                                k = abs(inList - i);
                                        }
                                }
                        } else {
                                j = autojoin;
                        }
                        Form1->StringGrid1->Cells[0][k] = " " + String(ServerArray[j].index);
                        Form1->StringGrid1->Cells[1][k] = ServerArray[j].name;
                        Form1->StringGrid1->Cells[2][k] = String(ServerArray[j].players) + " / " + String(ServerArray[j].maxplayers);
                        String gs = getGameState(ServerArray[j].gamestate);

                        if(ServerArray[j].gametime > 0) {
                                gs += " " + calcElapsedTime(ServerArray[j].gametime, time(0));
                        }

                        Form1->StringGrid1->Cells[3][k] = gs;
                        Form1->StringGrid1->Cells[4][k] = ServerArray[j].island;
                        Form1->StringGrid1->Cells[5][k] = ServerArray[j].mission;
                        Form1->StringGrid1->Cells[6][k] = String(averagePing(ServerArray[j].ping));
                        if(autojoin < 0) {
                                ServerSortList->Delete(0);
                        } else {
                                autojoin = -2;
                        }
                }
                Form1->StringGrid1->RowCount = inList;

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
                Form1->CoolTrayIcon1->Hint = ServerArray[selectedIndex].name + "     " + getGameState(ServerArray[selectedIndex].gamestate) + "     " +  String(ServerArray[selectedIndex].players) + " Players";
        } else {
                Form1->CoolTrayIcon1->Hint = "OFPMonitor";
        }
        filterChanging = false;
}

/**
   Reads an internet address "IP:Port" in string format
   and returns an Address object
 */

Address getAddress(String address) {
        for(int i = 0; i < address.Length(); i++) {
                if(address.SubString(i,1) == ":") {
                        try {
                                String ip = address.SubString(0,i - 1);
                                int port = StrToInt(address.SubString(i + 1, address.Length() - i));
                                return Address(ip, port);
                        } catch (...) {
                                break;
                        }
                }
        }
        return Address();
}

/**
   Reads an list of server internet addresses and sets up the ServerArray
 */

void TForm1::readServerList(list<String> &servers) {
        Form1->StatusBar1->Panels->Items[0]->Text = "";
        Form1->StatusBar1->Panels->Items[1]->Text = "";
        TStringList *watched = WINDOW_SETTINGS->getWatchedList();
        numOfServers = 0;
        while (servers.size() > 0) {
                String tmp = servers.front();
                if(tmp.Length() > 8) {
                        Address a = getAddress(tmp);
                        if(!a.ip.IsEmpty()) {
                                ServerArray[numOfServers] = Server(a.ip, a.port, numOfServers);
                                ServerArray[numOfServers].watch = (watched->IndexOf(a.ip+ ":" + String(a.port)) > -1);
                                numOfServers++;
                        }
                }
                servers.pop_front();
        }
        for(int i = numOfServers; i < GetArrLength(ServerArray); i++) {
                if(ServerArray[i].index == -1) {
                        break;
                } else {
                        ServerArray[i] = Server();
                }
        }
        if(numOfServers == 0) {
                MENUITEM_MAINMENU_GETNEWSERVERLIST->Click();
        }
}

/**
   Converts an String into a list of Strings by using 'split' as seperator
 */

list<String> TForm1::splitUpMessage(String msg, String split) {
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

/**
   Removes all elements of list b and adds them in order to the end of list a
 */

void mergeLists(list<String> &a, list<String> &b) {
        while(b.size() > 0) {
                String tmp = b.front();
                a.push_back(tmp);
                b.pop_front();
        }
}

/**
   Plays an wavefile for the the new status of a server, if it's marked for watch
 */

void playAudioServerStatus(int i, int newStatus) {
        if(ServerArray[i].watch) {
                int j = 0;
                if(newStatus == SERVERSTATE_CREATING) {
                        j = 1;
                } else if(newStatus == SERVERSTATE_WAITING) {
                        j = 2;
                } else if(newStatus == SERVERSTATE_BRIEFING) {
                        j = 3;
                } else if(newStatus == SERVERSTATE_PLAYING) {
                        j = 4;
                } else if(newStatus == SERVERSTATE_DEBRIEFING) {
                        j = 5;
                }
                if(j > 0) {
                        PlaySound(PChar(j), NULL, SND_RESOURCE | SND_ASYNC);
                }
        }
}

/**
   Disables autojoin for all servers. Used before setting up a server for autojoin,
   to make sure that it's active for one server only.
 */

void disableAutoJoin() {
        for(int i = 0; i < GetArrLength(ServerArray); i++) {
                if(ServerArray[i].index < 0) {
                        break;
                }
                ServerArray[i].autojoin = false;
                ServerArray[i].autojoinConf = "";
        }
}

/**
   Launches OFP with the passed start up configuration
 */

void startTheGame(String configuration, int actVer, int reqVer) {
        String exe = WINDOW_SETTINGS->getExe(actVer, reqVer);
        if(FileExists(exe)) {
                ShellExecute(NULL, "open", PChar(exe.c_str()), PChar(configuration.c_str()), PChar(WINDOW_SETTINGS->getExeFolder(actVer, reqVer).c_str()), SW_NORMAL);
        }
}

/**
   Checks a received query answer for validity and processes it then
 */

bool readInfoPacket(int i, String msg, String ip, int port) {
        bool out = false;
        list<String> a = Form1->splitUpMessage(msg,"\\");
        if(a.size() <= 1) {
                return false;
        }
        String idstring = a.back();
        a.pop_back();
        String querystring = a.back();
        bool final = false;
        a.pop_back();

        if(querystring == "queryid" && a.size()%2 == 0) {
                list<String> b = Form1->splitUpMessage(idstring,".");
                if(b.size() == 2) {
                        int id = 0;
                        int part = 1;
                        try {
                                id = StrToInt(b.front());
                                part = StrToInt(b.back());
                        } catch (...) {
                                return false;
                        }
                        list<String> tmp;
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

        list<String> answer;
        bool success = false;
        if(final) {
                bool correct = true;
                int endingIndex = -1;
                for(int j = 0; j < queryArrayLength && correct; j++) {
                        try {
                                correct = (ServerArray[i].queryid == StrToInt(ServerArray[i].queries[j].id));
                        } catch (...) {
                                correct = false;
                        }
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
                        return false;
                }
        }

        bool players = false;
                if(ServerArray[i].ip == ip && ServerArray[i].gamespyport == port && success) {
                        bool once = true;
                        int counter = answer.size();
                        for (list<String>::iterator ci = answer.begin(); ci != answer.end(); ++ci) {
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
                                                try {
                                                        ServerArray[i].gameport = StrToInt(*ci);
                                                } catch (...) {}
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
                                                try {
                                                        ServerArray[i].players = StrToInt(*ci);
                                                        if(once && ServerArray[i].players == 0) {
                                                                while(!ServerArray[i].playerlist.empty()) {
                                                                        Player *t = &(ServerArray[i].playerlist.front());
                                                                        delete t;
                                                                        ServerArray[i].playerlist.pop_front();
                                                                }
                                                                once = false;
                                                        }
                                                } catch (...) {}
                                        } else if (tmp == "maxplayers") {
                                                ++ci;
                                                counter--;
                                                try {
                                                        ServerArray[i].maxplayers = StrToInt(*ci) - 2;
                                                } catch (...) {}
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
                                                try {
                                                        ServerArray[i].actver = StrToInt(*ci);
                                                } catch (...) {}
                                        } else if (tmp == "reqver") {
                                                ++ci;
                                                counter--;
                                                try {
                                                        ServerArray[i].reqver = StrToInt(*ci);
                                                } catch (...) {}
                                        } else if (tmp == "mod") {
                                                ++ci;
                                                counter--;
                                                String m = *ci;
                                                if(m.SubString(1,3) == "RES") {
                                                        m = m.SubString(4, m.Length() - 3);
                                                }
                                                if(m.SubString(1,1) == ";") {
                                                        m = m.SubString(2, m.Length() - 1);
                                                }
                                                ServerArray[i].mod = m;
                                        } else if (tmp == "equalModRequired") {
                                                ++ci;
                                                counter--;
                                                try {
                                                        ServerArray[i].equalMod = StrToInt(*ci);
                                                } catch (...) {}
                                        } else if (tmp == "password") {
                                                ++ci;
                                                counter--;
                                                try {
                                                        ServerArray[i].password = StrToInt(*ci);
                                                } catch (...) {}
                                        } else if (tmp == "gstate") {
                                                ++ci;
                                                counter--;
                                                int oldStatus = ServerArray[i].gamestate;
                                                try {
                                                        int newStatus = StrToInt(*ci);
                                                        if(ServerArray[i].gamestate != newStatus) {
                                                                playAudioServerStatus(i, newStatus);
                                                                if(oldStatus == SERVERSTATE_BRIEFING && newStatus == SERVERSTATE_PLAYING) {
                                                                        ServerArray[i].gametime = time(0);
                                                                } else {
                                                                        ServerArray[i].gametime = 0;
                                                                }
                                                                if(oldStatus == SERVERSTATE_PLAYING &&
                                                                   newStatus != SERVERSTATE_PLAYING &&
                                                                   ServerArray[i].autojoin) {
                                                                        ServerArray[i].autojoin = false;
                                                                        startTheGame(ServerArray[i].autojoinConf, ServerArray[i].actver, ServerArray[i].reqver);
                                                                        disableAutoJoin();
                                                                }
                                                        }
                                                        ServerArray[i].gamestate = newStatus;
                                                } catch (...) {}
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
                        if(WINDOW_SETTINGS->areCustomNotificationsEnabled()) {
                                list<String> playerList;
                                for (list<Player>::iterator ci = ServerArray[i].playerlist.begin(); ci != ServerArray[i].playerlist.end(); ++ci) {
                                        playerList.push_back((*ci).name);
                                }
                                int now = WINDOW_SETTINGS->checkNotifications(ServerArray[i].name,
                                                        ServerArray[i].players,
                                                        ServerArray[i].gamestate,
                                                        ServerArray[i].mission,
                                                        ServerArray[i].password,
                                                        playerList);
                                if(now == -1 && ServerArray[i].notificationRuleIndex >= -1) {
                                        int old = ServerArray[i].notificationRuleIndex;
                                        ServerArray[i].notificationRuleIndex = now;
                                        WINDOW_SETTINGS->MP3remove(old);
                                } else if(ServerArray[i].notificationRuleIndex == -1 && now >= -1) {
                                        ServerArray[i].notificationRuleIndex = now;
                                        WINDOW_SETTINGS->MP3add(ServerArray[i].notificationRuleIndex);
                                }
                        }
                }
        return out;
}

/**
   Copys a String to the clipboard of the OS
 */

 
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
}

/**
   Object for settings concerning the chat
 */

class ChatSettings {
        public:
                String host;
                int port;
                String channel;
                String userName;
                bool autoConnect;
                int connectionLost;
                bool doConnect;
                ChatSettings() {
                        this->host = "irc.freenode.net";
                        this->port = 6666;
                        this->channel = "operationflashpoint1";
                        this->userName = "";
                        this->setAutoConnect(false);
                        this->connectionLost = 0;
                        this->doConnect = false;
                }

                ChatSettings(String h, int p, String c, String user, bool ac) {
                        this->host = h;
                        this->port = p;
                        this->channel = c;
                        this->userName = user;
                        this->setAutoConnect(ac);
                        this->connectionLost = 0;
                        this->doConnect = false;
                }

                void setAutoConnect(bool ac) {
                        this->autoConnect = ac;
                }

                /**
                   Creates the section about the chat settings that will be
                   written to the configuration file of the program
                */

                list<String> createFileEntry() {
                        list<String> output;
                        output.push_back("[ChatSettings]");
                        output.push_back("Host = " + this->host);
                        output.push_back("Port = " + String(this->port));
                        output.push_back("Channel = " + this->channel);
                        output.push_back("UserName = " + this->userName);
                        output.push_back("AutoConnect = " + this->checkBool(this->autoConnect));
                        output.push_back("[\\ChatSettings]");
                        return output;
                }
        private:
                String checkBool(bool in) {
                        if(in) {
                                return "1";
                        } else {
                                return "0";
                        }
                }
};

ChatSettings chatsettings;
TStringList *blockedChatUsers = new TStringList();

/**
   Gives Unit2, which loades the config file, access to the object
   storing the chat settings
 */

void TForm1::setChat(String host, int port, String channel, String user, bool autoConnect) {
        chatsettings = ChatSettings(host, port, channel, user, autoConnect);
}

/**
   Checks if a certain name is on the list of blocked users
 */

bool TForm1::isChatUserBlocked(String username) {
        int index;
        return blockedChatUsers->Find(username, index);
}

String TForm1::getChatHost() {
        return chatsettings.host;
}

String TForm1::getChatChannel() {
        return chatsettings.channel;
}

int TForm1::getChatPort() {
        return chatsettings.port;
}

String TForm1::getChatUserName() {
        return chatsettings.userName;
}

bool TForm1::getChatAutoConnect() {
        return chatsettings.autoConnect;
}
/**
   Does a notification because of a new chat messages.
   If the chat window is not visible, a ballon hint will be displayed 
 */

void TForm1::ChatNotification(String msg) {
        if(!Form1->Visible || PageControl1->TabIndex != TABSHEET_CHAT->PageIndex) {
                CoolTrayIcon1->HideBalloonHint();
                Form1->CoolTrayIcon1->ShowBalloonHint(WideString("OFPMonitor " + TABSHEET_CHAT->Caption), WideString(msg), bitInfo, 3);
        }
}

void TForm1::ChatConnectionLost() {
        chatsettings.connectionLost = 1;
}

/**
   Checks if a certain notification rule @index
   is set for any server at the moment
 */

bool TForm1::isNotificationRuleActive(int index) {
        for(int i = 0; i < GetArrLength(ServerArray); i++) {
                if(ServerArray[i].index < 0) {
                        break;
                }
                if(ServerArray[i].notificationRuleIndex == index) {
                        return true;
                }
        }
        return false;
}


void TForm1::resetNotifications(int notificationIndex) {
        for(int i = 0; i < GetArrLength(ServerArray); i++) {
                if(ServerArray[i].index < 0) { break; }
                if(ServerArray[i].notificationRuleIndex == notificationIndex ||
                        notificationIndex == -1) {
                        ServerArray[i].notificationRuleIndex = -1;
                }
        }
}

int getSelectedServer() {
        return Form1->StringGrid1->Tag;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Application->OnMinimize = OnMinimize;
        windowsettings = WindowSettings(0,0,0,0,0.0f, 0.0f,0.0f, 0.0f,
                                0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f, 0);
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
        blockedChatUsers->Sorted = true;
        blockedChatUsers->CaseSensitive = true;
        blockedChatUsers->Duplicates = dupIgnore;
        updateTimeoutLimit();
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
        if(!z.IsEmpty()) {
                int index = -1;
                try {
                        index = StrToInt(z);
                        StringGrid1->Tag = index;
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
        Timer1->Enabled = false;
        Application->ProcessMessages();
        filterChanged(false);
        processPlayerList(-1);
        Timer2->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        Form1->Enabled = false;
        if(MENUITEM_MAINMENU_CHAT_DISCONNECT->Enabled) {
                MENUITEM_MAINMENU_CHAT_DISCONNECT->Click();
        }
        WINDOW_SETTINGS->MP3shutdown();
        Timer2->Enabled = false;
        Timer1->Enabled = false;
        delete ServerSortList;
        delete PlayerSortList;
        delete PlayerSortList2;
        delete blockedChatUsers;
        list<String> servers;
        list<String> watched;
        for(int i = 0; i < GetArrLength(ServerArray); i++) {
                if(ServerArray[i].index == -1) {
                        break;
                }
                String tmp = ServerArray[i].ip + ":" + String(ServerArray[i].gamespyport);
                if(ServerArray[i].watch) {
                        watched.push_back(tmp);
                } else {
                        servers.push_back(tmp);
                }
        }
        WINDOW_SETTINGS->writeSettingToFile(servers, watched, fontsettings.createFileEntry(), windowsettings.createFileEntry(), chatsettings.createFileEntry());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BUTTON_SERVERINFO_COPYADDRESSClick(TObject *Sender)
{
        copyToClipBoard(LABEL_SERVERINFO_IP_VALUE->Caption + ":" + LABEL_SERVERINFO_PORT_VALUE->Caption);
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
                        WINDOW_SETTINGS->setSettingsChanged();
                }
        } else if(Button == mbRight && Y >= StringGrid1->DefaultRowHeight) {
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
                                list<String> t = splitUpMessage(ServerArray[index].mod,";");

                                PopupMenu1->Items->Items[0]->Tag = index;
                                PopupMenu1->Items->Items[1]->Tag = index;
                                PopupMenu1->Items->Items[1]->Visible = (ServerArray[index].gamestate == SERVERSTATE_PLAYING) && !ServerArray[index].autojoin;
                                PopupMenu1->Items->Items[2]->Visible = ServerArray[index].autojoin;
                                PopupMenu1->Items->Items[2]->Checked = ServerArray[index].autojoin;
                                PopupMenu1->Items->Items[2]->Tag = index;
                                PopupMenu1->Items->Items[3]->Tag = index;
                                PopupMenu1->Items->Items[4]->Tag = index;
                                PopupMenu1->Items->Items[4]->OnClick = ClickWatchButton;
                                PopupMenu1->Items->Items[4]->Checked = ServerArray[index].watch;
                                int i = 0;
                                for (list<String>::iterator ci = t.begin(); ci != t.end(); ++ci) {
                                        if(!(*ci).IsEmpty()) {
                                                TMenuItem *m = PopupMenu1->Items->Items[3]->Items[i];
                                                m->Caption = *ci;
                                                m->Visible = true;
                                                i++;
                                        }
                                }
                                PopupMenu1->Items->Items[3]->Enabled = (i > 0);
                                for(; i < PopupMenu1->Items->Items[3]->Count; i++) {
                                        TMenuItem *m = PopupMenu1->Items->Items[3]->Items[i];
                                        m->Visible = false;
                                }
                                PopupMenu1->Tag = index;
                                PopupMenu1->Popup(Form1->Left + StringGrid1->Left + X + 5,Form1->Top + StringGrid1->Top + Y + StringGrid1->DefaultRowHeight + 25);
                        } catch (...) {}
                }
        }
        StringGrid1->Refresh();
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
        int index = PopupMenu1->Tag;
        int additionalItems = 2;

        TMenuItem *join;
        TMenuItem *autojoin;

        int i = 0;
        for(i = 0; i < additionalItems; i++) {
                join = PopupMenu1->Items->Items[0]->Items[i];
                autojoin = PopupMenu1->Items->Items[1]->Items[i];
                join->Tag = i - additionalItems;
                autojoin->Tag = i - additionalItems;
                if(i == 0) {
                        join->OnClick = ClickJoinButton;
                        autojoin->OnClick = ClickAutoJoinConfButton;
                        join->Enabled = !(ServerArray[index].equalMod == 1 && !ServerArray[index].mod.IsEmpty());
                        autojoin->Enabled = join->Enabled;
                        join->Visible = true;
                        autojoin->Visible = true;
                } else if(i == 1) {
                        join->OnClick = ClickJoinButton;
                        autojoin->OnClick = ClickAutoJoinConfButton;
                        join->Visible = ServerArray[index].equalMod;
                        autojoin->Visible = join->Visible;
                }
        }
        int gameid = WINDOW_SETTINGS->getGameId(ServerArray[index].actver, ServerArray[index].reqver);
        MENUITEM_POPUP_JOIN->Enabled = (gameid >= 0);
        MENUITEM_POPUP_AUTOJOIN->Enabled = (gameid >= 0);
        MENUITEM_POPUP_AUTOJOINB->Enabled = (gameid >= 0);
        for(i = additionalItems; i - additionalItems < WINDOW_SETTINGS->getConfAmount(gameid) || i < PopupMenu1->Items->Items[0]->Count; i++) {
                String s = "";
                if(gameid >= 0) {
                        s = WINDOW_SETTINGS->getConfListEntry(gameid, i - additionalItems);
                }
                if(!s.IsEmpty()) {
                        if(i < PopupMenu1->Items->Items[0]->Count) {
                                join = PopupMenu1->Items->Items[0]->Items[i];
                        } else {
                                join = new TMenuItem(this);
                                PopupMenu1->Items->Items[0]->Add(join);
                        }
                        if(i < PopupMenu1->Items->Items[1]->Count) {
                                autojoin = PopupMenu1->Items->Items[1]->Items[i];
                        } else {
                                autojoin = new TMenuItem(this);
                                PopupMenu1->Items->Items[1]->Add(autojoin);
                        }
                        join->Tag = i - additionalItems;
                        join->Caption = s;
                        join->Visible = true;
                        join->OnClick = ClickJoinButton;

                        autojoin->Tag = i - additionalItems;
                        autojoin->Caption = s;
                        autojoin->Visible = true;
                        autojoin->OnClick = ClickAutoJoinConfButton;

                        String modline = WINDOW_SETTINGS->getConfModLine(gameid, i - additionalItems);
                        join->Enabled = !(ServerArray[index].equalMod == 1 && modline != ServerArray[index].mod);
                        autojoin->Enabled = join->Enabled;
                } else {
                        if(i < PopupMenu1->Items->Items[0]->Count) {
                                PopupMenu1->Items->Items[0]->Items[i]->Visible = false;
                                PopupMenu1->Items->Items[1]->Items[i]->Visible = false;
                        }
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClickJoinButton(TObject *Sender)
{
        disableAutoJoin();
        TMenuItem *a = (TMenuItem *) Sender;
        int index = a->Parent->Tag;
        int port = ServerArray[index].gameport;
        String ip = ServerArray[index].ip;
        int gameid = WINDOW_SETTINGS->getGameId(ServerArray[index].actver, ServerArray[index].reqver);
        if(gameid >= 0) {
                String playername = WINDOW_SETTINGS->getPlayerName(ServerArray[index].actver, ServerArray[index].reqver);
                bool found = false;
                for (CustomPlayerList::iterator ci = ServerArray[index].playerlist.begin(); ci != ServerArray[index].playerlist.end(); ++ci) {
                        Player p = *ci;
                        if(p.name == playername) {
                                found = true;
                                break;
                        }
                }
                int zz = 6;
                if(found) {
                        zz = MessageBoxA(NULL, WINDOW_SETTINGS->getGuiString("STRING_PLAYER_ALREADY_ON_SERVER").c_str(),
                                    "", MB_YESNO | MB_ICONQUESTION);
                }
                if(zz == 6) {

                        if(a->Tag >= 0 && a->Tag < WINDOW_SETTINGS->getConfAmount(gameid)) {
                                startTheGame(WINDOW_SETTINGS->getConfStartLine(gameid, a->Tag, ip, port), ServerArray[index].actver, ServerArray[index].reqver);
                        } else if(a->Tag == -2) {
                                startTheGame(WINDOW_SETTINGS->getNoModsStartLine(gameid, ip, port), ServerArray[index].actver, ServerArray[index].reqver);
                        } else if(a->Tag == -1) {
                                startTheGame(WINDOW_SETTINGS->getSameModsStartLine(gameid, ip, port, ServerArray[index].mod), ServerArray[index].actver, ServerArray[index].reqver);
                        }
                }
        }
}
//---------------------------------------------------------------------------
  void __fastcall TForm1::ClickAutoJoinConfButton(TObject *Sender)
{
        disableAutoJoin();
        TMenuItem *a = (TMenuItem *) Sender;
        int index = a->Parent->Tag;
        int gameid = WINDOW_SETTINGS->getGameId(ServerArray[index].actver, ServerArray[index].reqver);
        if(gameid >= 0) {
                ServerArray[index].autojoin = true;
                if(a->Tag >= 0 && a->Tag < WINDOW_SETTINGS->getConfAmount(gameid)) {
                        ServerArray[index].autojoinConf = WINDOW_SETTINGS->getConfStartLine(gameid, a->Tag, ServerArray[index].ip, ServerArray[index].gameport);
                } else if(a->Tag == -2) {
                        ServerArray[index].autojoinConf = WINDOW_SETTINGS->getNoModsStartLine(gameid, ServerArray[index].ip, ServerArray[index].gameport);
                } else if(a->Tag == -1) {
                        ServerArray[index].autojoinConf = WINDOW_SETTINGS->getSameModsStartLine(gameid, ServerArray[index].ip, ServerArray[index].gameport, ServerArray[index].mod);
                }
        }
        StringGrid1->Refresh();
        filterChanged(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClickWatchButton(TObject *Sender)
{
        TMenuItem *a = (TMenuItem *) Sender;
        int index = a->Tag;
        a->Checked = !(a->Checked);
        ServerArray[index].watch = a->Checked;
        TStringList *watched = WINDOW_SETTINGS->getWatchedList();
        if(ServerArray[index].watch) {
                watched->Add(ServerArray[index].ip + ":" + String(ServerArray[index].gamespyport));
        } else {
                int i = watched->IndexOf(ServerArray[index].ip + ":" + String(ServerArray[index].gamespyport));
                if(i > -1) {
                        watched->Delete(i);
                }
        }
        StringGrid1->Refresh();
        playAudioServerStatus(index, ServerArray[index].gamestate);
        WINDOW_SETTINGS->setSettingsChanged();
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
        } else if(Key == VK_F13) {
                CoolTrayIcon1->ShowMainForm();
        } else if(Key == VK_F2) {
                WINDOW_SETTINGS->CHECKBOX_NOTIFICATIONS_ACTIVE->Checked = !WINDOW_SETTINGS->CHECKBOX_NOTIFICATIONS_ACTIVE->Checked;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        if(ACol > 0 && ARow > 0 && !(StringGrid1->Cells[0][ARow]).Trim().IsEmpty()) {
                int zelle = ARow;
                try {
                        int index = StrToInt((StringGrid1->Cells[0][zelle]).Trim());
                        TColor mark = WINDOW_SETTINGS->getMarkingColor(ServerArray[index].notificationRuleIndex);
                        if(mark != NULL || ServerArray[index].watch || ServerArray[index].autojoin) {
                                StringGrid1->Canvas->Font->Color = clWhite;
                                if(mark != NULL) {
                                        StringGrid1->Canvas->Brush->Color = mark;
                                } else if(ServerArray[index].watch) {
                                        StringGrid1->Canvas->Brush->Color = clBlue;
                                } else if(ServerArray[index].autojoin) {
                                        StringGrid1->Canvas->Brush->Color = clRed;
                                }
                                StringGrid1->Canvas->FillRect(Rect);
                                Rect.Left = Rect.Left + 2;
                                DrawText(StringGrid1->Canvas->Handle, StringGrid1->Cells[ACol][ARow].c_str(),
                                                -1, &Rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
                        }
                } catch (...) {}
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
        Form1->Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_GETNEWSERVERLISTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_GETNEWSERVERLIST->Enabled = false;
        Timer1->Enabled = false;
        Timer2->Enabled = false;
        setEmptyStringGrid();
        setEmptyPlayerList();
        updateServerInfoBox(-1);
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

        TStringList *games = WINDOW_SETTINGS->getGameSpyGames();
        for (int k = 0; k < games->Count; k++) {
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
        }
        list<String> addresses;
        while(CurrentList->Count > 0) {
                addresses.push_back(CurrentList->Strings[0]);
                CurrentList->Delete(0);
        }
        if(addresses.size() > 0) {
                readServerList(addresses);
        }
        delete CurrentList;
        delete games;
        WINDOW_SETTINGS->setSettingsChanged();
        Timer2->Enabled = true;
        MENUITEM_MAINMENU_GETNEWSERVERLIST->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_FONTClick(TObject *Sender)
{
        FontDialog1->Font = StringGrid1->Font;
        FontDialog1->Execute();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
        StringGrid2->Width = TABSHEET_SERVERINFO->PageControl->Pages[0]->Width - (GROUPBOX_SERVERINFO->Width + 5);
        StringGrid1->Width = Form1->ClientWidth;
        PageControl1->Height = Form1->ClientHeight - (StatusBar1->Height + StringGrid1->Height + Splitter1->Height);
        if(windowsettings.init) {
                windowsettings.refresh();
        }
        WINDOW_SETTINGS->setSettingsChanged();
        StatusBar1->Realign();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        windowsettings.updateGrid1();
        if(Button == mbLeft && Y < StringGrid1->DefaultRowHeight) {
                WINDOW_SETTINGS->setSettingsChanged();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        windowsettings.updateGrid2();
        if(Button == mbLeft && Y < StringGrid2->DefaultRowHeight) {
                WINDOW_SETTINGS->setSettingsChanged();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FontDialog1Apply(TObject *Sender, HWND Wnd)
{
        fontsettings.name = FontDialog1->Font->Name;
        fontsettings.size = FontDialog1->Font->Size;
        fontsettings.charset = FontDialog1->Font->Charset;
        fontsettings.style = FontDialog1->Font->Style;
        fontsettings.update();
        WINDOW_SETTINGS->setSettingsChanged();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_POPUP_AUTOJOINBClick(TObject *Sender)
{
        disableAutoJoin();
        StringGrid1->Refresh();
        filterChanged(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
        int X = StringGrid1->ColWidths[0] + StringGrid1->ColWidths[1];
        int Y = (StringGrid1->DefaultRowHeight + 1) * (StringGrid1->Selection.Top - StringGrid1->TopRow + 1) + (StringGrid1->DefaultRowHeight/2);
        Form1->StringGrid1MouseDown(Sender, mbRight, TShiftState(), X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Splitter1Moved(TObject *Sender)
{
        Application->ProcessMessages();
        WINDOW_SETTINGS->setSettingsChanged();
        Form1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Info1Click(TObject *Sender)
{
        WINDOW_INFO->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerIrcChatTimerTimer(TObject *Sender)
{
        if(chatsettings.connectionLost == 1) {
                chatsettings.connectionLost = 2;
                MemoChatOutput->Lines->Add(WINDOW_SETTINGS->getGuiString("STRING_CHAT_CONNECTIONLOST"));
                MENUITEM_MAINMENU_CHAT_DISCONNECT->Click();
                MENUITEM_MAINMENU_CHAT_CONNECT->Click();
        } else {
                chat_client_timercallback( this );
        }
        if(chatsettings.doConnect) {
                chatsettings.doConnect = false;
                bool result = chat_client_connect();
                if(!result) {
                        MemoChatOutput->Lines->Add(WINDOW_SETTINGS->getGuiString("STRING_CHAT_CONNECTINGFAILED"));
                } else {
                        MemoChatInput->Clear();
                }
                MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = !result;
                MENUITEM_MAINMENU_CHAT_DISCONNECT->Enabled = result;
                MemoChatInput->Enabled = result;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_CONNECTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = false;
        Form1->PageControl1->ActivePage = Form1->TABSHEET_CHAT;
        if(chatsettings.connectionLost == 0) {
                MemoChatOutput->Lines->Add(WINDOW_SETTINGS->getGuiString("STRING_CHAT_CONNECTINGTO") +
                        "  " + Form1->getChatHost() + ":" + String(Form1->getChatPort()));
                MemoChatOutput->Lines->Add(WINDOW_SETTINGS->getGuiString("STRING_CHAT_CHANNEL") +
                        "  " + Form1->getChatChannel());
        }
        chatsettings.doConnect = true;
        TimerIrcChatTimer->Enabled = true;
        chatsettings.connectionLost = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_DISCONNECTClick(TObject *Sender)
{
        MemoChatInput->Enabled = false;
        MENUITEM_MAINMENU_CHAT_DISCONNECT->Enabled = false;
        ShowMessage("vor connectionLost: " + String(chatsettings.connectionLost));
        chat_client_disconnect();
        ShowMessage("nach connectionLost: " + String(chatsettings.connectionLost));
        TimerIrcChatTimer->Enabled = false;
        StringGrid3->RowCount = 0;
        StringGrid3->Cells[0][0] = "";
        StringGrid3->Cells[0][1] = "";
        if(chatsettings.connectionLost == 0) {
                MemoChatOutput->Lines->Add(WINDOW_SETTINGS->getGuiString("STRING_CHAT_DISCONNECTED"));
        }

        ShowMessage("xx_" + WINDOW_SETTINGS->getGuiString("STRING_CHAT_DISCONNECTED") + "_xx");
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_CLEARLOGClick(TObject *Sender)
{
        MemoChatOutput->Clear();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_SAVETOFILEClick(TObject *Sender)
{
        SaveDialog1->Execute();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveDialog1CanClose(TObject *Sender,
      bool &CanClose)
{
        TStringList *log = new TStringList;
        for(int i = 0; i < MemoChatOutput->Lines->Count; i++) {
                log->Add(MemoChatOutput->Lines->Strings[i]);
        }
        log->SaveToFile(SaveDialog1->FileName);
        log->Clear();
        delete log;
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
                int col, row;
                StringGrid3->MouseToCell(X, Y, col, row);
                String userToBlock = StringGrid3->Cells[col][row];
                int index = -1;
                if(blockedChatUsers->Find(userToBlock, index)) {
                        blockedChatUsers->Delete(index);
                } else {
                        blockedChatUsers->Add(userToBlock);
                }
                StringGrid3->Repaint();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid3DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        StringGrid3->Canvas->Font->Color = clBlack;
        StringGrid3->Canvas->Brush->Color = clWindow;
        if(Form1->isChatUserBlocked(StringGrid3->Cells[ACol][ARow])) {
                StringGrid3->Canvas->Font->Color = clWhite;
                StringGrid3->Canvas->Brush->Color = clBlack;
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
void __fastcall TForm1::MemoChatOutputChange(TObject *Sender)
{
        if(PageControl1->TabIndex != TABSHEET_CHAT->PageIndex) {
                TABSHEET_CHAT->Highlighted = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MemoChatInputKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_RETURN) {
                String input = "";
                for(int i = 0; i < Form1->MemoChatInput->Lines->Count; i++) {
                        input += Form1->MemoChatInput->Lines->Strings[i];
                }
                MemoChatInput->Clear();
                if(!input.Trim().IsEmpty()) {
                        chat_client_pressedReturnKey(this, input.c_str());
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MemoChatInputKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_RETURN) {
                MemoChatInput->Clear();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_LOCALGAMEClick(TObject *Sender)
{
        WINDOW_LOCALGAME->ShowModal();        
}
//---------------------------------------------------------------------------
                                  
void __fastcall TForm1::IdUDPServer1UDPRead(TObject *Sender,
      TStream *AData, TIdSocketHandle *ABinding)
{
        DWORD i = timeGetTime();
        char buf[2048];
        int size = AData->Size;
        if(size < 2048) {
                AData->ReadBuffer(buf, size);
                buf[size] = 0;
                String content = String(buf);
                bool handled = false;
                for(int j = 0; j < GetArrLength(ServerArray); j++) {
                        if(ServerArray[j].index == -1) {
                                break;
                        }
                        if(ServerArray[j].ip == ABinding->PeerIP && ServerArray[j].gamespyport == ABinding->PeerPort) {
                                handled = true;
                                if(readInfoPacket(j, content, ABinding->PeerIP, ABinding->PeerPort)) {
                                        if(ServerArray[j].players > 0) {
                                                ServerArray[j].emptyServerCounter = 0;
                                        } else {
                                                if(ServerArray[j].emptyServerCounter < 5) {
                                                        ServerArray[j].emptyServerCounter++;
                                                }
                                        }
                                        if(ServerArray[j].messageSent > 1) {
                                                int curr = i - ServerArray[j].messageSent;
                                                if(ServerArray[j].ping.size() > 1) {
                                                        ServerArray[j].ping.pop_front();
                                                }
                                                ServerArray[j].ping.push_back(curr);
                                                ServerArray[j].messageSent = 0;
                                                ServerArray[j].timeouts = 0;
                                        }
                                        break;
                                }
                                if(!handled) {
                                        addToErrorReport("Non-handled message", String(ABinding->PeerIP) + ":" + String(ABinding->PeerPort) + "   =>   " + content);
                                }
                        }
                }
              //  messageReader.newMessage(Message(ABinding->PeerIP,ABinding->PeerPort,buf,i));
        } else {
                addToErrorReport("Fehler 1","Receiving buffer too small. Current: 2048. Received: " + IntToStr(size) + " Bytes");
        }
        free(buf);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
        int serverIndex = Timer2->Tag;
        serverIndex++;
        if(ServerArray[serverIndex].ip.IsEmpty()) {
                Timer2->Enabled = false;
                Timer1->Enabled = true;
                serverIndex = -1;
                Application->ProcessMessages();
                filterChanged(false);
                processPlayerList(-1);
        }
        Timer2->Tag = serverIndex;
        if(serverIndex >= 0) {
                int i = serverIndex;
                if(     ServerArray[i].missedQueryTurns >= ServerArray[i].emptyServerCounter ||
                        ServerArray[i].players > 0) {
                        String query = "\\info\\rules\\";
                        if(ServerArray[i].name.IsEmpty() || ServerArray[i].players != ServerArray[i].playerlist.size() || i == getSelectedServer()) {
                                query = "\\info\\rules\\players\\";
                        }
                        sendUdpMessage(i, ServerArray[i].ip, ServerArray[i].gamespyport, query);
                        ServerArray[i].missedQueryTurns = 0;
                } else {
                        ServerArray[i].missedQueryTurns++;
                }
        }
}
//---------------------------------------------------------------------------


