//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H

#include "LanguageDB.h"
#include "Observer.h"
#include "OFPMonitorModel.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TWINDOW_LOCALGAME : public TForm, public Observer
{
__published:	// IDE-managed Components
        TComboBox *COMBOBOX_LOCALGAMES;
        TComboBox *COMBOBOX_LOCALMODS;
        TButton *BUTTON_LOCALGAME_START;
        TLabel *LABEL_GAME;
        TLabel *LABEL_MOD;
        TCheckBox *CHECKBOX_MULTIPLAYER;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall COMBOBOX_LOCALGAMESChange(TObject *Sender);
        void __fastcall BUTTON_LOCALGAME_STARTClick(TObject *Sender);
private:	// User declarations
        OFPMonitorModel *ofpm;
        LanguageDB *languageDB;

public:		// User declarations
        void TWINDOW_LOCALGAME::setModel(OFPMonitorModel *ofpm);
        void TWINDOW_LOCALGAME::setLanguageDB(LanguageDB *languageDB);
        void TWINDOW_LOCALGAME::update(Observable *o);
        void TWINDOW_LOCALGAME::updateGuiLanguage();
        __fastcall TWINDOW_LOCALGAME(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWINDOW_LOCALGAME *WINDOW_LOCALGAME;
//---------------------------------------------------------------------------
#endif
