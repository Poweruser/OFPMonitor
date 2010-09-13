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
        TButton *BUTTON_OFPEXECUTABLE_BROWSE;
        TListBox *ListBox1;
        TButton *BUTTON_CONFIGURATION_REMOVE;
        TButton *BUTTON_NEWCONFIGURATION_ADD;
        TEdit *Edit3;
        TLabel *LABEL_CONFIGURATIONS_LISTOFCONFIGURATIONS;
        TListBox *ListBox2;
        TLabel *LABEL_NEWCONFIGURATION_PASSWORD;
        TCheckBox *CHECKBOX_NEWCONFIGURATION_NOSPLASH;
        TCheckBox *CHECKBOX_NEWCONFIGURATION_NOMAP;
        TEdit *Edit4;
        TLabel *LABEL_NEWCONFIGURATION_ADDITIONALPARAMETERS;
        TLabel *LABEL_NEWCONFIGURATION_MODFOLDERS;
        TGroupBox *GROUPBOX_OFPEXECUTABLE;
        TGroupBox *GROUPBOX_NEWCONFIGURATION;
        TLabel *LABEL_SERVERLIST_INTERVAL;
        TEdit *Edit5;
        TUpDown *UpDown1;
        TOpenDialog *OpenDialog1;
        TGroupBox *GROUPBOX_SERVERLIST;
        TListBox *ListBox3;
        TButton *Button6;
        TButton *Button7;
        TButton *BUTTON_NEWCONFIGURATION_UP;
        TButton *BUTTON_NEWCONFIGURATION_DOWN;
        TEdit *Edit6;
        TLabel *LABEL_NEWCONFIGURATION_LABEL;
        TButton *BUTTON_NEWCONFIGURATION_CLEAR;
        TGroupBox *GROUPBOX_LANGUAGE;
        TComboBox *ComboBox1;
        TButton *BUTTON_EDITCONFIGURATION_EDIT;
        TButton *BUTTON_EDITCONFIGURATION_OK;
        TButton *BUTTON_EDITCONFIGURATION_CANCEL;
        TGroupBox *GROUPBOX_PROFILE;
        TComboBox *COMBOBOX_PROFILE;
        TButton *BUTTON_EDITCONFIGURATION_UP;
        TButton *BUTTON_EDITCONFIGURATION_DOWN;
        void __fastcall BUTTON_OFPEXECUTABLE_BROWSEClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall OpenDialog1CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall BUTTON_NEWCONFIGURATION_UPClick(TObject *Sender);
        void __fastcall BUTTON_NEWCONFIGURATION_DOWNClick(TObject *Sender);
        void __fastcall BUTTON_CONFIGURATION_REMOVEClick(TObject *Sender);
        void __fastcall BUTTON_NEWCONFIGURATION_ADDClick(TObject *Sender);
        void __fastcall Edit5Change(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall BUTTON_NEWCONFIGURATION_CLEARClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_EDITClick(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_OKClick(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_CANCELClick(
          TObject *Sender);
        void __fastcall COMBOBOX_PROFILEChange(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_UPClick(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_DOWNClick(
          TObject *Sender);
private:	// User declarations
public:		// User declarations
        int TForm2::getConfAmount();
        String TForm2::getConfListEntry(int i);
        String TForm2::getConfModLine(int i);
        String TForm2::getCurrentPlayerName();
        boolean TForm2::isOFPResistance();
        void TForm2::writeSettingToFile(list<String> servers, list<String> watchedServers, list<String> font, list<String> window);
        void TForm2::setSettingsChanged();
        TStringList* TForm2::getWatchedList();
        String TForm2::getConfStartLine(int i, String ip, int port);
        String TForm2::getExe();
        String TForm2::getExeFolder();
        String TForm2::getGuiString(String ident);
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
