//---------------------------------------------------------------------------

#ifndef GameControlH
#define GameControlH

#include "Server.h"
#include "ProcessFinder.h"
#include "OFPMonitorModel.h"
#include "StatusChange.h"
#include "Observer.h"
#include <vcl.h>
#include <list.h>

class GameControl : public Observable {
        public:
                bool restoreGame;
                bool restoreOnCreating;
                bool restoreOnWaiting;
                bool restoreOnBriefing;
                bool restoreOnPlaying;
                bool restoreOnDebriefing;
                GameControl(OFPMonitorModel *ofpm);
                ~GameControl();
                bool verifyProcess();
                bool verifyServer();
                bool isAutoGreenOn();
                bool isRestoreGameOn();
                bool isAutoDetectOn();
                void setProcess(ProcessInfo *p);
                void setServer(int serverID);
                bool matchesProcess(ProcessInfo p);
                bool matchesProcess(ProcessInfo *p);
                bool matchesServer(String address);
                bool matchesServer(int serverID);
                void setGreenUpRepeat(bool enabled);
                bool getGreenUpRepeat();
                int getGreenUpDelay();
                void enableAutoGreenUp(bool enabled);
                void enableRestoreGame(bool enabled);
                void setAutoDetect(bool enabled);
                void setGreenUpDelay(int delay);
                void readSettings(TStringList *file);
                void ProcessMessages();
                void getSettingsFileEntry(TStringList *settings);


        private:
                OFPMonitorModel *ofpm;
                TTimer *autoGreenUpTimer;
                int selectedServerID;
                ProcessInfo proc;
                bool autoDetect;
                bool autoGreenUp;
                int greenUpDelay;
                bool greenUpRepeat;

                String checkBool(bool in);
                bool detectServer();
                bool detectProcess();
                void checkCurrentData();
                bool isProcessValid();
                void __fastcall onTimer(TObject *Sender);
                void sendGreenUpMessage();
                void statusChange(StatusChange *statusChange);
};



//---------------------------------------------------------------------------
#endif
