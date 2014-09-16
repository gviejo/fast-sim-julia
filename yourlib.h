/**
gcc -fPIC yourlib.c -shared -o libtest.so `sdl-config --cflags --libs`
*/

extern int init(Uint32 flags);
extern struct SDL_Surface* setvideomode(int w, 
										int h, 
										int bpp, 
										Uint32 flags);
extern struct SDL_Surface* creatergbsurface(int w, int h);
extern void putpixel(struct SDL_Surface* map, 
									int x, 
									int y, 
									Uint8 r, Uint8 g, Uint8 b);
extern void update(struct SDL_Surface* src, struct SDL_Surface* dest, int w, int h);