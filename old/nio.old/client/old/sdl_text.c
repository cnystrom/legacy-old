/*
    sdl_text.c
*/

#include "sdl_text.h"

SDL_Surface *text;

int
set_text(char *message, int rendertype, int rendersolid)
{
  SDL_Color *forecol;
  SDL_Color *backcol;
  TTF_Font *font;

  font = get_font();

  forecol = get_sdl_forecol();

  backcol = get_sdl_backcol();

  switch (rendertype)
  {
    case RENDER_LATIN1:
      if ( rendersolid )
      {
        text = TTF_RenderText_Solid(font, message, *forecol);
      }
      else
      {
        text = TTF_RenderText_Shaded(font, message, *forecol, *backcol);
      }
      break;

    case RENDER_UTF8:
      if ( rendersolid )
      {
        text = TTF_RenderUTF8_Solid(font, message, *forecol);
      }
      else
      {
        text = TTF_RenderUTF8_Shaded(font, message, *forecol, *backcol);
      }
      break;

    case RENDER_UNICODE:
      {
        Uint16 unicode_text[BUFSIZ];
        int index;

        for ( index = 0; (message[0] || message[1]); ++index )
        {
          unicode_text[index]  = ((Uint8 *)message)[0];
          unicode_text[index] <<= 8;
          unicode_text[index] |= ((Uint8 *)message)[1];
          message += 2;
        }

        if ( rendersolid )
        {
          text = TTF_RenderUNICODE_Solid(font, unicode_text, *forecol);
        }
        else
        {
          text = TTF_RenderUNICODE_Shaded(font, unicode_text, *forecol,
            *backcol);
        }
      }
      break;

    default:
      text = NULL;
      break;
  }

  if ( text == NULL )
  {
    fprintf(stderr, "fonttest: Couldn't render text: %s\n", SDL_GetError());

    close_font();

    exit(-2);
  }

  return(0);
}

SDL_Surface *
get_text(void)
{
  if (text == NULL)
  {
    printf("Error get_text(): text is not set.\n");
    exit (-1);
  }

  return(text);
}

int
get_text_width(void)
{
  if (text == NULL)
  {
    printf("Error get_text_width(): text is not set.\n");
    return(0);
  }

  return(text->w);
}

int
get_text_height(void)
{
  if (text == NULL)
  {
    printf("Error get_text_height(): text is not set.\n");
    return(0);
  }

  return(text->h);
}

/* ? */

int
what_is_this_for(void)
{
  SDL_Surface *temp;

  /* Set the text colorkey and convert to display format */

  if ( SDL_SetColorKey(text, SDL_SRCCOLORKEY|SDL_RLEACCEL, 0) < 0 )
  {
    fprintf(stderr, "Warning: Couldn't set text colorkey: %s\n",
       SDL_GetError());
  }

  temp = SDL_DisplayFormat(text);

  if ( temp != NULL ) {
    SDL_FreeSurface(text);
    text = temp;
  }

  return(0);
}

int
close_text(void)
{
  SDL_FreeSurface(text);
  return(0);
}


