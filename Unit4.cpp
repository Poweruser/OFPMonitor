//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWINDOW_INFO *WINDOW_INFO;
//---------------------------------------------------------------------------
__fastcall TWINDOW_INFO::TWINDOW_INFO(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWINDOW_INFO::FormCreate(TObject *Sender)
{
        Memo1->Lines->Strings[0] = Application->Title;
}
//---------------------------------------------------------------------------

void __fastcall TWINDOW_INFO::Memo1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_ESCAPE) {
                WINDOW_INFO->Close();
        }         
}
//---------------------------------------------------------------------------


