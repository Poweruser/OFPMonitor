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
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <list.h>
#include "OFPMonitor.h"
#include "Server.h"
#include <ImgList.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------

class TWINDOW_SETTINGS : public TForm
{
__published:	// IDE-managed Components
        TEdit *EDIT_OFPRES_EXECUTABLE;
        TButton *BUTTON_OFPRES_BROWSE;
        TListBox *LISTBOX_CONFIGURATIONS;
        TButton *BUTTON_CONFIGURATION_REMOVE;
        TButton *BUTTON_NEWCONFIGURATION_ADD;
        TEdit *EDIT_NEWCONFIGURATION_PASSWORD;
        TListBox *LISTBOX_MODFOLDERS_ALL;
        TLabel *LABEL_NEWCONFIGURATION_PASSWORD;
        TCheckBox *CHECKBOX_NEWCONFIGURATION_NOSPLASH;
        TCheckBox *CHECKBOX_NEWCONFIGURATION_NOMAP;
        TEdit *EDIT_NEWCONFIGURATION_PARAMETERS;
        TLabel *LABEL_NEWCONFIGURATION_ADDITIONALPARAMETERS;
        TLabel *LABEL_NEWCONFIGURATION_MODFOLDERS;
        TGroupBox *GROUPBOX_NEWCONFIGURATION;
        TLabel *LABEL_SERVERLIST_INTERVAL;
        TEdit *EDIT_SERVERLIST_UPDATE;
        TUpDown *UPDOWN_SERVERLIST_UPDATE;
        TOpenDialog *OpenDialog1;
        TGroupBox *GROUPBOX_SERVERLIST;
        TListBox *LISTBOX_MODFOLDERS_SELECTED;
        TButton *BUTTON_NEWCONFIGURATION_MOVELEFT;
        TButton *BUTTON_NEWCONFIGURATION_MOVERIGHT;
        TButton *BUTTON_NEWCONFIGURATION_UP;
        TButton *BUTTON_NEWCONFIGURATION_DOWN;
        TEdit *EDIT_NEWCONFIGURATION_LABEL;
        TLabel *LABEL_NEWCONFIGURATION_LABEL;
        TButton *BUTTON_NEWCONFIGURATION_CLEAR;
        TGroupBox *GROUPBOX_LANGUAGE;
        TComboBox *ComboBox1;
        TButton *BUTTON_EDITCONFIGURATION_EDIT;
        TButton *BUTTON_EDITCONFIGURATION_OK;
        TButton *BUTTON_EDITCONFIGURATION_CANCEL;
        TComboBox *COMBOBOX_OFPRES_PROFILE;
        TButton *BUTTON_EDITCONFIGURATION_UP;
        TButton *BUTTON_EDITCONFIGURATION_DOWN;
        TGroupBox *GROUPBOX_CONFIGURATIONS;
        TButton *BUTTON_EDITCONFIGURATION_COPY;
        TPageControl *PageControl1;
        TTabSheet *TABSHEET_GENERAL;
        TTabSheet *TABSHEET_GAMES;
        TTabSheet *TABSHEET_MODS;
        TTabSheet *TABSHEET_NOTIFICATIONS;
        TGroupBox *GROUPBOX_OFPCWC;
        TGroupBox *GROUPBOX_OFPRES;
        TGroupBox *GROUPBOX_ARMACWA;
        TCheckBox *CHECKBOX_OFPCWC;
        TCheckBox *CHECKBOX_OFPRES;
        TCheckBox *CHECKBOX_ARMACWA;
        TLabel *LABEL_OFPRES_EXECUTABLE;
        TLabel *LABEL_OFPRES_PLAYERNAME;
        TLabel *LABEL_OFPCWC_EXECUTABLE;
        TEdit *EDIT_OFPCWC_EXECUTABLE;
        TEdit *EDIT_ARMACWA_EXECUTABLE;
        TLabel *LABEL_ARMACWA_EXECUTABLE;
        TComboBox *COMBOBOX_OFPCWC_PROFILE;
        TComboBox *COMBOBOX_ARMACWA_PROFILE;
        TLabel *LABEL_ARMACWA_PLAYERNAME;
        TLabel *LABEL_OFPCWC_PLAYERNAME;
        TButton *BUTTON_OFPCWC_BROWSE;
        TButton *BUTTON_ARMACWA_BROWSE;
        TPanel *Panel1;
        TLabel *LABEL_OFPCWC_DETECTEDVERSION;
        TPanel *Panel2;
        TLabel *LABEL_OFPRES_DETECTEDVERSION;
        TPanel *Panel3;
        TLabel *LABEL_ARMACWA_DETECTEDVERSION;
        TTabSheet *TABSHEET_CHATSETTINGS;
        TComboBox *ComboBox2;
        TOpenDialog *OpenDialog2;
        TTimer *MP3Timer;
        TCheckBox *CHECKBOX_REPEAT;
        TTrackBar *TrackBar1;
        TBitBtn *PLAY;
        TBitBtn *STOP;
        TEdit *EDIT_SONGEND_SEC;
        TEdit *EDIT_SONGEND_MIN;
        TEdit *EDIT_SONGSTART_MILL;
        TEdit *EDIT_SONGSTART_SEC;
        TEdit *EDIT_SONGSTART_MIN;
        TEdit *EDIT_SONGEND_MILL;
        TColorBox *ColorBox1;
        TButton *BUTTON_BROWSE;
        TEdit *EDIT_NOTIFICATION_FILE;
        TEdit *EDIT_NOTIFICATION_NAME;
        TGroupBox *GROUPBOX_NOTIFICATIONS_FILTERS;
        TLabel *LABEL_FILTER_SERVERNAME_BOX;
        TLabel *LABEL_FILTER_MISSIONNAME_BOX;
        TLabel *LABEL_FILTER_PLAYERNAME_BOX;
        TLabel *LABEL_FILTER_STATUS;
        TLabel *LABEL_FILTER_PASSWORD;
        TLabel *LABEL_FILTER_PLAYERS;
        TCheckBox *CHECKBOX_FILTER_CREATING;
        TCheckBox *CHECKBOX_FILTER_WAITING;
        TCheckBox *CHECKBOX_FILTER_SETTINGUP;
        TCheckBox *CHECKBOX_FILTER_BRIEFING;
        TCheckBox *CHECKBOX_FILTER_PLAYING;
        TCheckBox *CHECKBOX_FILTER_DEBRIEFING;
        TCheckBox *CHECKBOX_FILTER_WITHPASSWORD;
        TCheckBox *CHECKBOX_FILTER_WITHOUTPASSWORD;
        TMemo *MEMO_FILTER_MISSIONNAME;
        TMemo *MEMO_FILTER_SERVERNAME;
        TMemo *MEMO_FILTER_PLAYERNAME;
        TUpDown *UPDOWN_MINPLAYERS;
        TUpDown *UPDOWN_MAXPLAYERS;
        TEdit *EDIT_FILTER_MINPLAYERS;
        TEdit *EDIT_FILTER_MAXPLAYERS;
        TCheckBox *CHECKBOX_FILTER_MINPLAYERS;
        TCheckBox *CHECKBOX_FILTER_MAXPLAYERS;
        TListBox *LISTBOX_NOTIFICATIONS;
        TButton *BUTTON_NEWNOTIFICATION_CLEAR;
        TButton *BUTTON_NEWNOTIFICATION_ADD;
        TButton *BUTTON_EDITNOTIFICATION_CANCEL;
        TButton *BUTTON_EDITNOTIFICATION_OK;
        TButton *BUTTON_EDITNOTIFICATION_EDIT;
        TButton *BUTTON_NOTIFICATION_REMOVE;
        TLabel *LABEL_AUDIOFILE;
        TLabel *LABEL_NOTIFICATION_NAME;
        TLabel *LabelMinutes;
        TLabel *LabelSeconds;
        TLabel *LabelMilli;
        TLabel *LABEL_VOLUME;
        TLabel *LABEL_MARKINGCOLOR;
        TLabel *LABEL_AUDIO_TO;
        TLabel *LABEL_AUDIO_FROM;
        TCheckBox *CHECKBOX_NOTIFICATIONS_ACTIVE;
        TGroupBox *GROUPBOX_NOTIFICATIONS;
        TGroupBox *GROUPBOX_CHATSETTINGS_SERVER;
        TGroupBox *GROUPBOX_CHATSETTINGS_GENERAL;
        TEdit *EDIT_CHAT_IRCSERVER_ADDRESS;
        TLabel *LABEL_CHAT_IRCSERVER_ADDRESS;
        TLabel *LABEL_CHAT_IRCSERVER_PORT;
        TEdit *EDIT_CHAT_IRCSERVER_PORT;
        TLabel *LABEL_CHAT_IRCSERVER_CHANNEL;
        TEdit *EDIT_CHAT_IRCSERVER_CHANNEL;
        TButton *BUTTON_CHAT_SETDEFAULT;
        TComboBox *COMBOBOX_CHAT_USERNAME;
        TCheckBox *CHECKBOX_CHAT_AUTOCONNECT;
        TLabel *LABEL_CHAT_USERNAME;
        TTrackBar *TRACKBAR_BANDWIDTH;
        TGroupBox *GROUPBOX_BANDWIDTHCONSUMPTION;
        TLabel *LABEL_BANDWIDTH_VERYLOW;
        TLabel *LABEL_BANDWIDTH_LOW;
        TLabel *LABEL_BANDWIDTH_MODERATE;
        TLabel *LABEL_BANDWIDTH_HIGH;
        TGroupBox *GROUPBOX_UPDATE;
        TCheckBox *CHECKBOX_UPDATE_CHECKATSTART;
        TButton *BUTTON_UPDATE;
        TTabSheet *TABSHEET_SERVEREDITOR;
        TListBox *ListBox1;
        TRadioButton *RADIOBUTTON_SERVERS_SHOW_ADDRESS;
        TRadioButton *RADIOBUTTON_SERVERS_SHOW_NAME;
        TTreeView *TreeView1;
        TGroupBox *GroupBox1;
        TEdit *Edit1;
        TButton *Button1;
        TImageList *ImageList1;
        TPopupMenu *POPUPMENU_SERVERLISTEDITOR;
        TMenuItem *MENUITEM_POPUP_SERVERLISTEDITOR_REMOVE;
        void __fastcall BUTTON_OFPRES_BROWSEClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall OpenDialog1CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall BUTTON_NEWCONFIGURATION_MOVERIGHTClick(TObject *Sender);
        void __fastcall BUTTON_NEWCONFIGURATION_MOVELEFTClick(TObject *Sender);
        void __fastcall BUTTON_NEWCONFIGURATION_UPClick(TObject *Sender);
        void __fastcall BUTTON_NEWCONFIGURATION_DOWNClick(TObject *Sender);
        void __fastcall BUTTON_CONFIGURATION_REMOVEClick(TObject *Sender);
        void __fastcall BUTTON_NEWCONFIGURATION_ADDClick(TObject *Sender);
        void __fastcall UPDOWN_SERVERLIST_UPDATEClick(TObject *Sender, TUDBtnType Button);
        void __fastcall BUTTON_NEWCONFIGURATION_CLEARClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_EDITClick(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_OKClick(TObject *Sender);
        void __fastcall LISTBOX_CONFIGURATIONSClick(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_CANCELClick(
          TObject *Sender);
        void __fastcall COMBOBOX_OFPRES_PROFILEChange(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_UPClick(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_DOWNClick(
          TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_COPYClick(
          TObject *Sender);
        void __fastcall CHECKBOX_ARMACWAClick(TObject *Sender);
        void __fastcall BUTTON_OFPCWC_BROWSEClick(TObject *Sender);
        void __fastcall BUTTON_ARMACWA_BROWSEClick(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall COMBOBOX_OFPCWC_PROFILEChange(TObject *Sender);
        void __fastcall COMBOBOX_ARMACWA_PROFILEChange(TObject *Sender);
        void __fastcall CHECKBOX_OFPCWCClick(TObject *Sender);
        void __fastcall CHECKBOX_OFPRESClick(TObject *Sender);
        void __fastcall TABSHEET_MODSShow(TObject *Sender);
        void __fastcall BUTTON_BROWSEClick(TObject *Sender);
        void __fastcall OpenDialog2CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall EDIT_NOTIFICATION_FILEChange(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_MINPLAYERSClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_MAXPLAYERSClick(TObject *Sender);
        void __fastcall BUTTON_NEWNOTIFICATION_CLEARClick(TObject *Sender);
        void __fastcall BUTTON_EDITNOTIFICATION_EDITClick(TObject *Sender);
        void __fastcall BUTTON_EDITNOTIFICATION_OKClick(TObject *Sender);
        void __fastcall BUTTON_NEWNOTIFICATION_ADDClick(TObject *Sender);
        void __fastcall BUTTON_NOTIFICATION_REMOVEClick(TObject *Sender);
        void __fastcall TABSHEET_NOTIFICATIONSShow(TObject *Sender);
        void __fastcall BUTTON_EDITNOTIFICATION_CANCELClick(
          TObject *Sender);
        void __fastcall PLAYClick(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall STOPClick(TObject *Sender);
        void __fastcall EDIT_FILTER_MINPLAYERSChange(TObject *Sender);
        void __fastcall EDIT_FILTER_MAXPLAYERSChange(TObject *Sender);
        void __fastcall EDIT_SONGEND_MILLChange(TObject *Sender);
        void __fastcall EDIT_SONGSTART_MINChange(TObject *Sender);
        void __fastcall EDIT_SONGSTART_SECChange(TObject *Sender);
        void __fastcall EDIT_SONGSTART_MILLChange(TObject *Sender);
        void __fastcall EDIT_SONGEND_MINChange(TObject *Sender);
        void __fastcall EDIT_SONGEND_SECChange(TObject *Sender);
        void __fastcall EDIT_NOTIFICATION_FILEKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MP3TimerTimer(TObject *Sender);
        void __fastcall LISTBOX_NOTIFICATIONSClick(TObject *Sender);
        void __fastcall CHECKBOX_NOTIFICATIONS_ACTIVEClick(TObject *Sender);
        void __fastcall EDIT_CHAT_IRCSERVER_PORTChange(TObject *Sender);
        void __fastcall BUTTON_CHAT_SETDEFAULTClick(TObject *Sender);
        void __fastcall TRACKBAR_BANDWIDTHChange(TObject *Sender);
        void __fastcall TABSHEET_GENERALShow(TObject *Sender);
        void __fastcall CHECKBOX_UPDATE_CHECKATSTARTClick(TObject *Sender);
        void __fastcall BUTTON_UPDATEClick(TObject *Sender);
        void __fastcall TreeView1DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall TreeView1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
        void __fastcall TABSHEET_SERVEREDITORShow(TObject *Sender);
        void __fastcall RADIOBUTTON_SERVERS_SHOW_NAMEClick(
          TObject *Sender);
        void __fastcall RADIOBUTTON_SERVERS_SHOW_ADDRESSClick(
          TObject *Sender);
        void __fastcall TreeView1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall MENUITEM_POPUP_SERVERLISTEDITOR_REMOVEClick(
          TObject *Sender);
private:	// User declarations
public:		// User declarations
        int TWINDOW_SETTINGS::getConfAmount(int gameid);
        String TWINDOW_SETTINGS::getConfListEntry(int gameid, int i);
        String TWINDOW_SETTINGS::getConfModLine(int gameid, int i);
        String TWINDOW_SETTINGS::getPlayerName(int actVer, int reqVer);
        String TWINDOW_SETTINGS::getSetGameFullName(int gameid);
        String TWINDOW_SETTINGS::getFolder(String in);
        void TWINDOW_SETTINGS::writeSettingToFile(list<ServerItem> servers, list<String> font, list<String> window, list<String> chat);
        void TWINDOW_SETTINGS::setSettingsChanged();
        void TWINDOW_SETTINGS::setCustomNotifications(bool active);
        bool TWINDOW_SETTINGS::areCustomNotificationsEnabled();
        String TWINDOW_SETTINGS::getConfStartLine(int gameid, int i, String ip, int port);
        String TWINDOW_SETTINGS::getConfStartLineLocal(int gameid, int i, bool multiplayer);
        String TWINDOW_SETTINGS::getNoModsStartLine(int gameid, String ip, int port);
        String TWINDOW_SETTINGS::getSameModsStartLine(int gameid, String ip, int port, String servermods);
        int TWINDOW_SETTINGS::getGameId(int actVer, int reqVer);
        String TWINDOW_SETTINGS::getExe(int actVer, int reqVer);
        String TWINDOW_SETTINGS::getExe(int gameid);
        String TWINDOW_SETTINGS::getExeFolder(int actVer, int reqVer);
        String TWINDOW_SETTINGS::getGuiString(String ident);
        TStringList* TWINDOW_SETTINGS::getGameSpyGames();
        void TWINDOW_SETTINGS::addCustomNotification(String name, int filters, list<String> &mission,
                                    list<String> &server, list<String> &player, int minPlayers,
                                    int maxPlayers, String soundFile, int volume, int start, int end,
                                    String color, int repeat);
        int TWINDOW_SETTINGS::checkNotifications(String servername, int players, int status,
                                String missionname, bool passworded,
                                list<String> playerList);
        TStringList* TWINDOW_SETTINGS::getNotificationsFileEntries();
        TColor TWINDOW_SETTINGS::getMarkingColor(int index);
        void TWINDOW_SETTINGS::MP3remove(int index);
        void TWINDOW_SETTINGS::MP3add(int index);
        void TWINDOW_SETTINGS::MP3shutdown();
        BandwidthUsage TWINDOW_SETTINGS::getBandwidthSettings();
        int TWINDOW_SETTINGS::getUpdateInterval();
        __fastcall TWINDOW_SETTINGS(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWINDOW_SETTINGS *WINDOW_SETTINGS;
//---------------------------------------------------------------------------
#endif
