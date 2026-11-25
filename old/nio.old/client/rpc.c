/*
 *    rpc.c
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

#include "rpc.h"

static int sound = NIO_ON;

// Control Functions

void
nio_app_init_1(void)
{
  char nio_ver[MSG_STR_LEN];
  char server[MSG_STR_LEN];
  char app_name[MSG_STR_LEN];
  char app_ver[MSG_STR_LEN];
  char cwd[MSG_STR_LEN];

//  printf("Initializing remote application...\n");

  msg_get_string(nio_ver);
  msg_get_string(server);
  msg_get_string(app_name);
  msg_get_string(app_ver);
  msg_get_string(cwd);

  init_file_loader(server, app_name, app_ver, cwd);

/*
  printf("nio_init_1:\n");
  printf(" nio_ver = %s\n", nio_ver);
  printf(" server = %s\n", server);
  printf(" app_name = %s\n", app_name);
  printf(" app_ver = %s\n", app_ver);
  printf(" cwd = %s\n", cwd);
*/

//  bg = get_color("black");

//  term_init(0, bg);

//  clear_screen(bg);

  nrpc_std_response();
}

void
nio_exit_1(void)
{
//  term_clear();

//  printf("nio_exit(): Program terminated at server.\n");

  nrpc_std_response();
  nrpc_close();
}

// STDIO Function

void
nio_char_to_stdout_1(void)
{
  int c;

  c = msg_get_int();
  putchar(c);
  fflush(stdout);
  nrpc_std_response();
}

void
nio_string_to_stdout_1(void)
{
  char s[MSG_STR_LEN];

  msg_get_string(s);

  printf(s);
  fflush(stdout);

  nrpc_std_response();
}

void
nio_int_to_stdout_1(void)
{
  int i;
  
  i = msg_get_int();

  printf("%d", i);
  fflush(stdout);

  nrpc_std_response();
}

// I/O Functions

void
nio_get_char_1(void)
{
  msg_reset();
  msg_put_int(get_char());
  nrpc_send_response();
}

void
nio_put_char_1(void)
{
  int i;

  i = msg_get_int();

  term_put_char(i);
//  update_screen();

  nrpc_std_response();
}

// Mouse I/O Functions

void
nio_mouse_button1_1(void)
{
  int mb1;

  msg_reset();
  mb1 = mouse_button_get(1);
  msg_put_int(mb1);
  nrpc_send_response();
}

void
nio_mouse_button2_1(void)
{
  int mb2;

  msg_reset();
  mb2 = mouse_button_get(2);
  msg_put_int(mb2);
  nrpc_send_response();
}

void
nio_mouse_button3_1(void)
{
  int mb3;

  msg_reset();
  mb3 = mouse_button_get(3);
  msg_put_int(mb3);
  nrpc_send_response();
}

void
nio_mouse_xy_1(void)
{
  nio_point mp;

  msg_reset();
  mp = mouse_xy_get();
  msg_put_int(mp.x);
  msg_put_int(mp.y);
  nrpc_send_response();
}

// System Command Functions

void
nio_system_local_1(void)
{
  char s[MSG_STR_LEN];

  msg_get_string(s);

  system(s);
  fflush(stdout);

  nrpc_std_response();
}

// Color Functions

void
nio_get_color_1(void)
{
  int color;
  char s[MSG_STR_LEN];

  msg_get_string(s);
//  fprintf(stderr, "nio_get_color_1(): s = %s\n", s);

  msg_reset();
  color = get_color(s);
//  fprintf(stderr, "nio_get_color_1(): color = %d\n", color);

  msg_put_int(color);
  nrpc_send_response();
}

void
nio_get_color_rgb_1(void)
{
  int red, green, blue, color;

  red = msg_get_int();
  green = msg_get_int();
  blue = msg_get_int();
  msg_reset();
  color = get_color_rgb(red, green, blue);
  msg_put_int(color);
  nrpc_send_response();
}

void
nio_get_rand_color_1(void)
{
  int color;

  msg_reset();
  color = get_rand_color();
  msg_put_int(color);
  nrpc_send_response();
}

// Font Functions

void
nio_load_font_1(void)
{
  char fontfile[MSG_STR_LEN];
  int point_size;
  int style;
  int fg_color;
  int bg_color;
  int font_num;

  msg_get_string(fontfile);
  point_size = msg_get_int();
  style = msg_get_int();
  fg_color = msg_get_int();
  bg_color = msg_get_int();

  msg_reset();
  font_num = load_font(load_file(fontfile), point_size, style, fg_color, bg_color);
  
  msg_put_int(font_num);
  nrpc_send_response();
}

void
nio_load_sys_font_1(void)
{
  int sys_font;
  int point_size;
  int style;
  int fg_color;
  int bg_color;
  int font_num;

  sys_font = msg_get_int();
  point_size = msg_get_int();
  style = msg_get_int();
  fg_color = msg_get_int();
  bg_color = msg_get_int();

  msg_reset();
  font_num = load_sys_font(sys_font, point_size, style, fg_color, bg_color);
  
  msg_put_int(font_num);
  nrpc_send_response();
}

