#include <stdio.h>
#include "SDL2/SDL.h"
// #include "SDL2/SDL_image.h"
#include "yourlib.h"

int init(Uint32 flags) {
	int res = SDL_Init(flags);
	return res;
};
void print_SDL_version(char* preamble, SDL_version* v) {
   printf("%s %u.%u.%u\n", preamble, v->major, v->minor, v->patch);
}
void version(void) {
    SDL_version ver;
    SDL_VERSION(&ver);
    print_SDL_version("SDL compile-time version", &ver);
}
union SDL_Event* get_events() {
	SDL_Event* event;
	return event;
}
void quit(Uint32 flags) {
	SDL_QuitSubSystem(flags);
	SDL_Quit();
};
struct SDL_Window* getwindow(int w, int h) {
    SDL_Window* window = NULL;
    window = SDL_CreateWindow( "fast-sim-julia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    return window;
}
struct SDL_Surface* getsurface(struct SDL_Window* window) {
    SDL_Surface* screen = SDL_GetWindowSurface( window );
    return screen;
}
struct SDL_Renderer* getrenderer(struct SDL_Window* window) {
    SDL_Renderer* rend = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( rend, 0xFF, 0xFF, 0xFF, 0xFF );
    return rend;
};
struct SDL_Texture* gettexture(SDL_Renderer* renderer, SDL_Surface* screen, char* image_path) {
    SDL_Texture* tex = NULL;
    SDL_Surface* image = SDL_LoadBMP(image_path);
    // SDL_Surface* loadedSurface = IMG_Load(image_path);
    // SDL_Surface* optimizedSurface = NULL;
    // optimizedSurface = SDL_ConvertSurface( image, screen->format, 0);
    tex = SDL_CreateTextureFromSurface( renderer, image);    
    SDL_FreeSurface(image);
    SDL_FreeSurface(screen);    

    return tex;
};
void render(struct SDL_Renderer* renderer, struct SDL_Texture* texture) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, texture, NULL, NULL );
    SDL_RenderPresent( renderer );
}

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
void update(struct SDL_Surface* src, struct SDL_Surface* dest, struct SDL_Window* window) {
	SDL_BlitSurface(src, NULL, dest, NULL);	    
	SDL_UpdateWindowSurface(window);
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

int sdl_events(union SDL_Event* event, struct SDL_Window* window) {     
    // printf("1\n");
    while ( SDL_PollEvent( event ) != 0 )
    {
        printf("2\n");        
        // if ( event->type == SDL_QUIT ) {
  //           // SDL_DestroyWindow(window);
  //           // window = NULL;
        //  // SDL_Quit();
            // printf("Hello\n");
            // return 0;
        // }
        // else
        //  return 1;
    }
    printf("3\n");
    return 1;
};