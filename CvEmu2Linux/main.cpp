//****************************************************************************************
//                                                                                        
// CvEmu2 versione 0.5 alpha 1
//                                                                                      
// Ideato progettato e relizzato da Giovanni Ortu                                        
//                                                                                       
// Il programma utilizza le seguenti librerie e porzioni di codice:                                                                               
//
// Cpu 6502    : Basato sul codice scritto da Neil Bradley.                              
// Vdp 9929    : EMULib Emulation Library, Copyright (C) Marat Fayzullin 1996-2002       
// Pia 6821    : Emulatore ricavato dal MAME                                             
// Audio 76489 : EMULib Emulation Library, Copyright (C) Marat Fayzullin 1996-2002
//
//
//                                                                                       
// Librerie    : SDL                                                                     
// Compilatore
//     Windows : DEV-C++ 4.9.7.0 gcc                                                     
//       Linux : g++ 2.9.6
//
//****************************************************************************************



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>

#include "include/memory.h"
#include "include/defs.h"
#include "font/font.h"

#include "cpu/cpu6502.h"
#include "video/tms9918.h"
#include "mem/cvmemory.h"
#include "pia/6821pia.h"
#include "audio/sn76496.h"
#include "menu/menu.h"
#include "keyboard/keyboard.h"

#include "main.h"

#ifdef WINDOWS
#include <windows.h>
#endif


 //****************
 //*     Main     *
 //****************
 
int main(int argc, char *argv[])
{


  //******************************
  // Check sui parametri da linea
  // di comando
  //******************************
  if (!CheckCmdLine(argc,argv))
  {
   FreeEmu();  
   exit(0);
  }

  //******************************
  // Inizializzazione Video (SDL)
  //******************************
  InitScreen();

  //******************************
  // Inizializzazione Audio (SDL)
  //******************************
  //InitAudio();

  InitMenu();

  //*********************************
  // Inizializzo la memoria della Cv 
  //********************************* 

  if (!createCvMemory(cvMemory, BiosName, RomName))
  {
   FreeEmu();
   exit(0);
  }  

  //******************************
  // Se necessario leggo il file
  // .INI. Se non esiste lo creo
  //******************************
  // if (!CmdLine) IniFile();

  //*********************************
  // Inizializzazione Hardware (EMU)
  //*********************************
  
  InitHardware();
  
  //******************************
  // Resetto la Cpu
  //******************************
  reset6502();
  
  //**************************************************
  // Inizializzo il timer video (50 frame al secondo)
  // La funzione aggiorna su schermo il contenuto del
  // buffer video
  //**************************************************
  VideoTimer = SDL_AddTimer(TIMER_SPEED, &RefreshVideo, (void *) Vdp->XBuf);
  
  //**************************************************
  // Avvio l'audio
  //**************************************************
  //SDL_PauseAudio(0);
  
  //******************************
  // Ciclo principale
  //******************************
  

  
  while (!done)
  {
  //*************************************************************
  // Se il gioco non �in pausa...
  //*************************************************************
  if (!Paused)
  {
  //*************************************************************
  // Check Loop video e lancio l'interrupt alla CPU
  //*************************************************************
  if (VdpIrq=Loop9918(Vdp)) irq6502();

  //****************************************************************
  // Eseguo le istruzioni 6502 intercettando l'IO su Vdp e Pia
  //****************************************************************
  exec6502(420);//420);

  //***********************************************
  // Sincronizzo l'emulatore
  //***********************************************
  Syncro(420);//420);
  

  //****************************
  // Check audio
  //****************************

 } // Fine Pausa


  //**************************************************************
  // Test sugli eventi SDL (Tastiera, joystick ed eventi windows)
  //**************************************************************
  CheckEvents();

 //******************************
 // Fine loop emulazione
 //******************************
 } // !Done

 //**************************************************
 // Interrompo l'audio
 //**************************************************

 //SDL_PauseAudio(1);

 //******************************
 // Distruggo i buffer allocati
 //******************************
  FreeEmu();

  //******************************
  // Fine del programma
  //******************************

  return 1;
}

