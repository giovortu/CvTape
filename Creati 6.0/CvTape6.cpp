//---------------------------------------------------------------------
#include <vcl.h>
#include "decode.h"
#include "wavefile.h"
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("SDIMain.cpp", SDIAppForm);
USEFORM("About.cpp", AboutBox);
USEFORM("Prefs.cpp", Preferences);
USEFORM("Advance.cpp", Status);
USEFORM("WaveInfo.cpp", WaveInfoForm);
USEFORM("Easter.cpp", Author);
USEFORM("TipOfDay.cpp", Tips);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
	Application->Initialize();
	Application->Title = "Creativision tape decoder";
		Application->CreateForm(__classid(TSDIAppForm), &SDIAppForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TPreferences), &Preferences);
                 Application->CreateForm(__classid(TStatus), &Status);
                 Application->CreateForm(__classid(TWaveInfoForm), &WaveInfoForm);
                 Application->CreateForm(__classid(TAuthor), &Author);
                 Application->CreateForm(__classid(TTips), &Tips);
                 Application->Run();
        }

        catch (ECreatiExc E)
        {
        Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
        }

 return 0;
}
//---------------------------------------------------------------------
