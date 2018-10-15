//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelDir.h"
#include "SDIMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSelect *Select;
//---------------------------------------------------------------------------
__fastcall TSelect::TSelect(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSelect::Button1Click(TObject *Sender)
{
 SDIAppForm->BatchDir=DirectoryListBox1->Directory;
 Close();        
}
//---------------------------------------------------------------------------
