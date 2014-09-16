#include <stdio.h>
#include "SDL/SDL.h"
#include "yourlib.h"

int init(Uint32 flags)
{
	int res = SDL_Init(flags);
	return res;
};
struct SDL_Surface* setvideomode(int w, int h, int bpp, Uint32 flags) {
    SDL_Surface *tmp = SDL_SetVideoMode(w, h, bpp, flags);    
	return tmp;
};
struct SDL_Surface* creatergbsurface(int w, int h)
{	
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
void putpixel(struct SDL_Surface* map, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{	
	SDL_LockSurface(map);
	Uint32 color = SDL_MapRGB(map->format, r, g, b);
	Uint32 *bufp = *( ( Uint32 * )map->pixels + y * map->w + x );
	*bufp = color;
	SDL_UnlockSurface(map);


};

void update(struct SDL_Surface* src, struct SDL_Surface* dest, int w, int h)
{
	SDL_BlitSurface(src, NULL, dest, NULL);	
	SDL_UpdateRect(dest, 0, 0, w, h);
}
