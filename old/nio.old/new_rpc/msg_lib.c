/*
 *    msg_lib.c
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

#include "new_rpc.h"
#include "msg_lib.h"

static char msg[MSG_MAX_LEN];
static int msg_index;

void
msg_get(char *s)
{
  strcpy(s, msg);
}

void
msg_set(char *s)
{
  strcpy(msg, s);
}

void
msg_reset(void)
{
  msg[0] = '\0';

  msg_index = 0;
}

void
msg_put_int(int i)
{
  char str[MSG_INT_SIZE + 1];

  msg_itoa(str, i);

  if (strlen(msg) > 0)
    strcat(msg, str);
  else
    strcpy(msg, str);
}

int
msg_get_int(void)
{
  int j;
  char str[MSG_INT_SIZE + 1];

  for (j = 0; j < MSG_INT_SIZE; j++)
    str[j] = msg[msg_index++];

  str[MSG_INT_SIZE] = '\0';

//  printf("get_int(): str = %s\n", str);
//  printf("get_int(): msg_index = %d\n", msg_index);

  return(atoi(str));
}

void
msg_put_double(double d)
{
  char str[MSG_DBL_SIZE + 1];

  msg_dtoa(str, d);

//  printf("msg_put_double(): msg = %s\n", msg);
//  printf("msg_put_double(): str = %s\n", str);

  if (strlen(msg) > 0)
    strcat(msg, str);
  else
    strcpy(msg, str);

//  printf("msg_put_double(): msg = %s\n", msg);
}

double
msg_get_double(void)
{
  int i;
  char str[MSG_DBL_SIZE + 1];

  for (i = 0; i < MSG_DBL_SIZE; i++)
    str[i] = msg[msg_index++];

  str[MSG_DBL_SIZE] = '\0';

//  printf("str = %s\n", str);

  return(atof(str));
}

void
msg_put_string(char *s_in)
{
  char str[MSG_STR_LEN];

  if (strlen(s_in) > MSG_STR_LEN)
    printf("msg_put_string() error: string length too big.\n");

  msg_itoa(str, strlen(s_in));

  if (strlen(msg) > 0)
    strcat(msg, str);
  else
    strcpy(msg, str);

  strcat(msg, s_in);
}

void
msg_get_string(char *s_out)
{
  int i, str_len;
  char str[MSG_STR_LEN];

  printf("--\nmsg_get_string(): msg_index = %d\n", msg_index);
  printf("msg_get_string(): msg = |%s|\n", msg);

  for (i = 0; i < MSG_INT_SIZE; i++) {
    str[i] = msg[msg_index++];
  }

  str[MSG_INT_SIZE] = '\0';

  str_len = atoi(str);

  printf("str_len = %d\n", str_len);

  if(str_len > MSG_STR_LEN)
    printf("msg_get_string() error: string length too big.\n");

//  printf("msg_get_string(): str_len = %d\n", str_len);
//  printf("msg_get_string(): msg_index = %d\n", msg_index);

  for (i = 0; i < str_len; i++) {
//    printf("i = %d\n", i);
//    printf("msg_index = %d\n", msg_index);
//    printf("msg[msg_index] = %d %c\n", msg[msg_index], msg[msg_index]);

    if (msg[msg_index] == 0) {
      nrpc_read_more();  // Need to check str len again
      msg_index = 0;
    }

   if (msg[msg_index] == 0) {
     fprintf(stderr, "msg_read_string(): read error\n");
     return;
   }

    s_out[i] = msg[msg_index++];
    printf("s_out[i] = %d %c\n", s_out[i], s_out[i]);
  }

  s_out[str_len] = '\0';

  printf("strlen(s_out) = %d\n", strlen(s_out));
  printf("msg_get_string(): s_out = |%s|\n--\n", s_out);
}

char *
msg_itoa(char *s, int i)
{
  snprintf(s, MSG_INT_SIZE + 1, "%+.10d", i);

//  printf("msg_itoa: s = |%s|\n", s);

  return(s);
}

char *
msg_dtoa(char *s, double d)
{
  snprintf(s, MSG_DBL_SIZE + 1, "%+17.10g", d);

//  printf("msg_dtoa: s = |%s|\n", s);

  return(s);
}

