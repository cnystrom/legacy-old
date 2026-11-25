/*
 * client.c
 */

#include "example.h"

int
main(void)
{
  char hostname[HOSTNAME_LEN];

  gethostname(hostname, HOSTNAME_LEN);

  printf("hostname = %s\n", hostname);

  nrpc_init_client("cnystrom", "localhost", "/Users/cnystrom/src/nrpc/server",
    "CHANGEME");

  echo_data();

  nrpc_exit();
  nrpc_close();

  exit(0);
}


