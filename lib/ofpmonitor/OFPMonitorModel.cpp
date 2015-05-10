//---------------------------------------------------------------------------


#pragma hdrstop

#include "OFPMonitorModel.h"
#include "ConfigReader.h"
#include "StringSplitter.h"
#include <windows.h>
#include <mmsystem.h>
#include "ServerListLoader.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

OFPMonitorModel::OFPMonitorModel(String settingsFile, ServerList *serverList) {
        this->servers = serverList;
        this->net = new UDPNetwork();
        this->notifications = new TList;
        this->masterServers = new TStringList;
        this->masterServers->Duplicates = dupIgnore;
        this->masterServers->Sorted = true;
        this->audioPlayer = new AudioPlayer();
        this->queryTimer = new TTimer(NULL);
        this->queryTimer->Enabled = false;
        this->queryTimer->Interval = 10;
        this->queryTimer->OnTimer = this->onQueryTimer;
        this->AppWorkdir = ExtractFileDir(Application->ExeName);
        this->customNotifications = false;
        this->checkUpdateAtStart = true;
        this->checkMasterServersAtStart = true;
        this->interval = 5;
        this->level = Moderate;
        this->settingsfile = settingsFile;
        this->languagefile = "";
        this->querying = false;
        for(int i = 0; i < GAMESTOTAL; i++) {
                this->games[i] = new Game((OFPGames)i);
        }
        this->volume = 100;
        this->shuttingDown = false;
        this->serverListUpdateDone = true;
        this->dropOfflineServersOnUpdate = true;
        this->aliasCounter = 0;
        this->processing = false;
}

OFPMonitorModel::~OFPMonitorModel() {
        this->shuttingDown = true;
        TerminateThread(this->getServerListThread, 0);
        this->queryTimer->Enabled = false;
        delete (this->queryTimer);
        delete (this->net);
        while(this->notifications->Count > 0) {
                CustomNotification *cN = (CustomNotification*) (this->notifications->First());
                this->notifications->Delete(0);
                delete cN;
        }
        delete (this->notifications);
        this->audioPlayer->stopAndReset();
        delete (this->audioPlayer);
        this->audioPlayer = NULL;
        delete (this->servers);
        delete[] (this->games);
}

BandwidthUsage OFPMonitorModel::getBandwidthUsage() {
        return this->level;
}

void OFPMonitorModel::setVolume(int v) {
        this->volume = v;
        this->NotifyObserver();
}

void __fastcall OFPMonitorModel::onQueryTimer(TObject *Sender) {
        if(!this->querying) {
                this->querying = true;
                if(this->serversToQuery.size() > 0) {

                        QueryRequest *qr = this->serversToQuery.front();

                        int serverID = qr->getServerID();
                        Server *svr = this->getServerByID(serverID);
                        if(svr != NULL) {
                                bool success = true;
                                if(!(qr->getQuery().IsEmpty())) {
                                        success = this->net->sendUdpMessage(svr->getIP(), svr->getGamespyPort(), qr->getQuery());
                                }
                                int timeOutLimit = (int)(30 / this->interval);
                                if(this->interval >= 15) {
                                        timeOutLimit = 2;
                                }
                                svr->queryIsAboutToBeSent(qr->getQuery(), success, timeOutLimit);
                        }
                        delete qr;
                        this->serversToQuery.pop_front();
                } else {
                        this->queryTimer->Enabled = false;
                }
                this->querying = false;
        }                              
}

