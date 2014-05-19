//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H

#include "Server.h"
#include "Player.h"
#include "OFPMonitorModel.h"
#include "GameControl.h"
#include "FontSettings.h"
#include "WindowSettings.h"
#include "ServerFilter.h"
#include "ServerTableSorter.h"
#include "PlayerTableSorter.h"
#include "Chat.h"
#include "Observer.h"
#include "LanguageDB.h"
#include "HttpsDownloader.h"

#include <list.h>

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
#include <Dialogs.hpp>
#include "CoolTrayIcon.hpp"
#include <ImgList.hpp>

//---------------------------------------------------------------------------


class TForm1 : public TForm, public Observer
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid1;
        TGroupBox *GROUPBOX_FILTERS;
        TGroupBox *GROUPBOX_SERVERINFO;
        TButton *BUTTON_SERVERINFO_COPYADDRESS;
        TTimer *Timer1;
        TLabel *LABEL_SERVERINFO_IP;
        TLabel *LABEL_SERVERINFO_IP_VALUE;
        TLabel *LABEL_SERVERINFO_PORT;
        TLabel *LABEL_SERVERINFO_PORT_VALUE;
        TCheckBox *CHECKBOX_FILTER_PLAYING;
        TCheckBox *CHECKBOX_FILTER_WAITING;
        TCheckBox *CHECKBOX_FILTER_CREATING;
        TCheckBox *CHECKBOX_FILTER_BRIEFING;
        TCheckBox *CHECKBOX_FILTER_DEBRIEFING;
        TEdit *Edit1;
        TLabel *LABEL_FILTER_MISSIONNAME;
        TEdit *Edit2;
        TLabel *LABEL_FILTER_SERVERNAME;
        TLabel *LABEL_SERVERINFO_PLATFORM;
        TLabel *LABEL_SERVERINFO_PLATFORM_VALUE;
        TLabel *LABEL_SERVERINFO_PASSWORD;
        TLabel *LABEL_SERVERINFO_PASSWORD_VALUE;
        TLabel *LABEL_SERVERINFO_VERSION;
        TLabel *LABEL_SERVERINFO_VERSION_VALUE;
        TCheckBox *CHECKBOX_FILTER_WITHPASSWORD;
        TCheckBox *CHECKBOX_FILTER_WITHOUTPASSWORD;
        TLabel *LABEL_FILTER_PASSWORD;
        TLabel *LABEL_FILTER_MINIMUMPLAYERS;
        TUpDown *UpDown1;
        TEdit *Edit3;
        TStringGrid *StringGrid2;
        TStatusBar *StatusBar1;
        TEdit *Edit4;
        TLabel *LABEL_FILTER_PLAYERNAME;
        TPopupMenu *PopupMenu1;
        TMenuItem *MENUITEM_POPUP_JOIN;
        TCheckBox *CHECKBOX_FILTER_SETTINGUP;
        TMenuItem *MENUITEM_POPUP_MODS;
        TMenuItem *MENUITEM_POPUP_JOIN_NOMODS;
        TMenuItem *MENUITEM_POPUP_JOIN_SAMEMODS;
        TMenuItem *N21;
        TMenuItem *N31;
        TMenuItem *N41;
        TMenuItem *N02;
        TMenuItem *N12;
        TMenuItem *N22;
        TMenuItem *N32;
        TMenuItem *N42;
        TMenuItem *N51;
        TMenuItem *N61;
        TMenuItem *N71;
        TMenuItem *N81;
        TMenuItem *N91;
        TMenuItem *N52;
        TMenuItem *N62;
        TMenuItem *N72;
        TMenuItem *N82;
        TMenuItem *N92;
        TLabel *LABEL_FILTER_STATUS;
        TMenuItem *MENUITEM_POPUP_WATCH;
        TLabel *LABEL_SERVERINFO_NAME;
        TMainMenu *MainMenu1;
        TMenuItem *MENUITEM_MAINMENU_EXIT;
        TMenuItem *MENUITEM_MAINMENU_SETTINGS;
        TMenuItem *MENUITEM_MAINMENU_SERVERLIST;
        TFontDialog *FontDialog1;
        TMenuItem *MENUITEM_MAINMENU_FONT;
        TMenuItem *MENUITEM_POPUP_AUTOJOIN;
        TMenuItem *MENUITEM_POPUP_AUTOJOIN_NOMODS;
        TMenuItem *MENUITEM_POPUP_AUTOJOIN_SAMEMODS;
        TMenuItem *N23;
        TMenuItem *N33;
        TMenuItem *N43;
        TMenuItem *N53;
        TMenuItem *N63;
        TMenuItem *N73;
        TMenuItem *N83;
        TMenuItem *N93;
        TMenuItem *MENUITEM_POPUP_AUTOJOINB;
        TSplitter *Splitter1;
        TPanel *Panel1;
        TMenuItem *Info1;
        TPageControl *PageControl1;
        TTabSheet *TABSHEET_SERVERINFO;
        TTabSheet *TABSHEET_CHAT;
        TStringGrid *StringGrid3;
        TPanel *Panel2;
        TMenuItem *MENUITEM_MAINMENU_CHAT;
        TMenuItem *MENUITEM_MAINMENU_CHAT_CONNECT;
        TMenuItem *MENUITEM_MAINMENU_CHAT_DISCONNECT;
        TMemo *MemoChatOutput;
        TMemo *MemoChatInput;
        TLabel *LABEL_SERVERINFO_EQMODREQ;
        TLabel *LABEL_SERVERINFO_EQMODREQ_VALUE;
        TCoolTrayIcon *CoolTrayIcon1;
        TMenuItem *MENUITEM_MAINMENU_LOCALGAME;
        TTabControl *TabControl1;
        TPopupMenu *PopupMenuChat;
        TMenuItem *Openchat1;
        TPopupMenu *PopupMenuChat2;
        TMenuItem *Close1;
        TTabSheet *TABSHEET_GAMECONTROL;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TGroupBox *GROUPBOX_GAMECONTROL_PROCESS;
        TGroupBox *GROUPBOX_GAMECONTROL_AUTOGREENUP;
        TRadioButton *RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCE;
        TRadioButton *RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEAT;
        TLabel *LABEL_GAMECONTROL_AUTOGREENUP_DELAY;
        TEdit *Edit5;
        TUpDown *UpDown2;
        TGroupBox *GROUPBOX_GAMECONTROL_RESTORE;
        TCheckBox *CHECKBOX_GAMECONTROL_RESTORE_CREATING;
        TCheckBox *CHECKBOX_GAMECONTROL_RESTORE_WAITING;
        TCheckBox *CHECKBOX_GAMECONTROL_RESTORE_BRIEFING;
        TCheckBox *CHECKBOX_GAMECONTROL_RESTORE_PLAYING;
        TCheckBox *CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFING;
        TCheckBox *CHECKBOX_GAMECONTROL_AUTOGREENUP;
        TCheckBox *CHECKBOX_GAMECONTROL_RESTORE;
        TLabel *LABEL_GAMECONTROL_PROCESS;
        TLabel *LABEL_GAMECONTROL_SERVER;
        TLabel *Label9;
        TImageList *ImageListTabIcons;
        TCheckBox *CHECKBOX_GAMECONTROL_AUTODETECT;
        TButton *BUTTON_GAMECONTROL_REFRESH;
        TLabel *LABEL_GAMECONTROL_EXE;
        TImageList *ImageListVolume;
        TImageList *ImageListNotification;
        TImageList *ImageListBandwidth;
        TImageList *ImageListPinned;
        TMenuItem *MENUITEM_MAINMENU_GETNEWSERVERLIST;
        TMenuItem *MENUITEM_MAINMENU_SERVERLIST_GAMESPY;
        TMenuItem *MENUITEM_MAINMENU_SERVERLIST_POWERSERVER;
        TMenuItem *N1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BUTTON_SERVERINFO_COPYADDRESSClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_PLAYINGClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_WAITINGClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_CREATINGClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_BRIEFINGClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_DEBRIEFINGClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_WITHPASSWORDClick(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_WITHOUTPASSWORDClick(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall StringGrid1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall StringGrid2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Edit4Change(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall ClickJoinButton(TObject *Sender);
        void __fastcall ClickAutoJoinConfButton(TObject *Sender);
        void __fastcall ClickWatchButton(TObject *Sender);
        void __fastcall OnMinimize(TObject *Sender);
        void __fastcall CHECKBOX_FILTER_SETTINGUPClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall MENUITEM_MAINMENU_SETTINGSClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_EXITClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_FONTClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FontDialog1Apply(TObject *Sender, HWND Wnd);
        void __fastcall MENUITEM_POPUP_AUTOJOINBClick(TObject *Sender);
        void __fastcall StringGrid1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall Splitter1Moved(TObject *Sender);
        void __fastcall Info1Click(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_CHAT_CONNECTClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_CHAT_DISCONNECTClick(TObject *Sender);
        void __fastcall MemoChatInputChange(TObject *Sender);
        void __fastcall StringGrid3MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall StringGrid3DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall CoolTrayIcon1Click(TObject *Sender);
        void __fastcall TABSHEET_CHATShow(TObject *Sender);
        void __fastcall MemoChatInputKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MENUITEM_MAINMENU_LOCALGAMEClick(TObject *Sender);
        void __fastcall TabControl1DrawTab(TCustomTabControl *Control,
          int TabIndex, const TRect &Rect, bool Active);
        void __fastcall TabControl1Change(TObject *Sender);
        void __fastcall TabControl1Changing(TObject *Sender,
          bool &AllowChange);
        void __fastcall StringGrid3ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall Openchat1Click(TObject *Sender);
        void __fastcall TabControl1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall Close1Click(TObject *Sender);
        void __fastcall RADIOBUTTON_GAMECONTROL_AUTOGREENUP_ONLYONCEClick(TObject *Sender);
        void __fastcall RADIOBUTTON_GAMECONTROL_AUTOGREENUP_REPEATClick(TObject *Sender);
        void __fastcall CHECKBOX_GAMECONTROL_AUTOGREENUPClick(TObject *Sender);
        void __fastcall CHECKBOX_GAMECONTROL_RESTOREClick(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall TABSHEET_GAMECONTROLShow(TObject *Sender);
        void __fastcall CHECKBOX_GAMECONTROL_RESTORE_CREATINGClick(TObject *Sender);
        void __fastcall CHECKBOX_GAMECONTROL_RESTORE_WAITINGClick(TObject *Sender);
        void __fastcall CHECKBOX_GAMECONTROL_RESTORE_BRIEFINGClick(TObject *Sender);
        void __fastcall CHECKBOX_GAMECONTROL_RESTORE_PLAYINGClick(TObject *Sender);
        void __fastcall CHECKBOX_GAMECONTROL_RESTORE_DEBRIEFINGClick(TObject *Sender);
        void __fastcall UpDown2ChangingEx(TObject *Sender,
          bool &AllowChange, short NewValue, TUpDownDirection Direction);
        void __fastcall CHECKBOX_GAMECONTROL_AUTODETECTClick(
          TObject *Sender);
        void __fastcall BUTTON_GAMECONTROL_REFRESHClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall StringGrid1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall StringGrid2MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormConstrainedResize(TObject *Sender,
          int &MinWidth, int &MinHeight, int &MaxWidth, int &MaxHeight);
        void __fastcall UpDown1ChangingEx(TObject *Sender,
          bool &AllowChange, short NewValue, TUpDownDirection Direction);
        void __fastcall StatusBar1DrawPanel(TStatusBar *StatusBar,
          TStatusPanel *Panel, const TRect &Rect);
        void __fastcall StatusBar1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall PageControl1DrawTab(TCustomTabControl *Control,
          int TabIndex, const TRect &Rect, bool Active);
        void __fastcall MENUITEM_MAINMENU_GETNEWSERVERLISTClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_SERVERLIST_GAMESPYClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_SERVERLIST_POWERSERVERClick(
          TObject *Sender);
private:	// User declarations
        OFPMonitorModel *ofpm;
        GameControl *gameControl;
        ServerFilter *serverFilter;
        FontSettings *fontSettings;
        WindowSettings *windowSettings;
        ServerTableSorter *serverTableSorter;
        PlayerTableSorter *playerTableSorter;
        Server* selectedServer;
        Server* selectedServerForPopUp;
        ChatSettings *chatSettings;
        Chat* chat;
        LanguageDB *languageDB;
        bool filterChanging;
        HANDLE chatThreadHandle;
        HttpsDownloader *downloader;

        float TForm1::checkIfTableRatioZero(float in, TStringGrid *grid);
        void TForm1::updateFilterOfGui();
        void TForm1::updateGameControlGui();
        void TForm1::updateFontOfGui(TFont *font);
        void TForm1::writeServerToStringGrid(int rowIndex, Server *srv);
        void TForm1::processPlayerList(Server *srv);
        void TForm1::writePlayerToStringGrid(int rowIndex, Player *p);
        void TForm1::updateServerInfoBox(Server *srv);
        void TForm1::filterChanged(bool userinput);
        void TForm1::setEmptyServerList();
        void TForm1::setEmptyPlayerList();
        String TForm1::getGameState (int i);
        void TForm1::updateWindowSettingsPosition();
        void TForm1::applyWindowSettingsRatios();
        bool TForm1::getServerPasswordDialog(String &password);
        String TForm1::calcElapsedTime(long a, long b);
        String TForm1::addLeadingZeros(int number, int length);
        void TForm1::copyToClipBoard (String msg);

public:		// User declarations
        void TForm1::readServerList(list<ServerConfigEntry> &in);
        bool TForm1::doNameFilter(String c, String d);
        void TForm1::setModel(OFPMonitorModel *model);
        void TForm1::setGameControl(GameControl *gameControl);
        void TForm1::setServerFilter(ServerFilter *serverFilter);
        void TForm1::setFontSettings(FontSettings *fontSettings);
        void TForm1::setWindowSettings(WindowSettings *windowSettings);
        void TForm1::setChatSettings(ChatSettings *chatSettings);
        void TForm1::setLanguageDB(LanguageDB *languageDB);
        void TForm1::applyWindowSettings();
        void TForm1::setSelectedServer(Server *srv);
        void TForm1::setAlwaysOnTop(bool active);
        void TForm1::toggleAlwaysOnTop();
        __fastcall TForm1(TComponent* Owner);
        void TForm1::update(Observable *o);
        void TForm1::updateGuiLanguage();
        void TForm1::updateMainMenuSettings();

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
