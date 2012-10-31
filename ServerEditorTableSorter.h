//---------------------------------------------------------------------------

#ifndef ServerEditorTableSorterH
#define ServerEditorTableSorterH

#include <vcl.h>

enum ServerEditorTableColumn { SETC_ID, SETC_IP, SETC_NAME, SETC_FAVORITES, SETC_WATCHED, SETC_PERSISTENT, SETC_BLOCKED };

class ServerEditorTableSorter {
        public:
                ServerEditorTableSorter();
                void reset();
                void setName();
                void setIP();
                void setID();
                void setFavorites();
                void setWatched();
                void setPersistent();
                void setBlocked();
                bool isNameSet();
                bool isIPSet();
                bool isIDSet();
                bool isFavoritesSet();
                bool isWatchedSet();
                bool isPersistentSet();
                bool isBlockedSet();
                bool isNormalOrder();

        private:
                ServerEditorTableColumn currentColumn;
                bool normalOrder;

                void setProperty(ServerEditorTableColumn setc);
};

//---------------------------------------------------------------------------
#endif
