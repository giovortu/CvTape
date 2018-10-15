//---------------------------------------------------------------------------
#ifndef WaveFileH
#define WaveFileH
//---------------------------------------------------------------------------
#endif


// Classe per la gestione di file wave
class EWaveFile;

class TWaveFile
{
 private:
  AnsiString FileName;               //  Nome del file
  unsigned long  ByteLen;            //  Lunghezza in Byte
  unsigned long  Position;           //  Posizioni nel file (in campioni)
  unsigned long  SampleLen;          //  Lunghezza in campioni
  bool           IsComp;             //  File Compresso/non compresso
  unsigned int   SamplingRate;       //  Frequenza di campionamento
  unsigned int   Channels;           //  Numero di canali
  unsigned int   BytePerSec;         //  Byte al secondo
  unsigned int   BytePerSample;      //  Byte per campione
  unsigned int   BitPerSample;       //  Numero di bit per campione
  char *         Buffer;             //  Buffer che uso per leggere
  TFileStream    *Stream;            //  File Wave
  long           MaxSampleValue;     //  Massimi valori del campione
  long           MinSampleValue;
  long           Pow256[4];          //  Tabella delle potenze di 256

  void           CreateEmpty(AnsiString,unsigned int,unsigned int,unsigned int) throw (EWaveFile);
  
 public:

 TWaveFile(AnsiString FileName) throw (EWaveFile);
 ~TWaveFile();

unsigned  long   GetByteLen( void ) throw (EWaveFile);
unsigned  long   GetSampleLen( void ) throw (EWaveFile);
unsigned  int    GetSamplingRate( void ) throw (EWaveFile);
unsigned  int    GetChannels( void ) throw (EWaveFile);
unsigned  int    GetBytePerSec( void ) throw (EWaveFile);
unsigned  int    GetBitPerSample( void ) throw (EWaveFile);
unsigned  int    GetBytePerSample( void ) throw (EWaveFile);
float            GetNextSample( void ) throw (EWaveFile);
float            GetSample( unsigned long ) throw (EWaveFile);
unsigned  long   GetPos( void ) throw (EWaveFile);
bool             EndOfWave( void ) throw (EWaveFile);
void             SetPos( unsigned long ) throw (EWaveFile);
bool             IsCompressed( void ) throw (EWaveFile);
long             MaxValue( void );
long             MinValue( void );
void             PreviewDraw( Graphics::TBitmap * );

void             WriteSample( float ) throw (EWaveFile);
void             WriteSample( unsigned long , float ) throw (EWaveFile);


 }   ;


 // Classe per la gestione delle eccezioni

 class EWaveFile
 {
  AnsiString Error;

  public:

  EWaveFile(AnsiString Error);
  AnsiString GetErrorMessage(void);

 };

