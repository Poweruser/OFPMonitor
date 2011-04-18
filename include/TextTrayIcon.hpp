// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TextTrayIcon.pas' rev: 6.00

#ifndef TextTrayIconHPP
#define TextTrayIconHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <CoolTrayIcon.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Texttrayicon
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TOffsetOptions;
class PASCALIMPLEMENTATION TOffsetOptions : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FOffsetX;
	int FOffsetY;
	int FLineDistance;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetOffsetX(int Value);
	void __fastcall SetOffsetY(int Value);
	void __fastcall SetLineDistance(int Value);
	
protected:
	DYNAMIC void __fastcall Changed(void);
	
__published:
	__property int OffsetX = {read=FOffsetX, write=SetOffsetX, nodefault};
	__property int OffsetY = {read=FOffsetY, write=SetOffsetY, nodefault};
	__property int LineDistance = {read=FLineDistance, write=SetLineDistance, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TOffsetOptions(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TOffsetOptions(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class DELPHICLASS TTextTrayIcon;
class PASCALIMPLEMENTATION TTextTrayIcon : public Cooltrayicon::TCoolTrayIcon 
{
	typedef Cooltrayicon::TCoolTrayIcon inherited;
	
private:
	Graphics::TFont* FFont;
	Graphics::TColor FColor;
	Graphics::TColor FInvertTextColor;
	bool FBorder;
	Graphics::TColor FBorderColor;
	AnsiString FText;
	Graphics::TBitmap* FTextBitmap;
	TOffsetOptions* FOffsetOptions;
	Graphics::TIcon* FBackgroundIcon;
	void __fastcall FontChanged(System::TObject* Sender);
	void __fastcall SplitText(const Classes::TList* Strings);
	void __fastcall OffsetOptionsChanged(System::TObject* OffsetOptions);
	void __fastcall SetBackgroundIcon(Graphics::TIcon* Value);
	
protected:
	virtual void __fastcall Loaded(void);
	virtual bool __fastcall LoadDefaultIcon(void);
	virtual bool __fastcall LoadDefaultBackgroundIcon(void);
	virtual void __fastcall Paint(void);
	void __fastcall SetText(AnsiString Value);
	void __fastcall SetTextBitmap(Graphics::TBitmap* Value);
	void __fastcall SetFont(Graphics::TFont* Value);
	void __fastcall SetColor(Graphics::TColor Value);
	void __fastcall SetBorder(bool Value);
	void __fastcall SetBorderColor(Graphics::TColor Value);
	void __fastcall SetOffsetOptions(TOffsetOptions* Value);
	bool __fastcall TransparentBitmapToIcon(const Graphics::TBitmap* Bitmap, const Graphics::TIcon* Icon, Graphics::TColor MaskColor);
	
public:
	__fastcall virtual TTextTrayIcon(Classes::TComponent* AOwner);
	__fastcall virtual ~TTextTrayIcon(void);
	void __fastcall Draw(void);
	
__published:
	__property Graphics::TIcon* BackgroundIcon = {read=FBackgroundIcon, write=SetBackgroundIcon};
	__property AnsiString Text = {read=FText, write=SetText};
	__property Graphics::TFont* Font = {read=FFont, write=SetFont};
	__property Graphics::TColor Color = {read=FColor, write=SetColor, default=-2147483633};
	__property bool Border = {read=FBorder, write=SetBorder, nodefault};
	__property Graphics::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=0};
	__property TOffsetOptions* Options = {read=FOffsetOptions, write=SetOffsetOptions};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Texttrayicon */
using namespace Texttrayicon;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TextTrayIcon
