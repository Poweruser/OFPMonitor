//---------------------------------------------------------------------------

#ifndef ServerListLoaderH
#define ServerListLoaderH

#include <vcl.h>
#include <ScktComp.hpp>

class ServerListLoader {

        private:
                int timeout;
                String gamename;
                String gamekey;
                TClientSocket *socket;
                TWinSocketStream *stream;
                void reset();

        public:
                ServerListLoader(int timeout);
                ~ServerListLoader();
                TStringList* getServerList(String masterServerDomain, int port, String gamename, String gamekey);
                String getGamename();
                String getGameKey();
        
};

//---------------------------------------------------------------------------
#endif
