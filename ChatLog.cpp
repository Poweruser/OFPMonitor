//---------------------------------------------------------------------------


#pragma hdrstop

#include "ChatLog.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



ChatLog::ChatLog(String name) {
        this->name = name;
        this->output = new TStringList();
        this->input = new TStringList();
        this->changed = false;
}

ChatLog::~ChatLog() {
        delete this->output;  
        delete this->input;
}

void ChatLog::saveCurrentInput(TMemo *inputMemo) {
        this->input->Clear();
        for(int i = 0; i < inputMemo->Lines->Count; i++) {
                this->input->Add(inputMemo->Lines->Strings[i]);
        }
}

void ChatLog::loadThisChat(TMemo *outputMemo, TMemo *inputMemo) {
        inputMemo->Lines->Clear();
        outputMemo->Lines->Clear();
        for(int i = 0; i < this->output->Count; i++) {
                outputMemo->Lines->Add(this->output->Strings[i]);
        }
        for(int i = 0; i < this->input->Count; i++) {
                inputMemo->Lines->Add(this->input->Strings[i]);
        }
        this->changed = false;
}

void ChatLog::syncChat(TMemo *outputMemo) {
        int line = outputMemo->Lines->Count;
        if(line > this->output->Count) {
                line = 0;
                outputMemo->Lines->Clear();
        }
        for(int i = line; i < this->output->Count; i++) {
                outputMemo->Lines->Add(this->output->Strings[i]);
        }
        this->changed = false;
}

void ChatLog::incomingMsg(String msg, bool control) {
        if(!msg.IsEmpty()) {
                this->output->Add(msg);
                if(!control) {
                        this->changed = true;
                }
        }
}

bool ChatLog::hasNewMessages() {
        return this->changed;
}
