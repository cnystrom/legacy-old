/*
    sdl_colors.h
*/

#ifndef NIO_SDL_COLORS
#define NIO_SDL_COLORS

#include "SDL.h"

int set_forecol(SDL_Color *c);
int set_backcol(SDL_Color *c);
SDL_Color *get_forecol(void);
SDL_Color *get_backcol(void);

#endif /* NIO_SDL_COLORS */

