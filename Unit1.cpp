//---------------------------------------------------------------------------

#include "QueryAnswer.h"                                                                    
#include "OFPMonitor.h"
#include "Address.h"
#include "Player.h"
#include "Server.h"
#include "Message.h"
#include "Sorter.h"
#include "irc/irc.h"
#include "ProcessFinder.h"

#include ".\gamespy\msquery_header.h"
#include <vcl.h>
#include <list.h>
#include <mmsystem.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CoolTrayIcon"
#pragma resource "*.dfm"
#pragma resource "wavefiles.res"

TForm1 *Form1;

using namespace OFPMonitor_Unit1;

HANDLE getServerListThread;



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
                        WINDOW_UPDATE->Font->Charset = this->charset;
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


typedef list<Player> CustomPlayerList;
int errorreports = 0;

/**
   Add an entry to the error report file

   @err  Type of error
   @msg  Additional debug output
 */

void addToErrorReport(String err, String msg) {
        if(err.SubString(1,5)== "Error") {
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
        switch (i) {
                case SERVERSTATE_CREATING:
                        out = Form1->CHECKBOX_FILTER_CREATING->Caption;
                        break;
                case SERVERSTATE_WAITING:
                        out = Form1->CHECKBOX_FILTER_WAITING->Caption;
                        break;
                case SERVERSTATE_DEBRIEFING:
                        out = Form1->CHECKBOX_FILTER_DEBRIEFING->Caption;
                        break;
                case SERVERSTATE_SETTINGUP:
                        out = Form1->CHECKBOX_FILTER_SETTINGUP->Caption;
                        break;
                case SERVERSTATE_BRIEFING:
                        out = Form1->CHECKBOX_FILTER_BRIEFING->Caption;
                        break;
                case SERVERSTATE_PLAYING:
                        out = Form1->CHECKBOX_FILTER_PLAYING->Caption;
                        break;
        }
        return out;
}

Server ServerArray[SERVERARRAY_LENGTH];
int numOfServers = 0;

class GameControl {
        private:
                ProcessInfo proc;
                int serverIndex;
                String serverIP;
                int serverPort;
                bool autoGreenUp;
                int greenUpDelay;
                bool greenUpRepeat;

        public:

                bool restoreGame;
                bool restoreOnCreating;
                bool restoreOnWaiting;
                bool restoreOnBriefing;
                bool restoreOnPlaying;
                bool restoreOnDebriefing;

                GameControl() {
                        this->autoGreenUp = false;
                        this->restoreGame = false;
                        this->serverPort = 0;
                        this->serverIP = "";
                        this->serverIndex = -1;
                        this->greenUpDelay = 10;
                        this->restoreOnCreating = false;
                        this->restoreOnWaiting = false;
                        this->restoreOnBriefing = false;
                        this->restoreOnPlaying = false;
                        this->restoreOnDebriefing = false;
                }
                void setProcess(ProcessInfo *p) {
                        this->proc.pid = p->pid;
                        this->proc.hWindow = p->hWindow;
                        this->proc.title = p->title;
                        this->proc.moduleName = p->moduleName;
                }

                void setServer(int id, String ip, int port) {
                        this->serverIndex = id;
                        this->serverIP = ip;
                        this->serverPort = port;
                }

                bool verifyProcess() {
                        bool out = false;
                        if(this->proc.pid > 0 &&
                           !this->proc.title.IsEmpty() &&
                           !this->proc.moduleName.IsEmpty()) {
                                ProcessFinder *pf = new ProcessFinder();
                                TStringList *startsWith = new TStringList();
                                startsWith->Add(this->proc.title);
                                TStringList *modules = new TStringList();
                                modules->Add(this->proc.moduleName);
                                pf->enumerate(startsWith, modules);
                                for (list<ProcessInfo>::iterator ci = pf->output.begin(); ci != pf->output.end(); ++ci) {
                                        if((*ci).pid == this->proc.pid &&
                                           (*ci).title == this->proc.title &&
                                           (*ci).moduleName == this->proc.moduleName) {
                                                out = true;
                                        }                  
                                }
                                delete pf;
                                delete startsWith;
                                delete modules;
                                if(!out) {
                                        this->proc.clear();
                                        Form1->BUTTON_GAMECONTROL_REFRESH->Click();
                                }
                        }
                        return out;
                }

                bool verifyServer(int serverId) {
                        bool out = this->matchesServer(serverId);
                        if(!out) {
                                this->serverIndex = -1;
                                this->serverPort = 0;
                                this->serverIP = "";
                                Form1->BUTTON_GAMECONTROL_REFRESH->Click();
                        }
                        return out;
                }

                void statusChange(int serverId, int oldStatus, int newStatus) {
                        if(this->matchesServer(serverId)) {
                                if(this->verifyProcess() && this->verifyServer(serverId)) {
                                        if(this->autoGreenUp) {
                                                if(newStatus == SERVERSTATE_BRIEFING) {
                                                        if(!Form1->TimerAutoGreenUp->Enabled) {
                                                                Form1->TimerAutoGreenUp->Interval = this->greenUpDelay * 1000;
                                                                Form1->TimerAutoGreenUp->Tag = serverId;
                                                                Form1->TimerAutoGreenUp->Enabled = true;
                                                        }
                                                } else {
                                                        Form1->TimerAutoGreenUp->Enabled = false;
                                                        Form1->TimerAutoGreenUp->Tag = -1;
                                                }
                                        }
                                        if(this->restoreGame) {
                                                if((oldStatus != SERVERSTATE_CREATING &&
                                                        newStatus == SERVERSTATE_CREATING &&
                                                        this->restoreOnCreating) ||
                                                        (oldStatus != SERVERSTATE_WAITING &&
                                                        newStatus == SERVERSTATE_WAITING &&
                                                        this->restoreOnWaiting) ||
                                                        (oldStatus != SERVERSTATE_BRIEFING &&
                                                        newStatus == SERVERSTATE_BRIEFING &&
                                                        this->restoreOnBriefing) ||
                                                        (oldStatus != SERVERSTATE_PLAYING &&
                                                        newStatus == SERVERSTATE_PLAYING &&
                                                        this->restoreOnPlaying) ||
                                                        (oldStatus != SERVERSTATE_DEBRIEFING &&
                                                        newStatus == SERVERSTATE_DEBRIEFING &&
                                                        this->restoreOnDebriefing)) {
                                                                ShowWindowAsync(this->proc.hWindow, SW_RESTORE);
                                                }
                                        }
                                }
                        }
                }

                void setGreenUpRepeat(bool enabled) {
                        this->greenUpRepeat = enabled;
                }

                bool getGreenUpRepeat() {
                        return this->greenUpRepeat;
                }

                void enableAutoGreenUp(bool enabled) {
                        this->autoGreenUp = enabled;
                }

                void enableRestoreGame(bool enabled) {
                        this->restoreGame = enabled;
                }

                void setGreenUpDelay(int delay) {
                        this->greenUpDelay = delay;
                }

                void sendGreenUpMessage(int serverId) {
                        if(this->verifyProcess() && this->verifyServer(serverId)) {
                                if(ServerArray[serverId].gamestate == SERVERSTATE_BRIEFING) {
                                        SendMessage(this->proc.hWindow, WM_KEYDOWN, VK_RETURN, NULL);
                                        SendMessage(this->proc.hWindow, WM_KEYUP  , VK_RETURN, NULL);
                                }
                        }
                }

                bool matchesProcess(ProcessInfo *p) {
                        bool out = false;
                        if(this->proc.pid > 0 &&
                           !this->proc.title.IsEmpty() &&
                           !this->proc.moduleName.IsEmpty()) {
                                if(this->proc.pid == p->pid &&
                                   this->proc.title == p->title &&
                                   this->proc.moduleName == p->moduleName) {
                                        out = true;
                                }
                        }
                        return out;
                }

                bool matchesServer(int serverId) {
                        bool out = false;
                        if(         serverId >= 0 &&          serverId < SERVERARRAY_LENGTH &&
                           this->serverIndex >= 0 && this->serverIndex < SERVERARRAY_LENGTH) {
                                if(ServerArray[serverId].ip == this->serverIP &&
                                   ServerArray[serverId].gamespyport == this->serverPort) {
                                        out = true;
                                }
                        }
                        return out;
                }
};

ServerSorter tableSorter = ServerSorter();
PlayerSorter playerListSorter = PlayerSorter();
WindowSettings windowsettings;
FontSettings fontsettings;
GameControl gameControl = GameControl();
int timeoutLimit = 10;
TStringList *ServerSortList = new TStringList;
TStringList *ServerFavoriteSortList = new TStringList;
TStringList *PlayerSortList = new TStringList;
TStringList *PlayerSortList2 = new TStringList;

Server* TForm1::getServer(int i) {
        if(i >= 0 && i < SERVERARRAY_LENGTH) {
                return &(ServerArray[i]);
        }
        return NULL;
}

bool TForm1::addServer(String ip, int gameport) {
        bool added = false;
        for(int i = 0; i < SERVERARRAY_LENGTH; i++) {
                if(ServerArray[i].ip.IsEmpty() ) {
                        ServerArray[i] = Server(ip, gameport + 1, numOfServers);
                        numOfServers++;
                        added = true;
                        break;
                } else if(ServerArray[i].ip == ip && ServerArray[i].gameport == gameport) {
                        added = true;
                        break;
                }

        }
        return added;
}

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
        timeoutLimit = (int)(10 / WINDOW_SETTINGS->getUpdateInterval());
}

