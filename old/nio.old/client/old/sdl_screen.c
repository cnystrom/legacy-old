/*
    sdl_screen.c
*/

#include "sdl_screen.h"

SDL_Surface *screen;

static SDL_Color sdl_forecol;
static SDL_Color sdl_backcol;
static SDL_Color sdl_tempcol;

static Uint32 forecol;
static Uint32 backcol;
static Uint32 tempcol;

/*
int
set_forecol(SDL_Color *c)
{
  forecol = c;

  return 0;
}

int
set_backcol(SDL_Color *c)
{
  backcol = c;

  return 0;
}
*/

void lockScreen(void)
{
  if ( SDL_MUSTLOCK(screen) ) {
    if ( SDL_LockSurface(screen) < 0 ) {
      fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
      return;
    }
  }
}

void unlockScreen(void)
{
  if ( SDL_MUSTLOCK(screen) ) {
    SDL_UnlockSurface(screen);
  }
}

SDL_Color *
get_sdl_forecol(void)
{
  return(&sdl_forecol);
}

SDL_Color *
get_sdl_backcol(void)
{
  return(&sdl_backcol);
}

void
set_fg_color(int red, int green, int blue)
{
  forecol = SDL_MapRGB(screen->format, red, green, blue);

  sdl_forecol.r = red;
  sdl_forecol.g = green;
  sdl_forecol.b = blue;
}

void
set_bg_color(int red, int green, int blue)
{
  backcol = SDL_MapRGB(screen->format, red, green, blue);

#ifdef DEBUG
//  printf("Setting bg color to %d, %d, %d\n", red, green, blue);
#endif

  sdl_backcol.r = red;
  sdl_backcol.g = green;
  sdl_backcol.b = blue;
}

void
inverse_colors(void)
{
  tempcol = forecol;
  forecol = backcol;
  backcol = tempcol;

  sdl_tempcol = sdl_forecol;
  sdl_forecol = sdl_backcol;
  sdl_backcol = sdl_tempcol;
}

int
init_screen(int sw, int sh, int options)
{
  screen = SDL_SetVideoMode(sw, sh, 0, options);

  if ( screen == NULL )
  {
    fprintf(stderr, "Can not set video mode: %s\n", SDL_GetError());
    return(-1);
  }

  set_bg_color(0, 0, 0);
  set_fg_color(255, 255, 255);

  set_palette();

  clear_screen();

  return(0);
}

void
reset_screen(void)
{
  set_bg_color(0, 0, 0);
  set_fg_color(255, 255, 255);

//  printf("Resetting screen...\n");

  clear_screen();
}

int
get_screen_width(void)
{
  if (screen == NULL)
  {
    printf("Error get_screen_width(): screen not set.\n");
    exit(-1);
  }

  return(screen->w);
}

int
get_screen_height(void)
{
  if (screen == NULL)
  {
    printf("Error get_screen_height(): screen not set.\n");
    exit(-1);
  }

  return(screen->h);
}

int
set_palette(void)
{
  int i, rdiff, gdiff, bdiff;
  SDL_Color colors[NUM_COLORS];

//  printf("Setting palette...\n");

  rdiff = sdl_backcol.r - sdl_forecol.r;
  gdiff = sdl_backcol.g - sdl_forecol.g;
  bdiff = sdl_backcol.b - sdl_forecol.b;

  for ( i = 0; i < NUM_COLORS; ++i )
  {
    colors[i].r = sdl_forecol.r + (i * rdiff) / 4;
    colors[i].g = sdl_forecol.g + (i * gdiff) / 4;
    colors[i].b = sdl_forecol.b + (i * bdiff) / 4;
  }

  SDL_SetColors(screen, colors, 0, NUM_COLORS);

  return(0);
}

int
clear_screen(void)
{
  SDL_FillRect(screen, NULL, backcol);

  SDL_UpdateRect(screen, 0, 0, 0, 0);

//  printf("clearing screen...\n");

  return(0);
}

int
clear_rectangle(int x, int y, int w, int h)
{
  SDL_Rect dstrect;

//  printf("Clearing rectangle at %d, %d\n", x, y);

  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = w;
  dstrect.h = h;

  SDL_FillRect(screen, &dstrect, backcol);

  SDL_UpdateRects(screen, 1, &dstrect);

  return(0);
}

