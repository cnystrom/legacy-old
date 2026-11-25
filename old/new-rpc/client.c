/*
 * client.c
 */

#include "example.h"

int
main(void)
{
  char hostname[HOSTNAME_LEN];

  gethostname(hostname, HOSTNAME_LEN);

  nrpc_init_client(hostname, PORTNUM);

  printf ("INT_MAX = %d\n", INT_MAX);
  test_send_int(INT_MAX);
  printf ("INT_MIN = %d\n", INT_MIN);
  test_send_int(INT_MIN);

/*
  printf("Sending PI...\n");
  test_send_double(PI);

  printf ("DBL_MAX = %f\n", DBL_MAX);
  test_send_double(DBL_MAX);

  printf ("DBL_MIN = %f\n", DBL_MIN);
  test_send_double(DBL_MIN);

  test_send_string("This test is a very long string!");

  printf("Testing combo...\n");
  test_combo(3, PI, "The double is: ");

  printf("--\nSENDING REVERSE\n--\n");

  nrpc_reverse();
  echo_data();
*/

  nrpc_exit();
  nrpc_close();

  exit(0);
}

