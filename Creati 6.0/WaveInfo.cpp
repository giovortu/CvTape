//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#define BORD 10

#include "WaveInfo.h"
#include "SDIMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWaveInfoForm *WaveInfoForm;
//---------------------------------------------------------------------------
__fastcall TWaveInfoForm::TWaveInfoForm(TComponent* Owner)
        : TForm(Owner)
{
 StringGrid1->Cells[0][0]="Attributes";
 StringGrid1->Cells[0][1]="File name";
 StringGrid1->Cells[0][2]="Sampling rate";
 StringGrid1->Cells[0][3]="Channels";
 StringGrid1->Cells[0][4]="Byte per sample";
 StringGrid1->Cells[0][5]="Bit per sample";
 StringGrid1->Cells[0][6]="Byte per second";
 StringGrid1->Cells[0][7]="Compressed";
 StringGrid1->Cells[0][8]="File size (Byte)";
 StringGrid1->Cells[0][9]="File size (Sample)";

 StringGrid1->Cells[1][0]="Values";
}
//---------------------------------------------------------------------------



