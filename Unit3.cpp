//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop      
#include "Unit2.h"
#include "Unit3.h"
#include <OFPMonitor\OFPMonitor.h>

using namespace OFPMonitor_Unit2;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWINDOW_LOCALGAME *WINDOW_LOCALGAME;

/**
   Launches OFP with the passed start up configuration
 */

void startTheGame(String configuration, String exe) {
        if(FileExists(exe)) {
                ShellExecute(NULL, "open", PChar(exe.c_str()), PChar(configuration.c_str()), PChar(WINDOW_SETTINGS->getFolder(exe).c_str()), SW_NORMAL);
        }
}

//---------------------------------------------------------------------------
__fastcall TWINDOW_LOCALGAME::TWINDOW_LOCALGAME(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TWINDOW_LOCALGAME::FormShow(TObject *Sender)
{
        COMBOBOX_LOCALGAMES->Items->Clear();
        for(int i = 0; i < GAMES_TOTAL; i++) {
                String name = WINDOW_SETTINGS->getSetGameFullName(i);
                if(!name.IsEmpty()) {
                        COMBOBOX_LOCALGAMES->Items->AddObject(name, (TObject *)i);
                }
        }
        if(COMBOBOX_LOCALGAMES->Items->Count > 0) {
                COMBOBOX_LOCALGAMES->ItemIndex = 0;
                COMBOBOX_LOCALGAMES->Enabled = true;
                BUTTON_LOCALGAME_START->Enabled = true;
        } else {
                COMBOBOX_LOCALGAMES->ItemIndex = -1;
                COMBOBOX_LOCALGAMES->Enabled = false;
                BUTTON_LOCALGAME_START->Enabled = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_LOCALGAME::COMBOBOX_LOCALGAMESChange(
      TObject *Sender)
{
        int index = COMBOBOX_LOCALGAMES->ItemIndex;
        int gameid = (int) COMBOBOX_LOCALGAMES->Items->Objects[index];
        int confNum = WINDOW_SETTINGS->getConfAmount(gameid);
        COMBOBOX_LOCALMODS->Items->Clear();
        for(int i = 0; i < confNum; i++) {
                String entry = WINDOW_SETTINGS->getConfListEntry(gameid, i);
                COMBOBOX_LOCALMODS->Items->AddObject(entry, (TObject *)i);
        }
        if(COMBOBOX_LOCALMODS->Items->Count > 0) {
                COMBOBOX_LOCALMODS->Enabled = true;
                COMBOBOX_LOCALMODS->ItemIndex = 0;    
        } else {
                COMBOBOX_LOCALMODS->Enabled = false;
                COMBOBOX_LOCALMODS->ItemIndex = -1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_LOCALGAME::BUTTON_LOCALGAME_STARTClick(
      TObject *Sender)
{
        int gameid = -1;
        int modid = -1;
        if(COMBOBOX_LOCALGAMES->ItemIndex >= 0) {
                gameid = (int) COMBOBOX_LOCALGAMES->Items->Objects[COMBOBOX_LOCALGAMES->ItemIndex];
        }
        if(COMBOBOX_LOCALMODS->ItemIndex >= 0) {
                modid =  (int) COMBOBOX_LOCALMODS->Items->Objects[COMBOBOX_LOCALMODS->ItemIndex];
        }
        String startup = "";
        if(modid >= 0) {
                startup = WINDOW_SETTINGS->getConfStartLineLocal(gameid, modid, CHECKBOX_MULTIPLAYER->Checked);
        } else if(CHECKBOX_MULTIPLAYER->Checked) {
                startup = "-host";
        }
        if(gameid >= 0 && gameid < GAMES_TOTAL) {
                String exe = WINDOW_SETTINGS->getExe(gameid);
                WINDOW_LOCALGAME->Close();
                startTheGame(startup, exe);
        }
}
//---------------------------------------------------------------------------

