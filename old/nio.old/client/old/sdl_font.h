/*
    sdl_font.h
*/

#ifndef NIO_SDL_FONT
#define NIO_SDL_FONT

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "misc_io.h"
#include "nio_font.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

#define DEFAULT_PTSIZE	18

#define NUM_FONT_FILES	12

char * get_font_path(int font_num);
char * get_font_file_name(int font_num);
int set_font(int font_num, int ptsize, int renderstyle);
TTF_Font *get_font(void);
int close_font(void);

#endif /* NIO_SDL_FONT */


