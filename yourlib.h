/**
gcc -fPIC yourlib.c -shared -o libtest.so `sdl2-config --cflags --libs`
*/

extern void init(void);
extern void print_SDL_version(char* preamble, SDL_version* v);
extern void version(void);
extern void quit(struct SDL_Window* window);
extern SDL_Window* getwindow();
extern struct SDL_Surface* getsurface(struct SDL_Window* window);
extern void setpixel(struct SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b);
extern void update(struct SDL_Renderer* renderer);
extern int sdl_events(union SDL_Event* event);
extern union SDL_Event* get_events(void);
extern struct SDL_Texture* gettexture(SDL_Renderer* renderer, char* image_path);
extern SDL_Renderer* getrenderer(struct SDL_Window* window, int width, int height);
extern void render(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
extern void renderagent(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, double angle);