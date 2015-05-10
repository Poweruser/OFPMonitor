//---------------------------------------------------------------------------


#pragma hdrstop

#include "GameControl.h"
#include "OFPMonitorDefinitions.h"
#include "ConfigReader.h"
#include "FileVersion.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


GameControl::GameControl(OFPMonitorModel *ofpm) {
        this->ofpm = ofpm;
        this->autoGreenUpTimer = new TTimer(NULL);
        this->autoGreenUpTimer->Enabled = false;
        this->autoGreenUpTimer->OnTimer = this->onTimer;
        this->selectedServerID = NULL_SERVERID;
        this->restoreGame = false;
        this->restoreOnCreating = false;
        this->restoreOnWaiting = false;
        this->restoreOnBriefing = false;
        this->restoreOnPlaying = false;
        this->restoreOnDebriefing = false;
        this->autoDetect = false;
        this->autoGreenUp = false;
        this->selectedMasterServer = "";
        this->masterServerOverwrite = false;
        this->greenUpDelay = 10;
        this->greenUpRepeat = false;
}

GameControl::~GameControl() {
        this->autoGreenUpTimer->Enabled = false;
        delete (this->autoGreenUpTimer);
}

bool GameControl::verifyProcess() {
        bool out = false;
        if(this->isProcessValid()) {
                ProcessFinder *pf = new ProcessFinder();
                TStringList *startsWith = new TStringList();
                startsWith->Add(this->proc.title);
                TStringList *modules = new TStringList();
                modules->Add(this->proc.moduleName);
                pf->enumerate(startsWith, modules);
                for (list<ProcessInfo>::iterator ci = pf->output.begin(); ci != pf->output.end(); ++ci) {
                        if(this->matchesProcess(*ci)) {
                                out = true;
                                break;
                        }
                }
                delete pf;
                delete startsWith;
                delete modules;
                if(!out) {
                        this->proc.clear();
                        this->NotifyObserver();
                }
        }
        return out;
}

bool GameControl::verifyServer() {
        if(this->selectedServerID >= 0) {
                Server *srv = this->ofpm->getServerByID(this->selectedServerID);
                if(srv != NULL) {
                        bool out = srv->isOnline() && !srv->isBlocked();
                        if(this->autoDetect) {
                                out = out && (this->ofpm->findUserOnServer() == this->selectedServerID);
                        }
                        return out;
                } else {
                        this->selectedServerID = NULL_SERVERID;
                }
        }
        return false;
}

bool GameControl::isAutoGreenOn() {
        return this->autoGreenUp;
}

bool GameControl::isRestoreGameOn() {
        return this->restoreGame;
}

bool GameControl::isAutoDetectOn() {
        return this->autoDetect;
}

bool GameControl::isOverwriteMasterServerOn() {
        return this->masterServerOverwrite;
}

void GameControl::setProcess(ProcessInfo *p) {
        this->proc.pid = p->pid;
        this->proc.hWindow = p->hWindow;
        this->proc.title = p->title;
        this->proc.moduleName = p->moduleName;
        if(this->masterServerOverwrite) {
                this->overwriteMasterServer(this->selectedMasterServer);
        }
}

void GameControl::setServer(int serverID) {
        this->selectedServerID = serverID;
        this->checkCurrentData();
}

bool GameControl::matchesProcess(ProcessInfo p) {
        return (this->proc.equals(p));
}

bool GameControl::matchesProcess(ProcessInfo *p) {
        return (this->proc.equals(p));
}

bool GameControl::matchesServer(String serverAddress) {
        if(this->selectedServerID >= 0) {
                Server *srv = this->ofpm->getServerByID(this->selectedServerID);
                if(srv != NULL) {
                        return srv->equals(serverAddress);
                }
        }
        return false;
}

bool GameControl::matchesServer(int serverID) {
        if(this->selectedServerID >= 0) {
                Server *srv = this->ofpm->getServerByID(this->selectedServerID);
                Server *other = this->ofpm->getServerByID(serverID);
                if(srv != NULL && other != NULL) {
                        return srv->equals(other);
                }
        }
        return false;
}

void GameControl::ProcessMessages() {
        while(this->ofpm->hasServerStatusChanged()) {
                StatusChange *sc = this->ofpm->takeStatusChange();
                if(sc != NULL) {
                        this->statusChange(sc);
                        delete sc;
                }
        }
}

