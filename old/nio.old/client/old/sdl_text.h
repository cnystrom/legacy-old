/*
    sdl_text.h
*/

#ifndef _NIO_SDL_TEXT_H
#define _NIO_SDL_TEXT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "fonts.h"
#include "colors.h"

enum {
  RENDER_LATIN1,
  RENDER_UTF8,
  RENDER_UNICODE
} rendertype;

int set_text(char *message, int rendertype, int rendersolid);
SDL_Surface *get_text(void);
int get_text_width(void);
int get_text_height(void);
int what_is_this_for(void);
int close_text(void);

#endif /* _NIO_SDL_TEXT_H */

