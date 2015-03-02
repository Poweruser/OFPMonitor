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
                Game* getMatchingGame(int serverID);
                void readSettings(TStringList *file);
                void setGame(OFPGames id, String exe, String player);
                void removeGame(OFPGames id);
                Game* getGame(OFPGames id);
                int findUserOnServer();
                bool hasServerStatusChanged();
                StatusChange* takeStatusChange();
                list<int> getAllMatchingServers(ServerFilter *filter);
                int getTotalServerCount();
                int getOnlineServerCount();
                void addServer(String address);
                bool removeServer(String address);
                Server* getServerByID(int serverID);
                void addServer(ServerConfigEntry entry);
                void removeOfflineServers();
                void disableAutoJoin();
                void playAudioServerStatus(StatusChange *status);
                void startTheGame(Game *game, String configuration);
                CustomNotification* getNotification(int index);
                void addNotification(CustomNotification *notif);
                void removeNotification(CustomNotification *notif);
                int getNotificationCount();
                TColor getMarkingColor(int serverID);
                void queryGameSpyList();
                bool isGameSpyUpdateDone();
                void getAllAppTitlesOfGames(TStringList *list);
                void getAllExesOfGames(TStringList *list, bool includeFWatch);
                String getWorkDir();
                void setLanguageFile(String file);
                String getSettingsFile();
                String getLanguageFile();
                bool isUpdateOnStartSet();
                bool isUpdateOfMasterServersOnStartSet();
                void setUpdateOfMasterServersOnStart(bool on);
                void addMasterServer(String domain);
                void removeMasterServer(String domain);
                void getMasterServers(TStringList *domains);
                String generateNewAudioAlias();
                void setCustomNotifications(bool on);
                void toggleUpdateOnStart(bool on);
                bool areCustomNotificationsOn();
                void setGameSpyUpdateDone(bool done);
                void getSettingsFileEntry(TStringList *settings);
                AudioPlayer* getAudioPlayer();
                void parseMasterServerFile(TStringList *list);

        private:
                bool processing;
                bool querying;
                list<QueryRequest*> serversToQuery;
                list<StatusChange*> statusChanges;
                TList *notifications;
                TStringList *masterServers;
                TTimer *queryTimer;
                AudioPlayer *audioPlayer;
                ServerList *servers;
                UDPNetwork *net;
                HANDLE getServerListThread;

                void __fastcall onQueryTimer(TObject *Sender);
                void checkCustomNotifications(int serverID);

                String AppWorkdir;
                String AppExe;
                int interval;
                bool customNotifications;
                bool checkUpdateAtStart;
                bool checkMasterServersAtStart;
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
