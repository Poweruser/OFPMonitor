//---------------------------------------------------------------------------

#ifndef AddressH
#define AddressH

#include <vcl.h>

/**
   Represents an internet address with IP and port
 */

class Address {
        public:
                Address();
                bool readAddress(String address, int defaultPort, bool gamespy);
                String getIP();
                String getHostname();
                void setGamePort(int port);
                int getGamePort();
                int getGameSpyPort();
                bool isValid();
                String getAddress(bool hostname, bool gamespy);
                bool hasHostname();

        private:
                String ip;
                String hostname;
                int gamePort;
                int gameSpyPort;
                bool valid;

                int checkPortFormat(String port);
                bool checkIPFormat(String ip);
                String resolveHostnameToIP(String domain);
};

//---------------------------------------------------------------------------
#endif
