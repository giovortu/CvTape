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
// Compilatore : DEV-C++ 4.9.7.9 gcc                                                     
//
//****************************************************************************************


//******************************************************
//
// Funzioni per la gestione del menu interno
//
//******************************************************

#include <time.h>
#include "menu.h"
#include "../savestate/savestate.h"

extern char RomName[255];

//******************************************************
// Struttura contenente il Menu
//
// String : Stringa descrittiva dell'operazione
// func   : Funzione da richiamare
//******************************************************

#define MENU_ITEMS 7

struct
{

 char String[20];
 void (*func)();

} MenuItems[MENU_ITEMS]=
{
 "LOAD ROM",NULL,
 "LOAD TAPE",NULL,
 "-----------",NULL,
 "SAVE STATE",SaveState,
 "LOAD STATE",LoadState,
 "-----------",NULL,
 "SNAPSHOT",Snapshot
};


//******************************************************
// Inizializzazione del Menu
//******************************************************

void InitMenu( void )
{

   MenuRect.w=MENU_WIDTH;
   MenuRect.h=MENU_HEIGHT;
   MenuRect.x=(VIDEO_WIDTH-MENU_WIDTH)/2;
   MenuRect.y=(VIDEO_HEIGHT-MENU_HEIGHT)/2;

   Menu=SDL_CreateRGBSurface(SDL_SRCALPHA, MENU_WIDTH, MENU_HEIGHT, 8, RMASK,GMASK,BMASK,AMASK);
   SDL_SetPalette(Menu,SDL_LOGPAL,SDL_CvPal,1,16);
   font = initFont(1,1,1,20);


}

//******************************************************
// Ritraccia del Menu
//******************************************************

void DrawMenu( int Selected )
{

 // Cancella lo schermo ricopiando l'ultima immagine dell'emulatore

 SDL_UpperBlit(CvScreen,NULL,Screen,&CvRect);

 // Disegna sul menu un rettangolo
 color = SDL_MapRGB (Menu->format, 0x00, 0x3f, 0x7f);
 SDL_FillRect (Menu, NULL, color);

 // Scrive l'intestazione
 drawString(Menu,font,25,10,"CVEMU 0.5 ALPHA");

 // Coordinate e dimensione del rettangolo che seleziona la scelta
 rect2.w=MENU_WIDTH-10; rect2.h=10; rect2.x=5; rect2.y=34+Selected*10;
 color = SDL_MapRGB (Menu->format, 0x7f, 0x7f, 0x3f);
 SDL_FillRect (Menu, &rect2, color);

 // Scrivo gli elementi del menu
 for (int i=0; i<MENU_ITEMS; i++)
  drawString(Menu,font,(int) (0.5*(MENU_WIDTH-8*strlen( MenuItems[i].String ) ) ),30+i*10,MenuItems[i].String);

 // Setto la trasparenza del menu...
 SDL_SetAlpha(Menu, SDL_SRCALPHA, 220);
 // ...lo copio sullo schermo...
 SDL_UpperBlit(Menu,NULL,Screen,&MenuRect);

 // ... e ripristino la trasparenza...
 SDL_SetAlpha(Menu, SDL_SRCALPHA, 255);

 // ... e lo visualizzo.
 SDL_Flip(Screen);

}

//******************************************************
// Mostra il menu e gestisce i tasti
//******************************************************

void ShowMenu( void )
{

 int KeySymbol , Selected=0 , OldSel;



if (sMenu)
{

 // Metto in pausa l'emulazione
 Paused=true;

 // Inizializzo il menu
 InitMenu();

 // Rimuovo il timer video
 SDL_RemoveTimer(VideoTimer);

 // Setto i colori dell'ultima immagine dell'emulazione in scala di grigi
 GrayVideo();

 // Disegno il menu.
 DrawMenu( Selected );


 // Verifica dei tasti...
 while ( sMenu )
 {

 // Ritraccio il menu solo se la selezione cambia
 OldSel=Selected;

 // Pool degli eventi SDL
 if (SDL_PollEvent(&event))
 {
  KeySymbol=event.key.keysym.sym;

  switch (event.type)
  {
   case SDL_QUIT:
    done = true; sMenu = false; break;

   case SDL_KEYDOWN:
    switch (KeySymbol)
	{
	 // Uscita dal menu
	 case SDLK_TAB: case SDLK_ESCAPE:
	  sMenu = false; break;

	 // Scelta dell'elemento del menu
	 case SDLK_DOWN:
      Selected++; if (Selected>=MENU_ITEMS) Selected=0; break;
	 case SDLK_UP:
      Selected--; if (Selected<0) Selected=MENU_ITEMS-1; break;

	 // Selezione
	 case SDLK_RETURN:
	  if (MenuItems[Selected].func!=NULL)
	   MenuItems[Selected].func();
	   sMenu=false;
	  break;

	 default: break;
    }
  }
 }

 // Ritraccio il menu solo se la selezione cambia
 if (OldSel!=Selected)
  DrawMenu( Selected );

}

}

// Se devo invece disattivare il menu...
if (!sMenu)
{
 // Disattivo la pausa...
 Paused=false;
 // Riattivo il timer video
 VideoTimer = SDL_AddTimer(TIMER_SPEED, &RefreshVideo, (void *) Vdp->XBuf);
}




}

//******************************************************
// Cambia la palette dello schermo in toni di grigio
//******************************************************

void GrayVideo( void )
{
 SDL_SetPalette(CvScreen,SDL_LOGPAL,SDL_CvPalBw,1,16);
 SDL_UpperBlit(CvScreen,NULL,Screen,&CvRect);
 SDL_Flip(Screen);
}

//******************************************************
// Mette in pausa l'emulazione
//******************************************************

void PauseCv( void )
{
 // Se sono in pausa...
 if (Paused)
 {
  // Disativa il timer video
  SDL_RemoveTimer(VideoTimer);

  // Se il menu �attivo lo disattivo
  if (sMenu) { sMenu=false; ShowMenu(); }
  // Setto lo schermo in scala di grigio
  GrayVideo();
  // Inizializzo font e colori
  font = initFont(0,0,1,20);
  rect2.w=50;  rect2.h=16;  rect2.x=VIDEO_WIDTH/2-25; rect2.y=VIDEO_HEIGHT/2;
  color = SDL_MapRGB (Screen->format, 0x90, 0x9f, 0xdf);

  // Setto la trasparenza dello schermo
  SDL_SetAlpha(Screen, SDL_SRCALPHA, 210 );
  // Traccio il rettangolo...
  SDL_FillRect (Screen, &rect2, color);
  // ... e la stringa.
  drawString(Screen,font,VIDEO_WIDTH/2-20,VIDEO_HEIGHT/2,"PAUSE");

  // Ripristino la trasparenza dello schermo
  SDL_SetAlpha(Screen, SDL_SRCALPHA, 255);

  // Visualizzo lo schermo.
  SDL_Flip(Screen);
 }
  // Se non e' in pausa riattivo il timer dello schermo
  else
   VideoTimer = SDL_AddTimer(TIMER_SPEED, &RefreshVideo, (void *) Vdp->XBuf);

}

//******************************************************
// Salva una foto dell'emulatore
//******************************************************


void Snapshot( void )
{
 char name[255];
 
 sprintf(name,"snapshots/shot_%d.bmp",time (NULL));
 

 SDL_SetPalette(CvScreen,SDL_LOGPAL,SDL_CvPal,1,16);
 
 SDL_SaveBMP(CvScreen, name);
 SDL_SetPalette(CvScreen,SDL_LOGPAL,SDL_CvPalBw,1,16);


}



