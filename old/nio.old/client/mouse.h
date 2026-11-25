
#ifndef _NIO_SDL_MOUSE
#define _NIO_SDL_MOUSE

#include <stdio.h>
#include "SDL.h"
#include "nio_lib.h"

void set_mouse_x(int x);
void set_mouse_y(int y);

void MouseButtonHandler(Uint8 type, Uint8 button);

int mouse_button_get(int i);
nio_point mouse_xy_get(void);

#endif /* _NIO_SDL_MOUSE */
 
