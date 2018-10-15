//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Decode.h"
#include "SDIMain.h"
#include "Error.h"
#include "math.h"
#include "io.h"
#include "WaveFile.h"
#include "Prefs.h"
#include "Advance.h"


//---------------------------------------------------------------------------

class TwaveFile;

// Classe per le eccezioni

ECreatiExc::ECreatiExc(AnsiString Error)
{
 this->Error=Error;
}

AnsiString ECreatiExc::GetErrorMessage()
{
 return this->Error;
}

// Fine classe eccezioni

// Classe CreatiDecode

// Costruttori

CreatiDecode::CreatiDecode( AnsiString FileName )
{
 float Middle,Segno,MinSearch;
 bool MinZero=true;

 GetStat=false;

 Count2=0;

 this->FileName=FileName;

 try  // Inizia a leggere dal File e crea Temp[] e Temp2[]
 {
  File=new TWaveFile( FileName);
  Log=new TStringList;

  Channels=File->GetChannels();
  Log->Add("Numero di canali: "+AnsiString((int)Channels));

  Compressed=File->IsCompressed();
  Log->Add("Formato compresso: "+AnsiString(Compressed?"Si":"No"));

  SamplingRate=File->GetSamplingRate();
  Log->Add("Frequenza di campionamento: "+AnsiString((int)SamplingRate)+" Hz");

  BitPerSample=File->GetBitPerSample();
  Log->Add("Risoluzione: "+AnsiString((int)BitPerSample)+" Bit");

  Len=File->GetSampleLen();
  Log->Add("Numero campioni : "+AnsiString((int)Len));

 // Controllo che il File sia di tipo giusto

 SDIAppForm->RightCh->Enabled=(Channels!=1);
 SDIAppForm->RightChRadio->Enabled=(Channels!=1);

// if (Channels!=1) File->SetChannel(SDIAppForm->Channel);

//  throw ECreatiExc("Wrong number of channels");

 // Inizializzo la progress bar


}// Try

catch ( EWaveFile E )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ECreatiExc E )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ... )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox("Unexpected error!","Error",MB_OK);
}

} // Costruttore

CreatiDecode::~CreatiDecode( void )
{
  delete Temp;
  delete Temp2;

  delete Log;
}

// Metodi

bool CreatiDecode::TestSeq(unsigned char Bit,unsigned int word)
{
static unsigned  int State=0;   // Variabile per la macchina a stati che riconosce
                                   // le sequenze di Bit...

 State<<=1;

 if (Bit==1) State|=0x0001;
  else State&=0xfffe;

 if (State==word) return true;
  else return false;
}

