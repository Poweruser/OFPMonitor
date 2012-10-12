//---------------------------------------------------------------------------

#ifndef WindowSettingsH
#define WindowSettingsH

#include <vcl.h>
#include <Grids.hpp>

#define WS_ServerTableColumns 7
#define WS_PlayerTableColumns 4

class WindowSettings {
        public:
                WindowSettings();
                float getRatioServerTable(int columnIndex);
                float getRatioPlayerTable(int columnIndex);
                void setRatioServerTable(int columnIndex, float value);
                void setRatioPlayerTable(int columnIndex, float value);
                void readSettings(TStringList *settings);
                int getHeight();
                int getWidth();
                int getTop();
                int getLeft();
                int getDevider();
                void setHeight(int height);
                void setWidth(int width);
                void setTop(int top);
                void setLeft(int left);
                void setDevider(int devider);
                void getSettingsFileEntry(TStringList *settings);
                float checkIfZero(float in, TStringGrid *grid);
                bool isAlwaysOnTopSet();
                void setAlwaysOnTop(bool active);

        private:
                int top;
                int left;
                int height;
                int width;
                int devider;
                bool alwaysOnTop;
                float serverTable[WS_ServerTableColumns];
                float playerTable[4];


};



//---------------------------------------------------------------------------
#endif
