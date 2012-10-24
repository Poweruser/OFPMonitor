//---------------------------------------------------------------------------


#pragma hdrstop

#include "ChatSettings.h"
#include "ConfigReader.h"

#define DEFAULT_IRCSERVER_HOST "irc.freenode.net"
#define DEFAULT_IRCSERVER_PORT 6666
#define DEFAULT_IRCSERVER_CHANNEL "#operationflashpoint1"

//---------------------------------------------------------------------------
#pragma package(smart_init)


ChatSettings::ChatSettings() {
        this->userName = "";
        this->autoConnect = false;        
        this->setDefault();
}

ChatSettings::ChatSettings(String host, int port, String channel, String userName, bool ac) {
        this->host = host;
        this->port = port;
        this->channel = channel;
        this->userName = userName;
        this->autoConnect = ac;
}

void ChatSettings::setSettings(String host, int port, String channel, String userName, bool ac) {
        this->host = host;
        this->port = port;
        this->channel = channel;
        this->userName = userName;
        this->autoConnect = ac;
}

void ChatSettings::setDefault() {
        this->host = DEFAULT_IRCSERVER_HOST;
        this->port = DEFAULT_IRCSERVER_PORT;
        this->channel = DEFAULT_IRCSERVER_CHANNEL;
}

/**
        Creates the section about the chat settings that will be
        written to the configuration file of the program
*/

void ChatSettings::getSettingsFileEntry(TStringList *settings) {
        settings->Add("[ChatSettings]");
        settings->Add("Host = " + this->host);
        settings->Add("Port = " + IntToStr(this->port));
        settings->Add("Channel = " + this->channel);
        String n = this->userName;
        if(n.SubString(1, 1) == " " || n.SubString(n.Length(), 1) == " ") {
                n = "\"" + n + "\"";
        }
        settings->Add("UserName = " + n);
        settings->Add("AutoConnect = " + IntToStr(this->autoConnect));
        settings->Add("[\\ChatSettings]");
}

String ChatSettings::getHost() {
        return this->host;
}

int ChatSettings::getPort() {
        return this->port;
}

String ChatSettings::getChannel() {
        return this->channel;
}

String ChatSettings::getUserName() {
        return this->userName;
}

bool ChatSettings::isAutoConnectOn() {
        return this->autoConnect;
}

String ChatSettings::extractNameFromValue(String in) {
        int start = 0;
        int end = 0;
        for(int i = 1; i < in.Length(); i++) {
                if(in.SubString(i, 1) == "\"") {
                        start = i;
                        break;
                }
        }
        for(int i = in.Length(); i > start; i--) {
                if(in.SubString(i, 1) == "\"") {
                        end = i;
                        break;
                }
        }
        if(end && start) {
                return in.SubString(start + 1, end - (start + 1));
        }
        return in;
}

void ChatSettings::readSettings(TStringList *file) {
        String user = this->userName;
        ConfigSection *chat = new ConfigSection("ChatSettings");
        chat->add(new ConfigEntry("AutoConnect", dtBool, (void*)(&(this->autoConnect))));
        chat->add(new ConfigEntry("Host", dtString, (void*)(&(this->host))));
        chat->add(new ConfigEntry("Port", dtInt, (void*)(&(this->port))));
        chat->add(new ConfigEntry("Channel", dtString, (void*)(&(this->channel))));
        chat->add(new ConfigEntry("UserName", dtString, (void*)(&user)));
        chat->scan(file, 0);
        delete chat;
        if(channel.SubString(1,1) != "#") {
                channel = "#" + channel;
        }
        this->userName = extractNameFromValue(user);
}


