/*
 *     flip.c
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
 *    Soli Deo Gloria
 *
 */

#include "nio_lib.h"
#include "nio_font.h"

#define WHITE   (0)
#define COLORED (1)

void flip_init(void);
void init_board(void);
void draw_board(void);
void game_loop(void);
void quit_game(void);
void flip_slot(int);
void flip_board(int);
int  get_slot(int, int);
void you_lost(void);
void you_won(void);
void new_game(void);
bool you_win(void);
bool all_white(void);
bool all_color(void);

static bool board[9];
static int score = 25; 

static bool all_white_flag = TRUE;
static bool all_color_flag = TRUE;

int pssst;
int tink;
int ricochet;
int flip;
int youwin;
int youlose;
int allwhite;
int allcolor;
int instructions;
int black;
int red;
int white;
int font0;
int font1;
int font2;

int
main(int argc, char *argv[])
{
  char server[MAXHOSTNAMELEN];

  if (argc < 2)
    strcpy(server, "localhost");
  else
    strcpy(server, argv[1]);

  nio_app_init(server, "flip", "0.1");

  flip_init();

  game_loop();

  exit(-1);
}

void
flip_init(void)
{
  int c, black;

  black = nio_get_color("black");
  red = nio_get_color("red");
  white = nio_get_color("white");
                                                                                
  nio_clear_screen(black);

  font0 = nio_load_sys_font(
    NIO_DEFAULT_FONT,
    NIO_DEFAULT_PTSIZE,
    NIO_STYLE_NORMAL,
    white,
    black);
                                                                                
  nio_term_init(font0, black);

  nio_print("\nNIO Flip 0.01\n");

  pssst = nio_load_sound("src/nio/examples/pssst.wav");
  tink = nio_load_sound("src/nio/examples/tink.wav");
  ricochet = nio_load_sound("src/nio/examples/ricochet.wav");
  youwin = nio_load_sound("src/nio/examples/youwin.wav");
  youlose = nio_load_sound("src/nio/examples/youlose.wav");
  flip = nio_load_sound("src/nio/examples/flip.wav");
  allwhite = nio_load_sound("src/nio/examples/allwhite.wav");
  allcolor = nio_load_sound("src/nio/examples/allcolor.wav");
  instructions = nio_load_sound("src/nio/examples/Instructions.wav");

  nio_play_sound(flip, 0);

  font1 = nio_load_sys_font(
    NIO_SERIF_BOLD_ITALIC,
    64,
    NIO_STYLE_NORMAL,
    white,
    black);

  nio_draw_text(font1, 400, 150, "FLIP!");

  font2 = nio_load_sys_font(
    NIO_SANS,
    24,
    NIO_STYLE_NORMAL,
    white,
    black);

  nio_draw_textf(font2, 400, 250, "TURNS: %d", score);

  init_board();

  draw_board();

  nio_draw_text(font0, 50, 400, "Do you want instructions? (y/n)");
 
  c = nio_get_char(FALSE);

  nio_draw_rectangle(50, 400, 310, 30, black);

  if (c == 'y')
    nio_play_sound(instructions, 0);
}

void
init_board(void)
{
  int i;

  for (i = 0; i < 9; i++)
    board[i] = nio_rand_bool();
}

void
draw_square(int slot)
{
  int color;
  int x = 150;
  int y = 150;
  int box_size=50;
  int space_size = box_size + 5;
  int x1 = 0, y1 = 0;

  if (board[slot] == WHITE)
    color = white;
  else
    color = nio_get_rand_color();

  if (0 == slot) {
    x1 = 0;
    y1 = 0;
  }
  else if (1 == slot) {
    x1 = 1;
    y1 = 0;
  }
  else if (2 == slot) {
    x1 = 2;
    y1 = 0;
  }
  else if (3 == slot) {
    x1 = 0;
    y1 = 1;
  }
  else if (4 == slot) {
    x1 = 1;
    y1 = 1;
  }
  else if (5 == slot) {
    x1 = 2;
    y1 = 1;
  }
  else if (6 == slot) {
    x1 = 0;
    y1 = 2;
  }
  else if (7 == slot) {
    x1 = 1;
    y1 = 2;
  }
  else if (8 == slot) {
    x1 = 2;
    y1 = 2;
  }

  nio_draw_rectangle(x + (space_size * x1), y + (space_size * y1),
    box_size, box_size, color);
}

void
draw_board(void)
{
  int i;

  for (i = 0; i < 9; i++)
    draw_square(i);
}

void
game_loop(void)
{
  int slot;


  while(1) {

    nio_point p;

    if (nio_mouse_button1()) {
      p = nio_mouse_xy();

      slot = get_slot(p.x, p.y);

      if (slot != -1) {
        flip_board(slot);
        draw_board();
        nio_play_sound(tink, 0);

	      if (you_win())
          you_won();
	      else if (all_color()) {
          if (all_color_flag) {
            nio_play_sound(allcolor, 0);
            score = score + 10;
            all_color_flag = FALSE;
          }
	      }
	      else if (all_white()) {
          if (all_white_flag) {
            nio_play_sound(allwhite, 0);
            score = score + 10;
            all_white_flag = FALSE;
          }
        }

        score--;

        nio_draw_rectangle(490, 257, 35, 35, black);

        nio_draw_textf(font2, 400, 250, "TURNS: %d", score);

        if (score == 0)
          you_lost();
      }

      // Wait until user releases button...
      while (nio_mouse_button1())
        ;
    }

    // cheat here...
    if (nio_mouse_button2())
      you_won();

    if (nio_mouse_button3())
      quit_game();
  }
}

