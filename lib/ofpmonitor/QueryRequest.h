//---------------------------------------------------------------------------

#ifndef QueryRequestH
#define QueryRequestH

#include "Server.h"
#include <vcl.h>

class QueryRequest {
        public:
                QueryRequest(int serverID, String query);
                int getServerID();
                String getQuery();

        private:
                int serverID;
                String query;

};







//---------------------------------------------------------------------------
#endif
