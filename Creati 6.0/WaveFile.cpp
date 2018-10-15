//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "WaveFile.h"
#include "math.h"

//---------------------------------------------------------------------------


// Costruttori e Distruttori

// Il costruttore apre lo stream e prende gli attributi
// lasciando lo stream aperto pronto per leggere i campioni

 TWaveFile::TWaveFile(AnsiString name) throw (EWaveFile)
 {
   char buffer[9];
   unsigned int Count;

   // controllo se il file esiste se no lo creo vuoto (standard)


   // Preparo la tabella delle potenze
   for (Count=0; Count<4; Count++) Pow256[Count]=pow(256,Count);

   Stream=new TFileStream(name,fmOpenRead | fmShareDenyWrite);

   // Primo Tag : 'RIFF'

   Stream->Seek(0,soFromBeginning);

   Stream->Read((char *) buffer,4);
   buffer[4]='\0';

   if (AnsiString(buffer)!=AnsiString("RIFF"))
     throw EWaveFile("Not a Wave File");

   // Lunghezza del file in byte

   Stream->Read(buffer,4);

   // Secondo Tag: 'WAVEfmt '

   Stream->Read(buffer,8);
   buffer[8]=0;

    if (AnsiString(buffer)!=AnsiString("WAVEfmt "))
     throw EWaveFile("Unrecognized file type");

   // Lunghezza dei tag dei dati

   Stream->Read(buffer,4);

   // Compresso/non compresso
   Stream->Read(buffer,2);
   IsComp=AnsiString(buffer)!=AnsiString("\0\1");

   // Numero di canali
   Stream->Read(buffer,2);

   Channels=buffer[0]+buffer[1]*256;

   // Frequenza di campionamento
   Stream->Read(buffer,4);

   SamplingRate=0;
   for (Count=0; Count<4; Count++)
    SamplingRate+=(unsigned char)buffer[Count]*Pow256[Count];

    // Byte per secondo
   Stream->Read(buffer,4);
   BytePerSec=0;
   for (Count=0; Count<4; Count++)
    BytePerSec+=(unsigned char)buffer[Count]*Pow256[Count];

    // Byte per Campione
    Stream->Read(buffer,2);
    BytePerSample=buffer[0]+buffer[1]*256;

    // Bit Per Byte nel campione
    Stream->Read(buffer,2);
    BitPerSample=buffer[0]+buffer[1]*256;

    // 'data' tag
    Stream->Read(buffer,4);
    buffer[4]=0;

    if (strcmp(buffer,"data"))
     throw EWaveFile("Unable to find 'data' tag.");

   // Numero di campioni
   Stream->Read(buffer,4);
   ByteLen=0;
   for (Count=0; Count<4; Count++)
    ByteLen+=(unsigned char)buffer[Count]*Pow256[Count];
    SampleLen=ByteLen/BytePerSample;

    Position=0;
    this->Buffer=new char[BytePerSample];

    MaxSampleValue=0;
   for (Count=0; Count<BytePerSample; Count++)
     MaxSampleValue+=(unsigned char)0xff * Pow256[Count];

     MinSampleValue=-MaxSampleValue;

}

 TWaveFile::~TWaveFile()
 { delete Stream; delete Buffer; }

unsigned  long TWaveFile::GetByteLen( void ) throw (EWaveFile)
 {
  return ByteLen;
 }

unsigned  long TWaveFile::GetSampleLen( void ) throw (EWaveFile)
 { return SampleLen; }

unsigned  int  TWaveFile::GetSamplingRate( void ) throw (EWaveFile)
 { return SamplingRate; }

unsigned  int  TWaveFile::GetChannels( void ) throw (EWaveFile)
 { return Channels; }

unsigned  int  TWaveFile::GetBytePerSec( void ) throw (EWaveFile)
 { return BytePerSec; }

unsigned  int  TWaveFile::GetBitPerSample( void ) throw (EWaveFile)
 { return BitPerSample; }

