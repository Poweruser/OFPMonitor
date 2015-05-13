//---------------------------------------------------------------------------

#ifndef Form_InfoH
#define Form_InfoH

#include "LanguageDB.h"
#include "Observer.h"

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TWINDOW_INFO : public TForm, public Observer
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Memo1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
        LanguageDB *languageDB;

public:		// User declarations
        void TWINDOW_INFO::update(Observable *o);
        void TWINDOW_INFO::setLanguageDB(LanguageDB *languageDB);
        void TWINDOW_INFO::updateGuiLanguage();
        __fastcall TWINDOW_INFO(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWINDOW_INFO *WINDOW_INFO;
//---------------------------------------------------------------------------
#endif
