//---------------------------------------------------------------------------

#ifndef ChatSettingsH
#define ChatSettingsH

#include <vcl.h>

class ChatSettings {
        private:
                String host;
                int port;
                String channel;
                String userName;
                bool autoConnect;

        public:

                ChatSettings();
                ChatSettings(String host, int port, String channel, String userName, bool ac);
                void setSettings(String host, int port, String channel, String userName, bool ac);
                String getHost();
                int getPort();
                String getChannel();
                String getUserName();
                bool isAutoConnectOn();
                void getSettingsFileEntry(TStringList *settings);
                void readSettings(TStringList *file);
                void setDefault();
};
//---------------------------------------------------------------------------
#endif
