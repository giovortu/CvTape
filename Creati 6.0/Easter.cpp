//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Easter.h"
#include "SDIMain.h"
#include <Filectrl.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define EXT ".bmp"
TAuthor *Author;
//extern AnsiString SDIAppForm->AppPath;

bool Clicked=false;
int Counter=0;
AnsiString FileName[16]={ "airsea"  ,"astropib","autochas","basic",
                          "chopper" ,"crazych" ,"deepsea" ,"locomot",
                          "mousepuz","musicmak","planetd" ,"policejum",
                          "soccer"  ,"sonicinv","tankatk" ,"tennis" };



//---------------------------------------------------------------------------
__fastcall TAuthor::TAuthor(TComponent* Owner)
        : TForm(Owner)
{
 Path=SDIAppForm->AppPath+"\\"+SDIAppForm->GalleryDir+"\\";
}
//---------------------------------------------------------------------------
void __fastcall TAuthor::Timer1Timer(TObject *Sender)
{

 Author->Caption=Author->Caption.SubString(2,Author->Caption.Length())
  +Author->Caption.SubString(1,1);


}
//---------------------------------------------------------------------------
void __fastcall TAuthor::Button1Click(TObject *Sender)
{

 if (!Clicked)
 {
 Clicked=true;
 Image1->Left=17;
 Image1->Top=17;
 Bevel1->Left=15;
 Bevel1->Top=15;
 Image1->ShowHint=false;
 Memo1->Visible=true;
 Button1->Caption="&Next >>";
 Button2->Visible=true;
 Button3->Visible=true;
 Image1->Picture->LoadFromFile(Path+"cvsystem.bmp");
 }

 Counter++;

  if (Counter>15) Counter=0;

   Image1->Picture->LoadFromFile(Path+FileName[Counter]+EXT);
   Bevel1->Width=Image1->Width+4;
   Bevel1->Height=Image1->Height+4;
}
//---------------------------------------------------------------------------

void __fastcall TAuthor::FormShow(TObject *Sender)
{
 Clicked=false;
 Memo1->Visible=false;
 Image1->Left=2;
 Image1->Top=3;
 Bevel1->Left=0;
 Bevel1->Top=0;
 Button1->Caption="&Gallery >>";
 Button2->Visible=false;

 Bevel1->Width=425;
 Bevel1->Height=273;

 Image1->ShowHint=true;

 if (!DirectoryExists("Games"))
 {
  Button1->Caption="No Gallery";
  Button1->Enabled=false;
 }
 else Image1->Picture->LoadFromFile(Path+"cvsystem.bmp");
}
//---------------------------------------------------------------------------


void __fastcall TAuthor::Label2Click(TObject *Sender)
{
ShellExecute(0,"open","iexplore.exe","http://creativemu.emuhq.com",NULL,SW_MAXIMIZE );
}
//---------------------------------------------------------------------------


void __fastcall TAuthor::Button2Click(TObject *Sender)
{
 Counter--;

  if (Counter<0) Counter=15;

   Image1->Picture->LoadFromFile(Path+FileName[Counter]+EXT);
   Bevel1->Width=Image1->Width+4;
   Bevel1->Height=Image1->Height+4;
}
//---------------------------------------------------------------------------

void __fastcall TAuthor::Button3Click(TObject *Sender)
{
 Button3->Visible=false;
 FormShow(Sender);
}
//---------------------------------------------------------------------------

