//---------------------------------------------------------------------------

#ifndef ChatMessageH
#define ChatMessageH

#include <vcl.h>

class ChatMessage {
        private:
                String sender;
                String message;
                String channel;
                bool controlMsg;

        public:
                ChatMessage(String sender, String channel, String message, bool controlMsg);
                String getSender();
                String getChannel();
                String getMessage();
                bool isControlMsg();
                bool isChannelMsg();
                bool isPrivateMsg();
};


//---------------------------------------------------------------------------
#endif
