/*
 *    list.c
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
  char server[MAXHOSTNAMELEN];
  int black, white;
  int font;

  if (argc < 2)
    strcpy(server, "localhost");
  else
   strcpy(server, argv[1]);

  nio_app_init(server, "list", "0.1");

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

  nio_print("\nNIO List version 0.01\n");
  nio_print("Programs available:\n\n");
  nio_print("Test line 3.\n");
  nio_print("Test line 4.\n");
//  nio_system_remote("cd nio; ls -1 *.nio | sed 's/.nio//g'");
  nio_pause("Hit any key to continue...\n");

  nio_free_font(font);

  nio_exit();
  exit(0);
}

