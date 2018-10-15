//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TipOfDay.h"
#include "SDIMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TTips *Tips;
//---------------------------------------------------------------------------
__fastcall TTips::TTips(TComponent* Owner)
        : TForm(Owner)
{
 File=SDIAppForm->HelpDir+"\\"+SDIAppForm->TipFile;
 ShowTips=SDIAppForm->ShowTips;
 ComboBox1->ItemIndex=ShowTips?1:0;

 Randomize();

 if (FileExists(File))
  {
   St=new TStringList();
   St->LoadFromFile( File );
  }

 else St=NULL;


}
//---------------------------------------------------------------------------


void __fastcall TTips::ComboBox1Change(TObject *Sender)
{
 ShowTips=(ComboBox1->ItemIndex==1);
 SDIAppForm->ShowTips=ShowTips;
}
//---------------------------------------------------------------------------

void __fastcall TTips::FormDestroy(TObject *Sender)
{
 if (St!=NULL) delete St;
}
//---------------------------------------------------------------------------

void __fastcall TTips::NextTipBtnClick(TObject *Sender)
{
//
int NumTip,Tip;

if (St!=NULL)
{

 NumTip=St->Count;
 Tip=random(NumTip/ROW);
 Memo1->Clear();
 
 for (int i=0; i<ROW; i++ )
  {
   Memo1->Lines->Add(St->Strings[Tip*ROW+i]);
  }


}
}
//---------------------------------------------------------------------------

void __fastcall TTips::FormClose(TObject *Sender, TCloseAction &Action)
{
ShowTips=(ComboBox1->ItemIndex==1);
SDIAppForm->ShowTips=ShowTips;

}
//---------------------------------------------------------------------------

void __fastcall TTips::CloseTipsBtnClick(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------