void OFPMonitorModel::ProcessMessages() {
        if(this->processing ||this->shuttingDown) { return; }
        this->processing = true;
        while(this->net->messageList.size() > 0) {
                Message *msg = this->net->messageList.front();
                if(!this->servers->incomingMessage(msg)) {
                        // message has not been handled.
                        // message is not in expected format,
                        // could be corrupted or garbage
                }
                delete msg;
                this->net->messageList.pop_front();
        }
        for(int i = 0; i < this->servers->getServerCount(); i++) {
                Server *svr = this->servers->getServer(i);
                if(svr != NULL) {
                        if(svr->hasStatusChanged()) {
                                StatusChange *sc = svr->takeStatusChange();
                                if(sc != NULL) {
                                        this->statusChanges.push_back(sc);
                                        if(svr->isWatched()) {
                                                this->playAudioServerStatus(sc);
                                        }
                                        if(svr->isAutoJoin()) {
                                                if(sc->getOldStatus() == SERVERSTATE_PLAYING &&
                                                   sc->getCurrentStatus() != SERVERSTATE_PLAYING) {
                                                        this->startTheGame(this->getMatchingGame(svr->getServerID()), svr->getAutoJoinConf());
                                                        this->disableAutoJoin();
                                                }
                                        }
                                }
                        }
                        this->checkCustomNotifications(svr->getServerID());
                }
        }
        if(this->audioPlayer != NULL) {
                if(this->customNotifications) {
                        for(int i = 0; i < this->notifications->Count; i++) {
                                CustomNotification *cN = this->getNotification(i);
                                if(cN != NULL) {
                                        AudioTask *aT = cN->getAudioTask();
                                        if(cN->hasNewClients()) {
                                                if(!this->audioPlayer->addAudioTask(aT)) {
                                                        this->audioPlayer->restartTask(aT->getAlias());
                                                }
                                        } else if(!cN->hasClients()) {
                                                this->audioPlayer->removeAudioTask(aT->getAlias());
                                        }
                                }
                        }
                } else {
                        for(int i = 0; i < this->notifications->Count; i++) {
                                CustomNotification *cN = this->getNotification(i);
                                if(cN != NULL) {
                                        AudioTask *aT = cN->getAudioTask();
                                        this->audioPlayer->removeAudioTask(aT->getAlias());
                                        if(aT->hasStarted()) {
                                                aT->reset();
                                        }
                                }
                        }
                }
        }
        this->processing = false;
}

void OFPMonitorModel::checkCustomNotifications(int serverID) {
        for(int i = 0; i < this->notifications->Count; i++) {
                CustomNotification *cN = this->getNotification(i);
                Server *svr = this->getServerByID(serverID);
                if(cN != NULL && svr != NULL) {
                        String ident = svr->getGamespyAddress();
                        bool alreadySet = cN->hasClient(ident);
                        if(this->customNotifications) {
                                ServerFilterResult sfr = svr->checkFilter(cN->getFilter());
                                if(sfr >= SFR_PASSED) {
                                        if(!alreadySet) {
                                                cN->addClient(ident);
                                        }
                                } else {
                                        if(alreadySet) {
                                                cN->removeClient(ident);
                                        }
                                }
                        } else if(alreadySet) {
                                cN->removeClient(ident);
                        }
                }
        }
}

void OFPMonitorModel::queryServers() {
        this->servers->createQueryRequests(this->serversToQuery, this->level);
        this->queryTimer->Enabled = true;
}

int OFPMonitorModel::findUserOnServer() {
        for(int i = 0; i < this->servers->getServerCount(); i++) {
                Server *svr = this->servers->getServer(i);
                if(svr != NULL) {
                        Game *g = this->getMatchingGame(svr->getServerID());
                        if(g != NULL) {
                                String profile = g->getProfileName();
                                if(svr->isPlayerOnServer(profile, true)) {
                                        return svr->getServerID();
                                }
                        }
                }
        }
        return NULL_SERVERID;
}

void OFPMonitorModel::setInterval(int seconds) {
        this->interval = seconds;
        this->NotifyObserver();
}

int OFPMonitorModel::getInterval() {
        return (this->interval);
}

void OFPMonitorModel::setBandwidthUsage(int level) {
        switch(level) {
                case 3:
                        this->level = VeryLow;
                        break;
                case 2:
                        this->level = Low;
                        break;
                case 1:
                        this->level = Moderate;
                        break;
                case 0:
                default:
                        this->level = High;
        }
        this->NotifyObserver();
}

