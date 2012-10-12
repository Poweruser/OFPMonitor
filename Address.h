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
                int getPort();
                bool isValid();
                String getAddress();

        private:
                String ip;
                int port;
                bool valid;
};

//---------------------------------------------------------------------------
#endif
