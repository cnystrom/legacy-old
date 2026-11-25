/*
 *    nio_lib.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#ifdef UNIX
#include <sys/param.h>
#endif
#include <stdarg.h>
#include <time.h>
#include "../new_rpc/new_rpc.h"
#include "nio.h"
#include "ascii_key.h"
#include "nio_lib.h"

#define SYSTEM_BUFFER    (24*80*10)  // 10 Terminals full enough?

// Control Functions

void
nio_app_init(char *server, char *app_name, char *app_ver)
{
  char nio_ver[8] = NIO_LIB_VER;
  char hostname[MAXHOSTNAMELEN];
  char cwd[256];
  char s[BUFSIZ];

  snprintf(s, BUFSIZ, "%s.%s.log", app_name, app_ver);

//  wlog_init_file(s);

  gethostname(hostname, MAXHOSTNAMELEN);

  snprintf(s, BUFSIZ, "%s %s %s\n", server, app_name, app_ver);

  getcwd(cwd, 256);

//  sleep(1);    /* pause to give server time to start up */

//  printf("nio_app_init()\n");
//  printf("server = %s\n", server);

  nrpc_init_server(NIO_PORT_NUM);
  nrpc_welcome(s);

  nrpc_set_function(NIO_INIT);

  msg_put_string(nio_ver);
  msg_put_string(hostname);
  msg_put_string(app_name);
  msg_put_string(app_ver);
  msg_put_string(cwd);

  nrpc_send_message();

  randomize();
}

void
nio_exit(void)
{
//  printf("nio_exit() called.\n");

  nrpc_set_function(NIO_EXIT);
  nrpc_send_message();
  nrpc_close();
//  wlog_close();
}

// stdio Functions

void
nio_char_to_stdout(int c)
{
  nrpc_set_function(NIO_CHAR_TO_STDOUT);
  msg_put_int(c);
  nrpc_send_message();
}

void
nio_string_to_stdout(char *s)
{
  nrpc_set_function(NIO_STRING_TO_STDOUT);
  msg_put_string(s);
  nrpc_send_message();
}

void
nio_int_to_stdout(int i)
{
  nrpc_set_function(NIO_INT_TO_STDOUT);
  msg_put_int(i);
  nrpc_send_message();
}

void
nio_printf_to_stdout(char *format, ...)
{
  nio_string s;
  va_list ap;

  va_start(ap, format);
  vsprintf(s, format, ap);
  va_end(ap);

  nio_string_to_stdout(s);
}

// io Functions

int
nio_get_char(bool b)
{
  int c = NUL;

  nrpc_set_function(NIO_GET_CHAR);
  nrpc_send_message();

  c  = msg_get_int();

  if (b == TRUE)
    nio_put_char(c);

  return(c);
}

void
nio_put_char(int c)
{
  nrpc_set_function(NIO_PUT_CHAR);
  msg_put_int(c);
  nrpc_send_message();
}

int
nio_get_string(char *s, int lim)
{
  int c, i = 0;

  c = nio_get_char(TRUE);

  while (lim > 0 && c != EOF && c != RET) {
    if (c == BS) {
      if (i != 0 ) {
        lim++;
        s[i--] = '\0';
      }
    }
    else {
      lim--;
      s[i++] = c;
    }
    c = nio_get_char(TRUE);
  }

  s[i] = '\0';

  return i;
}

void
nio_print(char *s)
{
  nrpc_set_function(NIO_PRINT);
  msg_put_string(s);

//  wlog("s = |%s|\n", s);

  nrpc_send_message();
}

void
nio_printf(char *format, ...)
{
  nio_string s;
  va_list ap;

  va_start(ap, format);
  vsprintf(s, format, ap);
  va_end(ap);

  nio_print(s);
}

void
nio_input(char *s1, char *s2, int str_len)
{
  nio_print(s1);
  nio_get_string(s2, str_len);
  nio_print("\n");
}

void
nio_pause(char *s)
{
  nio_print(s);
  nio_get_char(FALSE);
}

// Mouse I/O Functions

