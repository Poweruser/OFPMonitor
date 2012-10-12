//---------------------------------------------------------------------------


#pragma hdrstop

#include "AudioPlayer.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


AudioPlayer::AudioPlayer() {
        this->audioTimer = new TTimer(NULL);
        this->audioTimer->Interval = 20;
        this->audioTimer->Enabled = false;
        this->audioTimer->OnTimer = onAudioTimer;
        this->tasks = new TList;

}

AudioPlayer::~AudioPlayer() {
        this->audioTimer->Enabled = false;
        delete (this->audioTimer);
        this->stopAndReset();
        delete (this->tasks);
}

void __fastcall AudioPlayer::onAudioTimer(TObject *Sender) {
        this->audioTimer->Enabled = this->checkTasks();
}

AudioTask* AudioPlayer::getTask(int i) {
        AudioTask *out = NULL;
        if(i >= 0 && i < this->tasks->Count) {
                out = (AudioTask*)(this->tasks->Items[i]);
        }
        return out;
}

AudioTask* AudioPlayer::getTask(String alias) {
        for(int i = 0; i < this->tasks->Count; i++) {
                AudioTask *t = this->getTask(i);
                if(t != NULL) {
                        if(t->getAlias() == alias) {
                                return t;
                        }
                }
        }
        return NULL;
}

bool AudioPlayer::hasAlias(String alias) {
        for(int i = 0; i < this->tasks->Count; i++) {
                AudioTask *t = this->getTask(i);
                if(t != NULL) {
                        if(t->getAlias() == alias) {
                                return true;
                        }
                }
        }
        return false;
}

bool AudioPlayer::addAudioTask(AudioTask *task) {
        if(!this->hasAlias(task->getAlias())) {
                this->tasks->Add((void*)task);
                task->play();
                this->audioTimer->Enabled = true;
                return true;
        }
        return false;
}

void AudioPlayer::stopAndReset() {
        while(this->tasks->Count > 0) {
                AudioTask *t = (AudioTask*)(this->tasks->Items[0]);
                t->stop();
                if(t->isDeleteOnEndSet()) {
                        delete t;
                }
                this->tasks->Delete(0);
        }
}

bool AudioPlayer::checkTasks() {
        bool hasJob = false;
        for(int i = 0; i < this->tasks->Count; i++) {
                AudioTask *t = this->getTask(i);
                if(t != NULL) {
                        hasJob = true;
                        if(t->hasEnded()) {
                                t->stop();
                                if(t->isRepeatOn()) {
                                                t->reset();
                                                t->play();
                                } else {
                                        this->tasks->Remove((void*)t);
                                        if(t->isDeleteOnEndSet()) {
                                                delete t;
                                        }
                                }
                        }
                }
        }
        return hasJob;
}

void AudioPlayer::removeAudioTask(String alias) {
        for(int i = 0; i < this->tasks->Count; i++) {
                AudioTask *t = this->getTask(i);
                if(t != NULL) {
                        if(t->getAlias() == alias) {
                                t->stop();
                                t->reset();
                                this->tasks->Remove((void*)t);
                                if(t->isDeleteOnEndSet()) {
                                        delete t;
                                }
                        }
                }
        }
}

void AudioPlayer::restartTask(String alias) {
        AudioTask *at = this->getTask(alias);
        if(at != NULL) {
                at->reset();
                at->play();
        }                  
}

AudioPosition AudioPlayer::getCurrentPosition(String alias) {
        AudioTask *at = this->getTask(alias);
        if(at != NULL) {
                return at->getCurrentPosition();
        }
        return AudioPosition(0);
}