void OFPMonitorModel::readSettings(TStringList *file) {
        ConfigSection *general = new ConfigSection("General");
        general->add(new ConfigEntry("Interval", dtInt, (void*)(&(this->interval))));
        general->add(new ConfigEntry("LangFile", dtString, (void*)(&(this->languagefile))));
        general->add(new ConfigEntry("customNotifications", dtBool, (void*)(&(this->customNotifications))));
        general->add(new ConfigEntry("BandwidthUsage", dtInt, (void*)(&(this->level))));
        general->add(new ConfigEntry("checkUpdateAtStart", dtBool, (void*)(&(this->checkUpdateAtStart))));
        general->add(new ConfigEntry("checkMasterServersAtStart", dtBool, (void*)(&(this->checkMasterServersAtStart))));
        general->add(new ConfigEntry("Volume", dtInt, (void*)(&(this->volume))));
        general->scan(file, 0);
        delete general;

        if(!FileExists(this->languagefile)) {
                String english = "OFPM_English.lang";
                if(FileExists(this->getWorkDir() + "\\" + english)) {
                        this->setLanguageFile(english);
                }
        }

        std::list<String> masterServerList;
        ConfigSection *servers = new ConfigSection("MasterServers");
        servers->add(new ConfigEntry("", dtServerItem, (void*)(&masterServerList)));
        servers->scan(file, 0);
        delete servers;
        while(masterServerList.size() > 0) {
                String s = masterServerList.front();
                this->masterServers->Add(s);
                masterServerList.pop_front();
        }
        
        int lineIndex = 0;
        String exe, player, name;
        ConfigSection *game = new ConfigSection("Game");
        game->add(new ConfigEntry("Exe", dtString, (void*)(&exe)));
        game->add(new ConfigEntry("LastPlayer", dtStringQuoted, (void*)(&player)));
        game->add(new ConfigEntry("Name", dtString, (void*)(&name)));
        bool gameSet = false;
        while(lineIndex < file->Count) {
                exe = "", player = "", name = "";
                lineIndex = game->scan(file, lineIndex);
                if(lineIndex < file->Count) {
                        OFPGames gameid = getGameId(name);
                        if(isValidGameID(gameid)) {
                                this->setGame(gameid, exe, player);
                                gameSet = true;
                        }
                }
        }
        delete game;

        if(!gameSet) {
                for(int i = 0; i < GAMESTOTAL; i++) {
                        Game *g = this->getGame((OFPGames)i);
                        if(g != NULL) {
                                g->autodetect("");
                        }
                }
        }
        
        lineIndex = 0;
        String password, mods, parameters, label, gameStr;
        ConfigSection *conf = new ConfigSection("Conf");
        conf->add(new ConfigEntry("Password", dtString, (void*)(&password)));
        conf->add(new ConfigEntry("Mods", dtString, (void*)(&mods)));
        conf->add(new ConfigEntry("Parameters", dtString, (void*)(&parameters)));
        conf->add(new ConfigEntry("Label", dtString, (void*)(&label)));
        conf->add(new ConfigEntry("Game", dtString, (void*)(&gameStr)));
        while(lineIndex < file->Count) {
                parameters = "", gameStr = "", mods = "", label = "", password = "";
                lineIndex = conf->scan(file, lineIndex);
                if(lineIndex < file->Count) {
                        OFPGames gameid = getGameId(gameStr);
                        if(isValidGameID(gameid)) {
                                this->games[gameid]->addConfiguration(new Configuration(
                                        gameid, label, mods, password, parameters));
                        }
                }
        }
        delete conf;

        lineIndex = 0;

        String notifName, soundFile, color, missionF, serverF, playerF;
        int statusFilter, volume, minPlayers, maxPlayers, start, end;
        bool repeat = false;
        ConfigSection *notification = new ConfigSection("CustomNotification");
        notification->add(new ConfigEntry("name", dtString, (void*)(&notifName)));
        notification->add(new ConfigEntry("missionFilter", dtString, (void*)(&missionF)));
        notification->add(new ConfigEntry("serverFilter", dtString, (void*)(&serverF)));
        notification->add(new ConfigEntry("playerFilter", dtString, (void*)(&playerF)));
        notification->add(new ConfigEntry("statusFilter", dtInt, (void*)(&statusFilter)));
        notification->add(new ConfigEntry("soundFile", dtString, (void*)(&soundFile)));
        notification->add(new ConfigEntry("playbackVolume", dtInt, (void*)(&volume)));
        notification->add(new ConfigEntry("playbackStart", dtInt, (void*)(&start)));
        notification->add(new ConfigEntry("playbackEnd", dtInt, (void*)(&end)));
        notification->add(new ConfigEntry("markingColor", dtString, (void*)(&color)));
        notification->add(new ConfigEntry("minimumPlayers", dtInt, (void*)(&minPlayers)));
        notification->add(new ConfigEntry("maximumPlayers", dtInt, (void*)(&maxPlayers)));
        notification->add(new ConfigEntry("repeat", dtBool, (void*)(&repeat)));
        while(lineIndex < file->Count) {
                notifName = "Unnamed", soundFile = "", color = "clNone", missionF = "", serverF = "", playerF = "";
                statusFilter = 0, volume = 100, minPlayers = -1, maxPlayers = -1, start = 0, end = -1;
                lineIndex = notification->scan(file, lineIndex);
                if(lineIndex < file->Count) {
                        StringSplitter sspm(missionF);
                        sspm.setKeepEmptyParts(false);
                        TStringList *missions = sspm.split(";");
                        StringSplitter ssps(serverF);
                        ssps.setKeepEmptyParts(false);
                        TStringList *servers = ssps.split(";");
                        StringSplitter sspp(playerF);
                        sspp.setKeepEmptyParts(false);
                        TStringList *players = sspp.split(";");
                        ServerFilter *sf = new ServerFilter(missions, servers, players);
                        sf->parseBinaryStatusFilter(statusFilter);
                        sf->setMinPlayers(minPlayers);
                        sf->setMaxPlayers(maxPlayers);
                        AudioTask *task = new AudioTask(soundFile, this->generateNewAudioAlias() , repeat);
                        task->setPlayLength(start, end);
                        task->setVolume(volume);
                        CustomNotification *notif = new CustomNotification(notifName, sf, task, color);
                        this->addNotification(notif);
                }
        }
        delete notification;
        this->NotifyObserver();
} 

