//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Easter2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPhoto *Photo;
int Dirx=5,Diry=5;
//---------------------------------------------------------------------------
__fastcall TPhoto::TPhoto(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TPhoto::Timer1Timer(TObject *Sender)
{
 Top+=Diry;
 Left+=Dirx;

 if ((Top>Screen->Height-Height) || (Top<0)) Diry=-Diry;
 if ((Left>Screen->Width-Width) || (Left<0)) Dirx=-Dirx;

}
//---------------------------------------------------------------------------

void __fastcall TPhoto::Image1Click(TObject *Sender)
{
 Photo->Hide();        
}
//---------------------------------------------------------------------------
void __fastcall TPhoto::FormHide(TObject *Sender)
{
 Photo->Timer1->Enabled=false;
}
//---------------------------------------------------------------------------

