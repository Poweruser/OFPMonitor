//---------------------------------------------------------------------------

#ifndef MessageH
#define MessageH

#include <vcl.h>

/**
   Each incoming answer of a server query will be first stored in a
   Message-Object, which holds all important information about it
   (IP, Port, Content, Time of arrival) and will be later procressed
   by the MessageReader
 */

class Message {
        public:
                String content;
                String ip;
                int port;
                DWORD toa;

                /**
                   Constructor

                   @ip  the ip the message came from
                   @port  the port it came from
                   @content  the message data
                   @toa  time the message arrived at
                         (is used to measure the ping)
                */

                Message(String ip, int port, String content, DWORD toa);
};
//---------------------------------------------------------------------------
#endif
