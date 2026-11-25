/*
 * server.c
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "uio.h"
#include "tty_echo.h"
#include "example.h"
#include "../ssh_lib/wlog.h"

#define STR_LEN		(128)

void test2_get_line(void);

int log_fd;

int
main(void)
{
  char hostname[HOSTNAME_LEN];
  char welcome[STR_LEN];
  int i = 0;

  echo_off();

  log_fd = uio_open_file_wr("test2b.log");

  while (1) {
    i++;

    // Tell client exiting after 10 lines
    if (i == 10) {
      uio_put_line(log_fd, "server -> client: exit\n");
      uio_put_line(STDOUT, "exit\n");
      close(log_fd);
      echo_on();
      exit (0);
    }
    else { 
      uio_put_linef(log_fd, "Server: Welcome to line %d!\n", i);
      uio_put_linef(STDOUT, "Server: Welcome to line %d!\n", i);
    }

    test2_get_line();
  }

  wlog_init_file("server.log");

  gethostname(hostname, HOSTNAME_LEN);

  snprintf(welcome, STR_LEN, "NRPC Test Server 0.1 (%s)", hostname);

  nrpc_init_server();
  nrpc_welcome(welcome);

  test_send_int(INT_MAX);
  test_send_int(INT_MIN);
  test_send_double(PI);
  test_send_double(DBL_MAX);
  test_send_double(DBL_MIN);
  test_send_string("This test is a very long string!");
  test_combo(3, PI, "The double is: ");
//  nrpc_reverse();
//  echo_data();

  nrpc_exit();
  nrpc_close();

  wlog_close();

  close (log_fd);
  echo_on();
  exit(0);
}

void
test2_get_line(void)
{
  byte l[BUFSIZ];

  uio_get_line(STDIN, l, BUFSIZ);
  uio_put_line(log_fd, l);

  if (strncmp(l, "exit", 4) == 0) {
    close(log_fd);
    exit (0);
  }

  if (strncmp(l, "reverse", 7) == 0) {
    uio_get_line(STDIN, l, BUFSIZ);
    uio_put_line(log_fd, l);
  }
}

