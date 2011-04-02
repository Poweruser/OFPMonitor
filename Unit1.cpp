//---------------------------------------------------------------------------
#include <vcl.h>
#include <list>
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
#pragma link "trayicon"
#pragma resource "*.dfm"
#pragma resource "wavefiles.res"
#pragma resource "XP.res"
TForm1 *Form1;

#define SERVERSTATE_CREATING 2
#define SERVERSTATE_WAITING 6
#define SERVERSTATE_DEBRIEFING 9
#define SERVERSTATE_SETTINGUP 12
#define SERVERSTATE_BRIEFING 13
#define SERVERSTATE_PLAYING 14

#define SERVERARRAY_LENGTH 256

typedef list<String> CustomStringList;

/**                                                                                       
   Macro to retrieve the length of an array
 */

template<typename T, int size>
int GetArrLength(T(&)[size]){return size;}


TNMUDP *udpSocket;

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
   Each incoming answer of a server query will be first stored in a
   Message-Object, which holds all important information about it
   (IP, Port, Content, Time of arrival) and will be later procressed
   by the MessageReader
 */

class Message {
        public:
                String content;
                String ip;
                int port;
                DWORD toa;

                /**
                   Constructor

                   @ip  the ip the message came from
                   @port  the port it came from
                   @content  the message data
                   @toa  time the message arrived at
                         (is used to measure the ping)
                */

                Message(String ip, int port, String content, DWORD toa) {
                        this->ip = ip;
                        this->port = port;
                        this->content = content;
                        this->toa = toa;
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
                        WINDOW_NOTIFICATIONS->updateFontSettings(this->charset);
                        return;
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
                        return;
                }

                /**
                   Creates the section about the window settings that will be
                   written to the configuration file of the program
                */

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
                        return;
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
                        return;
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
                CustomStringList content;

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
const unsigned int queryArrayLength = 10;
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
        return;
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
                bool loseATurn;
                CustomPlayerList playerlist;
                QueryAnswer queries[queryArrayLength];

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

                Server(String &i, int &p, int &ind) {
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
                        this->loseATurn = false;
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
        return;
}

/**
   Wrapping method around the Udp socket to send messages easier.
   The time of sending is stored in the corresponding server object
 */

void sendUdpMessage(int index, String ip, int port, String msg) {
        if(udpSocket != NULL) {
                char buffer[256];
                int len;
                strcpy(buffer,msg.c_str());
                len=strlen(buffer);
                udpSocket->RemotePort = port;
                udpSocket->RemoteHost = ip;
                udpSocket->SendBuffer(buffer,256,len);
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
        return;
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
        return;
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
        return;
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
        return;
}

/**
   Updates the Server Info part of the GUI

   @index  the index of the server
 */

void updateServerInfoBox(int index) {
        if(index >= 0 && index < numOfServers) {
                Form1->Label2->Caption = ServerArray[index].ip;
                Form1->Label4->Caption = ServerArray[index].gamespyport - 1;
                Form1->Label9->Caption = ServerArray[index].platform;
                //Form1->Label18->Caption = ServerArray[index].impl;
                Form1->Label21->Caption = ServerArray[index].name;
                Form1->BUTTON_SERVERINFO_COPYADDRESS->Enabled = true;
                int a = ServerArray[index].password;
                if(a == 0) {
                        Form1->Label11->Caption = WINDOW_SETTINGS->getGuiString("STRING_NO");
                } else if(a == 1) {
                        Form1->Label11->Caption = WINDOW_SETTINGS->getGuiString("STRING_YES");
                }
                Form1->Label13->Caption = ServerArray[index].actver;
        } else {
                Form1->BUTTON_SERVERINFO_COPYADDRESS->Enabled = false;
                Form1->Label2->Caption = " ";
                Form1->Label4->Caption = " ";
                Form1->Label9->Caption = " ";
                //Form1->Label18->Caption = " ";
                Form1->Label21->Caption = " ";
                Form1->Label11->Caption = " ";
                Form1->Label13->Caption = " ";
        }
        return;
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
                selectedIndex = StrToInt(Form1->StringGrid1->Cells[0][row]);
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
                Form1->TrayIcon1->Hint = ServerArray[selectedIndex].name + "     " + getGameState(ServerArray[selectedIndex].gamestate) + "     " +  String(ServerArray[selectedIndex].players) + " Players";
        } else {
                Form1->TrayIcon1->Hint = "OFPMonitor";
        }
        filterChanging = false;
        return;
}

/**
   This class makes sure that the query of only one server is sent at a time, by
   providing the index of one server and only increasing it, when the query
   of the server before has been successfully sent.
 */

class BroadcastRotation {
        public:
                int current;
                bool receivingFirstTime;
                bool loseTurnValue;
                bool IsReady;
                BroadcastRotation() {
                        this->reset();
                }

