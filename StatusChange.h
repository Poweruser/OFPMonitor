//---------------------------------------------------------------------------

#ifndef StatusChangeH
#define StatusChangeH

#include "OFPMonitorDefinitions.h"
#include <vcl.h>

class StatusChange {
        public:
                StatusChange(String serverAddress, int oldStatus, int currentStatus);
                String getServerAddress();
                int getOldStatus();
                int getCurrentStatus();
        private:
                int oldStatus;
                int currentStatus;
                String serverAddress;                 
};
//---------------------------------------------------------------------------
#endif
