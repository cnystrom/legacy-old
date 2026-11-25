/*
    sdl_screen.h
*/

#ifndef NIO_SDL_SCREEN
#define NIO_SDL_SCREEN

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_prim.h"
#include "sdl_colors.h"
#include "sdl_text.h"

#define NUL					0

#define NUM_COLORS	256

//#define V_VMODE			482
#define V_VMODE			466
#define H_VMODE			812

SDL_Color * get_sdl_forecol(void);
SDL_Color * get_sdl_backcol(void);

void set_fg_color(int red, int green, int blue);
void set_bg_color(int red, int green, int blue);
void inverse_colors(void);

int init_screen(int sw, int sh, int options);
int set_palette(void);
int clear_screen(void);
void reset_screen(void);
int clear_rectangle(int x, int y, int w, int h);
int draw_rectangle(int x, int y, int w, int h);
int display_text_on_screen(int x, int y);
void draw_text(char *s, int x, int y);
void draw_char(int c, int x, int y);
void draw_point(int x, int y);
void draw_line(int x1, int y1, int x2, int y2);
void draw_arc(int x, int y, int r);
Uint32 getpixel(int x, int y);
void putpixel(int x, int y, Uint32 pixel);
int draw_image(char *file_name, int x, int y);

#endif /* NIO_SCREEN */

