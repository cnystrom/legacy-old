/*
 * server.c
 */

#include "example.h"

#define STR_LEN		(128)

int
main(void)
{
  char hostname[HOSTNAME_LEN];
  char welcome[STR_LEN];

  gethostname(hostname, HOSTNAME_LEN);

  snprintf(welcome, STR_LEN, "NRPC Test Server 0.1 (%s)", hostname);

  nrpc_init_server(PORTNUM);
  nrpc_welcome(welcome);
  echo_data();
  nrpc_close();
  exit(0);
}

