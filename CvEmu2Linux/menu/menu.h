
#ifndef __menu__
#define __menu__

#include <SDL/SDL.h>
#include <string.h>
#include "../include/defs.h"
#include "../video/tms9918.h"


#define MENU_WIDTH 150
#define MENU_HEIGHT 140


extern SDL_Surface *Menu;
extern SDL_Rect MenuRect,CvRect,rect2;
extern SDL_TimerID VideoTimer;
extern SDL_Surface *Screen;
extern SDL_Surface *CvScreen;
extern tms9918 *Vdp;
extern bool sMenu,Paused,done;
extern Uint32 RefreshVideo(Uint32 interval,void *Buffer);
extern struct SDLFont *font;
extern SDL_Color SDL_CvPal[16],SDL_CvPalBw[16];
extern Uint32 color;
extern SDLFont *initFont(float r, float g, float b, float a);
extern void drawString(SDL_Surface *screen, SDLFont *font, int x, int y, char *str,...);
extern SDL_Event event;


void ShowMenu( void );
void PauseCv( void );
void GrayVideo( void );
void DrawMenu( int  );
void InitMenu( void );
void Snapshot( void );



#endif


