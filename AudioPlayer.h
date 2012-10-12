//---------------------------------------------------------------------------

#ifndef AudioPlayerH
#define AudioPlayerH

#include "AudioTask.h"
#include <vcl.h>

class AudioPlayer {
        private:
                TList *tasks;
                TTimer *audioTimer;
                AudioTask* getTask(int i);
                void __fastcall onAudioTimer(TObject *Sender);
                void updateList();

        public:
                AudioPlayer();
                ~AudioPlayer();
                bool addAudioTask(AudioTask *task);
                AudioTask* getTask(String alias);
                bool hasAlias(String alias);
                void stopAndReset();
                bool checkTasks();
                void removeAudioTask(String alias);
                void restartTask(String alias);
                AudioPosition getCurrentPosition(String alias);
};
//---------------------------------------------------------------------------
#endif
