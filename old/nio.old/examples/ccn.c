/*
 *    ccn.c
 *
 *    Copyright (C) 2004  <Chris Nystrom>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: ccn@olenska.hn.org, nystrom@cactus.org,
 *              or cnystrom@talmid.sps.mot.com
 *
 *    Soli Deo Gloria
 *
 */

#include "nio_lib.h"
#include "nio_font.h"

#define MAX_MODE    (3)

void ccn_init(void);
void clear_screen(void);

int
main(int argc, char *argv[])
{
  int mode = 0;
  char server[MAXHOSTNAMELEN];

  if (argc < 2)
    strcpy(server, "localhost");
  else
   strcpy(server, argv[1]);

  nio_app_init(server, "ccn", "0.1");

  ccn_init();

  while(1)
  {
    int x, y, color;

    color = nio_get_rand_color();

    x = nio_rand_int(640);
    y = nio_rand_int(480);

    if (0 == mode)
    {
      nio_draw_rectangle(x, y, 10, 10, color);
    }
    if (1 == mode)
    {
      nio_draw_arc(x, y, 10, color);
    }
    if (2 == mode)
    {
      nio_draw_point(x, y, color);
    }
    if (3 == mode)
    {
      int x2, y2;

      x2 = nio_rand_int(640);
      y2 = nio_rand_int(480);

      nio_draw_line(x, y, x2, y2, color);
    }

    if (nio_mouse_button1())
      clear_screen();

    if (nio_mouse_button2())
    {
      mode++;

      if (mode > MAX_MODE) {
        mode = 0;
      }

      nio_printf_to_stdout("mode = %d\n", mode);
    }

    if (nio_mouse_button3())
    {
      nio_exit();
      exit(0);
    }
  }
}

void
ccn_init(void)
{
  int black, white, font;

  black = nio_get_color("black");
  white = nio_get_color("white");

  nio_clear_screen(black);

  font = nio_load_sys_font(
    NIO_DEFAULT_FONT,
    NIO_DEFAULT_PTSIZE,
    NIO_STYLE_NORMAL,
    white,
    black);

  nio_term_init(font, black);

  nio_print("\nCCN version 0.01\n");
}

void
clear_screen(void)
{
  int color;

  color = nio_get_rand_color();

  nio_draw_rectangle(1, 1, 640, 480, color);
}