//**************************************************************************
//************************* Definizione funzioni ***************************
//**************************************************************************

//*******************************************
// FreeEmu :
//*******************************************
// Liber la memoria allocata dall'emulatore
//*******************************************

void FreeEmu(void)
{

  //******************************  
  // Blocco il timer
  //******************************  
  if (VideoTimer) SDL_RemoveTimer(VideoTimer);
 
  //******************************  
  // Distruggo le superfici SDL
  //******************************
    
  if (Screen) SDL_FreeSurface(Screen);
  if (CvScreen) SDL_FreeSurface(CvScreen);
  if (Menu)  SDL_FreeSurface(Menu);

  //******************************
  // Elimino il font usato
  //******************************

  if (font) freeFont(font);
  
  //******************************
  // Elimino i timer
  //******************************
  
  if (VideoTimer) SDL_RemoveTimer(VideoTimer);

  if (Vdp)
  { Trash9918(Vdp);  delete Vdp; }

  if (VdpRam)   delete VdpRam;
  if (cvMemory) delete cvMemory;
  
  delete Audio_spec;
  
  SDL_CloseAudio();  
  SDL_Quit();
  
} // Fine Free Emu

//*******************************************
// InitScreen :
//*******************************************
// Inizializza le SDL ed il layout del video
//*******************************************


void InitScreen(void)
{

    //************************************
    // Initializzo SDL  
    //************************************
    if (SDL_Init (SDL_INIT_VIDEO || SDL_INIT_AUDIO || SDL_INIT_TIMER) < 0)
    {
     sprintf (msg, "Couldn't initialize SDL video and timer: %s\n", SDL_GetError ());
     #ifdef WINDOWS
     MessageBox (0, msg, "Error", MB_ICONHAND);
     #else
     printf("%s",msg);
     #endif
     exit (1);
    }

    //SDL_WM_SetIcon(SDL_LoadBMP("cvemu2.bmp"), NULL);
    //***************************************************
    // Set VIDEO_WIDTH x VIDEO_HEIGHT  video mode 
    //***************************************************
    
    Screen = SDL_SetVideoMode (VIDEO_WIDTH, VIDEO_HEIGHT, CV_NUMCOLORS, SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF );// | SDL_FULLSCREEN);

    if (Screen == NULL)
    {
     sprintf (msg, "Couldn't set video mode: %s\n", SDL_GetError ());
     #ifdef WINDOWS
     MessageBox (0, msg, "Error", MB_ICONHAND);
     #else
     printf("%s",msg);
     #endif
     exit (2);
    }


   // Setto la palette
   SDL_SetColors(Screen, SDL_CvPal, 0, 16);
   
   // Setta la caption della finestra
   #ifdef WINDOWS
   SDL_WM_SetCaption ("CreatiVemu2 for Windows", NULL);
   #else
   SDL_WM_SetCaption ("CreatiVemu2 for Linux", NULL);
   #endif
   
   SetupScreen();
   
   SDL_EnableUNICODE(1);
   
}

void SetupScreen()
{

   // Colora di "Blu Creativision" la finestra
   color = SDL_MapRGB (Screen->format, 0x00,0x00,0x00);
   SDL_FillRect (Screen, NULL, color);

    // Mostra il riquadro video della Cv
   color = SDL_MapRGB (Screen->format, 0x00, 0x00, 0x00);//0x3f);
   CvRect.w = CV_VIDEO_WIDTH;
   CvRect.h = CV_VIDEO_HEIGHT;
   CvRect.x = (Screen->w / 2) - (CvRect.w / 2);
   CvRect.y = (Screen->h / 2) - (CvRect.h / 2);
   SDL_FillRect (Screen, &CvRect, color);

   SDL_Flip(Screen);
  // Fine inizializzazione video    


}

