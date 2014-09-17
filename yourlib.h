/**
gcc -fPIC yourlib.c -shared -o libtest.so `sdl2-config --cflags --libs`
*/

extern int init(Uint32 flags);
extern void print_SDL_version(char* preamble, SDL_version* v);
extern void version(void);
extern struct SDL_Window* getwindow(int w, int h);
extern struct SDL_Surface* getsurface(struct SDL_Window* window);
// extern struct SDL_Surface* setvideomode(int w, 
// 										int h, 
// 										int bpp, 
// 										Uint32 flags);
extern struct SDL_Surface* creatergbsurface(int w, int h);
extern void setpixel(struct SDL_Surface* surface, 
									int x, 
									int y, 
									Uint8 r, Uint8 g, Uint8 b);
extern void setfullcolor(struct SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b);
extern void update(struct SDL_Surface* src, struct SDL_Surface* dest, struct SDL_Window* window);
extern struct SDL_Surface* getbackground(struct SDL_Surface* screen, char *image_path);
extern int sdl_events(union SDL_Event* event, struct SDL_Window* window);
extern union SDL_Event* get_events(void);
extern void circle(struct SDL_Surface* surface, struct SDL_Surface* map, int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b);
extern struct SDL_Texture* gettexture(struct SDL_Renderer* renderer, struct SDL_Surface* screen, char* image_path);
extern struct SDL_Renderer* getrenderer(struct SDL_Window* window);
extern void render(struct SDL_Renderer* renderer, struct SDL_Texture* texture);