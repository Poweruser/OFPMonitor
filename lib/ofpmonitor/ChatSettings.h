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
                String audioFile;
                bool audioNotification;
                bool displayBallonHint;

        public:

                ChatSettings();
                void setSettings(String host, int port, String channel, String userName, bool ac);
                String getHost();
                int getPort();
                String getChannel();
                String getUserName();
                bool isAutoConnectOn();
                void getSettingsFileEntry(TStringList *settings);
                void readSettings(TStringList *file);
                void setDefault();
                bool isBallonHintOn();
                bool isAudioNotificationOn();
                void setBallonHint(bool enabled);
                void setAudioNotification(bool enabled);
                String getNotificationSoundFile();
                void setNotificationSoundFile(String file);
};
//---------------------------------------------------------------------------
#endif