float CreatiDecode::GetAverage(long Pos,long Offset )
{
 float Sum=4*Massimo;

 for (int i=Pos; i<Pos+Offset; i++)
  Sum+=Temp[i];

 return Sum/(Offset+4);
}

 // Funzioni principali di decodifica

 // Sintesi FM



 void CreatiDecode::DecodeFm( TStringList *Result )
 {
  //  Devo contare i campioni > 0 , gli intervalli > sono gli uno, gli altri zero
  //  Dati in Temp2[]

  int *Vett,i;
  int nDim,Dim=0;
  int Max=-1,Min=-1;
  int iMax,iMin,Soglia;
  unsigned char Bit;

  try
  {
   if (!GetStat) GetStatistics();

  GetStat=true;

  Result->Clear();

  NumByte=0;
  BitPos=7;
  Bit=0;
  Detected=false;

  // calcolo il valore del massimo picco delle somme

  for (i=0; i<Count2; i++) if (Temp2[i]>Dim) Dim=Temp2[i];

  // dimensiono il vettore delle occorrenze per contenerle tutte

  int Div=1;

  Dim=(int)(Dim/Div);

  Vett=new int[Dim+1];
  // lo azzero

  for ( i=0; i<Dim; i++) Vett[i]=0;

  // Setto lo status form

  Status->Show();
  SDIAppForm->Enabled=false;

  Status->Caption=AnsiString("Scanning file...");
  Status->ProgressBar1->Progress=0;
  Status->Label2->Caption="Input file: "+FileName;

  Step=(long) (Count2/100);

  for ( i=0; i<Count2; i++)
  {
  Application->ProcessMessages();

  if (!(i % Step)) Status->ProgressBar1->Progress++;

  Vett[(int)(Temp2[i]/Div)]++;

  }
  Status->ProgressBar1->Progress=0;
  Step=(long) Dim;
  // Cerco due massimi
  for ( i=4; i< Dim ; i++)
  {
  Application->ProcessMessages();

  if (!(i % Step)) Status->ProgressBar1->Progress++;

   if (Vett[i]>Max) { Max=Vett[i]; iMax=i; }

  }
  for (i=0; i<=iMax+5; i++) if (i<Dim) Vett[i]=0;

  Status->ProgressBar1->Progress=0;

  //for ( i=0; i< Dim ; i++)  SDIAppForm->Memo1->Lines->Add(AnsiString(i)+"="+AnsiString(Vett[i]));

  Vett[iMax]=0;

  for ( i=2; i< Dim ; i++)
  {
  Application->ProcessMessages();



  if (!(i % Step)) Status->ProgressBar1->Progress++;

  if (Vett[i]>Min) { Min=Vett[i]; iMin=i; }
  }

  // in iMax ed iMin ci sono i valori più frequenti di campioni > 0
  /*
  SDIAppForm->Memo1->Lines->Add("-------");
  SDIAppForm->Memo1->Lines->Add(AnsiString(Max)+"     "+AnsiString(iMax));
  SDIAppForm->Memo1->Lines->Add(AnsiString(Min)+"     "+AnsiString(iMin));
  SDIAppForm->Memo1->Lines->Add("-------");
  */

  Soglia=(int) (iMax+iMin)/2.1;

  Status->Caption=AnsiString("Decoding processed file...");
  Status->ProgressBar1->Progress=0;
  Step=(long) (Count2/100);

  for ( i=0; i<Count2; i++)
  {

  Application->ProcessMessages();

  if (!(i % Step)) Status->ProgressBar1->Progress++;

  if (Temp2[i]>=Soglia) Bit=1; else Bit=0;

   Detect( Bit, Result);

  }

 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();

delete Vett;
   
}  // Try

catch ( EWaveFile E )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ECreatiExc E )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ... )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox("Unexpected error!","Error",MB_OK);
}

}



 // Sintesi AM

 void CreatiDecode::DecodeAm( TStringList *Result )
 {

 float Max,Min;


try  // Inizia a leggere da Temp[]
{

 if (!GetStat) GetStatistics();

 GetStat=true;

 NumByte=0;
 BitPos=7;
 Bit=0;
 Detected=false;

 Result->Clear();

 Status->Show();
 SDIAppForm->Enabled=false;

 Step=(long) (Len/100);

 Status->Caption=AnsiString("Decoding processed file...");
 Status->ProgressBar1->Progress=0;
 Status->Label2->Caption="Input file: "+FileName;

 Treshold=SDIAppForm->Edit1->Text.ToInt();

 Count=0;
 while ((Count<Len) && (!Status->Canceled) )
 {
  Application->ProcessMessages();

  if (!(Count % Step)) Status->ProgressBar1->Progress++;

  Relative=Temp[Count++]; // Leggo un livello

 // inserisco la tecnica adattiva. Parametro: numero di campioni

 if (((Count % 10)==0) && (SDIAppForm->AutoTreshold))
   {
   if (NumByte<63)   // evito i problema degli ultimi picchi
    Treshold=GetAverage( Count, 15 );
   }

  if (Relative>Treshold) Bit=1; else Bit=0;

  Detect(Bit, Result);

 }      // While Count

 Status->ProgressBar1->Progress=0;

 if (Status->Canceled)
 {
  SDIAppForm->IsSaved=true;
  Status->Canceled=false;
 }

 if (Preferences->LogCheckBox->Checked) Log->SaveToFile(SDIAppForm->LogFile);

 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();

  

 }// Try

catch ( EWaveFile E )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ECreatiExc E )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ... )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox("Unexpected error!","Error",MB_OK);
}


} // fine del Main


void CreatiDecode::Detect( unsigned char Bit, TStringList *Result)
{
  // Rilevamento

   if ( !Detected && (TestSeq(Bit,0x0073))  ) // Rilevo la sequenza 01110011 (0x0073)
    {
    Detected=true;
    }
	else
   if (Detected)   // Se ho trovato 0x73 metto i Bit nel Byte
    {
     if (BitPos==7) Byte[NumByte]=0;    // Se Stò iniziando azzero il Byte
     Byte[NumByte] |= (Bit << BitPos ); // Setto il Bit BitPos-esimo del Byte b-esimo
     BitPos--;                    // Passo al Bit successivo
     if (BitPos<0)                // Se sono arrivato all'ultimo Bit...
     {
      BitPos=7;                   // ...ricomincio a contarli...
      NumByte++;                   // ...passo al Byte successivo.
      if (NumByte==64)             // Se ho letto 64 Byte (una Linea Creativision)
       {
        for (i=NumByte-1; i>1 ; i--)
         if ((Byte[i]!=13) && (Byte[i]!=0))
          Line+=AnsiString((char) Byte[i]);
        Result->Add(Line);
        Line=AnsiString("");
        NumByte=0;
        Detected=false;
       } // NumByte==64
      }  // BitPos<00
    }   // Detected


 } // fine



