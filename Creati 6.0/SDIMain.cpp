//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SDIMain.h"
#include "TipOfDay.h"
#include "Advance.h"
#include "About.h"
#include "Error.h"
#include "Decode.h"
#include "Prefs.h"
#include "WaveInfo.h"
#include "vcl/registry.hpp"
#include "Wavefile.h"
#include "process.h"
#include "dir.h"
#include "Easter.h"
#include "SelDir.h"
#include <Printers.hpp>
#include <FileCtrl.hpp>

//---------------------------------------------------------------------
#pragma link "Trayicon"
#pragma resource "*.dfm"


TSDIAppForm *SDIAppForm;
int PosX,PosY;

//---------------------------------------------------------------------
__fastcall TSDIAppForm::TSDIAppForm(TComponent *AOwner)
	: TForm(AOwner)
{

 TRegistry *Reg=new TRegistry;
  char st[255];

  ProgressiveCount=0;
  Canc=false;
  BatchDir="";
  CanModify=false;
  SaveLog=false;
  AutoTreshold=true;
  ManualTreshold="15000";
  Fm=false;
  TipFile="Tips.txt";
  ShowTips=true;
  Channel=1;

  // Directory del programma
   strcpy(st, "X:\\");
   st[0] = 'A' + getdisk();
   getcurdir(0, st+3);
   AppPath=AnsiString(st);
   HelpDir="Help";
   GalleryDir="Games";

  // Testo se esiste la chiave, se no creo l'albero


 if (!(Reg->KeyExists("Software\\CreatiVemu\\CvTapeWin")))
  {

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin",true);
   Reg->WriteString("Version","3.6 Beta");
   Reg->WriteString("Author","Giovanni Ortu");
   Reg->WriteString("Company","Go! Software");
   Reg->CloseKey();

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\Locations",true);
   Reg->WriteString("ProgramDir",AppPath);
   Reg->WriteString("HelpDir","Help");
   Reg->WriteString("GalleryDir","Games");
   Reg->WriteString("LogFile","Log.txt");
   Reg->WriteString("TipFile","Tips.txt");
   Reg->CloseKey();


   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\Options",true);
   Reg->WriteBool("SaveLog",false);
   Reg->WriteBool("ModifyResult",false);
   Reg->WriteBool("ShowTips",true);
   Reg->CloseKey();

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\MRUList",true);
   Reg->CloseKey();

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\MenuStatus",true);
   Reg->CloseKey();


   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\MenuStatus\\WaveInfoWin",true);
   Reg->WriteBool("Visible",true);
   Reg->WriteInteger("PosX",0);
   Reg->WriteInteger("PosY",0);
   Reg->CloseKey();

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\Options",true);
   Reg->WriteBool("SaveLog",false);
   Reg->WriteBool("ModifyResult",false);
   Reg->WriteString("ManualTresholdValue",ManualTreshold);
   Reg->WriteBool("AutoTreshold",false);
   Reg->WriteBool("FmSynt",false);
   Reg->CloseKey();



  }

  else
 {

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\Locations",true);
   HelpDir   = Reg->ReadString("HelpDir");
   GalleryDir= Reg->ReadString("GalleryDir");
   LogFile   = Reg->ReadString("LogFile");
   TipFile   = Reg->ReadString("TipFile");
   Reg->CloseKey();

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\MenuStatus\\WaveInfoWin",true);
   WaveInfoFormVisible=Reg->ReadBool("Visible");
   WaveInfoPosX=Reg->ReadInteger("PosX");
   WaveInfoPosY=Reg->ReadInteger("PosY");
   Reg->CloseKey();

   Reg->OpenKey("Software\\CreativEmu\\CvTapeWin\\Options",true);
   SaveLog        = Reg->ReadBool("SaveLog");
   CanModify      = Reg->ReadBool("ModifyResult");
   ManualTreshold = Reg->ReadString("ManualTresholdValue");
   AutoTreshold   = Reg->ReadBool("AutoTreshold");
   Fm             = Reg->ReadBool("FmSynt");
   ShowTips       = Reg->ReadBool("ShowTips");
   Reg->CloseKey();

 }
  delete Reg;

  Edit1->Text=ManualTreshold;
  FmButton->Checked=Fm;

  IsSaved=true; IsLoaded=false; MRUOpen=false;

  Buffer=new Graphics::TBitmap();

  Buffer->Width=530;
  Buffer->Height=60;

  Buffer->Canvas->Pen->Mode=pmCopy;
  Buffer->Canvas->Pen->Color=clBtnFace;
  Buffer->Canvas->Pen->Style=psSolid;

  Buffer->Canvas->Brush->Style=bsSolid;
  Buffer->Canvas->Brush->Color=clBtnFace;
  Buffer->Canvas->Rectangle(0,0,Buffer->Width,Buffer->Height);
  Buffer->Canvas->CopyMode=cmNotSrcCopy;

  Canvas->CopyMode=cmNotSrcCopy;

  CvTape=NULL;
  
}
//---------------------------------------------------------------------
void __fastcall TSDIAppForm::ShowHint(TObject *Sender)
{
	StatusBar->SimpleText = Application->Hint;
}
//---------------------------------------------------------------------
void __fastcall TSDIAppForm::ExitItemClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------
void __fastcall TSDIAppForm::OpenItemClick(TObject *Sender)
{

try
   {
    OpenDialog->Execute();
    FileName=OpenDialog->FileName;
    OpenDialog->FileName="";
    OpenDialogClose(Sender);
   }
catch ( EWaveFile E )
{
  Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ECreatiExc E )
{
  Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}


}
//---------------------------------------------------------------------
void __fastcall TSDIAppForm::SaveItemClick(TObject *Sender)
{
  if (SaveDialog->Execute())
    {
      // Scrivo il risultato su un file
      Memo1->Lines->SaveToFile(SaveDialog->FileName);
      IsSaved=true;
    }
}
//---------------------------------------------------------------------
void __fastcall TSDIAppForm::About1Click(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------
void __fastcall TSDIAppForm::FormCreate(TObject *Sender)
{
   //Application->OnHint = ShowHint;
}
//---------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TSDIAppForm::HelpBtnClick(TObject *Sender)
{
   AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TSDIAppForm::Setpreferences1Click(TObject *Sender)
{
 Preferences->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TSDIAppForm::DecodeClick(TObject *Sender)
{
  TStringList *Res=new TStringList;

       if (IsLoaded)
       {
        Memo1->Clear();
        // Controllo il tipo di codifica
        if (AmButton->Checked)
         CvTape->DecodeAm(Res);
        else
         CvTape->DecodeFm(Res);

         for (int i=0; i<Res->Count; i++)
         Memo1->Lines->Add(Res->Strings[i]);

        IsSaved=false;
       }
  delete Res;
}
//---------------------------------------------------------------------------
void __fastcall TSDIAppForm::Contents1Click(TObject *Sender)
{
AnsiString Path=AppPath+"\\"+HelpDir+"\\"+"CvTape.chm";

ShellExecute(0,"open",Path.c_str(),NULL,NULL,SW_SHOWNORMAL );

}
//---------------------------------------------------------------------------


void __fastcall TSDIAppForm::FormClose(TObject *Sender, TCloseAction &Action)
{
try
{
  if (!IsSaved)
   switch (MessageDlg("Do you want to save decoded file?",mtConfirmation,TMsgDlgButtons() << mbYes << mbNo << mbCancel,0) )
    {
    case mrYes:     { SaveItemClick(NULL);  break;}
    case mrNo:      { Action=caFree ; IsSaved=true; break; }
    case mrCancel:  { Action=caNone; IsSaved=false; throw EAbort( NULL ); }
    }

delete Buffer;
delete CvTape;

// Aggiorno la MRU List nel registro

// Salvo la posizione dei menu

TRegistry *Reg=new TRegistry;

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\Locations",true);
   Reg->WriteString("LogFile",LogFile);
   Reg->WriteString("TipFile",TipFile);
   Reg->CloseKey();

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\MenuStatus\\WaveInfoWin",true);
   Reg->WriteBool("Visible",WaveInfoForm->Visible);
   Reg->WriteInteger("PosX",WaveInfoForm->Left);
   Reg->WriteInteger("PosY",WaveInfoForm->Top);
   Reg->CloseKey();

   Reg->OpenKey("Software\\CreatiVemu\\CvTapeWin\\Options",true);
   Reg->WriteBool("SaveLog",SaveLog);
   Reg->WriteBool("ModifyResult",CanModify);
   Reg->WriteString("ManualTresholdValue",Edit1->Text);
   Reg->WriteBool("AutoTreshold",AutoTreshold);
   Reg->WriteBool("FmSynt",Fm);
   Reg->WriteBool("ShowTips",ShowTips);
   Reg->CloseKey();


delete Reg;

}
catch (EAbort *E)
{
 //
}




}

//---------------------------------------------------------------------------



void __fastcall TSDIAppForm::CheckBox1Click(TObject *Sender)
{
  Edit1->Enabled= CheckBox1->State==cbUnchecked;
  UpDown1->Enabled= CheckBox1->State==cbUnchecked;
  AutoTreshold=(CheckBox1->State==cbChecked);
}
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::OpenDialogClose(TObject *Sender)
{
char empty[255],empty1[255],st[255],ext[10];

if (FileName!="")
{

  if (!IsSaved)
   switch (MessageDlg("Do you want to save decoded file?",mtConfirmation,TMsgDlgButtons() << mbYes << mbNo << mbCancel,0) )
    {
    case mrYes:     { SaveItemClick(Sender); break ;}
    case mrNo:      { IsSaved=true; break; }
    case mrCancel:  { IsSaved=false; throw EAbort( NULL ); }
    }

  if(IsSaved)

 try
  {
   Memo1->Clear();
   IsLoaded=true;
   LeftCh->Enabled=true;
   LeftChRadio->Enabled=true;
   
   TWaveFile *File=new TWaveFile(FileName);

   //  Aggiorno la caption del form

   _splitpath(FileName.c_str(),empty,empty1,st,ext);
   Caption=AnsiString("Creativision wave decoder : ")+AnsiString(st)+AnsiString(ext);

   // Scrivo sul memo i dati del file

   WaveInfoForm->StringGrid1->Cells[1][1]=AnsiString(st)+AnsiString(ext);
   WaveInfoForm->StringGrid1->Cells[1][2]=AnsiString(File->GetSamplingRate());
   WaveInfoForm->StringGrid1->Cells[1][3]=AnsiString(File->GetChannels());
   WaveInfoForm->StringGrid1->Cells[1][4]=AnsiString(File->GetBytePerSample());
   WaveInfoForm->StringGrid1->Cells[1][5]=AnsiString(File->GetBitPerSample());
   WaveInfoForm->StringGrid1->Cells[1][6]=AnsiString(File->GetBytePerSec());
   WaveInfoForm->StringGrid1->Cells[1][7]=(File->IsCompressed())?"No":"Yes";
   WaveInfoForm->StringGrid1->Cells[1][8]=AnsiString(File->GetByteLen());
   WaveInfoForm->StringGrid1->Cells[1][9]=AnsiString(File->GetSampleLen());

   // Traccio l'immagine

   File->PreviewDraw( Buffer );

   LeftCh->Picture->Bitmap->Assign(Buffer);

   delete File;

   // Creo un nuovo CreatiDecode

   if (CvTape!=NULL) delete CvTape;

   CvTape=new CreatiDecode( FileName );

   }
catch ( EWaveFile E )
{

  for (int i=1; i<10; i++)
  {
   WaveInfoForm->StringGrid1->Cells[1][i]="";
  }

   Caption=AnsiString("Creativision wave decoder");
   Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ECreatiExc E )
{

  for (int i=1; i<10; i++)
  {
   WaveInfoForm->StringGrid1->Cells[1][i]="";
  }
   Caption=AnsiString("Creativision wave decoder");
   Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);

}

catch ( EAbort *E )
{
  //  Nothing!!
}

}

}

//---------------------------------------------------------------------------






void __fastcall TSDIAppForm::HomePageClick(TObject *Sender)
{
 ShellExecute(0,"open","iexplore.exe","http://space.tin.it/computer/giovanni.ortu",NULL,SW_MAXIMIZE	 );
}
//---------------------------------------------------------------------------


void __fastcall TSDIAppForm::CveHomeClick(TObject *Sender)
{
 ShellExecute(0,"open","iexplore.exe","http://creativemu.emuhq.com",NULL,SW_MAXIMIZE	 );
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::MadHomeClick(TObject *Sender)
{
 ShellExecute(0,"open","iexplore.exe","http://madrigal.emuita.it",NULL,SW_MAXIMIZE	 );
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::FormResize(TObject *Sender)
{
 LeftCh->Width=Width;

}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::FormShow(TObject *Sender)
{
 CheckBox1->Checked=AutoTreshold;
 Edit1->Text=ManualTreshold;
 Memo1->ReadOnly=!CanModify;
 WaveInfoForm->Visible=WaveInfoFormVisible;
 if ( WaveInfoFormVisible )WaveInfoForm->Show();
 if ( ShowTips ) Tips->Show();

}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::Memo1Change(TObject *Sender)
{
 IsSaved=false;
}
//---------------------------------------------------------------------------





void __fastcall TSDIAppForm::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

  if (Key==VK_RETURN)
  {
    DecodeClick(this);
  }

 }
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::PrintClick(TObject *Sender)
{
  TPrinter *Lpt=new TPrinter;

  PrintDialog1->Options.Clear();
  PrintDialog1->FromPage = 1;
  PrintDialog1->MinPage = 1;

  if (PrintDialog1->Execute())
  {
   Lpt->BeginDoc();
    for (int i = 0; i <= Memo1->Lines->Count; i++)
   {
   Lpt->Canvas->TextOut(10,50*i,Memo1->Lines->Strings[i]);
   }
   Lpt->EndDoc();
  }
delete Lpt;
}
//---------------------------------------------------------------------------


void __fastcall TSDIAppForm::Image1DblClick(TObject *Sender)
{
 Author->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::BatchClick(TObject *Sender)
{
//  Batch conversion

AnsiString WaveFile,TextFile,ThisPath;
char disk[3],path[255],name[255],ext[3];
TStringList *Res =new TStringList;
TStringList *Res2=new TStringList;
AnsiString Dir = "";

try
{
if (OpenMulti->Execute())
 {
 if (SelectDirectory("Select Directory", "", Dir))
  BatchDir = Dir;
 else return;

 if (BatchDir.Length()!=3) BatchDir+="\\";

 Memo1->Clear();
 Memo1->Lines->Add("Output directory: "+BatchDir);

 IsLoaded=false;
 IsSaved=true;

 for (int i=0; i<OpenMulti->Files->Count; i++)
 {
  Res->Clear();
  WaveFile=OpenMulti->Files->Strings[i];
  _splitpath(WaveFile.c_str(),disk,path,name,ext);
  ThisPath=AnsiString(disk)+AnsiString(path);

  if (ProgressiveName)
   TextFile=BatchDir+"File"+AnsiString(i)+".txt";
  else
   TextFile=BatchDir+AnsiString(name)+".txt";

   delete CvTape;
   CvTape=new CreatiDecode( WaveFile );

   if (AmButton->Checked)
    CvTape->DecodeAm(Res);
   else
    CvTape->DecodeFm(Res);

   Res2->Assign(Res);
   Res2->SaveToFile(TextFile);

   if (Canc) throw EAbort( NULL );
   Memo1->Lines->Add(AnsiString(name)+".txt");

 } // for


} // if

delete Res;
IsSaved=true;
IsLoaded=false;
}

catch ( EAbort *e)
{
  //
}

}
//---------------------------------------------------------------------------







void __fastcall TSDIAppForm::WaveInfo1Click(TObject *Sender)
{
 WaveInfoForm->Show();
}
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::AmButtonClick(TObject *Sender)
{
 Fm=!AmButton->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::FmButtonClick(TObject *Sender)
{
 Fm=FmButton->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TSDIAppForm::Tipoftheday1Click(TObject *Sender)
{
 Tips->Show();        
}
//---------------------------------------------------------------------------







void __fastcall TSDIAppForm::Close1Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::DecodeButtonClick(TObject *Sender)
{

AnsiString WaveFile,TextFile,ThisPath;
char disk[3],path[255],name[255],ext[3];
TStringList *Res =new TStringList;
AnsiString Dir = "";

  CvTape=new CreatiDecode( FileName );

   if (AmButton->Checked)
    CvTape->DecodeAm(Res);
   else
    CvTape->DecodeFm(Res);


   if (Canc) throw EAbort( NULL );
   Memo1->Lines->Add(AnsiString(name)+".txt");


}
//---------------------------------------------------------------------------

