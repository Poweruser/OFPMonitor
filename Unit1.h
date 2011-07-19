//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
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
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>

//---------------------------------------------------------------------------

class TForm1 : public TForm
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
        TMenuItem *MENUITEM_MAINMENU_GETNEWSERVERLIST;
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
        TTimer *TimerIrcChatTimer;
        TStringGrid *StringGrid3;
        TPanel *Panel2;
        TMenuItem *MENUITEM_MAINMENU_CHAT;
        TMenuItem *MENUITEM_MAINMENU_CHAT_CONNECT;
        TMenuItem *MENUITEM_MAINMENU_CHAT_DISCONNECT;
        TMemo *MemoChatOutput;
        TMemo *MemoChatInput;
        TMenuItem *MENUITEM_MAINMENU_CHAT_LOG;
        TMenuItem *MENUITEM_MAINMENU_CHAT_SAVETOFILE;
        TMenuItem *MENUITEM_MAINMENU_CHAT_CLEARLOG;
        TSaveDialog *SaveDialog1;
        TLabel *LABEL_SERVERINFO_EQMODREQ;
        TLabel *LABEL_SERVERINFO_EQMODREQ_VALUE;
        TCoolTrayIcon *CoolTrayIcon1;
        TMenuItem *MENUITEM_MAINMENU_LOCALGAME;
        TTimer *Timer2;
        TIdUDPServer *IdUDPServer1;
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
        void __fastcall Edit3Change(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
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
        void __fastcall MENUITEM_MAINMENU_GETNEWSERVERLISTClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_FONTClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall StringGrid1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall StringGrid2MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FontDialog1Apply(TObject *Sender, HWND Wnd);
        void __fastcall MENUITEM_POPUP_AUTOJOINBClick(TObject *Sender);
        void __fastcall StringGrid1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall Splitter1Moved(TObject *Sender);
        void __fastcall Info1Click(TObject *Sender);
        void __fastcall TimerIrcChatTimerTimer(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_CHAT_CONNECTClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_CHAT_DISCONNECTClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_CHAT_CLEARLOGClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_CHAT_SAVETOFILEClick(TObject *Sender);
        void __fastcall SaveDialog1CanClose(TObject *Sender,
          bool &CanClose);
        void __fastcall MemoChatInputChange(TObject *Sender);
        void __fastcall StringGrid3MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall StringGrid3DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall CoolTrayIcon1Click(TObject *Sender);
        void __fastcall TABSHEET_CHATShow(TObject *Sender);
        void __fastcall MemoChatOutputChange(TObject *Sender);
        void __fastcall MemoChatInputKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MemoChatInputKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MENUITEM_MAINMENU_LOCALGAMEClick(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread,
          TIdBytes AData, TIdSocketHandle *ABinding);
private:	// User declarations
public:		// User declarations
        void TForm1::readServerList(list<String> &in);
        void TForm1::setFont(String name, int size, int charset,bool bold, bool italic);
        void TForm1::setWindowSettings(int top,int left, int height, int width, float ratioID,float ratioSN,
                                float ratioPN,float ratioST,float ratioIS,
                                float ratioMN,float ratioPI,float ratioPL,
                                float ratioSC,float ratioDE,float ratioTE,
                                int devider);
        list<String> TForm1::splitUpMessage(String msg, String split);
        bool TForm1::doNameFilter(String c, String d);
        void TForm1::setChat(String host, int port, String channel, String user, bool autoConnect);
        String TForm1::getChatHost();
        int TForm1::getChatPort();
        String TForm1::getChatChannel();
        String TForm1::getChatUserName();
        bool TForm1::getChatAutoConnect();
        void TForm1::ChatNotification(String msg);
        void TForm1::ChatConnectionLost();
        bool TForm1::isChatUserBlocked(String username);
        bool TForm1::isNotificationRuleActive(int index);
        void TForm1::resetNotifications(int notificationIndex);
        __fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
