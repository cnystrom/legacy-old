/*
 * example.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>
#include "new_rpc.h"

#define HOSTNAME_LEN    (32)

#define PORTNUM   32662

/* Function numbers */

#define SEND_INT       (0)
#define SEND_DBL       (1)
#define SEND_STR       (2)
#define COMBO          (3)

#define PI	(3.141592653)

void echo_data(void);

int  test_send_int(int i);        // SEND_INT
int  test_send_double(double d);  // SEND_DBL
int  test_send_string(char *s);   // SEND_STR
int  test_combo(int i, double d, char *s);  // COMBO

int  test_string(char *s);
int do_combo(int i, double d, char *s);