//*******************************************
// AudioCallback function
//*******************************************
void AudioCallback(void *udata, Uint8 *stream, int len)
{
        /* Only play if we have data left */
          
        if ( audio_len == 0 )
            return;

        /* Mix as much data as possible */
        len = ( len > audio_len ? audio_len : len );
        SDL_MixAudio(stream,(Uint8 *) sn->Output[1], len, SDL_MIX_MAXVOLUME);
        //sn->Output += (Uint8 ) len ;
        audio_len -= len;
        
        

}

//*******************************************
// InitAudio :
//*******************************************
// Inizializza il sottosistema audio
//*******************************************

void InitAudio(void)
{

SDL_AudioSpec *desired=new SDL_AudioSpec;
SDL_AudioSpec *obtained;

desired->freq = SAMPLE_RATE;
desired->format = AUDIO_U8;
desired->samples = 1024;
desired->channels = 1;
desired->callback=AudioCallback;
desired->userdata=NULL;


if (SDL_OpenAudio(desired,obtained)<0)
    {
     sprintf (msg, "Couldn't start audio subsystem: %s\n", SDL_GetError ());
     #ifdef WINDOWS
     MessageBox (0, msg, "Error", MB_ICONHAND);
     #else
     printf("%s",msg);
     #endif
     exit (2);
    }

 Audio_spec=desired;

//delete desired;

 SDL_PauseAudio(0);
 
}

//*******************************************
// InitHardware :
// Inizializza l'hardware dell'emulatore
//*******************************************

void InitHardware(void)
{
  //**********************************
  // Inizializzo l'emulazione del PIA
  //**********************************
  pia_config(0,PIA_STANDARD_ORDERING,&PiaInterface);
  pia_reset();
  pia_set_input_ca1(0,1);
  pia_set_input_ca2(0,1);
 

  //************************************
  // Inizializzo l'emulazione del suono
  //************************************
  
  sn76496Init(1, 600000, 150, SAMPLE_RATE);

  //******************************************
  // Inizializzo l'emulazione del chip video
  // e la palette dei colori
  //******************************************
  New9918(Vdp,VdpRam,CV_VIDEO_WIDTH,CV_VIDEO_HEIGHT);
  SetPalette(Vdp);

  //******************************
  // Inizializzo la Cpu
  //******************************
  init6502();


}


//*******************************************
// RefreshVideo :
//*******************************************
// Scrivo il buffer video sullo schermo 
// 50 volte al secondo
//*******************************************

Uint32 RefreshVideo(Uint32 interval,void *Buffer)
{
 CvScreen = SDL_CreateRGBSurfaceFrom((BYTE*) Vdp->XBuf,CV_VIDEO_WIDTH,CV_VIDEO_HEIGHT,8,CV_VIDEO_WIDTH,RMASK,GMASK,BMASK,AMASK);
 SDL_SetPalette(CvScreen,SDL_LOGPAL,SDL_CvPal,1,16);

 SDL_UpperBlit(CvScreen,NULL,Screen,&CvRect);

 SDL_Flip(Screen);

 return interval;

}

//*******************************************
// Syncro :
//*******************************************
// Sincronizzazione dell'eulatore
//*******************************************

void Syncro( int time )
{
 unsigned int Diff,TimeCycle;
  
 Cycle++;
 if (Cycle>=SYNCRO_TIME)
 {
  Diff=SDL_GetTicks()-Ticks; 
  TimeCycle=(unsigned int)(CPUTIME*time*SYNCRO_TIME);
  
  if (Diff<TimeCycle) { SDL_Delay(TimeCycle-Diff); }
  Ticks=SDL_GetTicks();
  Cycle=0;


  
 }
 
}

