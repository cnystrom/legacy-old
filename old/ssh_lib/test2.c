//
//    test2.c
//
//    02/02/05 - Chris Nystrom <cnystrom@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "uio.h"
#include "wlog.h"
#include "tty_echo.h"
#include "ssh_lib.h"

int test2(char *username, char *hostname, char *command, char *passwd);
int main_loop(void);


int
main(void)
{
  int ret;
  char password[10] = "CHANGEME";

  echo_off();

  wlog_init_file("test2.log");

  printf("\nLoading server on shuttle.newio.org...\n\n");

  ret = test2("cnystrom", "shuttle.newio.org", "src/nrpc/server", password);

  if (ret < 0) {
    printf("ssh failed\n");
  }

  printf("\n");
  wlog_close();
  echo_on();
  exit(0);
}

int
test2(char *username, char *hostname, char *command, char *passwd)
{
  int ret;

  ret = call_ssh(username, hostname, command);

  if (ret < 0)
    return (ret);

  ret = verify_passwd(passwd);

  if (ret < 0)
    return (ret);

  return(main_loop());
}

int
main_loop(void)
{
  int cc;        // char count
  int flag = 1;  // Flag to keep track of first line read
  int ret;       
  char buf[BUFSIZ];

  cc = read_ssh(buf, BUFSIZ, USE_UIO);

  wlog("ssh cc # = %d\n", cc);

  while(cc > 0) {
    while (cc <= 2) {
      wlog("cc <= 2. Bad packet.\n");
      write_ssh("\n");
      wlog("Re-reading...\n");
      cc = read_ssh(buf, BUFSIZ, USE_UIO);
      wlog("Re-read.\n");
    }

    buf[cc] = 0;

    printf("server -> client: |%s|\n", buf);

    if (flag) {
      ret = check_login(buf);

      if (ret == LOGIN_BAD) {
        printf("login or password bad. Sorry!\n");
        done_ssh();
        return (-1);
      }
      else if (ret == NO_PROG) {
        printf("Program not available. Sorry!\n");
        done_ssh();
        return (-1);
      }
      else {
        flag = 0;
      }
    }

    if (strncmp(buf, "exit", 4) == 0) {
      printf("normal exit.\n");
      done_ssh();
      return 0;
    }

    write_ssh("ACK");

    printf("client -> server: ACK\n");
    printf("---------------------\n");

    cc = read_ssh(buf, BUFSIZ, USE_UIO);
  }

  wlog("exiting ssh_rpc()\n");
  done_ssh();
  return (-1);
}

