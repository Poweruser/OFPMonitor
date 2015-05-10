//---------------------------------------------------------------------------


#pragma hdrstop

#include "AudioTask.h"
#include <mmsystem.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

AudioTask::AudioTask(String file, String alias, bool repeat) {
        this->setFile(file);
        this->alias = alias;
        this->setRepeat(repeat);
        this->setPlayLength(-1,-1);
        this->volume = 100;
        this->error = false;
        this->opened = false;
        this->stopped = false;
        this->started = false;
        this->deleteOnEnd = false;
        this->initiatedPlay = false;
}

void AudioTask::setFile(String file) {
        this->file = file;
}

void AudioTask::setRepeat(bool on) {
        this->repeat = on;
}

void AudioTask::setPlayLength(int start, int end) {
        this->start = start;
        if(end <= 0) {
                this->end = this->readSongLength(this->file);
        } else {
                this->end = end;
        }
}

void AudioTask::setVolume(int volume) {
        this->volume = volume;
        if(!this->hasEnded() && (this->started || this->opened)) {
                mciSendString(("setaudio " + this->alias + " volume to " + IntToStr(this->volume*10)).c_str(), 0, 0, 0);
        }
}

int AudioTask::getVolume() {
        return this->volume;
}

void AudioTask::play() {
        this->initiatedPlay = true;
        if(FileExists(this->file) && !this->alias.IsEmpty()) {
                if(mciSendString(("Open \"" + this->file + "\" alias " + this->alias + " type MPEGVideo").c_str(),0,0,0)) {
                        this->error = true;
                } else {
                        this->opened = true;
                        this->setVolume(this->volume);
                }
                String range = "";
                if(this->start >= 0 && this->end >= 0) {
                        range = " from " + String(this->start) + " to " + String(this->end);
                }
                if(mciSendString(("play " + this->alias + range).c_str(), 0, 0, 0)) {
                        this->error = true;
                } else {
                        this->started = true;

                }
        }
}

bool AudioTask::hasEnded() {
        if(this->stopped) { return true; }
        if(!this->alias.IsEmpty() && this->started) {
                AudioPosition curr = this->getCurrentPosition();
                return (curr.getPosition() >= this->end || this->error);
        }
        return (this->started && this->error);
}

bool AudioTask::hasStarted() {
        return this->started;
}

void AudioTask::stop() {
        if(!this->alias.IsEmpty() && !this->stopped) {
                if(!mciSendString(("Close " + this->alias).c_str(), 0, 0, 0)) {
                        this->opened = false;
                        this->stopped = true;
                }
        }
}

bool AudioTask::isRepeatOn() {
        return this->repeat;
}

String AudioTask::getAlias() {
        return this->alias;
}

void AudioTask::reset() {
        if(this->opened || this->started) {
                this->started = false;
                this->stop();
        }
        this->initiatedPlay = false;
        this->opened = false;
        this->stopped = false;
        this->error = false;
}

int AudioTask::readSongLength(String file) {
        int out = 0;
        if(FileExists(file)) {
                if(!mciSendString(("open \"" + file + "\" alias LengthCheck").c_str(),0,0,0)) {
                        this->opened = true;
                        mciSendString("set LengthCheck time format milliseconds",0,0,0);
                        char text[128];
                        mciSendString("status LengthCheck length", text, 128, 0);
                        if(!mciSendString("close LengthCheck", 0, 0, 0)) {
                                this->opened = false;
                        }
                        out = StrToIntDef(text, 0);
                }
        }
        return out;
}

String AudioTask::getSoundFile() {
        return this->file;
}

AudioPosition AudioTask::getStartTime() {
        return AudioPosition(this->start);
}

AudioPosition AudioTask::getEndTime() {
        return AudioPosition(this->end);
}

void AudioTask::setDeleteOnEnd(bool active) {
        this->deleteOnEnd = active;
}

bool AudioTask::isDeleteOnEndSet() {
        return this->deleteOnEnd;
}

AudioPosition AudioTask::getCurrentPosition() {
        AudioPosition out = AudioPosition(0);
        if(!this->stopped && this->started && !this->alias.IsEmpty()) {
                char text[128];
                if(!mciSendString(("status " + this->alias + " position").c_str(), text, 128, 0)) {
                        int pos = StrToIntDef(String(text), -1);
                        if(pos >= 0) {
                                out = AudioPosition(pos);
                        }
                }
        }
        return out;
}

bool AudioTask::hasInitiatedPlay() {
        return this->initiatedPlay;
}


