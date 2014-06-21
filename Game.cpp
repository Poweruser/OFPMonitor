//---------------------------------------------------------------------------


#pragma hdrstop

#include "Game.h"
#include "FileVersion.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Game::Game(OFPGames id) {
        this->game = id;
        this->exeNames = getExesByGameId(id, false);
        this->gamespyToken = getGameSpyTokenByGameId(id);
        this->gamespyKey = getGameSpyKeyByGameId(id);
        this->fullName = getFullGameNameByGameId(id);
        this->set = false;
        this->exe = "";
        this->folder = "";
        this->player = "";
        this->version = 0;
        this->startupConfs = new TList;
}

Game::~Game() {
        while(this->startupConfs->Count > 0) {
                Game *g = (Game*) (this->startupConfs->First());
                this->startupConfs->Delete(0);
                delete g;                     
        }
        delete (this->startupConfs);
}

String Game::getGameFolder() {
        return this->folder;
}

String Game::getGameExe() {
        return this->exe;
}

bool Game::isValid() {
        return FileExists(this->exe);
}

void Game::autodetect(String exe) {
        this->autodetect(exe, "");
}

void Game::autodetect(String exe, String player) {
        list<String> exes = getExePathsByGameId(this->game, false);
        if(!exe.IsEmpty()) { exes.push_front(exe); }
        for(list<String>::iterator ci = exes.begin(); ci != exes.end(); ++ci) {
                if(FileExists(*ci)) {
                        this->exe = (*ci);
                        this->folder = this->getFolder(this->exe);
                        this->queryVersion();
                        this->detectPlayer(player);
                        this->setActive(true);
                        break;
                }
        }
}

void Game::detectPlayer(String setP) {
        list<String> regPlayer = getRegistryPathByGameId(this->game);
        String regP = GetRegistryValue(HKEY_CURRENT_USER, regPlayer, "Player Name");
        list<String> profiles = findPlayerProfiles();
        bool fRegPlayer = false, fSetPlayer = false;
        for (list<String>::iterator ci = profiles.begin(); ci != profiles.end(); ++ci) {
                if((*ci) == setP && !setP.IsEmpty()) {
                        fSetPlayer = true;
                }
                if((*ci) == regP && !regP.IsEmpty()) {
                        fRegPlayer = true;
                }
        }
        if(fSetPlayer) {
                this->player = setP;
        } else if(fRegPlayer) {
                this->player = regP;
        } else if(profiles.size() > 0) {
                this->player = profiles.front();
        }
}

void Game::queryVersion() {
        if(FileExists(this->exe)) {
                String fileToQuery = "";
                String file = ExtractFileName(this->exe);
                if(isFileFWatch(file)) {
                        String path = ExtractFileDir(this->exe);
                        list<String> exeList = getExesByGameId(this->game, false);
                        for(list<String>::iterator ci = exeList.begin(); ci != exeList.end(); ++ci) {
                                String fullPath = path;
                                fullPath += "\\";
                                fullPath += (*ci);
                                if(FileExists(fullPath)) {
                                        fileToQuery = fullPath;
                                        break;
                                }
                        }
                } else {
                        fileToQuery = this->exe;
                }
                FileVersion *fv = new FileVersion(fileToQuery);
                this->version = fv->getOFPVersion();
                delete fv;
        }
}

bool Game::checkIfCorrectGame(int actVer, int reqVer) {
        if(!this->set) { return false; }
        return (reqVer <= this->version && this->version <= actVer && !this->player.IsEmpty());
}

int Game::getConfigurationsCount() {
        return (this->startupConfs->Count);
}

String Game::getFolder(String in) {
        String out = "";
        for(int i = in.Length() - 1; i >= 0; i--) {
                if(in.SubString(i,1) == "\\") {
                        out = in.SubString(0, i).Trim();
                        break;
                }
        }
        return out;
}

void Game::setActive(bool active) {
        this->set = active;
}

bool Game::isActive() {
        return this->set;
}

OFPGames Game::getGameId() {
        return this->game;
}

Configuration* Game::getConfiguration(int index) {
        Configuration *out = NULL;
        if(index >= 0 && index < this->startupConfs->Count) {
                out = (Configuration*) (this->startupConfs->Items[index]);
        }
        return out;
}

void Game::addConfiguration(Configuration *conf) {
        if(conf != NULL) {
                if(conf->getGameId() == this->game) {
                        this->startupConfs->Add((TObject*)conf);
                }
        }
}

void Game::deleteConfiguration(Configuration *conf) {
        for(int i = 0; i < this->startupConfs->Count; i++) {
                Configuration *c = this->getConfiguration(i);
                if(c != NULL) {
                        if(c == conf) {
                                this->startupConfs->Delete(i);
                                delete conf;
                                conf = NULL;
                        }
                }
        }
}

void Game::exchangeConfs(int index1, int index2) {
        if(index1 >= 0 && index1 < this->startupConfs->Count &&
           index2 >= 0 && index2 < this->startupConfs->Count) {
                this->startupConfs->Exchange(index1, index2);
        }
}

String Game::getProfileName() {
        return this->player;
}

String Game::createDefaultStartLine(String ip, int port, String mods, String password) {
        String out = "";
        out += " -nosplash -nomap ";
        out += " -connect=" + ip;
        out += " -port=" + IntToStr(port);
        if(!this->player.IsEmpty()) {
                out += " \"-name=" + this->player + "\"";
        }
        if(!mods.IsEmpty()) {
                out += " \"-mod="+ mods +"\"";
        }
        if(!password.IsEmpty()) {
                out += " \"-password=" + password + "\"";
        }
        return out;
}

String Game::getGamespyToken() {
        return this->gamespyToken;
}

String Game::getGamespyKey() {
        return this->gamespyKey;
}

String Game::getFullName() {
        return this->fullName;
}

int Game::getFileVersion() {
        return this->version;
}

list<String> Game::findPlayerProfiles() {
        list<String> profiles;
        if(!this->folder.IsEmpty()) {
                TSearchRec daten;
                if(0 == FindFirst((this->folder +"\\Users\\*").c_str(), faDirectory, daten)) {
                        try {
                                do {
                                        if(     daten.Size == 0 &&
                                                daten.Name != "." &&
                                                daten.Name != ".." &&
                                                FileExists(this->folder + "\\Users\\" + daten.Name + "\\UserInfo.cfg")) {
                                                profiles.push_back(String(daten.Name));
                                        }
                                } while(FindNext(daten) == 0);
                        }__finally
                        {
                                FindClose(daten);
                        }
                }
        }
        return profiles;
}

void Game::setProfileName(String name) {
        this->player = name;
}

void Game::getSettingsFileEntry(TStringList *settings) {
        if(this->isActive()) {
                settings->Add("[Game]");
                settings->Add("Name = " + getGameName(this->game));
                settings->Add("Exe = " + this->exe);
                if(!this->player.IsEmpty()) {
                        settings->Add("LastPlayer = \"" + this->player + "\"");
                }
                settings->Add("[\\Game]");
        }
        for(int i = 0; i < this->getConfigurationsCount(); i++) {
                Configuration *conf = this->getConfiguration(i);
                if(conf != NULL) {
                        conf->getSettingsFileEntry(settings);
                }
        }
}

