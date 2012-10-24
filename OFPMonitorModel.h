//---------------------------------------------------------------------------

#ifndef OFPMonitorModelH
#define OFPMonitorModelH

#include "ServerList.h"
#include "UDPNetwork.h"
#include "QueryRequest.h"
#include "OFPMonitorDefinitions.h"
#include "ServerFilter.h"
#include "CustomNotification.h"
#include "Game.h"
#include "AudioPlayer.h"
#include "Observer.h"
#include <vcl.h>
#include <list.h>

class OFPMonitorModel : public Observable {
        public:

                OFPMonitorModel(String settingsFile, ServerList *serverList);
                ~OFPMonitorModel();
                void ProcessMessages();
                void queryServers();
                void setVolume(int v);
                int getVolume();
                void setInterval(int seconds);
                int getInterval();
                void setBandwidthUsage(int level);
                BandwidthUsage getBandwidthUsage();
                Game* getMatchingGame(int actVer, int reqVer);
                Game* getMatchingGame(Server *srv);
                void readSettings(TStringList *file);
                void setGame(OFPGames id, String exe, String player);
                void removeGame(OFPGames id);
                Game* getGame(OFPGames id);
                Server* findUserOnServer();
                bool hasServerStatusChanged();
                StatusChange* takeStatusChange();
                list<Server*> getAllMatchingServers(ServerFilter *filter);
                int getTotalServerCount();
                int getOnlineServerCount();
                void addServer(String address);
                bool removeServer(String address);
                void addServer(ServerConfigEntry entry);
                void removeOfflineServers();
                void disableAutoJoin();
                void playAudioServerStatus(StatusChange *status);
                void startTheGame(Game *game, String configuration);
                CustomNotification* getNotification(int index);
                void addNotification(CustomNotification *notif);
                void removeNotification(CustomNotification *notif);
                int getNotificationCount();
                TColor getMarkingColor(Server *svr);
                void queryGameSpyList();
                bool isGameSpyUpdateDone();
                void getAllAppTitlesOfGames(TStringList *list);
                void getAllExesOfGames(TStringList *list);
                String getWorkDir();
                void setLanguageFile(String file);
                String getSettingsFile();
                String getLanguageFile();
                bool isUpdateOnStartSet();
                String generateNewAudioAlias();
                void setCustomNotifications(bool on);
                void toggleUpdateOnStart(bool on);
                bool areCustomNotificationsOn();
                bool isUpdateOnStartOn();
                void setGameSpyUpdateDone(bool done);
                void getSettingsFileEntry(TStringList *settings);
                AudioPlayer* getAudioPlayer();


        private:
                bool processing;
                bool querying;
                list<QueryRequest*> serversToQuery;
                list<StatusChange*> statusChanges;
                TList *notifications;
                TTimer *queryTimer;
                AudioPlayer *audioPlayer;
                ServerList *servers;
                UDPNetwork *net;
                HANDLE getServerListThread;

                void __fastcall onQueryTimer(TObject *Sender);
                void checkCustomNotifications(Server *svr);

                String AppWorkdir;
                String AppExe;
                int interval;
                bool customNotifications;
                bool checkUpdateAtStart;
                Game *games[GAMESTOTAL];
                String settingsfile;
                String languagefile;
                BandwidthUsage level;
                int volume;
                bool shuttingDown;
                bool gameSpyUpdateDone;
                int aliasCounter;
};







//---------------------------------------------------------------------------
#endif
