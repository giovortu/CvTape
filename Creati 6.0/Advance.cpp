//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Advance.h"
#include "Decode.h"
#include "WaveInfo.h"
#include "SDIMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TStatus *Status;
//---------------------------------------------------------------------------
__fastcall TStatus::TStatus(TComponent* Owner)
        : TForm(Owner)
{
 Canceled=false;
 SDIAppForm->Canc=Canceled;
}
//---------------------------------------------------------------------------

void __fastcall TStatus::Button1Click(TObject *Sender)
{
 Canceled=true;
 SDIAppForm->Canc=Canceled;

 for (int i=1; i<10; i++)
  WaveInfoForm->StringGrid1->Cells[1][i]="";

 SDIAppForm->Caption="Creativision wave decoder";

}
//---------------------------------------------------------------------------


