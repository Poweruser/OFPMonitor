//---------------------------------------------------------------------------

#ifndef ServerEditorTableSorterH
#define ServerEditorTableSorterH

#include <vcl.h>

enum ServerEditorTableColumn { SETC_ID, SETC_IP, SETC_NAME };

class ServerEditorTableSorter {
        public:
                ServerEditorTableSorter();
                void reset();
                void setName();
                void setIP();
                void setID();
                bool isNameSet();
                bool isIPSet();
                bool isIDSet();
                bool isNormalOrder();

        private:
                ServerEditorTableColumn currentColumn;
                bool normalOrder;

                void setProperty(ServerEditorTableColumn setc);
};

//---------------------------------------------------------------------------
#endif
