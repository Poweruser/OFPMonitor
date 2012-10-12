//---------------------------------------------------------------------------

#ifndef QueryRequestH
#define QueryRequestH

#include "Server.h"
#include <vcl.h>

class QueryRequest {
        public:
                QueryRequest(Server *svr, String query);
                Server* getServer();
                String getQuery();

        private:
                Server *svr;
                String query;

};







//---------------------------------------------------------------------------
#endif