void CreatiDecode::GetStatistics (void )
{
 float Middle;
 int Segno,MinSearch,MinZero;

try
{
  Status->Show();
  SDIAppForm->Enabled=false;

 Count=0;
 Step=(long) (Len/100);

 Middle=abs(File->MaxValue()+File->MinValue())/2;

 Minimo=File->MaxValue();
 Massimo=File->MinValue();

 Temp=new float[Len];
 Temp2=new int[Len];

 Status->ProgressBar1->Progress=0;
 Status->Caption=AnsiString("Open File: Clearing buffer...");
 Status->Label2->Caption="Input file: "+FileName;

 for (int i=0; i<Len; i++)
 {
  if (!(i % Step)) Status->ProgressBar1->Progress++;
  Temp2[i]=0;
  }

 File->SetPos(0);

 // cerco il minimo assoluto ed il max assoluto
 // quello più grande in valore assoluto mi da la posizione dei picchi

 Status->ProgressBar1->Progress=0;
 Status->Caption=AnsiString("Open File: getting statistics...");
 Status->Label2->Caption="Input file: "+FileName;

 for (int i=0; i<File->GetSampleLen(); i+=50)
 {
  if (Status->Canceled) break;

  if (!(File->GetPos() % Step)) Status->ProgressBar1->Progress++;

  Sample1=File->GetSample(i);

  Application->ProcessMessages();

  if (Sample1>Massimo) Massimo=Sample1;
  if (Sample1<Minimo) Minimo=Sample1;
 }



 if (abs(Massimo)<abs(Minimo)) Segno=Massimo/abs(Massimo);
  else Segno=Minimo/abs(Minimo);

 MinSearch=Middle;

 Status->ProgressBar1->Progress=0;
 Status->Caption=AnsiString("Open File: Scanning...");

 File->SetPos(0);


 while(!File->EndOfWave() && (!Status->Canceled))
 {
  // setto  anche Temp2[]

  if (!(File->GetPos() % Step)) Status->ProgressBar1->Progress++;

  Sample2=File->GetNextSample(); // Questo per Temp2[]

  Sample1=Segno*Sample2;

  if (Sample2>=0) { MinZero=false; Temp2[Count2]++; }

  if ((Sample2<0) && (!MinZero))
   { MinZero=true; Count2++; }




  Application->ProcessMessages();

  if (Sample1>=Middle)
  {
   MinSearch=Middle;       // se il valore è > del Minimo ricomincio a settare il Minimo
   UseIt=true;    // inoltre i valori sono di nuovo utilizzabili
  }
  else if (UseIt)
  {
  if (Sample1<MinSearch) MinSearch=Sample1; // altrimenti setto il Minimo
   else
   if (Sample1>=MinSearch)
   {
    // memorizzo max e minimo dei picchi
    Sample1=(float)abs(Sample1);

    Temp[Count++]=Sample1;

    MinSearch=Middle;  UseIt=false;
   }
  }

 }
 if (!(Status->Canceled))
 {
  Minimo=MaxFileValue;
  Massimo=MinFileValue;
 // Calcolo la media dei valori di picco

  for (int i=0; i<Count; i++)
  {
   if (Temp[i]>Massimo) Massimo=Temp[i];
   if (Temp[i]<Minimo) Minimo=Temp[i];
  }


  Medio=(Massimo+Minimo)/2;

 }
 else
  {
   Status->Canceled=false;
   SDIAppForm->IsLoaded=false;
   SDIAppForm->IsSaved=true;

   // Cancello l'immagine

   SDIAppForm->LeftCh->Picture->Bitmap->Canvas->Pen->Mode=pmCopy;
   SDIAppForm->LeftCh->Picture->Bitmap->Canvas->Pen->Color=clBtnFace;
   SDIAppForm->LeftCh->Picture->Bitmap->Canvas->Pen->Style=psSolid;
   SDIAppForm->LeftCh->Picture->Bitmap->Canvas->Brush->Style=bsSolid;
   SDIAppForm->LeftCh->Picture->Bitmap->Canvas->Brush->Color=clBtnFace;
   SDIAppForm->LeftCh->Picture->Bitmap->Canvas->Rectangle(0,0,SDIAppForm->LeftCh->Picture->Bitmap->Width,SDIAppForm->LeftCh->Picture->Bitmap->Height);

   SDIAppForm->RightCh->Picture->Bitmap->Canvas->Pen->Mode=pmCopy;
   SDIAppForm->RightCh->Picture->Bitmap->Canvas->Pen->Color=clBtnFace;
   SDIAppForm->RightCh->Picture->Bitmap->Canvas->Pen->Style=psSolid;
   SDIAppForm->RightCh->Picture->Bitmap->Canvas->Brush->Style=bsSolid;
   SDIAppForm->RightCh->Picture->Bitmap->Canvas->Brush->Color=clBtnFace;
   SDIAppForm->RightCh->Picture->Bitmap->Canvas->Rectangle(0,0,SDIAppForm->RightCh->Picture->Bitmap->Width,SDIAppForm->RightCh->Picture->Bitmap->Height);

  }


 Len=Count;

 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();

 MaxFileValue=File->MaxValue();
 MinFileValue=File->MinValue();


 delete File;

 }

 catch ( EWaveFile E )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ECreatiExc E )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox(E.GetErrorMessage().c_str(),"Wave File Error",MB_OK);
}

catch ( ... )
{
 Status->Hide();
 SDIAppForm->Enabled=true;
 SDIAppForm->Show();
 Application->MessageBox("Unexpected error!","Error",MB_OK);
}



 }


void CreatiDecode::SetChannel(int Ch)
{
// File->SetChannel(Ch);
}