//*******************************************
// CheckCmdLine :
//*******************************************
// Verifica le opzioni della linea di comando
//*******************************************
// Versione 2: accetta sulla linea di comando il bios

int CheckCmdLine(int argc,char **argv)
{
 //****************************************
 // Se ho switch sulla linea di comando...
 //****************************************
 
 if (argc>1)
 {
  strcpy(RomName,argv[1]);
  if (argc>2)
   strcpy(BiosName,argv[2]);
  return 1;
 }
 
 printf("\nNo argument passed on command line!\n\n") ;
 printf("Usage:\n%s romname [ biosname ]\n\n",(argv[0]));
 
 return 0;

}

//*******************************************
// WaitKey :
//*******************************************
// Attende la pressione di un tasto
//*******************************************
   
void WaitKey(void)
{
   while(1)
   {
     SDL_PollEvent(&event);
     if (event.type==SDL_KEYDOWN) break;
   }
}

//*******************************************
// SwapFullScreen :
//*******************************************
// Cambia Fullscreen / windowed
//*******************************************


void SwapFullScreen()
{
int flags;

fullscreen = (fullscreen ? false : true);

if (fullscreen)
	flags = SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;
else
	flags = SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF;

 // Rimuovo il timer video
 SDL_RemoveTimer(VideoTimer);
	
 // Cambio il modo video
 SDL_SetVideoMode(VIDEO_WIDTH, VIDEO_HEIGHT, CV_NUMCOLORS, flags );



 if (fullscreen) SDL_ShowCursor(SDL_DISABLE );
 else SDL_ShowCursor(SDL_ENABLE );

 // Riattivo il timer video
 if (sMenu) ShowMenu();
 else if (Paused) PauseCv();
 else
 VideoTimer = SDL_AddTimer(20, &RefreshVideo, (void *) Vdp->XBuf);
 
}


void CheckEvents( void )
{
 int KeySymbol;

 if (SDL_PollEvent(&event))
 {
  KeySymbol=event.key.keysym.sym;

  switch (event.type)
  {
   // Uscita dall'applicazione
   case SDL_QUIT:
    done = true;
    break;
   // Tasto premuto
   case SDL_KEYDOWN:
     {
      switch ( KeySymbol )
      {

	  // tasti che devono essere sempre attivi.
       case SDLK_ESCAPE:
        done = true;
        break;

       case SDLK_TAB: // Apre il menu interno
          sMenu=!sMenu; ShowMenu();
          break;

       case SDLK_F12: // Toggle fullscreen
         SwapFullScreen();  break;


	   case SDLK_F2: // Pausa
          Paused=!Paused; PauseCv();
          break;

	    case SDLK_F5: // Pulsante di reset della Cv
         nmi6502(); break;

		default: CheckCvKeysDown( KeySymbol ); break;

     }
     break;


  case SDL_KEYUP:
        {
         CheckCvKeysUp( KeySymbol );   break;
        }


   default:  break;
    
   }
   
 } // Pool eventi

 }// if
 

}



void SetVideoSize(int Width, int Height, char* Caption)
{

int flags;

    
if (fullscreen)
	flags = SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;
else
	flags = SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF;

    //***************************************************
    // Set VIDEO_WIDTH x VIDEO_HEIGHT  video mode 
    //***************************************************
    
    Screen = SDL_SetVideoMode (Width, Height, CV_NUMCOLORS, flags);// | SDL_FULLSCREEN);
     
    if (Screen == NULL)
    {
     sprintf (msg, "Couldn't set video resolution : %s\n",
     SDL_GetError ());
     
     #ifdef WINDOWS
     MessageBox (0, msg, "Error", MB_ICONHAND);
     #else
     printf("%s",msg);
     #endif
     
     exit (2);
    }


   // Setto la palette 
   SDL_SetColors(Screen, SDL_CvPal, 0, 16);
   
   // Setta la caption della finestra
   SDL_WM_SetCaption (Caption, NULL);
}  