void OFPMonitorModel::setGame(OFPGames id, String exe, String player) {
        if(isValidGameID(id) && FileExists(exe)) {
                this->games[id]->setActive(true);
                this->games[id]->autodetect(exe, player);
        }
}

void OFPMonitorModel::removeGame(OFPGames id) {
        if(isValidGameID(id)) {
                this->games[id]->setActive(false);
        }
}

Game* OFPMonitorModel::getGame(OFPGames id) {
        if(isValidGameID(id)) {
                return (this->games[id]);
        }
        return NULL;
}

Game* OFPMonitorModel::getMatchingGame(int actVer, int reqVer) {
        Game *out = NULL;
        for(int i = 0; i < GAMESTOTAL; i++) {
                if(this->games[i]->isActive()) {
                        if(this->games[i]->checkIfCorrectGame(actVer, reqVer)) {
                                out = this->games[i];
                                break;
                        }
                }
        }
        return out;
}

Game* OFPMonitorModel::getMatchingGame(int serverID) {
        Server *srv = this->getServerByID(serverID);
        if(srv != NULL) {
                return this->getMatchingGame(srv->getActualVersion(), srv->getRequiredVersion());
        }
        return NULL;
} 

bool OFPMonitorModel::hasServerStatusChanged() {
        return this->statusChanges.size() > 0;
}

StatusChange* OFPMonitorModel::takeStatusChange() {
        StatusChange *sc = NULL;
        if(this->hasServerStatusChanged()) {
                sc = this->statusChanges.front();
                this->statusChanges.pop_front();
        }
        return sc;
}

list<int> OFPMonitorModel::getAllMatchingServers(ServerFilter *filter) {
        list<int> matchingServers;
        for(int i = 0; i < this->servers->getServerCount(); i++) {
                Server *srv = this->servers->getServer(i);
                if(srv != NULL) {
                        if(filter != NULL) {
                                ServerFilterResult sfr = srv->checkFilter(filter);
                                if(sfr > SFR_NOTPASSED) {
                                        matchingServers.push_back(srv->getServerID());
                                }
                        } else {
                                matchingServers.push_back(srv->getServerID());
                        }
                }
        }
        return matchingServers;
}

int OFPMonitorModel::getOnlineServerCount() {
        int online = 0;
        for(int i = 0; i < this->servers->getServerCount(); i++) {
                Server *srv = this->servers->getServer(i);
                if(srv != NULL) {
                        if(srv->isOnline() && !srv->isBlocked()) {
                                online++;
                        }
                }
        }
        return online;
}

int OFPMonitorModel::getTotalServerCount() {
        return this->servers->getServerCount();
}

