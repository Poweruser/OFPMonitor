//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
//---------------------------------------------------------------------------



bool MyAppAlreadyRunning() {
        HANDLE hMutex = NULL;
        hMutex = CreateMutex(NULL,true,"OFPMonitor");
        if (GetLastError() == ERROR_ALREADY_EXISTS ) {
                CloseHandle(hMutex);
                return true; // Already running
        } else {
                return false; // First instance
        }
}


WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        if(!MyAppAlreadyRunning()) {
	try
        {
                 Application->Initialize();
                 Application->Title = "OFPMonitor 1.031";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
	}
        return 0;
}
//---------------------------------------------------------------------------
