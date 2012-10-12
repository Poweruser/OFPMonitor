//---------------------------------------------------------------------------

#ifndef CustomNotificationH
#define CustomNotificationH

#include "ServerFilter.h"
#include "AudioTask.h";
#include <vcl.h>


class CustomNotification {
        public:
                CustomNotification (String name, ServerFilter *filter, AudioTask *task, String color);
                ~CustomNotification();
                ServerFilter* getFilter();
                AudioTask* getAudioTask();
                String getName();
                void setName(String name);
                TColor getMarkingColor();
                void setMarkingColor(TColor c);
                bool hasClients();
                bool hasNewClients();
                bool hasClient(String ident);
                void addClient(String ident);
                void removeClient(String ident);
                void getSettingsFileEntry(TStringList *settings);

        private:
                bool newClients;
                String name;
                TStringList *clients;
                ServerFilter *filter;
                AudioTask *task;
                TColor markingColor;
};
//---------------------------------------------------------------------------
#endif
