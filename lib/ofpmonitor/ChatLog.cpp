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
        this->linesLoaded = 0;
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
        outputMemo->Lines->Assign(this->output);
        this->linesLoaded = this->output->Count;
        outputMemo->SelStart = outputMemo->Text.Length();
        outputMemo->SelLength = 0;
        inputMemo->Lines->Assign(this->input);
        this->changed = false;
}

void ChatLog::syncChat(TMemo *outputMemo) {
        while(this->linesLoaded < this->output->Count) {
                outputMemo->Lines->Add(this->output->Strings[this->linesLoaded]);
                this->linesLoaded++;
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
