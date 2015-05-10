//---------------------------------------------------------------------------


#pragma hdrstop

#include "CustomNotification.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

CustomNotification::CustomNotification(String name, ServerFilter *filter, AudioTask *task, String color) {
        this->name = name;
        this->filter = filter;
        this->task = task;
        this->newClients = false;
        this->clients = new TStringList;
        this->clients->Sorted = true;
        this->clients->CaseSensitive = true;
        this->clients->Duplicates = dupIgnore;
        this->markingColor = StringToColor(color);
}
CustomNotification::~CustomNotification() {
        delete (this->clients);
        delete (this->filter);
        this->task->reset();
        delete (this->task);
}

ServerFilter* CustomNotification::getFilter() {
        return this->filter;
}

AudioTask* CustomNotification::getAudioTask() {
        return this->task;
}
String CustomNotification::getName() {
        return this->name;
}

TColor CustomNotification::getMarkingColor() {
        return this->markingColor;
}

bool CustomNotification::hasClients() {
        return (this->clients->Count > 0);
}

bool CustomNotification::hasClient(String ident) {
        int index;
        return (this->clients->Find(ident, index));
}

bool CustomNotification::hasNewClients() {
        bool out = this->newClients;
        this->newClients = false;
        return out;
}

void CustomNotification::addClient(String ident) {
        if(!this->hasClient(ident)) {
                this->clients->Add(ident);
                this->newClients = true;
        }
}

void CustomNotification::removeClient(String ident) {
        int index;
        if(this->clients->Find(ident, index)) {
                this->clients->Delete(index);
        }
}

void CustomNotification::setName(String name) {
        this->name = name;
}

void CustomNotification::setMarkingColor(TColor c) {
        this->markingColor = c;
}

void CustomNotification::getSettingsFileEntry(TStringList *settings) {
        settings->Add("[CustomNotification]");
        settings->Add("name = " + this->name);
        settings->Add("statusFilter = " + IntToStr(this->filter->getBinaryStatusFilter()));
        settings->Add("missionFilter = " + this->filter->concatenateFilter(this->filter->missionNames, ";"));
        settings->Add("serverFilter = "  + this->filter->concatenateFilter(this->filter->serverNames, ";"));
        settings->Add("playerFilter = "  + this->filter->concatenateFilter(this->filter->playerNames, ";"));
        if(this->filter->minPlayers > 0) {
                settings->Add("minimumPlayers = " + String(this->filter->minPlayers));
        }
        if(this->filter->maxPlayers > 0) {
                settings->Add("maximumPlayers = " + String(this->filter->maxPlayers));
        }
        settings->Add("markingColor = " + ColorToString(this->markingColor));
        settings->Add("soundFile = " + this->task->getSoundFile());
        settings->Add("playbackVolume = " + IntToStr(this->task->getVolume()));
        settings->Add("playbackStart = " + IntToStr(this->task->getStartTime().getPosition()));
        settings->Add("playbackEnd = " + IntToStr(this->task->getEndTime().getPosition()));
        settings->Add("repeat = " + IntToStr(this->task->isRepeatOn()));
        settings->Add("[\\CustomNotification]");
}