                /**
                   Resets the object to its start values
                */

                void reset() {
                        this->current = -1;
                        this->IsReady = true;
                        this->receivingFirstTime = true;
                        this->loseTurnValue = false;
                }

                /**
                   Decides which server is the next one to query
                   @return  index of the server in the ServerArray
                 */

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

                /**
                   Marks this object as Ready, meaning that the current
                   server query has been successfully procressed

                */

                void setReady() {
                        this->IsReady = true;
                        return;
                }

                /**
                   Used to distribute the "loseATurn" flags evenly among empty
                   servers, when querying them the first time. Results in lower
                   peaks of bandwidth usage
                 */

                bool loseTurn() {
                        this->loseTurnValue = !this->loseTurnValue;
                        return this->loseTurnValue;
                }

                /**
                   Returns the current state of the object 
                 */

                bool isReady() {
                        return this->IsReady;
                }
};

BroadcastRotation serverCycle = BroadcastRotation();

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

void TForm1::readServerList(CustomStringList &servers) {
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
        return;
}

/**
   Converts an String into a list of Strings by using 'split' as seperator
 */

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

/**
   Removes all elements of list b and adds them in order to the end of list a
 */

void mergeLists(CustomStringList &a, CustomStringList &b) {
        while(b.size() > 0) {
                String tmp = b.front();
                a.push_back(tmp);
                b.pop_front();
        }
        return;
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
        return;
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
        return;
}

/**
   Launches OFP with the passed start up configuration
 */

void startTheGame(String configuration) {
        ShellExecute(NULL, "open", PChar(WINDOW_SETTINGS->getExe().c_str()), PChar(configuration.c_str()), PChar(WINDOW_SETTINGS->getExeFolder().c_str()), SW_NORMAL);
}

/**
   Checks a received query answer for validity and processes it then
 */

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
                        int id = 0;
                        int part = 1;
                        try {
                                id = StrToInt(b.front());
                                part = StrToInt(b.back());
                        } catch (...) {
                                return false;
                        }
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
                                                ServerArray[i].mod = *ci;
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
                                                                        startTheGame(ServerArray[i].autojoinConf);
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

                                WINDOW_NOTIFICATIONS->checkNotifications(i,
                                                        ServerArray[i].name,
                                                        ServerArray[i].players,
                                                        ServerArray[i].gamestate,
                                                        ServerArray[i].mission,
                                                        ServerArray[i].password,
                                                        playerList);



                                /*
                                  String servername, int players, int status,
                                String missionname, bool passworded,
                                list<String> playerlist) {
                                */
                        }


                }

        return out;
}

/**
   This MessageReader makes sure that new incoming messages are procressed
   after each other (serial) and not at the same time (parallel). This resolves
   some concurrent access issues on the storing data structures.
 */

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
                                                                if(ServerArray[j].ping.size() > 1) {
                                                                        ServerArray[j].ping.pop_front();
                                                                }
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
        return;
}

class MP3Job {
    public:
        list<int> serverIndex;
        int notificationIndex;
        bool set;
        bool started;
        bool stopped;
        String file;
        String alias;
        int volume;
        int start;
        int end;
        bool error;
        TColor markColor;

        MP3Job() {
                this->set = false;

        }

        MP3Job(int index, int serverindex, String file, String alias, int volume, int start, int end, TColor color) {
                this->serverIndex.push_back(serverindex);
                this->notificationIndex = index;
                this->error = false;
                this->file = file;
                this->alias = alias;
                this->volume = volume;
                this->start = start;
                this->end = end;
                this->started = false;
                this->stopped = false;
                this->markColor = color;
                this->set = true;
        }

        void play() {
                if(0 != mciSendString(("Open \"" + this->file + "\" alias " + this->alias).c_str(),0,0,0)) {
                        this->error = true;
                }
                if(0 != mciSendString(("play " + this->alias + " from " + String(this->start) + " to " + String(this->end)).c_str(), 0, 0, 0)) {
                        this->error = true;
                }
                if(0 != mciSendString(("setaudio " + this->alias + " volume to " + String(this->volume)).c_str(), 0, 0, 0)) {
                        this->error = true;
                }
                this->started = true;
        }

