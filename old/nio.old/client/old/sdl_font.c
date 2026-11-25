/*
    sdl_font.c
*/

#include "sdl_font.h"

TTF_Font *font;

static char font_path[512];

static char *font_file[] = {
  "FreeMonoBoldOblique.ttf",
  "FreeMonoBold.ttf",
  "FreeMonoOblique.ttf",
  "FreeMono.ttf",
  "FreeSansBoldOblique.ttf",
  "FreeSansBold.ttf",
  "FreeSansOblique.ttf",
  "FreeSans.ttf",
  "FreeSerifBoldItalic.ttf",
  "FreeSerifBold.ttf",
  "FreeSerifItalic.ttf",
  "FreeSerif.ttf"
};

char *
get_font_path(int font_num)
{
  strcpy(font_path, get_homedir());
  strcat(font_path, "/.nio/fonts/");
  strcat(font_path, get_font_file_name(font_num));

#ifdef DEBUG
//  printf("font_path = %s\n", font_path);
#endif

  return(font_path);
}

char *
get_font_file_name(int font_num)
{
  if (font_num < 0 || font_num > MAX_FONT_NUM)
  {
    printf("get_font_file_name() error: bad font_num: %d\n", font_num);
    printf("switching to default font.\n");
    font_num = NIO_DEFAULT_FONT;
  }

//  printf("Font file: %s\n", font_file[font_num]);

  return(font_file[font_num]);
}

int
set_font(int font_num, int ptsize, int renderstyle)
{
  char fname[512];

  strcpy(fname, get_font_path(font_num));

  if (font != NULL)
    close_font();

  font = TTF_OpenFont(fname, ptsize);

  if ( font == NULL )
  {
    fprintf(stderr, "Couldn't load %d pt font from %s: %s\n",
      ptsize, fname, SDL_GetError());
    return(-1);
  }

  TTF_SetFontStyle(font, renderstyle);

  return(0);
}

TTF_Font *
get_font(void)
{
  if (font == NULL)
  {
    printf("Error get_font(): no font to get.\n");
    exit(-1);
  }

  return(font);
}

int
close_font(void)
{
  if (font == NULL)
  {
    printf("Error close_font(): no font to close.\n");
    exit(-1);
  }

  TTF_CloseFont(font);
  return(0);
}

