/**
gcc -fPIC yourlib.c -shared -o libtest.so `sdl-config --cflags --libs` -lSDL_image
*/

extern int init(Uint32 flags);
extern struct SDL_Surface* setvideomode(int w, 
										int h, 
										int bpp, 
										Uint32 flags);
extern struct SDL_Surface* creatergbsurface(int w, int h);
extern void setpixel(struct SDL_Surface* surface, 
									int x, 
									int y, 
									Uint8 r, Uint8 g, Uint8 b);
extern void setfullcolor(struct SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b);
extern void update(struct SDL_Surface* src, struct SDL_Surface* dest, int w, int h);
extern void background(struct SDL_Surface *surface, char *image_path);
extern void sdl_events(void);