        bool hasEnded() {
                char text[128];
                mciSendString(("status " + this->alias + " position").c_str(), text, 128, 0);
                int pos = 0;
                try {
                        pos = StrToInt(String(text));
                } catch (...) {
                }
                return (pos >= this->end || this->error || this->stopped);
        }

        void stop() {
                mciSendString(("Close " + this->alias).c_str(),0,0,0);
                this->stopped = true;
        }
};


class MP3Player {
    public:
        MP3Job jobs[5];

        MP3Player() {}

        void queueMP3(MP3Job job) {
                bool alreadyPlaying = false;
                int index = -1;
                for(int i = 0; i < 5; i++) {
                        if(!alreadyPlaying) {
                                alreadyPlaying = this->jobs[i].set &&
                                        (this->jobs[i].alias == job.alias ||
                                         this->jobs[i].notificationIndex == job.notificationIndex) &&
                                        !this->jobs[i].hasEnded();
                        }
                        if(alreadyPlaying) {
                                index = i;
                                break;
                        }
                        if(!this->jobs[i].set && index <= 0) {
                                index = i;
                        }
                }
                if(index != -1) {
                        if(!alreadyPlaying) {
                                this->jobs[index] = job;
                                this->jobs[index].play();
                                Form1->MP3Timer->Enabled = true;
                        } else {
                                bool alreadyIn = false;
                                for (list<int>::iterator ci = jobs[index].serverIndex.begin(); ci != jobs[index].serverIndex.end(); ++ci) {
                                        if(job.serverIndex.front() == *ci) {
                                                alreadyIn = true;
                                                break;
                                        }
                                }
                                if(!alreadyIn) {
                                        jobs[index].serverIndex.push_back(job.serverIndex.front());
                                }
                        }
                }
                return;
        }

        bool check() {
                bool hasJob = false;
                for(int i = 0; i < 5; i++) {
                        if(jobs[i].set) {
                                hasJob = true;
                                if(jobs[i].hasEnded()) {
                                        jobs[i].stop();
                                        if(String("OFPM_MP3PREVIEW") == jobs[i].alias) {
                                                WINDOW_NOTIFICATIONS->STOP->Click();
                                        }
                                        jobs[i] = MP3Job();
                                } else if(String("OFPM_MP3PREVIEW") == jobs[i].alias) {
                                        char text[128];
                                        mciSendString("status OFPM_MP3PREVIEW position", text, 128,0);
                                        String out = "";
                                        int minutes = StrToInt(text);
                                        int milliseconds = minutes % 1000;
                                        WINDOW_NOTIFICATIONS->LabelMilli->Caption = IntToStr(milliseconds);
                                        minutes = (minutes - milliseconds)/1000;
                                        int seconds = minutes % 60;
                                        if(seconds < 10) {
                                                WINDOW_NOTIFICATIONS->LabelSeconds->Caption = "0" + IntToStr(seconds) + ":";
                                        } else {
                                                WINDOW_NOTIFICATIONS->LabelSeconds->Caption = IntToStr(seconds) + ":";
                                        }
                                        minutes = (minutes - seconds) / 60;
                                        if(minutes < 10) {
                                                WINDOW_NOTIFICATIONS->LabelMinutes->Caption = "0" + IntToStr(minutes)+ ":";
                                        } else {
                                                WINDOW_NOTIFICATIONS->LabelMinutes->Caption = IntToStr(minutes)+ ":";
                                        }
                                }
                        }
                }
                return hasJob;
        }

        void stopMP3Job(String alias) {
                for(int i = 0; i < 5; i++) {
                        if(jobs[i].set) {
                                if(jobs[i].alias == alias || alias == "any") {
                                        jobs[i].stop();
                                        jobs[i] = MP3Job();
                                }
                        }
                }
                return;
        }

        TColor getMarkingColor(int serverindex) {
                for(int i = 0; i < 5; i++) {
                        if(jobs[i].set) {
                                if(!jobs[i].hasEnded()) {
                                        for (list<int>::iterator ci = jobs[i].serverIndex.begin(); ci != jobs[i].serverIndex.end(); ++ci) {
                                                if(serverindex == *ci) {
                                                        return jobs[i].markColor;
                                                }
                                        }
                                }
                        }
                }
                return NULL;
        }
};

MP3Player mp3p = MP3Player();

