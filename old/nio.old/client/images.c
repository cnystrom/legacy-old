/*
    images.c
*/

#include "images.h"

int next_free_image_num(void);

static SDL_Surface *image[MAX_IMAGES];
static bool i_flag[MAX_IMAGES] = {FALSE};

SDL_Surface *
get_image(int i_num)
{
  if (i_num < 0 && i_num >= MAX_IMAGES) {
    fprintf(stderr, "get_image(): bad image number: %d.\n", i_num);
    return(NULL);
  }

  if (NULL == image[i_num]) {
    fprintf(stderr, "get_image(): image %d not loaded.\n", i_num);
  }

  return(image[i_num]);
}

int
next_free_image_num(void)
{
  int i_num;

  for (i_num = 0; i_num < MAX_IMAGES; i_num++) {
    if (FALSE == i_flag[i_num]) {
      i_flag[i_num] = TRUE;
      return(i_num);
    }
  }

  fprintf(stderr, "next_free_image_num(): No more images available.\n");
  return(-1);
}

void
free_image(int i_num)
{
  if (i_num < 0 || i_num >= MAX_IMAGES) {
    fprintf(stderr, "free_image(): bad image number: %d.\n", i_num);
    return;
  }

  SDL_FreeSurface(image[i_num]);
  i_flag[i_num] = FALSE;
}

int
load_image(char *file_name)
{
  int i_num;
//  Uint32 black;
  SDL_Surface *s;

//  printf("load_image(): filename = %s\n", file_name);

  i_num = next_free_image_num();

  s = IMG_Load(file_name);

  if (NULL == s) {
    fprintf(stderr, "load_image(): Unable to load image file.\n");
  }

  image[i_num] = SDL_DisplayFormat(s);

  if (NULL == image[i_num]) {
    fprintf(stderr, "load_image(): Unable to convert image file.\n");
  }

/*
  black = get_color(BLACK);

  SDL_SetColorKey(s1,
                  (SDL_SRCCOLORKEY | 
                   SDL_RLEACCEL), 
                  black);
*/

  SDL_FreeSurface(s);

  return(i_num);
}

