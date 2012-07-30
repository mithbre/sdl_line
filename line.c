#include "SDL/SDL.h"
#include <math.h>
SDL_Surface *screen = NULL;

typedef struct point{
        int x, y;
} point_t;


void sdl_init()
{
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_WM_SetCaption("Custom Line Drawing", "Custom Line Drawing");
        screen = SDL_SetVideoMode(320, 320, 32, SDL_SWSURFACE);
}


void draw_pixel(SDL_Surface *surface, int x, int y, Uint32 color) {
        // 32bpp pixel address
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
        // assign color
        *(Uint32 *)p = color;
}


void draw_line(SDL_Surface *surface, point_t cord1, point_t cord2, Uint32 color)
{
        // bresenham line
        int x1 = cord1.x, y1 = cord1.y,
            x2 = cord2.x, y2 = cord2.y;

        int dx = fabs(x2 - x1),
            dy = fabs(y2 - y1),
            y = y1, x = x1,
            e = 0;

        for (x; x < x2; x++) {
                draw_pixel(surface, x, y, color);
                if ((e + dy) << 1 < dx){
                        e = e + dy;
                } else {
                        y++;
                        e = e + dy - dx;
                }
        }
}


int main(int argc, char *args[])
{
        sdl_init();
        int quit = 0;
        Uint8 *keystate;
        Uint32 black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
        Uint32 white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
        point_t cord1 = {0,0};
        point_t cord2 = {320, -1};
        //point_t cord2 = {-1, 320};

        while (!quit) {
                SDL_PumpEvents();
                keystate = SDL_GetKeyState(NULL);
                if(keystate[SDLK_ESCAPE]) {
                        break;
                }

                SDL_FillRect(screen, NULL, white);

                cord2.y++;
                SDL_LockSurface(screen);
                //draw_line(screen, cord1.x, cord2.x, cord1.y, cord2.y, black);
                draw_line(screen, cord1, cord2, black);
                SDL_UnlockSurface(screen);
                SDL_UpdateRect(screen, 0, 0, 0, 0);
                SDL_Delay(10);
        }
        SDL_Quit();
        return 0;
}
