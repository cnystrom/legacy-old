/*
 *    new_rpc.c
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

#include "new_rpc.h"

static SOCKET s, s_tmp;
static int nrpc_server = FALSE;

void
nrpc_init_server(int port_num)
{
  s_tmp = open_socket(port_num);
  s = accept_socket(s_tmp);
  nrpc_server = TRUE;
}

int
nrpc_init_client(char *server, int port_num)
{
  int len;
  char str[MSG_MAX_LEN];

  s = call_socket(server, port_num);

  /* Get welcome message */

  len = gets_socket(s, str, MSG_MAX_LEN);

  if (len == 0)
  {
    printf("new_rpc initialize_client error: login failed\n");
    close_socket(s);
    return(-1);
  }

  printf("%s\n", str);

/*
#ifdef DEBUG
  printf("str = %s\n", str);
#endif
*/

  return(0);
}

void
nrpc_welcome(char *str)
{
  puts_socket(s, str);
}

void
nrpc_send_message(void)
{
  char str[MSG_MAX_LEN];

  msg_get(str);

/*
#ifdef DEBUG
  if (strlen(str) <= 0)
  {
    printf("nrpc_send_message() error: no messsage to send.\n");
    exit(1);
  }
#endif
*/

  puts_socket(s, str);

  /* Every message deserves a response ... */

  gets_socket(s, str, sizeof(str));

  msg_reset();

  msg_set(str);
}

void
nrpc_send_response(void)
{
  char str[MSG_MAX_LEN];

  msg_get(str);

  puts_socket(s, str);
}

void
nrpc_reverse(void)
{
  puts_socket(s, "reverse");
}

void
nrpc_exit(void)
{
  puts_socket(s, "exit");
}

void
nrpc_close(void)
{
  close_socket(s);

  if (nrpc_server)
    close_socket(s_tmp);
}

void
nrpc_set_function(int func_num)
{
  char str[MSG_MAX_LEN];

  msg_itoa(str, func_num);
  msg_set(str);
}

int
nrpc_get_function(void)
{
  int func_num;
  char str[MSG_MAX_LEN];

  msg_reset();

  gets_socket(s, str, sizeof(str));

  if (strlen(str) <= 0)
  {
    printf("nrpc_get_funtion() error: strlen(str) <= 0\n");
    return(NRPC_INVALID);
  }

  if (strncmp(str, "exit", 4) == 0)
  {
/*
#ifdef DEBUG
    printf("Exit command rcvd\n");
#endif
*/
    return(NRPC_EXIT);
  }

  if (strncmp(str, "reverse", 7) == 0)
  {
/*
#ifdef DEBUG
    printf("Reverse command rcvd\n");
#endif
*/
    return(NRPC_REVERSE);
  }

  msg_set(str);

  func_num = msg_get_int();

  printf("func_num = %d\n", func_num);

/*
#ifdef DEBUG
  printf("get_function(): func_num = %d\n", func_num);
#endif
*/

  return(func_num);
}

void
nrpc_std_response(void)
{
  msg_reset();

  msg_put_int(0);

  nrpc_send_response();
}

void
nrpc_wait_for_reverse(void)
{
  for (;;)
  {
    int func_num;

    func_num = nrpc_get_function();

    if (func_num == NRPC_EXIT)
    {
      printf("Exit command rcvd.\n");
      nrpc_close();
      exit(0);
    }
    else if (func_num == NRPC_REVERSE)
    {
      printf("Reverse command rcvd.\n");
      break;
    }
    else
    {
      printf("bad function number!\n");
    }
  }
}

