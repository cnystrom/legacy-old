/*
*   test.c
*
*   12/06/04 - Chris Nystrom <cnystrom@gmail.com>

*/

#include <stdio.h>
#include <stdlib.h>
#include "uio.h"
#include "wlog.h"
#include "tty_echo.h"
#include "scp_file.h"
#include "ssh_cmd.h"

int
main(void)
{
  char password[10] = "CHANGEME";

  echo_off();

  password[8] = 10;
  password[9] = 0;

  wlog_init_file("test1.log");

  wlog("\n*** SCP Test ***\n\n");

  printf("\nCopying ssh_lib.022105.tar to macmini...\n\n");

  scp_file("/home/cnystrom/src/store/ssh_lib.022105.tar",
           "macmini.newio.org:/Users/cnystrom/",
           password);

  wlog("\n*** SSH Test ***\n\n");

  printf("\nGetting directory listing at macmini.newio.org...\n\n");

  ssh_cmd("cnystrom", "macmini.newio.org", "ls", password);

  printf("\n");

  wlog_close();

  echo_on();

  exit(0);
}

