//---------------------------------------------------------------------------
#ifndef DecodeH
#define DecodeH
//---------------------------------------------------------------------------
#endif

 class TWaveFile;

 class CreatiDecode
 {
  private:

  bool TestSeq(unsigned char Bit,unsigned int word);
  float GetAverage(long pos,long offset);
  void  Detect( unsigned char Bit , TStringList *Result);

  float Sample1,Sample2,Minimo,Massimo,Medio;
  long NumByte,i,BitPos;
  long Len,Count,Step;
  unsigned long Channels,SamplingRate,BitPerSample;
  unsigned char Bit,Byte[70];
  AnsiString Line;
  bool UseIt,Detected,Compressed;
  float Relative,Treshold,MaxTreshold;
  float MaxFileValue,MinFileValue;

  TWaveFile *File;
  TStringList *Log;
  float *Temp;
  int   *Temp2,Count2;

  public:

  AnsiString FileName;

  CreatiDecode( AnsiString FileName );
  ~CreatiDecode( void );

  void GetStatistics (void );
  void DecodeAm(  TStringList *Result );  // Am
  void DecodeFm( TStringList *Result );  // Fm
  bool GetStat;
  void SetChannel(int Ch);
 };

 // Classi per la gestione delle eccezioni

 class ECreatiExc
 {
  private:

  AnsiString Error;

  public:

  ECreatiExc(AnsiString Error);
  AnsiString GetErrorMessage(void);

 };