void TForm1::createMP3Job(int index, int serverindex, String file, String alias, int volume, int start, int end, TColor color) {
        mp3p.queueMP3(MP3Job(index, serverindex, file, alias, volume, start, end, color));
}

void TForm1::stopMP3Job(String alias) {
        mp3p.stopMP3Job(alias);
}

class ChatSettings {
        public:
                String host;
                int port;
                String channel;
                bool autoConnect;
                ChatSettings() {
                        this->host = "irc.freenode.net";
                        this->port = 6666;
                        this->channel = "operationflashpoint1";
                        this->setAutoConnect(false);
                }

                ChatSettings(String h, int p, String c, bool ac) {
                        this->host = h;
                        this->port = p;
                        this->channel = c;
                        this->setAutoConnect(ac);
                }

                void setAutoConnect(bool ac) {
                        this->autoConnect = ac;
                        if(Form1 != NULL) {
                                Form1->MENUITEM_MAINMENU_CHAT_AUTOCONNECT->Checked = ac;
                        }
                }

                /**
                   Creates the section about the chat settings that will be
                   written to the configuration file of the program
                */

                CustomStringList createFileEntry() {
                        CustomStringList output;
                        output.push_back("[ChatSettings]");
                        output.push_back("Host = " + this->host);
                        output.push_back("Port = " + String(this->port));
                        output.push_back("Channel = " + this->channel);
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

/**
   Gives Unit2, which loades the config file, access to the object
   storing the chat settings
 */

void TForm1::setChat(String host, int port, String channel, bool autoConnect) {
        chatsettings = ChatSettings(host, port, channel, autoConnect);
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

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
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
        updateTimeoutLimit();
        udpSocket = new TNMUDP(Form1);
        udpSocket->ReportLevel = 5;
        udpSocket->LocalPort = 0;
        udpSocket->RemotePort = 2303;
        udpSocket->RemoteHost = "localhost";
        udpSocket->OnDataReceived = UDPSocketDataReceived;
        udpSocket->OnDataSend = UDPSocketDataSend;
        Timer3->Enabled = true;
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
                try {
                        int index = StrToInt(z);
                        processPlayerList(index);
                        updateServerInfoBox(index);
                } catch (...) { }
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
        chat_client_disconnect();
        mp3p.stopMP3Job("any");
        Timer1->Enabled = false;
        Timer3->Enabled = false;
        delete ServerSortList;
        delete PlayerSortList;
        delete PlayerSortList2;
        CustomStringList servers;
        CustomStringList watched;
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
        WINDOW_SETTINGS->writeSettingToFile(servers, watched, fontsettings.createFileEntry(), windowsettings.createFileEntry(), chatsettings.createFileEntry(), WINDOW_NOTIFICATIONS->getFileEntry());
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
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
        messageReader.checkForNewMessages();
        if(serverCycle.isReady()) {
                int a = serverCycle.next();
                if(a >= 0) {
                        if(ServerArray[a].players > 0 || ServerArray[a].name.IsEmpty()) {
                                sendUdpMessage(a, ServerArray[a].ip,ServerArray[a].gamespyport,"\\info\\rules\\players\\");
                        } else {
                                sendUdpMessage(a, ServerArray[a].ip,ServerArray[a].gamespyport,"\\info\\rules\\");
                        }
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
                                CustomStringList t = splitUpMessage(ServerArray[index].mod,";");

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
                                for (CustomStringList::iterator ci = t.begin(); ci != t.end(); ++ci) {
                                        TMenuItem *m = PopupMenu1->Items->Items[3]->Items[i];
                                        m->Caption = *ci;
                                        m->Visible = true;
                                        i++;
                                }
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
        boolean isOFPR = WINDOW_SETTINGS->isOFPResistance();
        for(int i = 0; i < WINDOW_SETTINGS->getConfAmount() || i < PopupMenu1->Items->Items[0]->Count; i++) {
                String s = WINDOW_SETTINGS->getConfListEntry(i);
                if(!s.IsEmpty()) {
                        TMenuItem *join;
                        TMenuItem *autojoin;
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
                        join->Tag = i;
                        join->Caption = s;
                        join->Visible = true;
                        join->OnClick = ClickJoinButton;

                        autojoin->Tag = i;
                        autojoin->Caption = s;
                        autojoin->Visible = true;
                        autojoin->OnClick = ClickAutoJoinConfButton;

                        String modline = WINDOW_SETTINGS->getConfModLine(i);
                        if(isOFPR) {
                                if(modline.Length() > 0) {
                                        modline = ";" + modline;
                                }
                                modline = "RES" + modline;
                        }
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
        String playername = WINDOW_SETTINGS->getCurrentPlayerName();

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
              startTheGame(WINDOW_SETTINGS->getConfStartLine(a->Tag,ip, port));
        }
}
//---------------------------------------------------------------------------
  void __fastcall TForm1::ClickAutoJoinConfButton(TObject *Sender)
{
        disableAutoJoin();
        TMenuItem *a = (TMenuItem *) Sender;
        int index = a->Parent->Tag;
        ServerArray[index].autojoin = true;
        ServerArray[index].autojoinConf = WINDOW_SETTINGS->getConfStartLine(a->Tag, ServerArray[index].ip, ServerArray[index].gameport);
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
        } else if(Key == VK_RETURN) {
                TrayIcon1->Restore();
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
                        TColor mark = mp3p.getMarkingColor(index);
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
        CustomStringList addresses;
        while(CurrentList->Count > 0) {
                addresses.push_back(CurrentList->Strings[0]);
                CurrentList->Delete(0);
        }
        if(addresses.size() > 0) {
                readServerList(addresses);
        }
        delete CurrentList;
        WINDOW_SETTINGS->setSettingsChanged();
        Timer3->Enabled = true;
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
void __fastcall TForm1::MENUITEM_MAINMENU_NOTIFICATIONS_SETTINGSClick(TObject *Sender)
{
        WINDOW_NOTIFICATIONS->ShowModal();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVEClick(TObject *Sender)
{
        MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVE->Checked = !MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVE->Checked;
        WINDOW_SETTINGS->setCustomNotifications(MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVE->Checked);
        WINDOW_SETTINGS->setSettingsChanged();
        if(!MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVE->Checked) {
                mp3p.stopMP3Job("any");
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MP3TimerTimer(TObject *Sender)
{
        MP3Timer->Enabled = mp3p.check();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Info1Click(TObject *Sender)
{
        WINDOW_INFO->ShowModal();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UDPSocketDataReceived(TComponent *Sender,
      int NumberBytes, AnsiString FromIP, int Port)
{
        const int bytes = 2048;
        int len;
        if(NumberBytes < bytes) {
                DWORD i = timeGetTime();
                char buffer[bytes];
                udpSocket->ReadBuffer(buffer,bytes,len);
                buffer[len] = 0;
                String buf = String(buffer);
                messageReader.newMessage(Message(FromIP,Port,buf,i));
        } else {
                addToErrorReport("Fehler 1","Receiving buffer too small. Current: 2048. Received: " + String(NumberBytes) + " Bytes");
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UDPSocketDataSend(TObject *Sender)
{
        serverCycle.setReady();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
        if(udpSocket != NULL) {
              udpSocket->Free();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerIrcChatTimerTimer(TObject *Sender)
{
        chat_client_timercallback( this );        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_CONNECTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = false;
        Form1->PageControl1->ActivePage = Form1->TABSHEET_CHAT;
        MemoChatOutput->Lines->Add("Connecting to:  " + Form1->getChatHost() + ":" + String(Form1->getChatPort()));
        MemoChatOutput->Lines->Add("Channel:  " + Form1->getChatChannel());
        TimerIrcChatTimer->Enabled = true;
        bool result = chat_client_connect();
        if(!result) {
                MemoChatOutput->Lines->Add("Connecting failed.");
        }
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = !result;
        MENUITEM_MAINMENU_CHAT_DISCONNECT->Enabled = result;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_DISCONNECTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_CHAT_DISCONNECT->Enabled = false;
        chat_client_disconnect();
        TimerIrcChatTimer->Enabled = false;
        StringGrid3->RowCount = 0;
        StringGrid3->Cells[0][0] = "";
        StringGrid3->Cells[0][1] = "";
        MemoChatOutput->Lines->Add("Disconnected.");
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MemoChatInputKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_RETURN) {
                String input = "";
                for(int i = 0; i < Form1->MemoChatInput->Lines->Count; i++) {
                        input += Form1->MemoChatInput->Lines->Strings[i];
                }
                chat_client_pressedReturnKey(this, input.c_str());
                MemoChatInput->Clear();
        }
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
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_AUTOCONNECTClick(TObject *Sender)
{
        chatsettings.autoConnect = MENUITEM_MAINMENU_CHAT_AUTOCONNECT->Checked;
        WINDOW_SETTINGS->setSettingsChanged();
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


