//---------------------------------------------------------------------------

#ifndef AddressH
#define AddressH

#include <vcl.h>

/**
   Represents an internet address with IP and port
 */

class Address {
        public:
                String ip;
                int port;
                Address();

                Address(String ip, int port);

                bool getAddress(String address, int defaultPort);
};

//---------------------------------------------------------------------------
#endif