/**
   Wrapping method around the Udp socket to send messages easier.
   The time of sending is stored in the corresponding server object
 */

void sendUdpMessage(int index, String ip, int port, String msg) {
        try {
                Form1->IdUDPServer1->Send(ip, port, msg);
                if(ServerArray[index].messageSent <= 1) {
                        ServerArray[index].messageSent = timeGetTime();
                } else {
                        int tmp = ServerArray[index].timeouts;
                        if(tmp < timeoutLimit) {
                                ServerArray[index].timeouts = tmp + 1;
                        } else {
                                ServerArray[index].clear();
                        }
                }
        } catch (EIdException &E) {
                addToErrorReport("Error while sending a UDP packet", E.Message + "   Address:  " + ip + ":" + IntToStr(port));
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
            0 means: Server is offline/not set/blocked
            1 means: Server is online and does not pass the filter check
            2 means: Server is online and passes the filter check
            3 means: Server is online and marked for autojoin when game ends
            4 means: Server is online and favorited     
 */

int checkFilters(int j) {
        int out = 0;
        if(ServerArray[j].blocked) {
                out = 0;
        } else if(ServerArray[j].name.Length() > 0 && ServerArray[j].timeouts < timeoutLimit) {
                out = 1;
                if(ServerArray[j].autojoin) {
                        out = 3;
                } else if(ServerArray[j].favorite) {
                        out = 4;
                } else if(ServerArray[j].players >= Form1->UpDown1->Position) {   
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
        ServerFavoriteSortList->Clear();
        int inList = 1;
        int hasNoName = 0;
        int autojoin = -1;
        for (int j = 0; j < numOfServers; j++) {
                int abc = checkFilters(j);
                if(abc == 2 || abc == 4) {
                        TStringList *slist = ServerSortList;
                        if(abc == 4) {
                                slist = ServerFavoriteSortList;
                        }
                        if(tableSorter.id) {
                                slist->AddObject(addLeadingZeros(ServerArray[j].index),(TObject *) j);
                        } else if(tableSorter.name) {
                                slist->AddObject(ServerArray[j].name,(TObject *) j);
                        } else if(tableSorter.players) {
                                slist->AddObject(addLeadingZeros(ServerArray[j].players),(TObject *) j);
                        } else if(tableSorter.status) {
                                slist->AddObject(ServerArray[j].gamestate, (TObject *) j);
                        } else if(tableSorter.island) {
                                slist->AddObject(ServerArray[j].island, (TObject *) j);
                        } else if(tableSorter.mission) {
                                slist->AddObject(ServerArray[j].mission, (TObject *) j);
                        } else if(tableSorter.ping) {
                                slist->AddObject(addLeadingZeros(ServerArray[j].ping), (TObject *) j);
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
                        bool favorites = (ServerFavoriteSortList->Count > 0);
                        TStringList *slist = ServerSortList;
                        if(favorites) {
                                slist = ServerFavoriteSortList;
                        }
                        int rowIndex = i;
                        int j = 0;
                        if(autojoin >= 0) {
                                j = autojoin;
                        } else {
                                TObject *t = slist->Objects[0];
                                if(!tableSorter.normal) {
                                        t = slist->Objects[slist->Count - 1];
                                }
                                j = (int)t;
                        }
                        Form1->StringGrid1->Cells[0][rowIndex] = " " + String(ServerArray[j].index);
                        Form1->StringGrid1->Cells[1][rowIndex] = ServerArray[j].name;
                        Form1->StringGrid1->Cells[2][rowIndex] = String(ServerArray[j].players) + " / " + String(ServerArray[j].maxplayers);
                        String gs = getGameState(ServerArray[j].gamestate);

                        if(ServerArray[j].gametime > 0) {
                                gs += " " + calcElapsedTime(ServerArray[j].gametime, time(0));
                        }

                        Form1->StringGrid1->Cells[3][rowIndex] = gs;
                        Form1->StringGrid1->Cells[4][rowIndex] = ServerArray[j].island;
                        Form1->StringGrid1->Cells[5][rowIndex] = ServerArray[j].mission;
                        Form1->StringGrid1->Cells[6][rowIndex] = IntToStr(ServerArray[j].ping);
                        if(autojoin < 0) {
                                if(!tableSorter.normal) {
                                        slist->Delete(slist->Count - 1);
                                } else {
                                        slist->Delete(0);
                                }
                        } else {
                                autojoin = -2;
                        }
                }
                Form1->StringGrid1->RowCount = inList;

                if(selectedIndex > -1) {
                        for(int rowIndex = 1; rowIndex < Form1->StringGrid1->RowCount; rowIndex++) {
                                if((Form1->StringGrid1->Cells[0][rowIndex]).Trim() == String(selectedIndex).Trim()) {
                                        found = true;
                                        TGridRect myRect;
                                        myRect.Left = 0;
                                        myRect.Top = rowIndex;
                                        myRect.Right = 6;
                                        myRect.Bottom = rowIndex;
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
                Form1->CoolTrayIcon1->Hint = ServerArray[selectedIndex].name + "     " + getGameState(ServerArray[selectedIndex].gamestate) + "     " +  String(ServerArray[selectedIndex].players) + " " + WINDOW_SETTINGS->getGuiString("STRING_PLAYERS");
        } else {
                Form1->CoolTrayIcon1->Hint = "OFPMonitor";
        }
        filterChanging = false;
}

/**
   Reads an list of server internet addresses and sets up the ServerArray
 */

void TForm1::readServerList(list<ServerItem> &servers) {
        Form1->StatusBar1->Panels->Items[0]->Text = "";
        Form1->StatusBar1->Panels->Items[1]->Text = "";
        numOfServers = 0;
        while (servers.size() > 0) {
                ServerItem tmp = servers.front();
                if(tmp.address.Length() > 8) {
                        Address *a = new Address();
                        if(a->getAddress(tmp.address, 2303)) {
                                ServerArray[numOfServers] = Server(a->ip, a->port, numOfServers);
                                ServerArray[numOfServers].watch = tmp.watch;
                                ServerArray[numOfServers].favorite = tmp.favorite;
                                ServerArray[numOfServers].persistent = tmp.persistent;
                                ServerArray[numOfServers].blocked = tmp.blocked;
                                ServerArray[numOfServers].gamestate = tmp.gamestate;
                                ServerArray[numOfServers].gametime = tmp.gametime;
                                numOfServers++;
                        }
                        delete a;
                }
                delete (&(servers.front()));
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
        Form1->Timer2->Enabled = true;
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
                                                int newStatus = 0;
                                                try {
                                                        newStatus = StrToInt(*ci);
                                                } catch (...) {
                                                        newStatus = 1;
                                                }
                                                if(newStatus > 0) {
                                                        if(ServerArray[i].gamestate != newStatus) {
                                                                playAudioServerStatus(i, newStatus);
                                                                if(     ((oldStatus == SERVERSTATE_WAITING ||
                                                                         oldStatus == SERVERSTATE_SETTINGUP ||
                                                                         oldStatus == SERVERSTATE_BRIEFING
                                                                        ) && newStatus == SERVERSTATE_PLAYING) ||
                                                                        ((oldStatus == SERVERSTATE_WAITING ||
                                                                         oldStatus == SERVERSTATE_SETTINGUP
                                                                        ) && newStatus == SERVERSTATE_BRIEFING) ||
                                                                        ((oldStatus != SERVERSTATE_WAITING
                                                                        ) && newStatus == SERVERSTATE_WAITING) ||
                                                                        ((oldStatus == SERVERSTATE_PLAYING
                                                                        ) && newStatus == SERVERSTATE_DEBRIEFING)) {
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
                                                                gameControl.statusChange(i, oldStatus, newStatus);
                                                        }
                                                }
                                                ServerArray[i].gamestate = newStatus;
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
   This MessageReader makes sure that new incoming messages are procressed
   after each other (serial) and not at the same time (parallel). This resolves
   some concurrent access issues on the storing data structures.
 */

class MessageReader {
        private:
                bool working;
                list<Message*> messageList;
        public:
                MessageReader() {
                        this->working = false;
                }

                /**
                   Adds a new Message to the message queue
                 */

                void newMessage(Message *m) {
                        this->messageList.push_back(m);
                }

                /**
                   Checks for and processes messages. Only one thread does the work
                 */

                void checkForNewMessages() {
                        if(this->working) {
                                return;
                        }
                        this->working = true;
                        while(this->messageList.size() > 0) {
                                Message *m = this->messageList.front();
                                bool handled = false;
                                for(int j = 0; j < numOfServers; j++) {
                                        if(ServerArray[j].index == -1) {
                                                break;
                                        }
                                        if(ServerArray[j].ip == m->ip && ServerArray[j].gamespyport == m->port) {
                                                handled = true;
                                                if(readInfoPacket(j, m->content, m->ip, m->port)) {
                                                        if(ServerArray[j].messageSent > 1) {
                                                                ServerArray[j].ping = m->toa - ServerArray[j].messageSent;
                                                                if(ServerArray[j].ping < 0) {
                                                                        ServerArray[j].ping *= -1;
                                                                }
                                                                ServerArray[j].messageSent = 1;
                                                                ServerArray[j].timeouts = 0;
                                                        }
                                                        if(ServerArray[j].players > 0) {
                                                                ServerArray[j].emptyServerCounter = 0;
                                                        } else {
                                                                BandwidthUsage bu = WINDOW_SETTINGS->getBandwidthSettings();
                                                                switch(bu) {
                                                                        case VeryLow:
                                                                                if(ServerArray[j].emptyServerCounter < 5) {
                                                                                        ServerArray[j].emptyServerCounter++;
                                                                                }
                                                                                break;
                                                                        default:
                                                                        case Moderate:
                                                                        case Low:
                                                                                ServerArray[j].emptyServerCounter = 1;
                                                                                break;
                                                                        case High:
                                                                                ServerArray[j].emptyServerCounter = 0;
                                                                                break;
                                                                }
                                                        }
                                                }
                                                break;
                                        }
                                }
                                delete m;
                                this->messageList.pop_front();
                                if(!handled) {
                                        addToErrorReport("Warning: Non-handled message", String(m->ip) + ":" + String(m->port) + "   =>   " + m->content);
                                }
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
}

class Chat {
        public:
                String name;
                bool changed;
                TStringList *output;
                TStringList *input;
                TRect rect;

                Chat(String name) {
                        this->changed = false;
                        this->name = name;
                        this->output = new TStringList();
                        this->input = new TStringList();
                }

                void saveCurrentInput() {
                        this->input->Clear();
                        for(int i = 0; i < Form1->MemoChatInput->Lines->Count; i++) {
                                this->input->Add(Form1->MemoChatInput->Lines->Strings[i]);
                        }
                }

                void loadThisChat() {
                        Form1->MemoChatOutput->Lines->Clear();
                        Form1->MemoChatInput->Lines->Clear();
                        for(int i = 0; i < this->output->Count; i++) {
                                Form1->MemoChatOutput->Lines->Add(this->output->Strings[i]);
                        }
                        for(int i = 0; i < this->input->Count; i++) {
                                Form1->MemoChatInput->Lines->Add(this->input->Strings[i]);
                        }
                        this->changed = false;
                }

                bool incomingMessage(String name, String msg) {
                        if(name == this->name) {
                                if(!msg.IsEmpty()) {
                                        this->output->Add(msg);
                                        if(Form1->TabControl1->TabIndex == -1 || Form1->TabControl1->Tabs->Strings[Form1->TabControl1->TabIndex] == this->name) {
                                                Form1->MemoChatOutput->Lines->Add(msg);
                                        } else {
                                                this->changed = true;
                                        }
                                }
                                Form1->TabControl1->Repaint();
                                return true;
                        }
                        return false;
                }
};

TStringList *activeChats = new TStringList();
TStringList *blockedChatUsers = new TStringList();


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
                        this->channel = "#operationflashpoint1";
                        this->userName = "";
                        this->setAutoConnect(false);
                        this->init();
                }

                ChatSettings(String h, int p, String c, String user, bool ac) {
                        this->host = h;
                        this->port = p;
                        this->channel = c;
                        this->userName = user;
                        this->setAutoConnect(ac);
                        this->init();
                }

                void closeChats() {
                        Form1->TabControl1->Tabs->Clear();
                        for(int i = 0; i < activeChats->Count; i++) {
                                Chat *c = (Chat*) activeChats->Objects[i];
                                if(c != NULL) {
                                        delete c;
                                }
                        }
                        activeChats->Clear();
                }

                void incomingMsg(String chan, String msg, bool controlMsg) {
                        bool found = false;
                        for(int i = 0; i < activeChats->Count && !found; i++) {
                                Chat *c = (Chat*)(activeChats->Objects[i]);
                                found = c->incomingMessage(chan, msg);
                        }
                        if(!found && !controlMsg) {
                                Form1->TabControl1->Tabs->Add(chan);
                                Chat *n = new Chat(chan);
                                n->incomingMessage(chan, msg);
                                activeChats->AddObject(chan, (TObject*)n);
                        }
                        Form1->TabControl1->Repaint();
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
                void init() {
                        this->connectionLost = 0;
                        this->doConnect = false;
                }

                String checkBool(bool in) {
                        if(in) {
                                return "1";
                        } else {
                                return "0";
                        }
                }
};

ChatSettings chatsettings;

void TForm1::incomingChatMessage(String chan, String msg, bool controlMsg) {
        chatsettings.incomingMsg(chan, msg, controlMsg);
}

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

void TForm1::ChatConnected(bool success) {
        if(!success) {
                Form1->incomingChatMessage(Form1->getChatChannel(),WINDOW_SETTINGS->getGuiString("STRING_CHAT_CONNECTINGFAILED"), false);
        } else {
                MemoChatInput->Clear();
        }
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = !success;
        MENUITEM_MAINMENU_CHAT_DISCONNECT->Enabled = success;
        MemoChatInput->Enabled = success;
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

String decideQuery(BandwidthUsage bu, bool selected, int i) {
        String full = "\\info\\rules\\players\\";
        String part = "\\info\\rules\\";
        String none = "";
        bool someplayers = (ServerArray[i].players > 0);
        int missLimit = 1;
        switch(bu) {
                case Moderate:
                        if(someplayers || selected) {
                                return full;
                        } else if(ServerArray[i].missedQueryTurns >= missLimit) {
                                if(ServerArray[i].messageSent == 0) {
                                        return full;
                                } else {
                                        return part;
                                }
                        }
                        break;
                case VeryLow:
                        missLimit = ServerArray[i].emptyServerCounter;
                case Low:
                        if(selected) {
                                return full;
                        } else if(someplayers) {
                                if(ServerArray[i].players != ServerArray[i].playerlist.size()) {
                                        return full;
                                } else {
                                        return part;
                                }
                        } else if(ServerArray[i].missedQueryTurns >= missLimit) {
                                if(ServerArray[i].messageSent == 0) {
                                        return full;
                                } else {
                                        return part;
                                }
                        }
                        break;
                case High:
                default:
                        return full;
        }
        return none;
}

void updateGameControlGui() {
        bool selected = (Form1->ComboBox1->ItemIndex > -1) && (Form1->ComboBox2->ItemIndex > -1);
        if(!selected) {
                Form1->CHECKBOX_GAMECONTROL_AUTOGREENUP->Checked = false;
                gameControl.enableAutoGreenUp(false);
                Form1->CHECKBOX_GAMECONTROL_RESTORE->Checked = false;
                gameControl.enableRestoreGame(false);
        }
        Form1->RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCE->Enabled = selected;
        Form1->RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEAT->Enabled = selected;
        Form1->CHECKBOX_GAMECONTROL_RESTORE_CREATING->Enabled = selected;
        Form1->CHECKBOX_GAMECONTROL_RESTORE_WAITING->Enabled = selected;
        Form1->CHECKBOX_GAMECONTROL_RESTORE_BRIEFING->Enabled = selected;
        Form1->CHECKBOX_GAMECONTROL_RESTORE_PLAYING->Enabled = selected;
        Form1->CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFING->Enabled = selected;
        Form1->CHECKBOX_GAMECONTROL_AUTOGREENUP->Enabled = selected;
        Form1->CHECKBOX_GAMECONTROL_RESTORE->Enabled = selected;
        Form1->LABEL_GAMECONTROL_AUTOGREENUP_DELAY->Enabled = selected;
        Form1->UpDown2->Enabled = selected;
        Form1->Edit5->Enabled = selected;
        Form1->ComboBox1->Enabled = !(Form1->ComboBox1->Items->Count == 0);
        Form1->ComboBox2->Enabled = !(Form1->ComboBox2->Items->Count == 0);
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
        ServerFavoriteSortList->Sorted = true;
        ServerFavoriteSortList->CaseSensitive = true;
        ServerFavoriteSortList->Duplicates = dupAccept;
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
                } catch (...) {}
        } else {
                setEmptyPlayerList();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        int i = Timer1->Tag;
        i++;
        if(i >= 2*WINDOW_SETTINGS->getUpdateInterval()) {
                Timer2->Enabled = true;
                Timer1->Tag = 0;
        } else {
                Timer1->Tag = i;
        }
        Application->ProcessMessages();
        messageReader.checkForNewMessages();
        filterChanged(false);
        processPlayerList(-1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        TerminateThread(getServerListThread,0);
        Form1->Enabled = false;
        chat_client_disconnect();
        WINDOW_SETTINGS->MP3shutdown();
        Timer2->Enabled = false;
        Timer1->Enabled = false;
        delete ServerSortList;
        delete ServerFavoriteSortList;
        delete PlayerSortList;
        delete PlayerSortList2;
        list<ServerItem> servers;
        chatsettings.closeChats();
        delete blockedChatUsers;
        delete activeChats;
        for(int i = 0; i < GetArrLength(ServerArray) && ServerArray[i].index == i; i++) {
                ServerItem *sI = ServerArray[i].createServerItem();
                servers.push_back((*sI));
        }
        WINDOW_SETTINGS->writeSettingToFile(servers, fontsettings.createFileEntry(), windowsettings.createFileEntry(), chatsettings.createFileEntry());
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

                                MENUITEM_POPUP_JOIN->Tag = index;
                                MENUITEM_POPUP_AUTOJOIN->Tag = index;
                                MENUITEM_POPUP_AUTOJOIN->Visible = (ServerArray[index].gamestate == SERVERSTATE_PLAYING) && !ServerArray[index].autojoin;
                                MENUITEM_POPUP_AUTOJOINB->Visible = ServerArray[index].autojoin;
                                MENUITEM_POPUP_AUTOJOINB->Checked = ServerArray[index].autojoin;
                                MENUITEM_POPUP_AUTOJOINB->Tag = index;
                                MENUITEM_POPUP_MODS->Tag = index;
                                MENUITEM_POPUP_WATCH->Tag = index;
                                MENUITEM_POPUP_WATCH->Checked = ServerArray[index].watch;

                                int i = 0;
                                for (list<String>::iterator ci = t.begin(); ci != t.end(); ++ci) {
                                        if(!(*ci).IsEmpty()) {
                                                TMenuItem *m = MENUITEM_POPUP_MODS->Items[i];
                                                m->Caption = *ci;
                                                m->Visible = true;
                                                i++;
                                        }
                                }
                                MENUITEM_POPUP_MODS->Enabled = (i > 0);
                                for(; i < MENUITEM_POPUP_MODS->Count; i++) {
                                        TMenuItem *m = MENUITEM_POPUP_MODS->Items[i];
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
                join = MENUITEM_POPUP_JOIN->Items[i];
                autojoin = MENUITEM_POPUP_AUTOJOIN->Items[i];
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
        for(i = additionalItems; i - additionalItems < WINDOW_SETTINGS->getConfAmount(gameid) || i < MENUITEM_POPUP_JOIN->Count; i++) {
                String s = "";
                if(gameid >= 0) {
                        s = WINDOW_SETTINGS->getConfListEntry(gameid, i - additionalItems);
                }
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
                        if(i < MENUITEM_POPUP_JOIN->Count) {
                                MENUITEM_POPUP_JOIN->Items[i]->Visible = false;
                                MENUITEM_POPUP_AUTOJOIN->Items[i]->Visible = false;
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
                        if(     mark != NULL ||
                                ServerArray[index].watch ||
                                ServerArray[index].autojoin ||
                                ServerArray[index].favorite) {
                                StringGrid1->Canvas->Font->Color = clWhite;
                                if(mark != NULL) {
                                        StringGrid1->Canvas->Brush->Color = mark;
                                } else if(ServerArray[index].watch) {
                                        StringGrid1->Canvas->Brush->Color = clBlue;
                                } else if(ServerArray[index].autojoin) {
                                        StringGrid1->Canvas->Brush->Color = clRed;
                                } else if(ServerArray[index].favorite) {
                                        StringGrid1->Canvas->Font->Color = clBlack;
                                        StringGrid1->Canvas->Brush->Color = clYellow;
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

DWORD WINAPI gamespyQuery_ThreadProc (LPVOID lpdwThreadParam__ ) {
        Form1->Timer1->Enabled = false;
        Form1->Timer2->Enabled = false;
        TStringList *CurrentList = new TStringList;
        CurrentList->Sorted = true;
        CurrentList->Duplicates = dupIgnore;

        for(int si = 0; si < SERVERARRAY_LENGTH; si++) {
                if(ServerArray[si].index == si && ServerArray[si].persistent) {
                        ServerItem *scfi = ServerArray[si].createServerItem();
                        CurrentList->AddObject(scfi->address, (TObject*) scfi);
                }
        }
        for(int si = 0; si < SERVERARRAY_LENGTH; si++) {
                if(ServerArray[si].index == si && ServerArray[si].name.Length() > 0) {
                        ServerItem *scfi = ServerArray[si].createServerItem();
                        CurrentList->AddObject(scfi->address, (TObject*) scfi);
                }
        }

        Application->ProcessMessages();
        TStringList *games = WINDOW_SETTINGS->getGameSpyGames();
        for (int k = 0; k < games->Count; k++) {
                scandelay *= 1000;
                dnsdb(NULL);
                gslist_step_1(gamestr, filter);
                peer.sin_addr.s_addr = msip;
                peer.sin_port        = htons(msport);
                peer.sin_family      = AF_INET;

                buff = (unsigned char *) malloc(BUFFSZ + 1);
              //  if(!buff) std_err();
                dynsz = BUFFSZ;
                multigamename = gamestr;
                multigamenamep = strchr((char *)gamestr, ',');
                if(multigamenamep) {
                        *multigamenamep = 0;
                }
                sd = gslist_step_2(&peer, buff, secure, gamestr, validate, filter, &enctypex_data);
                if(sd != -1) {
                        ipport = gslist_step_3(sd, validate, &enctypex_data, &len, &buff, &dynsz);
                        itsok = gslist_step_4(secure, buff, &enctypex_data, &ipport, &len);
                        ipbuffer = ipport;
                        while(len >= 6) {
                                ipc = myinetntoa(ipport->ip);
                                if(!enctypex_query[0]) {
                                        String s;
                                        s.sprintf("%15s:%d", ipc, ntohs(ipport->port));
                                        ServerItem *seI = new ServerItem(s.Trim());
                                        CurrentList->AddObject(s.Trim(), (TObject*) seI);
                                }
                                ipport++;
                                len -= 6;
                        }
                }
        }
                       
        list<ServerItem> addresses;
        while(CurrentList->Count > 0) {
                ServerItem *p = (ServerItem*) (CurrentList->Objects[0]);
                addresses.push_back((*p));
                CurrentList->Delete(0);
        }
        if(addresses.size() > 0) {
                ServerItem si = addresses.front();

/*
                setEmptyStringGrid();
                setEmptyPlayerList();
                updateServerInfoBox(-1);
                tableSorter.reset();
*/
                Form1->readServerList(addresses);
        }
        delete CurrentList;
        delete games;
        WINDOW_SETTINGS->setSettingsChanged();
        Form1->Timer2->Enabled = true;
        Form1->Timer1->Tag = 0;
        Form1->Timer1->Enabled = true;
        Form1->MENUITEM_MAINMENU_GETNEWSERVERLIST->Enabled = true;
        return 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MENUITEM_MAINMENU_GETNEWSERVERLISTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_GETNEWSERVERLIST->Enabled = false;
        getServerListThread = CreateThread(0, 0, gamespyQuery_ThreadProc, 0, 0, 0);
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
                Form1->incomingChatMessage(Form1->getChatChannel(), WINDOW_SETTINGS->getGuiString("STRING_CHAT_CONNECTIONLOST"), false);
                MENUITEM_MAINMENU_CHAT_DISCONNECT->Click();
                MENUITEM_MAINMENU_CHAT_CONNECT->Click();
        } else {
                chat_client_timercallback( this );
        }
        if(chatsettings.doConnect) {
                chatsettings.doConnect = false;
                chat_client_connect();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_CONNECTClick(TObject *Sender)
{
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = false;
        Form1->PageControl1->ActivePage = Form1->TABSHEET_CHAT;
        if(chatsettings.connectionLost == 0) {
                Form1->incomingChatMessage(Form1->getChatChannel(), WINDOW_SETTINGS->getGuiString("STRING_CHAT_CONNECTINGTO") +
                        "  " + Form1->getChatHost() + ":" + String(Form1->getChatPort()), false);
                Form1->incomingChatMessage(Form1->getChatChannel(), WINDOW_SETTINGS->getGuiString("STRING_CHAT_CHANNEL") +
                        "  " + Form1->getChatChannel(), false);
        } else {
                Form1->incomingChatMessage(Form1->getChatChannel(), "", false);
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
        chat_client_disconnect();
        TimerIrcChatTimer->Enabled = false;
        StringGrid3->RowCount = 0;
        StringGrid3->Cells[0][0] = "";
        StringGrid3->Cells[0][1] = "";
        if(chatsettings.connectionLost == 0) {
                Form1->incomingChatMessage(Form1->getChatChannel(), WINDOW_SETTINGS->getGuiString("STRING_CHAT_DISCONNECTED"), false);
        }
        int i = activeChats->IndexOf(Form1->getChatChannel());
        if(i >= 0) {
                Chat *c = (Chat*) activeChats->Objects[i];
                c->loadThisChat();
        }
        chatsettings.closeChats();
        MENUITEM_MAINMENU_CHAT_CONNECT->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MENUITEM_MAINMENU_CHAT_CLEARLOGClick(TObject *Sender)
{
        int i = TabControl1->TabIndex;
        if(i >= 0) {
                String caption = TabControl1->Tabs->Strings[i];
                int j = activeChats->IndexOf(caption);
                if(j >= 0) {
                        Chat *c = (Chat*) activeChats->Objects[j];
                        c->output->Clear();
                        c->input->Clear();
                        c->loadThisChat();
                }
        }
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
        int i = TabControl1->TabIndex;
        if(i >= 0) {
                String caption = TabControl1->Tabs->Strings[i];
                int j = activeChats->IndexOf(caption);
                if(j >= 0) {
                        Chat *c = (Chat*) activeChats->Objects[j];
                        c->output->SaveToFile(SaveDialog1->FileName);
                }
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
                        String caption;
                        if(TabControl1->TabIndex == -1) {
                                caption = Form1->getChatChannel();
                        } else {
                                caption = TabControl1->Tabs->Strings[TabControl1->TabIndex];
                        }
                        chat_client_pressedReturnKey(this, caption.c_str(), input.c_str());
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

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
        int serverIndex = Timer2->Tag;
        serverIndex++;
        if(serverIndex >= SERVERARRAY_LENGTH || ServerArray[serverIndex].ip.IsEmpty()) {
                Timer2->Enabled = false;
                serverIndex = -1;
        }
        Timer2->Tag = serverIndex;
        Application->ProcessMessages();
        if(serverIndex >= 0) {
                bool serverIsSelected = (serverIndex == getSelectedServer());
                BandwidthUsage bu = WINDOW_SETTINGS->getBandwidthSettings();
                String query = decideQuery(bu, serverIsSelected, serverIndex);
                if(query.IsEmpty()) {
                        ServerArray[serverIndex].missedQueryTurns++;
                } else {
                        sendUdpMessage(serverIndex, ServerArray[serverIndex].ip, ServerArray[serverIndex].gamespyport, query);
                        ServerArray[serverIndex].missedQueryTurns = 0;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread,
      TIdBytes AData, TIdSocketHandle *ABinding)
{
        if(AData.Length > 0) {
                messageReader.newMessage(new Message(ABinding->PeerIP, ABinding->PeerPort, BytesToString(AData), timeGetTime()));
        }
}
//---------------------------------------------------------------------------
                          
void __fastcall TForm1::TabControl1DrawTab(TCustomTabControl *Control,
      int TabIndex, const TRect &Rect, bool Active)
{
        TRect r = Rect;
        r.Left += 4;
        String caption = TabControl1->Tabs->Strings[TabIndex];
        int i = activeChats->IndexOf(caption);
        if(i >= 0) {
                Chat *c = (Chat*) activeChats->Objects[i];
                c->rect.Top = Rect.Top;
                c->rect.Bottom = Rect.Bottom;
                c->rect.Left = Rect.Left;
                c->rect.Right = Rect.Right;
                if(TabIndex != TabControl1->TabIndex) {
                        if(c->changed) {
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
                int i = activeChats->IndexOf(caption);
                if(i >= 0) {
                        Chat *c = (Chat*) activeChats->Objects[i];
                        c->loadThisChat();
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
                int i = activeChats->IndexOf(caption);
                if(i >= 0) {
                        Chat *c = (Chat*) activeChats->Objects[i];
                        c->saveCurrentInput();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid3ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
        int col = -1, row = -1;
        StringGrid3->MouseToCell(MousePos.x, MousePos.y, col, row);
        bool success = false;
        String ownName = getOwnIrcName();
        if(col >= 0 && row >= 0) {
                String name = StringGrid3->Cells[0][row];
                if(!name.IsEmpty() && name != ownName) {
                        success = true;
                        int i = activeChats->IndexOf(name);
                        Openchat1->Tag = i;
                        Openchat1->Hint = name;
                }
        }
        Openchat1->Caption = WINDOW_SETTINGS->getGuiString("STRING_CHAT_CHATWITH"); 
        Openchat1->Visible = success;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Openchat1Click(TObject *Sender)
{
        int i = Openchat1->Tag;
        String name = Openchat1->Hint;
        if(i < 0) {
                Form1->incomingChatMessage(name, "", false);
                i = activeChats->IndexOf(name);
        }
        if(i >= 0) {
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
        for(int i = 0; i < activeChats->Count; i++) {
                Chat *c = (Chat*) activeChats->Objects[i];
                if(     c->rect.Left < MousePos.x &&
                        c->rect.Right > MousePos.x &&
                        c->rect.Top < MousePos.y &&
                        c->rect.Bottom > MousePos.y &&
                        c->name != Form1->getChatChannel()) {
                        Close1->Hint = c->name;
                        Close1->Caption = WINDOW_SETTINGS->getGuiString("STRING_CHAT_CLOSE");
                        Close1->Visible = true;
                        break;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Close1Click(TObject *Sender)
{
        String name = Close1->Hint;
        int j = TabControl1->Tabs->IndexOf(name);
        if(j >= 0) {
                TabControl1->Tabs->Delete(j);
        }
        int i = activeChats->IndexOf(name);
        if(i >= 0) {
                Chat *c = (Chat*) activeChats->Objects[i];
                delete c;
                activeChats->Delete(i);
        }
        TabControl1Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCEClick(TObject *Sender)
{
        gameControl.setGreenUpRepeat(RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCE->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEATClick(TObject *Sender)
{
        gameControl.setGreenUpRepeat(RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEAT->Checked);        
}
//---------------------------------------------------------------------------
                   
void __fastcall TForm1::CHECKBOX_GAMECONTROL_AUTOGREENUPClick(TObject *Sender)
{
        gameControl.enableAutoGreenUp(CHECKBOX_GAMECONTROL_AUTOGREENUP->Checked);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTOREClick(TObject *Sender)
{
        gameControl.enableRestoreGame(CHECKBOX_GAMECONTROL_RESTORE->Checked);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerAutoGreenUpTimer(TObject *Sender)
{
        TimerAutoGreenUp->Enabled = gameControl.getGreenUpRepeat();
        int serverId = TimerAutoGreenUp->Tag;
        gameControl.sendGreenUpMessage(serverId);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BUTTON_GAMECONTROL_REFRESHClick(TObject *Sender)
{
        Label6->Caption = "";
        Label9->Caption = "";
        for(int i = 0; i < ComboBox1->Items->Count; i++) {
                ProcessInfo *pi = (ProcessInfo*) ComboBox1->Items->Objects[i];
                delete pi;
        }
        ComboBox1->Clear();
        ProcessFinder *pf = new ProcessFinder();
        TStringList *s = new TStringList();
        s->Add("Operation Flashpoint");
        s->Add("Cold War Assault");
        TStringList *m = new TStringList();
        m->Add("OperationFlashpoint.exe");
        m->Add("OperationFlashpointbeta.exe");
        m->Add("FLASHPOINTRESISTANCE.EXE");
        m->Add("FLASHPOINTBETA.EXE");
        m->Add("ColdWarAssault.exe");

        if(pf->enumerate(s, m)) {
                for (list<ProcessInfo>::iterator proc = pf->output.begin(); proc != pf->output.end(); ++proc) {
                        ProcessInfo *p = new ProcessInfo((*proc).pid, (*proc).hWindow, (*proc).title, (*proc).moduleName);
                        ComboBox1->Items->AddObject(p->title, (TObject*) p);
                        if(gameControl.matchesProcess(p)) {
                                ComboBox1->ItemIndex = ComboBox1->Items->Count - 1;
                                ComboBox1Change(ComboBox1);
                        }
                }
        }
        delete pf;
        delete s;
        delete m;
        ComboBox2->Clear();
        for(int i = 0; i < SERVERARRAY_LENGTH; i++) {
                if(ServerArray[i].ip.IsEmpty()) {
                        break;
                }
                if(!ServerArray[i].name.IsEmpty()) {
                        ComboBox2->Items->AddObject(ServerArray[i].name, (TObject*) i);
                        if(gameControl.matchesServer(i)) {
                                ComboBox2->ItemIndex = ComboBox2->Items->Count - 1;
                                ComboBox2Change(ComboBox2);
                        }
                }
        }
        updateGameControlGui();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
        if(ComboBox1->ItemIndex > -1) {
                ProcessInfo *p = (ProcessInfo*) ComboBox1->Items->Objects[ComboBox1->ItemIndex];
                if(p != NULL) {
                        Label6->Caption = IntToStr(p->pid);
                        Label9->Caption = p->moduleName;
                        gameControl.setProcess(p);
                }
        }
        updateGameControlGui();
}
//---------------------------------------------------------------------------
      
void __fastcall TForm1::ComboBox2Change(TObject *Sender)
{
        if(ComboBox2->ItemIndex > -1) {
                int id = (int) (ComboBox2->Items->Objects[ComboBox2->ItemIndex]);
                if(id >= 0 && id < SERVERARRAY_LENGTH) {
                        gameControl.setServer(id, ServerArray[id].ip, ServerArray[id].gamespyport);
                }
        }
        updateGameControlGui();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TABSHEET_GAMECONTROLShow(TObject *Sender)
{
        BUTTON_GAMECONTROL_REFRESH->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_CREATINGClick(TObject *Sender)
{
        gameControl.restoreOnCreating = CHECKBOX_GAMECONTROL_RESTORE_CREATING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_WAITINGClick(TObject *Sender)
{
        gameControl.restoreOnWaiting = CHECKBOX_GAMECONTROL_RESTORE_WAITING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_BRIEFINGClick(TObject *Sender)
{
        gameControl.restoreOnBriefing = CHECKBOX_GAMECONTROL_RESTORE_BRIEFING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_PLAYINGClick(TObject *Sender)
{
        gameControl.restoreOnPlaying = CHECKBOX_GAMECONTROL_RESTORE_PLAYING->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFINGClick(TObject *Sender)
{
        gameControl.restoreOnDebriefing = CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFING->Checked;        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::UpDown2Changing(TObject *Sender, bool &AllowChange)
{
        gameControl.setGreenUpDelay(UpDown2->Position);        
}
//---------------------------------------------------------------------------