void GameControl::statusChange(StatusChange *statusChange) {
        this->checkCurrentData();
        if(this->matchesServer(statusChange->getServerAddress()) && isProcessValid()) {
                int oldStatus = statusChange->getOldStatus();
                int newStatus = statusChange->getCurrentStatus();
                if(this->autoGreenUp) {
                        if(newStatus == SERVERSTATE_BRIEFING) {
                                if(!this->autoGreenUpTimer->Enabled) {
                                        this->autoGreenUpTimer->Interval = this->greenUpDelay * 1000;
                                        this->autoGreenUpTimer->Enabled = true;
                                }
                        } else {
                                this->autoGreenUpTimer->Enabled = false;
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

void GameControl::setGreenUpRepeat(bool enabled) {
        this->greenUpRepeat = enabled;
}

bool GameControl::getGreenUpRepeat() {
        return this->greenUpRepeat;
}

int GameControl::getGreenUpDelay() {
        return this->greenUpDelay;
}

void GameControl::enableAutoGreenUp(bool enabled) {
        this->autoGreenUp = enabled;
        if(!enabled) {
                this->autoGreenUpTimer->Enabled = enabled;
        }
        this->checkCurrentData();
}

void GameControl::enableRestoreGame(bool enabled) {
        this->restoreGame = enabled;
        this->checkCurrentData();
}

void GameControl::enableMasterServerOverwrite(bool enabled) {
        this->masterServerOverwrite = enabled;
        this->checkCurrentData();
        if(enabled && this->isProcessValid() && !this->selectedMasterServer.IsEmpty()) {
                this->overwriteMasterServer(this->selectedMasterServer);
        }
}

void GameControl::setAutoDetect(bool enabled) {
        this->autoDetect = enabled;
        this->checkCurrentData();
}

void GameControl::setGreenUpDelay(int delay) {
        int toset = delay;
        if(delay < 10) {
                toset = 10;
        }
        if(delay > 600) {
                toset = 600;
        }
        this->greenUpDelay = toset;
        this->autoGreenUpTimer->Interval = this->greenUpDelay * 1000;
}

void GameControl::sendGreenUpMessage() {
        if(this->verifyProcess() && this->verifyServer()) {
                Server *srv = this->ofpm->getServerByID(this->selectedServerID);
                if(srv != NULL) {
                        if(srv->getCurrentGameState() == SERVERSTATE_BRIEFING) {
                                SendMessage(this->proc.hWindow, WM_KEYDOWN, VK_RETURN, NULL);
                                SendMessage(this->proc.hWindow, WM_KEYUP  , VK_RETURN, NULL);
                        }
                }
        }
}                

void GameControl::getSettingsFileEntry(TStringList *settings) {
        settings->Add("[Automation]");
        settings->Add("AutoDetectProcessAndServer = " + IntToStr(this->autoDetect));
        settings->Add("BriefingConfirmationOn = " + IntToStr(this->autoGreenUp));
        settings->Add("BriefingConfirmationDelay = " + IntToStr(this->greenUpDelay));
        settings->Add("BriefingConfirmationRepeat = " + IntToStr(this->greenUpRepeat));
        settings->Add("RestoreGame = " + IntToStr(this->restoreGame));
        settings->Add("RestoreOnCreating = " + IntToStr(this->restoreOnCreating));
        settings->Add("RestoreOnWaiting = " + IntToStr(this->restoreOnWaiting));
        settings->Add("RestoreOnBriefing = " + IntToStr(this->restoreOnBriefing));
        settings->Add("RestoreOnPlaying = " + IntToStr(this->restoreOnPlaying));
        settings->Add("RestoreOnDebriefing = " + IntToStr(this->restoreOnDebriefing));
        settings->Add("OverwriteMasterServer = " + IntToStr(this->masterServerOverwrite));
        settings->Add("[\\Automation]");
}

String GameControl::checkBool(bool in) {
        if(in) { return "1"; }
        return "0";
}

bool GameControl::detectServer() {
        bool detected = false;
        if(this->autoDetect) {
                int serverID = this->ofpm->findUserOnServer();
                if(serverID != this->selectedServerID) {
                        this->setServer(serverID);
                }
                if(serverID >= 0) {
                        detected = true;
                }
        }
        return detected;
}

bool GameControl::detectProcess() {
        bool detected = false;
        if(this->autoDetect) {
                ProcessFinder *pf = new ProcessFinder();
                TStringList *startsWith = new TStringList();
                startsWith->Sorted = true;
                startsWith->Duplicates = dupIgnore;
                startsWith->Add(getAppTitleByGameId(OFPCWC));
                startsWith->Add(getAppTitleByGameId(OFPRES));
                startsWith->Add(getAppTitleByGameId(ARMACWA));
                TStringList *modules = new TStringList();
                for(int i = 0; i < GAMESTOTAL; i++) {
                        list<String> exes = getExesByGameId((OFPGames)i, false);
                        while(exes.size() > 0) {
                                modules->Add(exes.front());
                                exes.pop_front();
                        }
                }
                if(pf->enumerate(startsWith, modules)) {
                        if(pf->output.size() == 1) {
                                this->setProcess(&(pf->output.front()));
                                detected = true;
                        }
                }
                delete pf;
                delete startsWith;
                delete modules;
        }
        return detected;
}

void GameControl::checkCurrentData() {
        bool serverOK = this->verifyServer();
        bool processOK = false;
        if(this->isProcessValid()) {
                processOK = this->verifyProcess();
        }
        if(this->autoDetect) {
                if(!serverOK) {
                        this->detectServer();
                }
                if(!processOK) {
                        this->detectProcess();
                }
        }
        this->NotifyObserver();
}

bool GameControl::isProcessValid() {
        return (this->proc.pid > 0 &&
                !this->proc.title.IsEmpty() &&
                !this->proc.moduleName.IsEmpty());
}

void __fastcall GameControl::onTimer(TObject *Sender) {
        this->autoGreenUpTimer->Enabled = this->getGreenUpRepeat();
        this->sendGreenUpMessage();
}

void GameControl::readSettings(TStringList *file) {
        ConfigSection *automation = new ConfigSection("Automation");
        automation->add(new ConfigEntry("AutoDetectProcessAndServer", dtBool, (void*)(&(this->autoDetect))));
        automation->add(new ConfigEntry("BriefingConfirmationOn", dtBool, (void*)(&(this->autoGreenUp))));
        automation->add(new ConfigEntry("BriefingConfirmationDelay", dtInt, (void*)(&(this->greenUpDelay))));
        automation->add(new ConfigEntry("BriefingConfirmationRepeat", dtBool, (void*)(&(this->greenUpRepeat))));
        automation->add(new ConfigEntry("RestoreGame", dtBool, (void*)(&(this->restoreGame))));
        automation->add(new ConfigEntry("RestoreOnCreating", dtBool, (void*)(&(this->restoreOnCreating))));
        automation->add(new ConfigEntry("RestoreOnWaiting", dtBool, (void*)(&(this->restoreOnWaiting))));
        automation->add(new ConfigEntry("RestoreOnBriefing", dtBool, (void*)(&(this->restoreOnBriefing))));
        automation->add(new ConfigEntry("RestoreOnPlaying", dtBool, (void*)(&(this->restoreOnPlaying))));
        automation->add(new ConfigEntry("RestoreOnDebriefing", dtBool, (void*)(&(this->restoreOnDebriefing))));
        automation->add(new ConfigEntry("OverwriteMasterServer", dtBool, (void*)(&(this->masterServerOverwrite))));
        automation->scan(file, 0);
        delete automation;
}

void GameControl::setMasterServer(String masterserver) {
        this->selectedMasterServer = masterserver;
        if(this->isProcessValid() && !masterserver.IsEmpty()) {
                this->overwriteMasterServer(masterserver);
        }
}

String GameControl::getSelectedMasterServer() {
        return this->selectedMasterServer;
}

void GameControl::overwriteMasterServer(String masterserver) {
        if(this->verifyProcess()) {
                HANDLE phandle = NULL;
                phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, this->proc.pid);
                if(phandle != NULL) {
                        FileVersion *fVersion = new FileVersion(this->proc.moduleName);
                        int ofpVersion = fVersion->getOFPVersion();
                        delete fVersion;
                        int offset1 = 0;
                        if(this->proc.title == getAppTitleByGameId(ARMACWA) && ofpVersion == 199) {
                                offset1 = 0x756530;
                        } else if(this->proc.title == getAppTitleByGameId(OFPRES) && ofpVersion == 196) {
                                offset1 = 0x76EBC0;
                        }
                        if(offset1 != 0) {
                                int lengthLimit = 63;
                                String master = masterserver;
                                if(master.IsEmpty()) {
                                        TStringList *list = new TStringList;
                                        this->ofpm->getMasterServers(list);
                                        for(int i = 0; i < list->Count; i++) {
                                                if(list->Strings[i].Length() <= lengthLimit) {
                                                        master = list->Strings[i];
                                                        break;
                                                }
                                        }
                                        delete list;
                                }
                                if(!master.IsEmpty() && master.Length() <= lengthLimit) {
                                        master += " ";
                                        int length = master.Length();
                                        char *data = master.c_str();
                                        data[length - 1] = 0;
                                        SIZE_T stBytes = 0;
                                        WriteProcessMemory(phandle, (LPVOID)offset1, data, length, &stBytes);
                                }
                        }
                        CloseHandle(phandle);
                }
        }
}



