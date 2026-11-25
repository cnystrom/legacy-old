/*
 * server.c
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../ssh_lib/uio.h"
#include "../ssh_lib/tty_echo.h"
#include "../ssh_lib/wlog.h"
#include "../ssh_lib/ssh_lib.h"
#include "server.h"

#define STR_LEN		(128)

void test2_get_line(void);

int
main(void)
{
  char hostname[HOSTNAME_LEN];
  char welcome[STR_LEN];

  wlog_init_file("server.log");

  gethostname(hostname, HOSTNAME_LEN);

  snprintf(welcome, STR_LEN, "NRPC Test Server 0.1 (%s)\n", hostname);

  wlog("welcome = %s\n", welcome);

  nrpc_init_server();
  nrpc_welcome(welcome);

  wlog("=================================================================\n");
  test_send_int(INT_MAX);
  wlog("=================================================================\n");
  test_send_int(INT_MIN);
  wlog("=================================================================\n");
  test_send_double(PI);
  wlog("=================================================================\n");
  test_send_double(DBL_MAX);
  wlog("=================================================================\n");
  test_send_double(DBL_MIN);
  wlog("=================================================================\n");
  test_send_string("This test is a very long string!");
  wlog("=================================================================\n");
  test_send_string("This test is a very long string!\nThis is string 2!\n");
  wlog("=================================================================\n");
  test_combo(3, PI, "The double is: ");
  wlog("=================================================================\n");

  nrpc_exit();
  nrpc_close();

  wlog_close();

  exit(0);
}

int
test_string(char *s)
{
  printf("s = %s\n", s);

  return(0);
}

int
do_combo(int i, double d, char *s)
{
  int j;

//  printf("do_combo(): s = %s\n", s);

  for (j = 0; j < i; j++)
    printf ("%s%.2f\n", s, d);
  
  return(0);
}

int
test_send_int(int i)
{
  int ret_code;

  nrpc_set_function(SEND_INT);
  msg_put_int(i);
  nrpc_send_message();
  ret_code = msg_get_int();

//  printf("Return Code: %d\n", ret_code);

  return(ret_code);
}

int
test_send_double(double d)
{
  int ret_code;

  nrpc_set_function(SEND_DBL);
  msg_put_double(d);
  nrpc_send_message();
  ret_code = msg_get_int();

//  printf("Return Code: %d\n", ret_code);

  return(ret_code);
}

int
test_send_string(char *s)
{
  int ret_code;

  nrpc_set_function(SEND_STR);
  msg_put_string(s);
  nrpc_send_message();
  ret_code = msg_get_int();

//  printf("Return Code: %d\n", i);

  return(ret_code);
}

int
test_combo(int i, double d, char *s)
{
  int ret_code;

//  printf("test_combo(): s = %s\n", s);

  nrpc_set_function(COMBO);
  msg_put_int(i);
  msg_put_double(d);
  msg_put_string(s);
  nrpc_send_message();
  ret_code = msg_get_int();

//  printf("Return Code: %d\n", ret_code);

  return(ret_code);
}

