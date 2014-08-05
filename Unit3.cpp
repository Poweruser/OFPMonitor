//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop      
#include "Unit3.h"
#include "OFPMonitorDefinitions.h"
#include "Game.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWINDOW_LOCALGAME *WINDOW_LOCALGAME;

/**
   Launches OFP with the passed start up configuration
 */

void TWINDOW_LOCALGAME::setModel(OFPMonitorModel *ofpm) {
        this->ofpm = ofpm;
}

void TWINDOW_LOCALGAME::setLanguageDB(LanguageDB *languageDB) {
        this->languageDB = languageDB;
}

void TWINDOW_LOCALGAME::update(Observable *o) {
        if(o == this->languageDB) {
                this->updateGuiLanguage();
        }
}

void TWINDOW_LOCALGAME::updateGuiLanguage() {
        this->Caption = this->languageDB->getGuiString(this->Name);
        this->BUTTON_LOCALGAME_START->Caption = this->languageDB->getGuiString(BUTTON_LOCALGAME_START->Name);
        this->CHECKBOX_MULTIPLAYER->Caption = this->languageDB->getGuiString(CHECKBOX_MULTIPLAYER->Name);
        this->LABEL_GAME->Caption = this->languageDB->getGuiString(LABEL_GAME->Name);
        this->LABEL_MOD->Caption = this->languageDB->getGuiString(LABEL_MOD->Name);
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
        for(int i = 0; i < GAMESTOTAL; i++) {
                Game *g = this->ofpm->getGame((OFPGames)i);
                if(g != NULL) {
                        if(g->isActive()) {
                                String name = g->getFullName();
                                if(!name.IsEmpty()) {
                                        COMBOBOX_LOCALGAMES->Items->AddObject(name, (TObject*)g);
                                }
                        }
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
        COMBOBOX_LOCALGAMES->OnChange(this);
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_LOCALGAME::COMBOBOX_LOCALGAMESChange(
      TObject *Sender)
{
        int index = COMBOBOX_LOCALGAMES->ItemIndex;
        if(index >= 0) {
                Game *g = (Game*) (COMBOBOX_LOCALGAMES->Items->Objects[index]);
                int confNum = g->getConfigurationsCount();
                COMBOBOX_LOCALMODS->Items->Clear();
                COMBOBOX_LOCALMODS->Items->AddObject(this->languageDB->getGuiString("MENUITEM_POPUP_JOIN_NOMODS"), (TObject*)(NULL));
                for(int i = 0; i < confNum; i++) {
                        Configuration *conf = g->getConfiguration(i);
                        if(conf != NULL) {
                                String entry = conf->createListEntry();
                                COMBOBOX_LOCALMODS->Items->AddObject(entry, (TObject *)conf);
                        }
                }
                if(COMBOBOX_LOCALMODS->Items->Count > 0) {
                        COMBOBOX_LOCALMODS->Enabled = true;
                        COMBOBOX_LOCALMODS->ItemIndex = 0;
                } else {
                        COMBOBOX_LOCALMODS->Enabled = false;
                        COMBOBOX_LOCALMODS->ItemIndex = -1;
                }
        } else {
                COMBOBOX_LOCALMODS->Enabled = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_LOCALGAME::BUTTON_LOCALGAME_STARTClick(
      TObject *Sender)
{
        Game *g = NULL;
        Configuration *conf = NULL;
        if(COMBOBOX_LOCALGAMES->ItemIndex >= 0) {
                g = (Game*) (COMBOBOX_LOCALGAMES->Items->Objects[COMBOBOX_LOCALGAMES->ItemIndex]);
        }
        if(COMBOBOX_LOCALMODS->ItemIndex >= 0) {
                conf = (Configuration*) (COMBOBOX_LOCALMODS->Items->Objects[COMBOBOX_LOCALMODS->ItemIndex]);
        }
        bool multiPlayer = CHECKBOX_MULTIPLAYER->Checked;
        String startup = " -nosplash -nomap ";
        if(g != NULL) {
                if(conf != NULL) {
                        startup = conf->createStartLineLocal(multiPlayer, g->getProfileName());
                } else {
                        if(multiPlayer) {
                                startup += " -host";
                        }
                        startup += (" \"-name=" + g->getProfileName() + "\"");
                }

                WINDOW_LOCALGAME->Close();
                this->ofpm->startTheGame(g, startup);
        }
}
//---------------------------------------------------------------------------

