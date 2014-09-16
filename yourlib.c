#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "yourlib.h"

int init(Uint32 flags)
{
	int res = SDL_Init(flags);
	return res;
};
void quit(Uint32 flags) {
	SDL_QuitSubSystem(flags);
	SDL_Quit();	
};
struct SDL_Surface* setvideomode(int w, int h, int bpp, Uint32 flags) {
    SDL_Surface *tmp = SDL_SetVideoMode(w, h, bpp, flags);    
	return tmp;
};
struct SDL_Surface* creatergbsurface(int w, int h) {
	SDL_Surface *surface;
	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif
	surface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	return surface;
};
void setpixel(struct SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b) {		
	*((Uint32*)(surface->pixels) + x + y * surface->w) = SDL_MapRGB(surface->format, r, g, b);;		
};
void setfullcolor(struct SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b) {
    Uint32 *pixels = (Uint32 *) surface->pixels;
	SDL_LockSurface(surface);    
    int i;
    for (i = 0; i < surface->w*surface->h; i++)
    {
    	pixels[i] = SDL_MapRGB(surface->format, r, g, b);    
    }
    SDL_UnlockSurface(surface);
};
void update(struct SDL_Surface* src, struct SDL_Surface* dest, int w, int h) {
	SDL_BlitSurface(src, NULL, dest, NULL);	
	SDL_UpdateRect(dest, 0, 0, w, h);
};
void background(struct SDL_Surface* surface, char* image_path) {	
   SDL_Surface *image = IMG_Load (image_path);
   if ( !image )
   {
      printf ( "IMG_Load: %s\n", IMG_GetError () );  
   }   
   SDL_BlitSurface(image, NULL, surface, 0);
   SDL_UpdateRect(surface, 0, 0, surface->w, surface->h);
   SDL_FreeSurface(image);   
};
void sdl_events() {	
	printf("Hello");
	SDL_Event event;
    // if( SDL_PollEvent( &event ) ) 
    // {
    // 	if( event.type == SDL_QUIT )
    // 		return 0;
    // 	else
    // 		return 1;
    // }	
	// return 1;
};
