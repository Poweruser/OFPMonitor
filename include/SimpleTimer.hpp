// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SimpleTimer.pas' rev: 6.00

#ifndef SimpleTimerHPP
#define SimpleTimerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Simpletimer
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TSimpleTimer;
class PASCALIMPLEMENTATION TSimpleTimer : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	unsigned FId;
	bool FEnabled;
	unsigned FInterval;
	bool FAutoDisable;
	int FTag;
	Classes::TNotifyEvent FOnTimer;
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetInterval(unsigned Value);
	void __fastcall SetOnTimer(Classes::TNotifyEvent Value);
	void __fastcall Initialize(unsigned AInterval, Classes::TNotifyEvent AOnTimer);
	
protected:
	bool __fastcall Start(void);
	bool __fastcall Stop(bool Disable);
	
public:
	__fastcall TSimpleTimer(void);
	__fastcall TSimpleTimer(unsigned AInterval, Classes::TNotifyEvent AOnTimer);
	__fastcall virtual ~TSimpleTimer(void);
	__property bool Enabled = {read=FEnabled, write=SetEnabled, nodefault};
	__property unsigned Interval = {read=FInterval, write=SetInterval, default=1000};
	__property bool AutoDisable = {read=FAutoDisable, write=FAutoDisable, nodefault};
	__property int Tag = {read=FTag, write=FTag, default=0};
	__property Classes::TNotifyEvent OnTimer = {read=FOnTimer, write=SetOnTimer};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE unsigned __fastcall GetSimpleTimerCount(void);
extern PACKAGE unsigned __fastcall GetSimpleTimerActiveCount(void);

}	/* namespace Simpletimer */
using namespace Simpletimer;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SimpleTimer
