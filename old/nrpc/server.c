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
#include "example.h"

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
  test_combo(3, PI, "The double is: ");
  wlog("=================================================================\n");

  nrpc_exit();
  nrpc_close();

  wlog_close();

  exit(0);
}

