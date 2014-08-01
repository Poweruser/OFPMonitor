//---------------------------------------------------------------------------

#ifndef AudioTaskH
#define AudioTaskH

#include <vcl.h>
#include "AudioPosition.h"

class AudioTask {
        public:
                AudioTask(String file, String alias, bool repeat);
                void setPlayLength(int start, int end);
                void setVolume(int volume);
                int getVolume();
                void play();
                bool hasEnded();
                bool hasStarted();
                void stop();
                bool isRepeatOn();
                void setRepeat(bool on);
                String getAlias();
                void reset();
                String getSoundFile();
                AudioPosition getStartTime();
                AudioPosition getEndTime();
                void setFile(String file);
                void setDeleteOnEnd(bool active);
                bool isDeleteOnEndSet();
                AudioPosition getCurrentPosition();
                bool hasInitiatedPlay();

        private:
                bool error;
                bool opened;
                bool started;
                bool stopped;
                bool repeat;
                String file;
                String alias;
                int volume;
                int start;
                int end;
                bool deleteOnEnd;
                bool initiatedPlay;

                int readSongLength(String file);
};

//---------------------------------------------------------------------------
#endif
