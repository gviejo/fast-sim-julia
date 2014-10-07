#include <stdio.h>
#include "SDL2/SDL.h"
#include "yourlib.h"

void init() {
	SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1");	
};
void print_SDL_version(char* preamble, SDL_version* v) {
   printf("%s %u.%u.%u\n", preamble, v->major, v->minor, v->patch);
}
void version(void) {
    SDL_version ver;
    SDL_VERSION(&ver);
    print_SDL_version("SDL compile-time version", &ver);
}
union SDL_Event* get_events(void) {
	SDL_Event* event;
	return event;
}
void quit(struct SDL_Window* window) {
    SDL_DestroyWindow( window );
	SDL_Quit();
};
SDL_Window* getwindow(void) {
    SDL_Window* window ;    
    return window;
}
SDL_Renderer* getrenderer(struct SDL_Window* window, int width, int height) {
    window = SDL_CreateWindow( "fast-sim-julia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer* rend;
    rend = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);    
    SDL_SetRenderDrawColor( rend, 0xFF, 0xFF, 0xFF, 0xFF );
    return rend;
};
struct SDL_Surface* getsurface(char* image_path) {
	// SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Surface* background;
    background = SDL_LoadBMP(image_path);
    // SDL_Surface* loaded_surface = SDL_LoadBMP(image_path);
    // background = SDL_ConvertSurface(loaded_surface, screen->format, 0);
    // SDL_FreeSurface(screen);
    // SDL_FreeSurface(loaded_surface);
    return background;
}
struct SDL_Texture* gettexture(SDL_Renderer* renderer, char* image_path) {
    SDL_Texture* tex;
    SDL_Surface* background;    
    background = SDL_LoadBMP(image_path);
    tex = SDL_CreateTextureFromSurface( renderer, background);
    SDL_FreeSurface(background);
    return tex;
};
void renderagent(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, double angle) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopyEx(renderer, texture, NULL, &dst, angle, NULL, SDL_FLIP_HORIZONTAL);
}
void render(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y){    
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}
void update(struct SDL_Renderer* renderer) {    
    SDL_RenderPresent( renderer );
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
int sdl_events(union SDL_Event* event) {     
    while ( SDL_PollEvent( event ) != 0 )
    {        
        if (event->type == SDL_WINDOWEVENT) {
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {                
                return 0;
            }                
        }
    }
    return 1;
};
int checkcollision(SDL_Texture* agent, SDL_Surface* surface, int x, int y) {
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    SDL_LockSurface(surface);
	Uint8 r, g, b;
	SDL_GetRGB(*((Uint32*)(surface->pixels) + x + y * surface->w), surface->format, &r, &g, &b);	
    SDL_UnlockSurface(surface);
    if (r+b+g != 0)
    	return 0;
    // for (i = 0; i < surface->w*surface->h; i++)
    // {    
    // 	SDL_GetRGB(pixels[i], surface->format, &r, &g, &b);	
    // 	printf("%u,%u,%u\n",r,g,b);
    // }

    return 1;
}