//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TWINDOW_INFO : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TWINDOW_INFO(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWINDOW_INFO *WINDOW_INFO;
//---------------------------------------------------------------------------
#endif
