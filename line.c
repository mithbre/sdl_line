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


void swap(int *i, int *j) {
        int t = *i;
        *i = *j;
        *j = t;
}


void draw_line(SDL_Surface *surface, point_t cord1, point_t cord2, Uint32 color)
{
        // bresenham line
        int x1 = cord1.x, y1 = cord1.y,
            x2 = cord2.x, y2 = cord2.y,
            steep = fabs(y2 - y1) > fabs(x2 - x1),
            inc = -1;

        if (steep) {
                swap(&x1, &y1);
                swap(&x2, &y2);
        }

        if (y1 < y2) {
                inc = 1;
        }

        int dx = fabs(x2 - x1),
            dy = fabs(y2 - y1),
            y = y1, x = x1,
            e = 0;

        for (x; x < x2; x++) {
                if (steep) {
                        draw_pixel(surface, y, x, color);
                } else {
                        draw_pixel(surface, x, y, color);
                }

                if ((e + dy) << 1 < dx){
                        e = e + dy;
                } else {
                        y += inc;
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
        point_t corner0 = {0,0};
        point_t corner1 = {320, 0};
        point_t corner2 = {320, 320};
        point_t corner3 = {0, 320};

        // top left to bottom right
        point_t octet1 = {80, 320};
        point_t octet2 = {320, 80};

        // top right to bottom left
        point_t octet3 = {160, 320};
        point_t octet4 = {80, 80};


        while (!quit) {
                SDL_PumpEvents();
                keystate = SDL_GetKeyState(NULL);
                if(keystate[SDLK_ESCAPE]) {
                        break;
                }

                SDL_FillRect(screen, NULL, white);

                SDL_LockSurface(screen);
                // top left to bottom right
                draw_line(screen, corner0, octet1, black);
                draw_line(screen, corner0, octet2, black);
                draw_line(screen, corner0, corner2, black);

                // top right to bottom left
                draw_line(screen, corner1, octet3, black);
                draw_line(screen, corner1, octet4, black);
                draw_line(screen, corner1, corner3, black);
                SDL_UnlockSurface(screen);
                SDL_UpdateRect(screen, 0, 0, 0, 0);
                SDL_Delay(10);
        }
        SDL_Quit();
        return 0;
}
