//
//    test2b.c
//
//    Chris Nystrom
//
//    02/04/05
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "uio.h"
#include "tty_echo.h"

void test2_get_line(void);

int log_fd;

int
main(void)
{
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