void OFPMonitorModel::disableAutoJoin() {
        for(int i = 0; i < this->servers->getServerCount(); i++) {
                Server *srv = this->servers->getServer(i);
                if(srv != NULL) {
                        srv->setAutoJoin(false, "");
                }
        }                                           
}

void OFPMonitorModel::playAudioServerStatus(StatusChange *status) {
        String file = this->AppWorkdir + "\\sound\\";
        String alias = status->getServerAddress();
        int resourceIndex = 0;
        switch(status->getCurrentStatus()) {
                case SERVERSTATE_EDITING:
                case SERVERSTATE_UNDEFINED:
                case SERVERSTATE_CREATING:
                        file += "creating";
                        resourceIndex = 1;
                        break;
                case SERVERSTATE_WAITING:
                        file += "waiting";
                        resourceIndex = 2;
                        break;
                case SERVERSTATE_BRIEFING:
                        file += "briefing";
                        resourceIndex = 3;
                        break;
                case SERVERSTATE_PLAYING:
                        file += "playing";
                        resourceIndex = 4;
                        break;
                case SERVERSTATE_DEBRIEFING:
                        file += "debriefing";
                        resourceIndex = 5;
                        break;
        }
        bool isWav = false;
        if(FileExists(file + ".mp3")) {
                file += ".mp3";
        } else if(FileExists(file + ".wav")) {
                file += ".wav";
                isWav = true;
        }
        if(FileExists(file)) {
                if(isWav && volume >= 100) {
                        PlaySound(file.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                } else {
                        AudioTask *at = new AudioTask(file, this->generateNewAudioAlias(), false);
                        at->setDeleteOnEnd(true);
                        at->setVolume(volume);
                        this->audioPlayer->addAudioTask(at);
                }
        } else if(resourceIndex > 0) {
                PlaySound(PChar(resourceIndex), NULL, SND_RESOURCE | SND_ASYNC);
        }
}

void OFPMonitorModel::startTheGame(Game *game, String configuration) {
        if(game != NULL) {
                if(game->isActive() && game->isValid()) {
                        String gameExe = game->getGameExe();
                        if(FileExists(gameExe)) {
                                String gameFolder = game->getGameFolder();
                                ShellExecute(NULL, "open", PChar(gameExe.c_str()), PChar(configuration.c_str()), PChar(gameFolder.c_str()), SW_NORMAL);
                        }
                }
        }
}

CustomNotification* OFPMonitorModel::getNotification(int index) {
        CustomNotification *out = NULL;
        if(index >= 0 && index < this->notifications->Count) {
                out = (CustomNotification*) (this->notifications->Items[index]);
        }
        return out;
}

void OFPMonitorModel::addNotification(CustomNotification *customN) {
        if(customN != NULL) {
                this->notifications->Add((void*)customN);
        }
}

TColor OFPMonitorModel::getMarkingColor(int serverID) {
        TColor out = clNone;
        for(int i = 0; i < this->notifications->Count; i++) {
                CustomNotification *cN = this->getNotification(i);
                Server *svr = this->getServerByID(serverID);
                if(cN != NULL && svr != NULL) {
                        if(cN->hasClient(svr->getGamespyAddress())) {
                                out = cN->getMarkingColor();
                                break;
                        }
                }
        }
        return out;
}

DWORD WINAPI masterServerQuery_ThreadProc (LPVOID lpdwThreadParam__ ) {
        OFPMonitorModel *main = (OFPMonitorModel*) lpdwThreadParam__; 
        TStringList *updateList = new TStringList;
        updateList->Sorted = true;
        updateList->Duplicates = dupIgnore;

        TStringList *selectedGames = new TStringList;
        selectedGames->Sorted = true;
        selectedGames->Duplicates = dupIgnore;

        TStringList *gameTokens = new TStringList;
        gameTokens->Sorted = true;
        gameTokens->Duplicates = dupIgnore;

        for(int i = 0; i < GAMESTOTAL; i++) {
                Game *g = main->getGame((OFPGames)i);
                if(g != NULL) {
                        if(g->isActive()) {
                                String token = getGameSpyTokenByGameId(g->getGameId());
                                int tmp;
                                if(!gameTokens->Find(token, tmp)) {
                                        gameTokens->Add(token);
                                        selectedGames->Add(getGameName(g->getGameId()));
                                }
                        }
                }
        }
        if(selectedGames->Count == 0) {
                selectedGames->Add(getGameName(ARMACWA));
        }

        delete gameTokens;

        for (int k = 0; k < selectedGames->Count; k++) {
                String gameIdName = selectedGames->Strings[k];
                String token = getGameSpyTokenByGameId(getGameId(gameIdName));
                String key = getGameSpyKeyByGameId(getGameId(gameIdName));
                if(key.IsEmpty()) {
                        continue;
                }
                TStringList *cms = new TStringList;
                main->getMasterServers(cms);
                for(int i = 0; i < cms->Count; i++) {
                        String serverdomain = cms->Strings[i];
                        TStringList *returnList = NULL;
                        ServerListLoader *loader = new ServerListLoader(5000);
                        try {
                                returnList = loader->getServerList(serverdomain, POWERSERVER_QUERYPORT, token, key);
                        } catch (Exception &E) {
                                ShowMessage(E.Message);
                        }
                        if(returnList != NULL) {
                                for(int j = 0; j < returnList->Count; j++) {
                                        String address = returnList->Strings[j];
                                        ServerConfigEntry *seI = new ServerConfigEntry(address.Trim());
                                        updateList->AddObject(address.Trim(), (TObject*) seI);
                                }
                                delete returnList;
                        }
                        delete loader;
                }
                delete cms;
        }
        if(updateList->Count > 0) {
                main->removeOfflineServers();
                while(updateList->Count > 0) {
                        ServerConfigEntry *p = (ServerConfigEntry*) (updateList->Objects[0]);
                        main->addServer(*p);
                        updateList->Delete(0);
                        delete p;
                }
                main->NotifyObserver();
        }

        delete updateList;
        delete selectedGames;
        main->setServerListUpdateDone(true);
        return 0;
}

void OFPMonitorModel::queryNewServerList() {
        this->queryNewServerList(true);
}

void OFPMonitorModel::queryNewServerList(bool dropOfflineServers) {
        if(this->isServerListUpdateDone()) {
                this->serverListUpdateDone = false;
                this->dropOfflineServersOnUpdate = dropOfflineServersOnUpdate;
                this->getServerListThread = CreateThread(0, 0, masterServerQuery_ThreadProc, (void*)this, 0, 0);
        }
}

bool OFPMonitorModel::isServerListUpdateDone() {
        return this->serverListUpdateDone;
}

void OFPMonitorModel::getAllAppTitlesOfGames(TStringList *titleList) {
        for(int i = 0; i < GAMESTOTAL; i++) {
                titleList->Add(getAppTitleByGameId((OFPGames)i));
        }
}

void OFPMonitorModel::getAllExesOfGames(TStringList *exeList, bool includeFWatch) {
        for(int i = 0; i < GAMESTOTAL; i++) {
                list<String> exes = getExesByGameId((OFPGames)i, includeFWatch);
                while(exes.size() > 0) {
                        exeList->Add(exes.front());
                        exes.pop_front();
                }
        }
}

String OFPMonitorModel::getWorkDir() {
        return this->AppWorkdir;
}

void OFPMonitorModel::setLanguageFile(String file) {
        this->languagefile = file;
        this->NotifyObserver();
}

String OFPMonitorModel::getLanguageFile() {
        return this->languagefile;
}

String OFPMonitorModel::getSettingsFile() {
        return this->settingsfile;
}

int OFPMonitorModel::getNotificationCount() {
        return this->notifications->Count;
}

bool OFPMonitorModel::isUpdateOnStartSet() {
        return this->checkUpdateAtStart;
}

bool OFPMonitorModel::isUpdateOfMasterServersOnStartSet() {
        return this->checkMasterServersAtStart;
}

void OFPMonitorModel::setUpdateOfMasterServersOnStart(bool on) {
        this->checkMasterServersAtStart = on;
}

String OFPMonitorModel::generateNewAudioAlias() {
        this->aliasCounter++;
        return ("OFPM_NOTIFICATION_" + IntToStr(this->aliasCounter));
}

void OFPMonitorModel::removeNotification(CustomNotification *notif) {
        if(notif != NULL) {
                AudioTask *at = notif->getAudioTask();
                this->audioPlayer->removeAudioTask(at->getAlias());
                this->notifications->Remove((void*)notif);
                delete notif;
        }
}

void OFPMonitorModel::setCustomNotifications(bool on) {
        this->customNotifications = on;
        this->NotifyObserver();
}

bool OFPMonitorModel::areCustomNotificationsOn() {
        return this->customNotifications;
}

void OFPMonitorModel::toggleUpdateOnStart(bool on) {
        this->checkUpdateAtStart = on;
}

int OFPMonitorModel::getVolume() {
        return this->volume;
}

void OFPMonitorModel::addServer(String address) {
        this->servers->addServer(address);
}

void OFPMonitorModel::addServer(ServerConfigEntry entry) {
        this->servers->addServer(entry);
}

bool OFPMonitorModel::removeServer(String address) {
        return (this->servers->removeServer(address));
}

void OFPMonitorModel::setServerListUpdateDone(bool done) {
        this->serverListUpdateDone = done;
        if(done) {
                this->dropOfflineServersOnUpdate = true;
        }
}

void OFPMonitorModel::getSettingsFileEntry(TStringList *settings) {
        settings->Add("[General]");
        settings->Add("LangFile = " + this->languagefile);
        settings->Add("Interval = " + IntToStr(this->interval));
        settings->Add("customNotifications = " + IntToStr(this->customNotifications));
        settings->Add("BandwidthUsage = " + IntToStr(this->level));
        settings->Add("checkUpdateAtStart = " + IntToStr(this->checkUpdateAtStart));
        settings->Add("checkMasterServersAtStart = " + IntToStr(this->checkMasterServersAtStart));
        settings->Add("Volume = " + IntToStr(this->volume));
        settings->Add("[\\General]");
        for(int i = 0; i < GAMESTOTAL; i++) {
                Game *g = this->getGame((OFPGames)i);
                if(g != NULL) {
                        g->getSettingsFileEntry(settings);
                }
        }
        for(int i = 0; i < this->getNotificationCount(); i++) {
                CustomNotification *notif = this->getNotification(i);
                if(notif != NULL) {
                        notif->getSettingsFileEntry(settings);
                }
        }
        this->servers->getSettingsFileEntry(settings);

        settings->Add("[MasterServers]");
        for(int i = 0; i < this->masterServers->Count; i++) {
                settings->Add(this->masterServers->Strings[i]);
        }
        settings->Add("[\\MasterServers]");
}

AudioPlayer* OFPMonitorModel::getAudioPlayer() {
        return this->audioPlayer;
}

void OFPMonitorModel::removeOfflineServers() {
        if(this->dropOfflineServersOnUpdate) {
                this->servers->removeOfflineServers();
        }
}

void OFPMonitorModel::addMasterServer(String domain) {
        if(!domain.IsEmpty()) {
                this->masterServers->Add(domain);
        }
}
void OFPMonitorModel::removeMasterServer(String domain) {
        int index;
        do {
                index = this->masterServers->IndexOf(domain);
                if(index >= 0) {
                        this->masterServers->Delete(index);
                }
        } while(index >= 0);
}

void OFPMonitorModel::getMasterServers(TStringList *domains) {
        domains->Clear();
        for(int i = 0; i < this->masterServers->Count; i++) {
                domains->Add(this->masterServers->Strings[i]);
        }
}

void OFPMonitorModel::parseMasterServerFile(TStringList *list) {
        std::list<String> masterServerList;
        ConfigSection *servers = new ConfigSection("Online");
        servers->add(new ConfigEntry("", dtServerItem, (void*)(&masterServerList)));
        servers->scan(list, 0);
        delete servers;
        while(masterServerList.size() > 0) {
                this->addMasterServer(masterServerList.front());
                masterServerList.pop_front();
        }

        servers = new ConfigSection("Offline");
        servers->add(new ConfigEntry("", dtServerItem, (void*)(&masterServerList)));
        servers->scan(list, 0);
        delete servers;
        while(masterServerList.size() > 0) {
                this->removeMasterServer(masterServerList.front());
                masterServerList.pop_front();
        }
}

Server* OFPMonitorModel::getServerByID(int serverID) {
        return this->servers->getServerByID(serverID);
}
