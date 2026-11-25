/*
 *     mouse_test.c
 *
 *    Copyright (C) 2002  <Chris Nystrom>
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

void mouse_test_init(void);

int black;
int white;
int font;

int
main(int argc, char *argv[])
{
  int cls_flag = 1;
  char server[MAXHOSTNAMELEN];

  if (argc < 2)
    strcpy(server, "localhost");
  else
   strcpy(server, argv[1]);

  nio_app_init(server, "mouse_test", "0.1");

  black = nio_get_color("black");
  white = nio_get_color("white");

  font = nio_load_sys_font(
    NIO_DEFAULT_FONT,
    NIO_DEFAULT_PTSIZE,
    NIO_STYLE_NORMAL,
    black,
    white);

  mouse_test_init();

  while(1) {

    int color;
    nio_point p;

    color = nio_get_rand_color();

    if (nio_mouse_button1()) {
      p = nio_mouse_xy();

      if (p.x > 630)
        p.x = 630;

      if (p.y > 470)
        p.y = 470;

      nio_draw_rectangle(p.x, p.y, 10, 10, color);
      cls_flag = 1;  // Draw first before clearing screen again.
    }

    if (nio_mouse_button2()) {
      if (cls_flag) {
        mouse_test_init();
      }

      cls_flag = 0;
    }

    if (nio_mouse_button3()) {
      nio_exit();
      exit(0);
    }
  }
}

void
mouse_test_init(void)
{
  nio_clear_screen(white);

  nio_term_init(font, white);

  nio_print("\nNIO Mouse Test version 0.01\n");
 
  nio_print("\ndraw with button1, erase with button 2, exit with button 3\n");
}
