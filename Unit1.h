//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <NMUDP.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid1;
        TGroupBox *GROUPBOX_FILTERS;
        TGroupBox *GROUPBOX_SERVERINFO;
        TButton *BUTTON_SERVERINFO_COPYADDRESS;
        TTimer *Timer1;
        TNMUDP *NMUDP1;
        TLabel *LABEL_SERVERINFO_IP;
        TLabel *Label2;
        TLabel *LABEL_SERVERINFO_PORT;
        TLabel *Label4;
        TCheckBox *CHECKBOX_FILTER_PLAYING;
        TCheckBox *CHECKBOX_FILTER_WAITING;
        TCheckBox *CHECKBOX_FILTER_CREATING;
        TCheckBox *CHECKBOX_FILTER_BRIEFING;
        TCheckBox *CHECKBOX_FILTER_DEBRIEFING;
        TEdit *Edit1;
        TLabel *LABEL_FILTER_MISSIONNAME;
        TEdit *Edit2;
        TLabel *LABEL_FILTER_SERVERNAME;
        TTimer *Timer3;
        TLabel *LABEL_SERVERINFO_PLATFORM;
        TLabel *Label9;
        TLabel *LABEL_SERVERINFO_PASSWORD;
        TLabel *Label11;
        TLabel *LABEL_SERVERINFO_VERSION;
        TLabel *Label13;
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
        TMenuItem *N01;
        TMenuItem *N11;
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
        TLabel *Label21;
        TMainMenu *MainMenu1;
        TMenuItem *MENUITEM_MAINMENU_EXIT;
        TMenuItem *MENUITEM_MAINMENU_SETTINGS;
        TMenuItem *MENUITEM_MAINMENU_GETNEWSERVERLIST;
        TTrayIcon *TrayIcon1;
        TFontDialog *FontDialog1;
        TMenuItem *MENUITEM_MAINMENU_FONT;
        TMenuItem *MENUITEM_POPUP_AUTOJOIN;
        TMenuItem *N03;
        TMenuItem *N13;
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
        TMenuItem *MENUITEM_MAINMENU_NOTIFICATIONS;
        TMenuItem *MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVE;
        TMenuItem *MENUITEM_MAINMENU_NOTIFICATIONS_SETTINGS;
        TTimer *MP3Timer;
        TMenuItem *Info1;
        TPanel *Panel2;
        TSplitter *Splitter2;
        TPanel *Panel3;
        TStringGrid *StringGrid3;
        TPanel *Panel4;
        TEdit *Edit5;
        TRichEdit *RichEditChatContent;
        TTimer *TimerIrcChat;
        TPanel *Panel5;
        void __fastcall NMUDP1DataReceived(TComponent *Sender,
          int NumberBytes, AnsiString FromIP, int Port);
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
        void __fastcall NMUDP1DataSend(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
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
        void __fastcall MENUITEM_MAINMENU_NOTIFICATIONS_SETTINGSClick(TObject *Sender);
        void __fastcall MENUITEM_MAINMENU_NOTIFICATIONS_ACTIVEClick(TObject *Sender);
        void __fastcall MP3TimerTimer(TObject *Sender);
        void __fastcall Info1Click(TObject *Sender);
        void __fastcall TimerIrcChatTimer(TObject *Sender);
        void __fastcall Edit5KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        typedef list<String> CustomStringList;
        void TForm1::readServerList(CustomStringList &in);
        void TForm1::setFont(String name, int size, int charset,bool bold, bool italic);
        void TForm1::setWindowSettings(int top,int left, int height, int width, float ratioID,float ratioSN,
                                float ratioPN,float ratioST,float ratioIS,
                                float ratioMN,float ratioPI,float ratioPL,
                                float ratioSC,float ratioDE,float ratioTE,
                                int devider);
        void TForm1::createMP3Job(int index,int serverindex, String file, String alias, int volume, int start, int end, TColor color);
        void TForm1::stopMP3Job(String alias);
        CustomStringList TForm1::splitUpMessage(String msg, String split);
        bool TForm1::doNameFilter(String c, String d);
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
