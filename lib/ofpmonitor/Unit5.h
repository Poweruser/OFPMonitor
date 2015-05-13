//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H

#include "LanguageDB.h"
#include "Observer.h"

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "IdIOHandler.hpp"
#include "IdIOHandlerSocket.hpp"
#include "IdIOHandlerStack.hpp"
#include "IdSSL.hpp"
#include <ComCtrls.hpp>
#include <IdSSLOpenSSL.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TWINDOW_UPDATE : public TForm, public Observer
{
__published:	// IDE-managed Components
        TProgressBar *PROGRESSBAR_UPDATE_CURRENTFILE;
        TProgressBar *PROGRESSBAR_UPDATE_OVERALL;
        TMemo *MEMO_UPDATE_LOG;
        TLabel *LABEL_UPDATE_CURRENTFILE;
        TTimer *Timer1;
        void __fastcall IdHTTPWorkBegin(TObject *ASender,
          TWorkMode AWorkMode, __int64 AWorkCountMax);
        void __fastcall IdHTTPWork(TObject *ASender, TWorkMode AWorkMode,
          __int64 AWorkCount);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        LanguageDB *languageDB;

        void TWINDOW_UPDATE::updateGuiLanguage();
        void TWINDOW_UPDATE::cleanUp();

public:		// User declarations
        void TWINDOW_UPDATE::checkForNewVersion(bool userTriggered);
        void TWINDOW_UPDATE::update(Observable *o);
        void TWINDOW_UPDATE::setLanguageDB(LanguageDB *languageDB);
        __fastcall TWINDOW_UPDATE(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWINDOW_UPDATE *WINDOW_UPDATE;
//---------------------------------------------------------------------------
#endif
