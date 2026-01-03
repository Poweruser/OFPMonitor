//---------------------------------------------------------------------------

#ifndef Form_SettingsH
#define Form_SettingsH

#include "OFPMonitorDefinitions.h"
#include "OFPMonitorModel.h"      
#include "Server.h"
#include "ServerEditorTableSorter.h"
#include "Observer.h"
#include "LanguageDB.h"

#include <list.h>

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Grids.hpp>
#include <CheckLst.hpp>
                     
//---------------------------------------------------------------------------
class TWINDOW_SETTINGS : public TForm, public Observer
{
__published:	// IDE-managed Components
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
        TOpenDialog *OpenDialogGameFile;
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
        TButton *BUTTON_EDITCONFIGURATION_EDIT;
        TButton *BUTTON_EDITCONFIGURATION_OK;
        TButton *BUTTON_EDITCONFIGURATION_CANCEL;
        TButton *BUTTON_EDITCONFIGURATION_UP;
        TButton *BUTTON_EDITCONFIGURATION_DOWN;
        TGroupBox *GROUPBOX_CONFIGURATIONS;
        TButton *BUTTON_EDITCONFIGURATION_COPY;
        TPageControl *PageControl1;
        TTabSheet *TABSHEET_GENERAL;
        TTabSheet *TABSHEET_GAMES;
        TTabSheet *TABSHEET_MODS;
        TTabSheet *TABSHEET_NOTIFICATIONS;
        TGroupBox *GROUPBOX_EDITGAME;
        TLabel *LABEL_EDITGAME_EXECUTABLE;
        TEdit *EDIT_EDITGAME_EXECUTABLE;
        TComboBox *COMBOBOX_EDITGAME_PROFILE;
        TLabel *LABEL_EDITGAME_PLAYERNAME;
        TButton *BUTTON_EDITGAME_BROWSE;
        TPanel *Panel1;
        TLabel *LABEL_EDITGAME_DETECTEDVERSION;
        TComboBox *ComboBox2;
        TOpenDialog *OpenDialogAudioFile;
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
        TTrackBar *TRACKBAR_BANDWIDTH;
        TGroupBox *GROUPBOX_BANDWIDTHCONSUMPTION;
        TLabel *LABEL_BANDWIDTH_VERYLOW;
        TLabel *LABEL_BANDWIDTH_LOW;
        TLabel *LABEL_BANDWIDTH_MODERATE;
        TLabel *LABEL_BANDWIDTH_HIGH;
        TGroupBox *GROUPBOX_UPDATE;
        TCheckBox *CHECKBOX_UPDATE_CHECKATSTART;
        TButton *BUTTON_UPDATE;
        TTabSheet *TABSHEET_SERVERS;
        TButton *BUTTON_SERVERS_ADD;
        TImageList *ImageListPropertyIcons;
        TGroupBox *GROUPBOX_VOLUME;
        TTrackBar *TRACKBAR_VOLUME;
        TLabel *Label1;
        TLabel *Label2;
        TImageList *ImageListFlags;
        TComboBoxEx *ComboBox1;
        TGroupBox *GROUPBOX_PREVIEW;
        TButton *BUTTON_SERVERS_REMOVE;
        TStringGrid *StringGrid1;
        TTimer *Timer1;
        TTabSheet *TABSHEET_MASTERSERVERS;
        TGroupBox *GROUPBOX_MASTERSERVERS;
        TButton *BUTTON_MASTERSERVERS_ADD;
        TButton *BUTTON_MASTERSERVERS_REMOVE;
        TListBox *LISTBOX_MASTERSERVERS;
        TCheckBox *CHECKBOX_MASTERSERVERS_UPDATEONSTART;
        TButton *BUTTON_SERVERS_EXPORT;
        TSaveDialog *SaveDialog1;
        TCheckListBox *CHECKLISTBOX_GAMES;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall OpenDialogGameFileCanClose(TObject *Sender,
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
        void __fastcall BUTTON_EDITCONFIGURATION_EDITClick(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_OKClick(TObject *Sender);
        void __fastcall LISTBOX_CONFIGURATIONSClick(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_CANCELClick(
          TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_UPClick(TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_DOWNClick(
          TObject *Sender);
        void __fastcall BUTTON_EDITCONFIGURATION_COPYClick(
          TObject *Sender);
        void __fastcall BUTTON_EDITGAME_BROWSEClick(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall COMBOBOX_EDITGAME_PROFILEChange(TObject *Sender);
        void __fastcall TABSHEET_MODSShow(TObject *Sender);
        void __fastcall BUTTON_BROWSEClick(TObject *Sender);
        void __fastcall OpenDialogAudioFileCanClose(TObject *Sender,
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
        void __fastcall LISTBOX_NOTIFICATIONSClick(TObject *Sender);
        void __fastcall CHECKBOX_NOTIFICATIONS_ACTIVEClick(TObject *Sender);
        void __fastcall TRACKBAR_BANDWIDTHChange(TObject *Sender);
        void __fastcall TABSHEET_GENERALShow(TObject *Sender);
        void __fastcall CHECKBOX_UPDATE_CHECKATSTARTClick(TObject *Sender);
        void __fastcall BUTTON_UPDATEClick(TObject *Sender);
        void __fastcall TABSHEET_SERVERSShow(TObject *Sender);
        void __fastcall BUTTON_SERVERS_ADDClick(TObject *Sender);
        void __fastcall TRACKBAR_VOLUMEChange(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall StringGrid1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BUTTON_SERVERS_REMOVEClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall BUTTON_MASTERSERVERS_ADDClick(TObject *Sender);
        void __fastcall TABSHEET_MASTERSERVERSShow(TObject *Sender);
        void __fastcall CHECKBOX_MASTERSERVERS_UPDATEONSTARTClick(
          TObject *Sender);
        void __fastcall BUTTON_MASTERSERVERS_REMOVEClick(TObject *Sender);
        void __fastcall LISTBOX_MASTERSERVERSClick(TObject *Sender);
        void __fastcall BUTTON_SERVERS_EXPORTClick(TObject *Sender);
        void __fastcall SaveDialog1CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall CHECKLISTBOX_GAMESClickCheck(TObject *Sender);
        void __fastcall CHECKLISTBOX_GAMESClick(TObject *Sender);
private:	// User declarations

        OFPMonitorModel *ofpm;
        LanguageDB *languageDB;
        ServerEditorTableSorter *serverEditorTableSorter;

        void TWINDOW_SETTINGS::updateConfList();
        void TWINDOW_SETTINGS::refreshGamesModList();
        void TWINDOW_SETTINGS::updateGames();
        void TWINDOW_SETTINGS::updateEDITGAMEBox();
        void TWINDOW_SETTINGS::updateMasterServerSettings();
        void TWINDOW_SETTINGS::checkNotificationListState();
        void TWINDOW_SETTINGS::exitEditNotificationMode();
        void TWINDOW_SETTINGS::profileChanged(TComboBox *box, OFPGames gameid);
        void TWINDOW_SETTINGS::updateNotificationsList();
        void TWINDOW_SETTINGS::findLanguageFiles();
        String TWINDOW_SETTINGS::getFolder(String in);
        void TWINDOW_SETTINGS::checkConfListState();
        void TWINDOW_SETTINGS::exitEditMode();
        void TWINDOW_SETTINGS::updateModFolderList(String ofpfolder);
        void TWINDOW_SETTINGS::writeServerToStringGrid(int rowIndex, int serverID);
        void TWINDOW_SETTINGS::setEmptyServerEditorList();
        String TWINDOW_SETTINGS::addLeadingZeros(int number, int length);
        void TWINDOW_SETTINGS::updateServerEditorList();
        void TWINDOW_SETTINGS::printPlaybackRange(AudioPosition start, AudioPosition end);
        void TWINDOW_SETTINGS::printPlaybackPosition(AudioPosition current);


public:		// User declarations
        void TWINDOW_SETTINGS::setModel(OFPMonitorModel *ofpm);
        __fastcall TWINDOW_SETTINGS(TComponent* Owner);
        void TWINDOW_SETTINGS::updateLanguage(String languagefile);
        void TWINDOW_SETTINGS::setLanguageDB(LanguageDB *languageDB);
        void TWINDOW_SETTINGS::update(Observable *o);
        void TWINDOW_SETTINGS::updateGuiLanguage();
};
//---------------------------------------------------------------------------
extern PACKAGE TWINDOW_SETTINGS *WINDOW_SETTINGS;
//---------------------------------------------------------------------------
#endif
