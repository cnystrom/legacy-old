/*
 * sdl_keyb.h
 *
 */

#ifndef NIO_SDL_KEYB
#define NIO_SDL_KEYB

#include "SDL.h"
#include "nio_sdl.h"

void PrintKeyInfo( SDL_KeyboardEvent *key );

int  get_char(void);

#endif /* NIO_SDL_KEYB */