int
nio_mouse_button1(void)
{
  int i;

  nrpc_set_function(NIO_MOUSE_BUTTON1);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

int
nio_mouse_button2(void)
{
  int i;

  nrpc_set_function(NIO_MOUSE_BUTTON2);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

int
nio_mouse_button3(void)
{
  int i;

  nrpc_set_function(NIO_MOUSE_BUTTON3);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

nio_point
nio_mouse_xy(void)
{
  nio_point p;

  nrpc_set_function(NIO_MOUSE_XY);
  nrpc_send_message();
  p.x = msg_get_int();
  p.y = msg_get_int();
  return(p);
}

// System Command Functions

void
nio_system_local(char *s)
{
  nrpc_set_function(NIO_SYSTEM_LOCAL);
  msg_put_string(s);
  nrpc_send_message();
}

void
nio_system_remote(char *s)
{
  int fd, n;
  char s2[SYSTEM_BUFFER+64];

  strcpy(s2, s);

#ifdef WIN32
  strcat(s2, " > C:\TMP\nlogin.tmp");
#else
  strcat(s2, " > /usr/tmp/nlogin.tmp");
#endif

  n = strlen(s2);

//  printf("Executing: %s\n", s2);

  system(s2);

  s2[0] = 0x00;

#ifdef WIN32
  fd = open("C:\TMP\nlogin.tmp", O_RDONLY, 0);
#else
  fd = open("/usr/tmp/nlogin.tmp", O_RDONLY, 0);
#endif
  n = read(fd, &s2, SYSTEM_BUFFER);
  close(fd);

  s2[n] = 0x00;

//  printf("results: %s\n", s2);

  nio_print(s2);
}

// Color Functions

int
nio_get_color(char *s)
{
  int i;

//  printf("nio_get_color(): s = %s\n", s);

  nrpc_set_function(NIO_GET_COLOR);
  msg_put_string(s);
  nrpc_send_message();
  i = msg_get_int();

//  printf("nio_get_color(): i = %d\n", i);
  return(i);
}

int
nio_get_color_rgb(int red, int green, int blue)
{
  int i;

  nrpc_set_function(NIO_GET_COLOR_RGB);
  msg_put_int(red);
  msg_put_int(green);
  msg_put_int(blue);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

int
nio_get_rand_color(void)
{
  int i;

  nrpc_set_function(NIO_GET_RAND_COLOR);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

// Font Functions

int
nio_load_font(char *filename, int point_size, int style,
	       	int fg_color, int bg_color)
{
  int i;

  nrpc_set_function(NIO_LOAD_FONT);
  msg_put_string(filename);
  msg_put_int(point_size);
  msg_put_int(style);
  msg_put_int(fg_color);
  msg_put_int(bg_color);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

int
nio_load_sys_font(int system_font, int point_size, int style,
	       	int fg_color, int bg_color)
{
  int i;

  nrpc_set_function(NIO_LOAD_SYS_FONT);
  msg_put_int(system_font);
  msg_put_int(point_size);
  msg_put_int(style);
  msg_put_int(fg_color);
  msg_put_int(bg_color);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

void
nio_free_font(int i)
{
  nrpc_set_function(NIO_FREE_FONT);
  msg_put_int(i);
  nrpc_send_message();
}

void
nio_draw_text(int font_num, int x, int y, char *s)
{
  nrpc_set_function(NIO_DRAW_TEXT);
  msg_put_int(font_num);
  msg_put_int(x);
  msg_put_int(y);
  msg_put_string(s);
  nrpc_send_message();
}

void
nio_draw_textf(int font_num, int x, int y, char *format, ...)
{
  nio_string s;
  va_list ap;

  va_start(ap, format);
  vsprintf(s, format, ap);
  va_end(ap);

  nio_draw_text(font_num, x, y, s);
}

// Screen Functions

void
nio_set_screen(int x, int y, int bg_color)
{
  nrpc_set_function(NIO_SET_SCREEN);
  msg_put_int(x);
  msg_put_int(y);
  msg_put_int(bg_color);
  nrpc_send_message();
}

void
nio_clear_screen(int bg_color)
{
  nrpc_set_function(NIO_CLEAR_SCREEN);
  msg_put_int(bg_color);
  nrpc_send_message();
}

// Drawing Functions

void
nio_draw_rectangle(int x, int y, int width, int height, int color)
{
  nrpc_set_function(NIO_DRAW_RECTANGLE);
  msg_put_int(x);
  msg_put_int(y);
  msg_put_int(width);
  msg_put_int(height);
  msg_put_int(color);
  nrpc_send_message();
}

void
nio_draw_point(int x, int y, int color)
{
  nrpc_set_function(NIO_DRAW_POINT);
  msg_put_int(x);
  msg_put_int(y);
  msg_put_int(color);
  nrpc_send_message();
}

void
nio_draw_line(int x1, int y1, int x2, int y2, int color)
{
  nrpc_set_function(NIO_DRAW_LINE);
  msg_put_int(x1);
  msg_put_int(y1);
  msg_put_int(x2);
  msg_put_int(y2);
  msg_put_int(color);
  nrpc_send_message();
}

void
nio_draw_arc(int x, int y, int r, int color)
{
  nrpc_set_function(NIO_DRAW_ARC);
  msg_put_int(x);
  msg_put_int(y);
  msg_put_int(r);
  msg_put_int(color);
  nrpc_send_message();
}

// Sound Functions

void
nio_sound(int status)
{
  nrpc_set_function(NIO_SOUND);
  msg_put_int(status);
  nrpc_send_message();
}

void
nio_beep(void)
{
  nrpc_set_function(NIO_BEEP);
  nrpc_send_message();
}

void
nio_load_music(char *filename)
{
  nrpc_set_function(NIO_LOAD_MUSIC);
  msg_put_string(filename);
  nrpc_send_message();
}

void
nio_play_music(int loops)
{
  nrpc_set_function(NIO_PLAY_MUSIC);
  msg_put_int(loops);
  nrpc_send_message();
}

void
nio_stop_music(void)
{
  nrpc_set_function(NIO_STOP_MUSIC);
  nrpc_send_message();
}

bool
nio_music_playing(void)
{
  bool b;

  nrpc_set_function(NIO_MUSIC_PLAYING);
  nrpc_send_message();
  b = msg_get_int();
  return(b);
}

int
nio_load_sound(char *filename)
{
  int i;

  nrpc_set_function(NIO_LOAD_SOUND);
  msg_put_string(filename);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

void
nio_play_sound(int sound_num, int loops)
{
  nrpc_set_function(NIO_PLAY_SOUND);
  msg_put_int(sound_num);
  msg_put_int(loops);
  nrpc_send_message();
}

void
nio_free_sound(int i)
{
  nrpc_set_function(NIO_FREE_SOUND);
  msg_put_int(i);
  nrpc_send_message();
}

// Image Functions

int
nio_load_image(char *filename)
{
  int i;

  nrpc_set_function(NIO_LOAD_IMAGE);
  msg_put_string(filename);
  nrpc_send_message();
  i = msg_get_int();
  return(i);
}

void
nio_draw_image(int x, int y, int image_num)
{
  nrpc_set_function(NIO_DRAW_IMAGE);
  msg_put_int(x);
  msg_put_int(y);
  msg_put_int(image_num);
  nrpc_send_message();
}

void
nio_free_image(int i)
{
  nrpc_set_function(NIO_FREE_IMAGE);
  msg_put_int(i);
  nrpc_send_message();
}

void
nio_term_init(int font_num, int color)
{
  nrpc_set_function(NIO_TERM_INIT);
  msg_put_int(font_num);
  msg_put_int(color);
  nrpc_send_message();
}

/********************************************************************/

/* Seed the randomizer with the timer */
void
randomize(void)
{
  time_t timer;
  srand ((unsigned) time (&timer));
}

/* Returns an integer from 0 to i */
int
nio_rand_int(int i)
{
  if (i <= 0)
  {
#ifdef DEBUG
//    printf("Error: nio_rand_int i <= 0.\n");
#endif
    return(0);
  }
  else
    return((int)(rand() % i) + .5);
}

bool
nio_rand_bool(void)
{
  bool b;

  if (nio_rand_int(100) < 50)
    b = TRUE;
  else
    b = FALSE;

  return(b);
}