void
quit_game(void)
{
  nio_exit();
  exit(0);
}

int
get_slot(int x, int y)
{
  if (x < 150 || x > 310 || y < 150 || y > 310)
    return(-1);

  if (x < 200 && y < 200)
    return(0);
  else if (x < 255 && y < 200)
    return(1);
  else if (x < 310 && y < 200)
    return(2);
  else if (x < 200 && y < 255)
    return(3);
  else if (x < 255 && y < 255)
    return(4);
  else if (x < 310 && y < 255)
    return(5);
  else if (x < 200 && y < 310)
    return(6);
  else if (x < 255 && y < 310)
    return(7);
  else
    return(8);
}

void
flip_slot(slot)
{
  if (slot < 0 || slot > 8) {
    nio_print("Error in flip_slot(): bad slot.\n");
    return;
  }

  if (board[slot] == 0)
    board[slot] = 1;
  else
    board[slot] = 0;
}

// The board:
//
//  0 | 1 | 2
//  ---------
//  3 | 4 | 5
//  ---------
//  6 | 7 | 8
//
void
flip_board(int slot)
{
  if (slot < 0 || slot > 8) {
    nio_print("Error in flip_board(): bad slot.\n");
    return;
  }

  if (0 == slot) {
    flip_slot(0);
    flip_slot(1);
    flip_slot(3);
  }
  else if (1 == slot) {
    flip_slot(0);
    flip_slot(1);
    flip_slot(2);
    flip_slot(4);
  }
  else if (2 == slot) {
    flip_slot(1);
    flip_slot(2);
    flip_slot(5);
  }
  else if (3 == slot) {
    flip_slot(0);
    flip_slot(3);
    flip_slot(4);
    flip_slot(6);
  }
  else if (4 == slot) {
    flip_slot(1);
    flip_slot(3);
    flip_slot(4);
    flip_slot(5);
    flip_slot(7);
  }
  else if (5 == slot) {
    flip_slot(2);
    flip_slot(4);
    flip_slot(5);
    flip_slot(8);
  }
  else if (6 == slot) {
    flip_slot(3);
    flip_slot(6);
    flip_slot(7);
  }
  else if (7 == slot) {
    flip_slot(4);
    flip_slot(6);
    flip_slot(7);
    flip_slot(8);
  }
  else if (8 == slot) {
    flip_slot(5);
    flip_slot(7);
    flip_slot(8);
  }
}

void
you_lost(void)
{
  int font3;

  nio_play_sound(ricochet, 0);

  font3 = nio_load_sys_font(
    NIO_SERIF_BOLD_ITALIC,
    128,
    NIO_STYLE_NORMAL,
    red,
    black);
                                                                                
  nio_draw_text(font3, 70, 120, "YOU LOSE!");

  nio_play_sound(youlose, 0);

  nio_draw_text(font0, 50, 400,
    "Left click for new game, right click to exit...");

  while(1) {
    if (nio_mouse_button1())
      new_game();

    if (nio_mouse_button3())
      quit_game();
  }

  nio_free_font(font3);
}

void
you_won(void)
{
  int i, font4;

  for (i = 0; i < 8; i++) {
    int color;

    color = nio_get_rand_color();

    font4 = nio_load_sys_font(
      NIO_SERIF_BOLD_ITALIC,
      128,
      NIO_STYLE_NORMAL,
      color,
      black);
                                                                                
    nio_play_sound(tink, 0);

    nio_draw_text(font4, 90, 120, "YOU WIN!");

    nio_free_font(font4);
  }

  nio_play_sound(youwin, 0);

  nio_draw_text(font0, 50, 400,
    "Left click for new game, right click to exit...");

  while(1) {
    if (nio_mouse_button1())
      new_game();

    if (nio_mouse_button3())
      quit_game();
  }
}

void
new_game(void)
{
  score = 25;

  nio_clear_screen(black);

  nio_print("\nNIO Flip 0.01\n");

  nio_play_sound(flip, 0);

  nio_draw_text(font1, 400, 150, "FLIP!");

  nio_draw_textf(font2, 400, 250, "TURNS: %d", score);

  init_board();
  draw_board();
  game_loop();
}

bool
all_white(void)
{
  int i;
  bool ret = TRUE;

  for (i = 0; i < 9; i++)
    if (board[i] == COLORED)
      ret = FALSE;

  return(ret);
}

bool
all_color(void)
{
  int i;
  bool ret = TRUE;

  for (i = 0; i < 9; i++)
    if (board[i] == WHITE)
      ret = FALSE;

  return(ret);
}

bool
you_win(void)
{
  int i;
  bool ret = TRUE;

  for (i = 0; i < 9; i++) {
    if (i == 4) {              /* middle slot */
      if (board[i] == WHITE)
        ret = FALSE;
    }
    else {
      if (board[i] == COLORED)
        ret = FALSE;
    }
  }

  return(ret);
}

