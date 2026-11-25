/*
 *    screen_test.c
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
 *    Soli Deo Gloria
 *
 */

#include "nio_lib.h"
#include "nio_font.h"

int
main(int argc, char *argv[])
{
	int i;
  char server[MAXHOSTNAMELEN];

  if (argc < 2)
    strcpy(server, "localhost");
  else
    strcpy(server, argv[1]);

  nio_app_init(server, "screen_test", "0.1");

/*
  nio_color_background(255, 255, 255);
  nio_set_text_fg_color("black");
  nio_set_text_bg_color("lightblue");
*/

	nio_font_set(NIO_MONO, 16);

	for (i = 0; i < 24; i++)
    nio_draw_string(2, (i * (20)), "123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789\n");

  nio_pause("Hit any key to continue...");

  nio_exit();
  exit(0);
}
