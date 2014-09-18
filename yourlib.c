#include <stdio.h>
#include "SDL2/SDL.h"
// #include "SDL2/SDL_image.h"
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
    // SDL_Window* window ;
    window = SDL_CreateWindow( "fast-sim-julia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer* rend;
    rend = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);    
    SDL_SetRenderDrawColor( rend, 0xFF, 0xFF, 0xFF, 0xFF );
    return rend;
};
struct SDL_Surface* getsurface(struct SDL_Window* window) {
    SDL_Surface* screen = SDL_GetWindowSurface( window );
    return screen;
}
struct SDL_Texture* gettexture(SDL_Renderer* renderer, char* image_path) {
    SDL_Texture* tex;
    SDL_Surface* background;    
    background = SDL_LoadBMP(image_path);
    tex = SDL_CreateTextureFromSurface( renderer, background);
    SDL_FreeSurface(background);
    return tex;
};
void render(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y){    
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}
// void render(struct SDL_Renderer* renderer, struct SDL_Texture* texture, int x, int y) {
    
//     SDL_Rect DestR;
//     DestR.x = x;
//     DestR.y = y;
//     SDL_RenderCopy( renderer, texture, NULL, &DestR);
//     SDL_RenderPresent( renderer );
// }
void update(struct SDL_Renderer* renderer) {    
    SDL_RenderPresent( renderer );
};
struct SDL_Surface* getbackground(struct SDL_Surface* screen, char* image_path) {  
    SDL_Surface *image = SDL_LoadBMP(image_path);
    SDL_Surface* optimizedSurface = NULL;
    optimizedSurface = SDL_ConvertSurface( image, screen->format, 0);
    SDL_FreeSurface(image);    
    return optimizedSurface;
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


void circle(struct SDL_Surface* surface, struct SDL_Surface* map, int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b) {
	SDL_LockSurface(map);
	double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5; 	
    while (x >= y)
    {
        setpixel(map, (int)(cx + x), (int)(cy + y), r, g, b);
        setpixel(map, (int)(cx + y), (int)(cy + x), r, g, b);
 
        if (x != 0)
        {
            setpixel(map, (int)(cx - x), (int)(cy + y), r, g, b);
            setpixel(map, (int)(cx + y), (int)(cy - x), r, g, b);
        }
 
        if (y != 0)
        {
            setpixel(map, (int)(cx + x), (int)(cy - y), r, g, b);
            setpixel(map, (int)(cx - y), (int)(cy + x), r, g, b);
        }
 
        if (x != 0 && y != 0)
        {
            setpixel(map, (int)(cx - x), (int)(cy - y), r, g, b);
            setpixel(map, (int)(cx - y), (int)(cy - x), r, g, b);
        }
 
        error += y;
        ++y;
        error += y;
 
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    } 	
 	SDL_UnlockSurface(map);
   	SDL_BlitSurface(map, NULL, surface, 0);
   	SDL_UpdateRect(surface, 0, 0, surface->w, surface->h);
   	
}

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