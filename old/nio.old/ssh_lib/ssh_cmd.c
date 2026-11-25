/*
*   ssh_cmd.c
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
#include "ssh_cmd.h"

int
ssh_cmd(char *username, char *hostname, char *command, char *passwd)
{
  int ret;

  ret = call_ssh(username, hostname, command);

  if (ret < 0) {
    printf("ssh failed\n");
    return (-1);
  }

  ret = verify_passwd(passwd);

  if (ret < 0) {
    printf("login or password bad.\n");
    return (-2);
  }

  display_ssh();

  return (0);
}

