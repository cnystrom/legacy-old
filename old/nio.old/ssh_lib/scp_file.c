/*
*   scp_file.c
*
*   12/06/04 - Chris Nystrom <cnystrom@gmail.com>

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "uio.h"
#include "tty_echo.h"
#include "ssh_lib.h"
#include "scp_file.h"

int
scp_file(char *from_file, char *to_file, char *passwd)
{
  int ret;

  ret = call_scp(from_file, to_file);

  if (ret < 0) {
    printf("scp failed\n");
    echo_on();
    return (-1);
  }

  ret = verify_passwd(passwd);

  if (ret < 0) {
    printf("login or password bad.\n");
    echo_on();
    return (-2);
  }

  display_ssh();

  return (0);
}

