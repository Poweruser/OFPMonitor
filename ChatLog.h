//---------------------------------------------------------------------------

#ifndef ChatLogH
#define ChatLogH

#include <vcl.h>

class ChatLog {
        private:
                String name;
                TStringList *output;
                TStringList *input;
                bool changed;
                int linesLoaded;


        public:
                ChatLog(String name);
                ~ChatLog();
                void saveCurrentInput(TMemo *inputMemo);
                void loadThisChat(TMemo *outputMemo, TMemo *inputMemo);
                void syncChat(TMemo *outputMemo);
                void incomingMsg(String msg, bool control);
                bool hasNewMessages();
};
//---------------------------------------------------------------------------
#endif