unsigned  int  TWaveFile::GetBytePerSample( void ) throw (EWaveFile)
 { return BytePerSample; }

bool   TWaveFile::EndOfWave( void ) throw (EWaveFile)
 { return Position>=SampleLen; }

void   TWaveFile::SetPos( unsigned long Position ) throw (EWaveFile)
{
 if (Position>SampleLen) throw EWaveFile("Position out of range");

 Stream->Seek(44+Position*BytePerSample,soFromBeginning	);

 this->Position=Position;

 }

unsigned long   TWaveFile::GetPos( void ) throw (EWaveFile)
 { return Position; }

bool   TWaveFile::IsCompressed( void ) throw (EWaveFile)
 { return IsComp; }

float   TWaveFile::GetNextSample( void ) throw (EWaveFile)
{
 float Sample=0;


 if (Position>SampleLen) throw EWaveFile("End of file");
 Stream->Read(Buffer,BytePerSample);

 for (unsigned int i=0; i<BytePerSample; i++)
  Sample+=(float) (Buffer[i]*Pow256[i]);
  Position++;

 return Sample;

 }

long   TWaveFile::MaxValue( void )
{ return MaxSampleValue; }

long   TWaveFile::MinValue( void )
{ return MinSampleValue; }


void TWaveFile::PreviewDraw( Graphics::TBitmap *Buffer )
 {
  unsigned long Len,Lenght,Sample,X,Inc;

  if (GetChannels()!=1)
  throw EWaveFile("Wrong number of channels");
  else
  if (GetBitPerSample()!=16)
   throw EWaveFile("Wrong number of byte per sample");

  Len=GetByteLen();
  Inc=(unsigned long)(Len/Buffer->Width/15);
  Lenght=GetSampleLen();

  Buffer->Canvas->Pen->Mode=pmCopy;
  Buffer->Canvas->Pen->Color=clBtnFace;
  Buffer->Canvas->Pen->Style=psSolid;

  Buffer->Canvas->Brush->Style=bsSolid;
  Buffer->Canvas->Brush->Color=clBtnFace;
  Buffer->Canvas->Rectangle(0,0,Buffer->Width,Buffer->Height);
  Buffer->Canvas->CopyMode=cmNotSrcCopy;

  Buffer->Canvas->Pen->Color=clBlack;

  Buffer->Canvas->MoveTo(2,Buffer->Height/2);

  for (unsigned long i=1; i<=Lenght; i+=Inc)
  {
   Sample=GetSample(i);
   X=(unsigned long)(i*Buffer->Width/Lenght);
   Buffer->Canvas->LineTo(2+X,Buffer->Height/2-(unsigned long)(Buffer->Height*Sample/MaxValue()));

  }

 Buffer->Canvas->Pen->Color=clRed;
 Buffer->Canvas->MoveTo(2,Buffer->Height/2);
 Buffer->Canvas->LineTo(Buffer->Width,Buffer->Height/2);

 SetPos(0);

 }

float   TWaveFile::GetSample( unsigned long Pos ) throw (EWaveFile)
{
 unsigned long Old;
 float Sample;
 Old=Position;

 if (Position>SampleLen) throw EWaveFile("End of file");

 this->SetPos(Pos);
 Sample=this->GetNextSample();
 Position=Old;
 this->SetPos(Old);

 return Sample;

}
void TWaveFile::CreateEmpty(AnsiString Name, unsigned int SRate, unsigned int BPS ,unsigned int Ch ) throw (EWaveFile)
{
// Usato dal costruttore se il file non esiste

}

void TWaveFile::WriteSample( float ) throw (EWaveFile)
{
//

}
void TWaveFile::WriteSample( unsigned long , float ) throw (EWaveFile)
{
//

}


// Definizione della classe per la gestione delle eccezioni


 EWaveFile::EWaveFile(AnsiString Error)
 {
  this->Error=Error;
 }

 AnsiString EWaveFile::GetErrorMessage()
 {
  return Error;
 }
