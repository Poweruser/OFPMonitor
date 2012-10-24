//---------------------------------------------------------------------------


#pragma hdrstop

#include "ChatMessage.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ChatMessage::ChatMessage(String sender, String channel, String message, bool controlMsg) {
        this->sender = sender;
        this->channel = channel;
        this->message = message;
        this->controlMsg = controlMsg;
}

String ChatMessage::getSender() {
        return this->sender;
}

String ChatMessage::getChannel() {
        return this->channel;
}

String ChatMessage::getMessage() {
        return this->message;
}

bool ChatMessage::isControlMsg() {
        return this->controlMsg;
}

bool ChatMessage::isChannelMsg() {
        return (this->channel != this->sender);
}

bool ChatMessage::isPrivateMsg() {
        return (this->channel == this->sender);
}
