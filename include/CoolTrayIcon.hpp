// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'CoolTrayIcon.pas' rev: 6.00

#ifndef CoolTrayIconHPP
#define CoolTrayIconHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ImgList.hpp>	// Pascal unit
#include <SimpleTimer.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cooltrayicon
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct TTimeoutOrVersion
{
	
	union
	{
		struct 
		{
			unsigned uVersion;
			
		};
		struct 
		{
			unsigned uTimeout;
			
		};
		
	};
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TNotifyIconDataEx
{
	unsigned cbSize;
	HWND hWnd;
	unsigned uID;
	unsigned uFlags;
	unsigned uCallbackMessage;
	HICON hIcon;
	char szTip[128];
	unsigned dwState;
	unsigned dwStateMask;
	char szInfo[256];
	TTimeoutOrVersion TimeoutOrVersion;
	char szInfoTitle[64];
	unsigned dwInfoFlags;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TBalloonHintIcon { bitNone, bitInfo, bitWarning, bitError, bitCustom };
#pragma option pop

typedef Shortint TBalloonHintTimeOut;

#pragma option push -b-
enum TBehavior { bhWin95, bhWin2000 };
#pragma option pop

typedef AnsiString THintString;

typedef void __fastcall (__closure *TCycleEvent)(System::TObject* Sender, int NextIndex);

typedef void __fastcall (__closure *TStartupEvent)(System::TObject* Sender, bool &ShowMainForm);

class DELPHICLASS TCoolTrayIcon;
class PASCALIMPLEMENTATION TCoolTrayIcon : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FEnabled;
	Graphics::TIcon* FIcon;
	unsigned FIconID;
	bool FIconVisible;
	AnsiString FHint;
	bool FShowHint;
	Menus::TPopupMenu* FPopupMenu;
	bool FLeftPopup;
	Classes::TNotifyEvent FOnClick;
	Classes::TNotifyEvent FOnDblClick;
	TCycleEvent FOnCycle;
	TStartupEvent FOnStartup;
	Controls::TMouseEvent FOnMouseDown;
	Controls::TMouseEvent FOnMouseUp;
	Controls::TMouseMoveEvent FOnMouseMove;
	Classes::TNotifyEvent FOnMouseEnter;
	Classes::TNotifyEvent FOnMouseExit;
	Classes::TNotifyEvent FOnMinimizeToTray;
	Classes::TNotifyEvent FOnBalloonHintShow;
	Classes::TNotifyEvent FOnBalloonHintHide;
	Classes::TNotifyEvent FOnBalloonHintTimeout;
	Classes::TNotifyEvent FOnBalloonHintClick;
	bool FMinimizeToTray;
	bool FClickStart;
	bool FClickReady;
	Simpletimer::TSimpleTimer* CycleTimer;
	Simpletimer::TSimpleTimer* ClickTimer;
	Simpletimer::TSimpleTimer* ExitTimer;
	int LastMoveX;
	int LastMoveY;
	bool FDidExit;
	bool FWantEnterExitEvents;
	TBehavior FBehavior;
	bool IsDblClick;
	int FIconIndex;
	bool FDesignPreview;
	bool SettingPreview;
	bool SettingMDIForm;
	Imglist::TCustomImageList* FIconList;
	bool FCycleIcons;
	unsigned FCycleInterval;
	void *OldWndProc;
	void *NewWndProc;
	void __fastcall SetDesignPreview(bool Value);
	void __fastcall SetCycleIcons(bool Value);
	void __fastcall SetCycleInterval(unsigned Value);
	bool __fastcall InitIcon(void);
	void __fastcall SetIcon(Graphics::TIcon* Value);
	void __fastcall SetIconVisible(bool Value);
	void __fastcall SetIconList(Imglist::TCustomImageList* Value);
	void __fastcall SetIconIndex(int Value);
	void __fastcall SetHint(AnsiString Value);
	void __fastcall SetShowHint(bool Value);
	void __fastcall SetWantEnterExitEvents(bool Value);
	void __fastcall SetBehavior(TBehavior Value);
	void __fastcall IconChanged(System::TObject* Sender);
	bool __fastcall HookAppProc(Messages::TMessage &Msg);
	void __fastcall HookForm(void);
	void __fastcall UnhookForm(void);
	void __fastcall HookFormProc(Messages::TMessage &Msg);
	void __fastcall ClickTimerProc(System::TObject* Sender);
	void __fastcall CycleTimerProc(System::TObject* Sender);
	void __fastcall MouseExitTimerProc(System::TObject* Sender);
	
protected:
	TNotifyIconDataEx IconData;
	virtual void __fastcall Loaded(void);
	virtual bool __fastcall LoadDefaultIcon(void);
	virtual bool __fastcall ShowIcon(void);
	virtual bool __fastcall HideIcon(void);
	virtual bool __fastcall ModifyIcon(void);
	DYNAMIC void __fastcall Click(void);
	DYNAMIC void __fastcall DblClick(void);
	DYNAMIC void __fastcall CycleIcon(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseEnter(void);
	DYNAMIC void __fastcall MouseExit(void);
	DYNAMIC void __fastcall DoMinimizeToTray(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	__property HWND Handle = {read=IconData.hWnd, nodefault};
	__property TBehavior Behavior = {read=FBehavior, write=SetBehavior, default=0};
	__fastcall virtual TCoolTrayIcon(Classes::TComponent* AOwner);
	__fastcall virtual ~TCoolTrayIcon(void);
	bool __fastcall Refresh(void);
	bool __fastcall ShowBalloonHint(AnsiString Title, AnsiString Text, TBalloonHintIcon IconType, TBalloonHintTimeOut TimeoutSecs);
	bool __fastcall ShowBalloonHintUnicode(WideString Title, WideString Text, TBalloonHintIcon IconType, TBalloonHintTimeOut TimeoutSecs);
	bool __fastcall HideBalloonHint(void);
	void __fastcall Popup(int X, int Y);
	void __fastcall PopupAtCursor(void);
	bool __fastcall BitmapToIcon(const Graphics::TBitmap* Bitmap, const Graphics::TIcon* Icon, Graphics::TColor MaskColor);
	Types::TPoint __fastcall GetClientIconPos(int X, int Y);
	HWND __fastcall GetTooltipHandle(void);
	HWND __fastcall GetBalloonHintHandle(void);
	bool __fastcall SetFocus(void);
	void __fastcall HideTaskbarIcon(void);
	void __fastcall ShowTaskbarIcon(void);
	void __fastcall ShowMainForm(void);
	void __fastcall HideMainForm(void);
	
__published:
	__property bool DesignPreview = {read=FDesignPreview, write=SetDesignPreview, default=0};
	__property Imglist::TCustomImageList* IconList = {read=FIconList, write=SetIconList};
	__property bool CycleIcons = {read=FCycleIcons, write=SetCycleIcons, default=0};
	__property unsigned CycleInterval = {read=FCycleInterval, write=SetCycleInterval, nodefault};
	__property bool Enabled = {read=FEnabled, write=FEnabled, default=1};
	__property AnsiString Hint = {read=FHint, write=SetHint};
	__property bool ShowHint = {read=FShowHint, write=SetShowHint, default=1};
	__property Graphics::TIcon* Icon = {read=FIcon, write=SetIcon};
	__property bool IconVisible = {read=FIconVisible, write=SetIconVisible, default=0};
	__property int IconIndex = {read=FIconIndex, write=SetIconIndex, nodefault};
	__property Menus::TPopupMenu* PopupMenu = {read=FPopupMenu, write=FPopupMenu};
	__property bool LeftPopup = {read=FLeftPopup, write=FLeftPopup, default=0};
	__property bool WantEnterExitEvents = {read=FWantEnterExitEvents, write=SetWantEnterExitEvents, default=0};
	__property bool MinimizeToTray = {read=FMinimizeToTray, write=FMinimizeToTray, default=0};
	__property Classes::TNotifyEvent OnClick = {read=FOnClick, write=FOnClick};
	__property Classes::TNotifyEvent OnDblClick = {read=FOnDblClick, write=FOnDblClick};
	__property Controls::TMouseEvent OnMouseDown = {read=FOnMouseDown, write=FOnMouseDown};
	__property Controls::TMouseEvent OnMouseUp = {read=FOnMouseUp, write=FOnMouseUp};
	__property Controls::TMouseMoveEvent OnMouseMove = {read=FOnMouseMove, write=FOnMouseMove};
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseExit = {read=FOnMouseExit, write=FOnMouseExit};
	__property TCycleEvent OnCycle = {read=FOnCycle, write=FOnCycle};
	__property Classes::TNotifyEvent OnBalloonHintShow = {read=FOnBalloonHintShow, write=FOnBalloonHintShow};
	__property Classes::TNotifyEvent OnBalloonHintHide = {read=FOnBalloonHintHide, write=FOnBalloonHintHide};
	__property Classes::TNotifyEvent OnBalloonHintTimeout = {read=FOnBalloonHintTimeout, write=FOnBalloonHintTimeout};
	__property Classes::TNotifyEvent OnBalloonHintClick = {read=FOnBalloonHintClick, write=FOnBalloonHintClick};
	__property Classes::TNotifyEvent OnMinimizeToTray = {read=FOnMinimizeToTray, write=FOnMinimizeToTray};
	__property TStartupEvent OnStartup = {read=FOnStartup, write=FOnStartup};
};


//-- var, const, procedure ---------------------------------------------------
static const Word WM_TRAYNOTIFY = 0x800;

}	/* namespace Cooltrayicon */
using namespace Cooltrayicon;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// CoolTrayIcon
