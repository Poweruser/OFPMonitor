//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TButton *Button1;
        TListBox *ListBox1;
        TEdit *Edit2;
        TButton *Button2;
        TButton *Button3;
        TEdit *Edit3;
        TLabel *Label2;
        TLabel *Label3;
        TListBox *ListBox2;
        TLabel *Label4;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TEdit *Edit4;
        TLabel *Label5;
        TLabel *Label6;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TEdit *Edit5;
        TUpDown *UpDown1;
        TOpenDialog *OpenDialog1;
        TGroupBox *GroupBox3;
        TListBox *ListBox3;
        TButton *Button6;
        TButton *Button7;
        TButton *Button8;
        TButton *Button9;
        TEdit *Edit6;
        TLabel *Label7;
        TButton *Button4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall OpenDialog1CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Edit5Change(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        void TForm2::init();
        int TForm2::getConfAmount();
        String TForm2::getConfListEntry(int i);
        void TForm2::writeSettingToFile();
        String TForm2::getConfStartLine(int i, String ip, int port);
        String TForm2::getExe();
        String TForm2::getExeFolder();
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
