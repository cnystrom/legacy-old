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
#include "../misc_lib/uio.h"
#include "../misc_lib/tty_echo.h"
#include "../misc_lib/wlog.h"
#include "stdio_lib.h"

void test2_get_line(void);

int
main(void)
{
  int i = 0;

  echo_off();

  wlog_init_file("test2b.log");

  while (1) {
    i++;

    // Tell client exiting after 10 lines
    if (i == 10) {
      wlog("server -> client: exit\n");
      write_stdout("exit");
      wlog_close();
      echo_on();
      exit (0);
    }
    else { 
      wlog("Server: Welcome to line %d!\n", i);
      write_stdoutf("Server: Welcome to line %d!", i);
    }

    test2_get_line();
  }

  wlog_close();
  echo_on();
  exit(0);
}

void
test2_get_line(void)
{
  byte l[BUFSIZ];

  read_stdin(l, BUFSIZ);
  wlog(l);

  if (strncmp(l, "exit", 4) == 0) {
    wlog_close();
    exit (0);
  }
}

