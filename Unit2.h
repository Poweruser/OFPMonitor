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

class TWINDOW_SETTINGS : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TButton *BUTTON_OFPEXECUTABLE_BROWSE;
        TListBox *ListBox1;
        TButton *BUTTON_CONFIGURATION_REMOVE;
        TButton *BUTTON_NEWCONFIGURATION_ADD;
        TEdit *Edit3;
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
        TGroupBox *GROUPBOX_CONFIGURATIONS;
        TButton *BUTTON_EDITCONFIGURATION_COPY;
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
        void __fastcall BUTTON_EDITCONFIGURATION_COPYClick(
          TObject *Sender);
private:	// User declarations
public:		// User declarations
        int TWINDOW_SETTINGS::getConfAmount();
        String TWINDOW_SETTINGS::getConfListEntry(int i);
        String TWINDOW_SETTINGS::getConfModLine(int i);
        String TWINDOW_SETTINGS::getCurrentPlayerName();
        boolean TWINDOW_SETTINGS::isOFPResistance();
        void TWINDOW_SETTINGS::writeSettingToFile(list<String> servers, list<String> watchedServers, list<String> font, list<String> window, list<String> chat, TStringList *notifications);
        void TWINDOW_SETTINGS::setSettingsChanged();
        void TWINDOW_SETTINGS::setCustomNotifications(bool active);
        bool TWINDOW_SETTINGS::areCustomNotificationsEnabled();
        TStringList* TWINDOW_SETTINGS::getWatchedList();
        String TWINDOW_SETTINGS::getConfStartLine(int i, String ip, int port);
        String TWINDOW_SETTINGS::getNoModsStartLine(String ip, int port);
        String TWINDOW_SETTINGS::getSameModsStartLine(String ip, int port, String servermods);
        String TWINDOW_SETTINGS::getExe();
        String TWINDOW_SETTINGS::getExeFolder();
        String TWINDOW_SETTINGS::getGuiString(String ident);
        __fastcall TWINDOW_SETTINGS(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWINDOW_SETTINGS *WINDOW_SETTINGS;
//---------------------------------------------------------------------------
#endif