void
nio_free_font_1(void)
{
  int font_num;

  font_num = msg_get_int();
  free_font(font_num);
  nrpc_std_response();
}

void
nio_draw_text_1(void)
{
  int font_num, x, y;
  char s[MSG_STR_LEN];
  glyphFont gf;

  font_num = msg_get_int();
  x = msg_get_int();
  y = msg_get_int();
  msg_get_string(s);

  gf = get_font(font_num);

  draw_text(&gf, s, x, y);

  nrpc_std_response();
}

// Screen Functions

void
nio_set_screen_1(void)
{
  int x, y, color;

  x = msg_get_int();
  y = msg_get_int();
  color = msg_get_int();

  init_screen(x, y, SDL_ANYFORMAT);
  clear_screen(color);

  nrpc_std_response();
}

void
nio_clear_screen_1(void)
{
  int color;

//  term_clear();
  color = msg_get_int();
  clear_screen(color);
  nrpc_std_response();
}

// Drawing Functions

void
nio_draw_rectangle_1(void)
{
  int x, y, width, height, color;

  x = msg_get_int();
  y = msg_get_int();
  width = msg_get_int();
  height = msg_get_int();
  color = msg_get_int();

  draw_rectangle(x, y, width, height, color);

  nrpc_std_response();
}

void
nio_draw_point_1(void)
{
  int x, y, color;

  x = msg_get_int();
  y = msg_get_int();
  color = msg_get_int();

  draw_point(x, y, color);

  nrpc_std_response();
}

void
nio_draw_line_1(void)
{
  int x1, y1, x2, y2, color;

  x1 = msg_get_int();
  y1 = msg_get_int();
  x2 = msg_get_int();
  y2 = msg_get_int();
  color = msg_get_int();

  draw_line(x1, y1, x2, y2, color);

  nrpc_std_response();
}

void
nio_draw_arc_1(void)
{
  int x, y, r, color;

  x = msg_get_int();
  y = msg_get_int();
  r = msg_get_int();
  color = msg_get_int();

  draw_arc(x, y, r, color);

  nrpc_std_response();
}

// Sound Functions

void
nio_sound_1(void)
{
  sound = msg_get_int();
  nrpc_std_response();
}

void
nio_beep_1(void)
{
  if (sound)
    putchar(7);
  else
    printf("beep\n");

  nrpc_std_response();
}

void
nio_load_music_1(void)
{
  char filename[MSG_STR_LEN];

  msg_get_string(filename);

  load_music(load_file(filename));
  
  nrpc_std_response();
}

void
nio_play_music_1(void)
{
  int loops;

  loops = msg_get_int();

  if (sound) {
    play_music(loops);
  }
  else
    printf("Sound is off...\n");

  nrpc_std_response();
}

void
nio_stop_music_1(void)
{
  stop_music();
  nrpc_std_response();
}

void
nio_load_sound_1(void)
{
  int sound_num;
  char filename[MSG_STR_LEN];

  msg_get_string(filename);

//  printf("nio_load_sound(): filename = %s\n", filename);

  msg_reset();
  sound_num = load_sound(load_file(filename));

//  printf("nio_load_sound(): sound_num = %d\n", sound_num);
 
  msg_put_int(sound_num);

  nrpc_send_response();
}

void
nio_play_sound_1(void)
{
  int channel, sound_num, loops;

  sound_num = msg_get_int();
  loops = msg_get_int();

  if (sound) {
    if (sound_num >= 0) {
      channel = play_sound(sound_num, loops);

//      printf("nio_play_sound_1(): channel = %d\n", channel);

      if (channel >= 0) {
        while(! sound_channel_done(channel))
          ;
      }
    }
  }
  else
    printf("Sound is off...\n");

  nrpc_std_response();
}

void
nio_free_sound_1(void)
{
  int sound_num;

  sound_num = msg_get_int();

  delete_sound(sound_num);
  nrpc_std_response();
}

// Image Functions

void
nio_load_image_1(void)
{
  int image_num;

  char filename[MSG_STR_LEN];

  msg_get_string(filename);

  msg_reset();
  image_num = load_image(load_file(filename));
 
  msg_put_int(image_num);

  nrpc_send_response();
}

void
nio_draw_image_1(void)
{
  int i_num, x, y;

  i_num = msg_get_int();
  x = msg_get_int();
  y = msg_get_int();

  draw_image(i_num, x, y);

  nrpc_std_response();
}

void
nio_free_image_1(void)
{
  int image_num;

  image_num = msg_get_int();

  free_image(image_num);
  nrpc_std_response();
}

void
nio_term_init_1(void)
{
  int font_num;
  int color;

  font_num = msg_get_int();
  color = msg_get_int();
  term_init(font_num, color);
  nrpc_std_response();
}

void
nio_print_1(void)
{
  int i, s_len;
  char s[MSG_STR_LEN];

  msg_get_string(s);

//  printf("s = |%s|\n", s);

  s_len = strlen(s);
 
 for (i = 0; i < s_len; i++)
   term_put_char(s[i]);

  nrpc_std_response();
}

