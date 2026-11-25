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
 *    E-Mail: ccn@olenska.hn.org, nystrom@cactus.org,
 *              or cnystrom@talmid.sps.mot.com
 *
 *    Soli Deo Gloria
 *
 */

#include "../ssh_lib/wlog.h"
#include "../ssh_lib/tty_echo.h"
#include "../ssh_lib/ssh_lib.h"
#include "new_rpc.h"

int nrpc_read(char *s);
int nrpc_write(char *s);

static int nrpc_server = FALSE;

void
nrpc_init_server(void)
{
  echo_off();

  nrpc_server = TRUE;

  wlog("server initialized\n");
}

int
nrpc_init_client(char *username, char *hostname, char *command, char *passwd)
{
  int len = 0;
  int ret;
  char str[MSG_MAX_LEN];

  echo_off();

  ret = call_ssh(username, hostname, command);

  if (ret < 0)
    return (ret);

  ret = verify_passwd(passwd);

  if (ret < 0)
    return (ret);

  /* Get welcome message */

  len = nrpc_read(str);

  if (len == 0)
  {
    printf("new_rpc initialize_client error: login failed\n");
    return(-1);
  }

  while (len < 3) {
    nrpc_write("\n");
    nrpc_read(str);
  }

  printf("welcome = %s\n", str);

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
  wlog("welcome = %s\n", str);
  nrpc_write(str);
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

  wlog("sending: %s\n", str);

  nrpc_write(str);

  /* Every message deserves a response ... */

  nrpc_read(str);

  wlog("response: %s\n", str);

  msg_reset();

  msg_set(str);
}

void
nrpc_send_response(void)
{
  char str[MSG_MAX_LEN];

  msg_get(str);

  nrpc_write(str);
}

void
nrpc_reverse(void)
{
  nrpc_write("reverse");
}

void
nrpc_exit(void)
{
  wlog("exit\n");

  nrpc_write("exit");
}

void
nrpc_close(void)
{
  wlog("nrpc_close()...\n");

  if (! nrpc_server) {
    done_ssh();
  }

  echo_on();
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

  nrpc_read(str);

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

int
nrpc_read(char *s)
{
  int ret;

  if (nrpc_server) {
    ret = read(STDIN, s, MSG_MAX_LEN);
  }
  else {
    printf("Waiting in read_ssh()...\n");
    ret = read_ssh(s, MSG_MAX_LEN, USE_UIO);
  }

  return ret;
}

int
nrpc_write(char *s)
{
  int ret;

  if (nrpc_server) {
    ret = write(STDOUT, s, strlen(s));
  }
  else {
    ret = write_ssh(s);
  }

  return ret;
}

