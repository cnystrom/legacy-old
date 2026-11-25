
#include "nio_sdl.h"

void
breakhandler(int a)
{
  SDL_Quit();
  exit(1);
}

void
sdl_init(void)
{
  if ((SDL_Init(SDL_INIT_EVERYTHING) == -1)) {
      fprintf(stderr, "sdl_init(): Could not initialize SDL: %s.\n",
        SDL_GetError());
      exit(-1);
  }

  atexit(SDL_Quit);

  signal(SIGTERM, breakhandler);
  signal(SIGINT, breakhandler);

  SDL_EnableUNICODE(TRUE);

  init_screen(640, 32, SDL_ANYFORMAT);
}

void
sdl_handle_event(void)
{
  int quit = 0;
  SDL_Event event;

  if (SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_MOUSEMOTION:
        set_mouse_x(event.motion.x);
        set_mouse_y(event.motion.y);
        break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        MouseButtonHandler(event.type, event.button.button);
        break;

      /* Keyboard event */
      /* Pass the event data onto PrintKeyInfo() */
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        PrintKeyInfo( &event.key );
        break;

      /* SDL_QUIT event (window close) */
      case SDL_QUIT:
//        quit = 1;
        breakhandler(quit);
        break;

      default:
        break;
    }
  }
}

void
delay(int ticks)
{
//  printf("Waiting %d...\n", ticks);
//  fflush(stdout);

  SDL_Delay(ticks);
}


