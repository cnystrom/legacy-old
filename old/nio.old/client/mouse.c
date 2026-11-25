
#include "mouse.h"

static int mouse_x = 0;
static int mouse_y = 0;

static int mouse_left;
static int mouse_middle;
static int mouse_right;

void
set_mouse_x(int x)
{
  mouse_x = x;
}

void
set_mouse_y(int y)
{
  mouse_y = y;
}

void
MouseButtonHandler(Uint8 type, Uint8 button)
{
  switch(button)
  {
    case SDL_BUTTON_LEFT:
      if (type == SDL_MOUSEBUTTONDOWN) {
        mouse_left = NIO_PRESSED;
      } else {
        mouse_left = NIO_RELEASED;
      }
      break;

    case SDL_BUTTON_MIDDLE:
      if (type == SDL_MOUSEBUTTONDOWN) {
        mouse_middle = NIO_PRESSED;
      } else {
        mouse_middle = NIO_RELEASED;
      }
      break;

    case SDL_BUTTON_RIGHT:
      if (type == SDL_MOUSEBUTTONDOWN) {
        mouse_right = NIO_PRESSED;
      } else {
        mouse_right = NIO_RELEASED;
      }
  }
}

int
mouse_button_get(int i)
{
  if (i == 1)
    return(mouse_left);

  if (i == 2)
    return(mouse_middle);

  if (i == 3)
    return(mouse_right);

  fprintf(stderr, "nlogin: bad value passed to mouse_button_get(): %d\n", i);

  return(0);
}

nio_point
mouse_xy_get(void)
{
  nio_point p;

  p.x = mouse_x;
  p.y = mouse_y;

  return(p);
}

