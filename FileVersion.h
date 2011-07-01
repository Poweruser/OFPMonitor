#ifndef FileVersionH
#define FileVersionH

#include <vcl.h>

class FileVersion {
       private:
                void *VersionInfo;
                void *FixedInfo;

       public:
                FileVersion(String file);

                ~FileVersion();

                unsigned short majorVersion ();
                unsigned short buildVersion ();

                int getVersion();
};

#endif