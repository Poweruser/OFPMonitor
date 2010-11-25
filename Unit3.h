//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TWINDOW_NOTIFICATIONS : public TForm
{
__published:	// IDE-managed Components
        TColorBox *ColorBox1;
        TGroupBox *GroupBox1;
        TListBox *ListBox1;
        TButton *BUTTON_NEWNOTIFICATION_ADD;
        TCheckBox *CHECKBOX_FILTER_CREATING;
        TCheckBox *CHECKBOX_FILTER_WAITING;
        TCheckBox *CHECKBOX_FILTER_SETTINGUP;
        TCheckBox *CHECKBOX_FILTER_BRIEFING;
        TCheckBox *CHECKBOX_FILTER_PLAYING;
        TCheckBox *CHECKBOX_FILTER_DEBRIEFING;
        TCheckBox *CHECKBOX_FILTER_WITHPASSWORD;
        TCheckBox *CHECKBOX_FILTER_WITHOUTPASSWORD;
        TMemo *Memo1;
        TMemo *Memo2;
        TLabel *LABEL_FILTER_SERVERNAME_BOX;
        TLabel *LABEL_FILTER_MISSIONNAME_BOX;
        TLabel *LABEL_FILTER_PLAYERNAME_BOX;
        TMemo *Memo3;
        TTrackBar *TrackBar1;
        TEdit *Edit1;
        TOpenDialog *OpenDialog1;
        TButton *BUTTON_BROWSE;
        TLabel *LABEL_FILTER_STATUS;
        TLabel *LABEL_FILTER_PASSWORD;
        TCheckBox *CHECKBOX_FILTER_MINPLAYERS;
        TEdit *Edit2;
        TCheckBox *CHECKBOX_FILTER_MAXPLAYERS;
        TUpDown *UpDown1;
        TUpDown *UpDown2;
        TEdit *Edit3;
        TLabel *LABEL_FILTER_PLAYERS;
        TButton *BUTTON_NEWNOTIFICATION_CLEAR;
        TEdit *Edit4;
        TLabel *LABEL_NOTIFICATION_NAME;
        TLabel *LABEL_AUDIOFILE;
        TLabel *LABEL_VOLUME;
        TLabel *LABEL_MARKINGCOLOR;
        TButton *BUTTON_EDITNOTIFICATION_EDIT;
        TButton *BUTTON_NOTIFICATION_REMOVE;
        TBitBtn *PLAY;
        TBitBtn *STOP;
        TButton *BUTTON_EDITNOTIFICATION_OK;
        TButton *BUTTON_EDITNOTIFICATION_CANCEL;
        TEdit *Edit5;
        TEdit *Edit6;
        TLabel *LABEL_AUDIO_FROM;
        TLabel *LABEL_AUDIO_TO;
        TEdit *Edit7;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit10;
        TLabel *LabelMinutes;
        TLabel *LabelSeconds;
        TLabel *LabelMilli;
        void __fastcall BUTTON_BROWSEClick(TObject *Sender);
        void __fastcall OpenDialog1CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_MINPLAYERSClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_MAXPLAYERSClick(TObject *Sender);
        void __fastcall BUTTON_NEWNOTIFICATION_CLEARClick(TObject *Sender);
        void __fastcall BUTTON_EDITNOTIFICATION_EDITClick(TObject *Sender);
        void __fastcall BUTTON_EDITNOTIFICATION_OKClick(TObject *Sender);
        void __fastcall BUTTON_NEWNOTIFICATION_ADDClick(TObject *Sender);
        void __fastcall BUTTON_NOTIFICATION_REMOVEClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall BUTTON_EDITNOTIFICATION_CANCELClick(
          TObject *Sender);
        void __fastcall PLAYClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall STOPClick(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Edit3Change(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Edit10Change(TObject *Sender);
        void __fastcall Edit5Change(TObject *Sender);
        void __fastcall Edit6Change(TObject *Sender);
        void __fastcall Edit7Change(TObject *Sender);
        void __fastcall Edit8Change(TObject *Sender);
        void __fastcall Edit9Change(TObject *Sender);
private:	// User declarations
public:
		// User declarations

       TStringList* TWINDOW_NOTIFICATIONS::getFileEntry();
       void TWINDOW_NOTIFICATIONS::addCustomNotification(String name, int filters, list<String> &mission,
                                    list<String> &server, list<String> &player, int minPlayers,
                                    int maxPlayers, String soundFile, int volume, int start, int end,
                                    String color);
       void TWINDOW_NOTIFICATIONS::checkNotifications(int serverindex, String servername, int players, int status,
                                String missionname, bool passworded,
                                list<String> playerlist);
       void TWINDOW_NOTIFICATIONS::updateFontSettings(int charset);
        __fastcall TWINDOW_NOTIFICATIONS(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWINDOW_NOTIFICATIONS *WINDOW_NOTIFICATIONS;
//---------------------------------------------------------------------------
#endif
 