int
draw_rectangle(int x, int y, int w, int h)
{
  SDL_Rect dstrect;

  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = w;
  dstrect.h = h;

  SDL_FillRect(screen, &dstrect, forecol);

//  SDL_drawLine_TG(screen, x1, y1, x2, y2, forecol, 0, 0);

  SDL_UpdateRects(screen, 1, &dstrect);

  return(0);
}

void
draw_line(int x1, int y1, int x2, int y2)
{
/*  SDL_Rect dstrect;

  dstrect.x = x1;
  dstrect.y = y1;
  dstrect.w = x2 - x1;
  dstrect.h = y2 - y1;
*/
  lockScreen();

//	printf("Drawing line from %d, %d to %d, %d\n", x1, y1, x2, y2);

  SDL_drawLine_TG(screen, x1, y1, x2, y2, forecol, 0, 0);

  unlockScreen();

  SDL_UpdateRects(screen, 1, &screen->clip_rect);
}

void
draw_arc(int x, int y, int r)
{
  lockScreen();
  SDL_drawCircle_TG(screen, x, y, r, forecol, 0, 0);
  unlockScreen();

  SDL_UpdateRects(screen, 1, &screen->clip_rect);
}

int
draw_image(char *file_name, int x, int y)
{
  SDL_Surface *image;
  SDL_Rect dstrect;

  image = IMG_Load(file_name);
  if (image == NULL) {
    fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
    return(-1);
  }

  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = image->w;
  dstrect.h = image->h;

  if (image->format->palette && screen->format->palette) {
    SDL_SetColors(screen, image->format->palette->colors, 0,
    image->format->palette->ncolors);
  }

  if (SDL_BlitSurface(image, NULL, screen, &dstrect) == 0) {
    SDL_UpdateRects(screen, 1, &dstrect);
    SDL_FreeSurface(image);
    return(0);
  }
  else
  {
    fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
    SDL_FreeSurface(image);
    return(-1);
  }
}

int
display_text_on_screen(int x, int y)
{
  SDL_Rect dstrect;
  SDL_Surface *text;

  text = get_text();

  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = text->w;
  dstrect.h = text->h;

  if ( SDL_BlitSurface(text, NULL, screen, &dstrect) == 0 )
  {
    SDL_UpdateRects(screen, 1, &dstrect);
  }
  else
  {
    fprintf(stderr, "Couldn't blit text to display: %s\n", SDL_GetError());
  }

  what_is_this_for();

  return(0);
}

void
draw_text(char *s, int x, int y)
{
  set_text(s, RENDER_LATIN1, 1);
  display_text_on_screen(x, y);
}

void
draw_char(int c, int x, int y)
{
  string s;

//  printf("Drawing char at %d, %d\n", x, y);

  s[0] = c;
  s[1] = NUL;

  draw_text(s, x, y);
}

void
draw_point(int x, int y)
{
  if ( SDL_MUSTLOCK(screen) ) {
    if ( SDL_LockSurface(screen) < 0 ) {
       fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
       return;
     }
   }

   putpixel(x, y, forecol);

   if ( SDL_MUSTLOCK(screen) ) {
     SDL_UnlockSurface(screen);
   }

   SDL_UpdateRect(screen, x, y, 1, 1);
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32
getpixel(int x, int y)
{
  int bpp = screen->format->BytesPerPixel;

  /* Here p is the address to the pixel we want to retrieve */

  Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;

  switch(bpp) {
    case 1:
      return *p;

    case 2:
      return *(Uint16 *)p;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
      return *(Uint32 *)p;

    default:
      return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 *  * Set the pixel at (x, y) to the given value
 *   * NOTE: The surface must be locked before calling this!
 *    */
void
putpixel(int x, int y, Uint32 pixel)
{
  int bpp = screen->format->BytesPerPixel;

  /* Here p is the address to the pixel we want to set */

  Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;

  switch(bpp) {
    case 1:
      *p = pixel;
      break;

    case 2:
      *(Uint16 *)p = pixel;
      break;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
      
    case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

