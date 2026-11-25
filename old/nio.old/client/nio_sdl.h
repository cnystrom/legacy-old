
#ifndef NIO_SDL
#define NIO_SDL

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "SDL.h"
#include "screen.h"
#include "fonts.h"
#include "mouse.h"
#include "keyboard.h"
#include "speaker.h"

void sdl_init(void);
void sdl_handle_event(void);
int FilterEvents(const SDL_Event *event);

#endif /* NIO_SDL */
 
