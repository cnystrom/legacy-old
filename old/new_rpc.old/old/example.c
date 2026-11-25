/*
 * example.c
 */

#include "../ssh_lib/wlog.h"
#include "example.h"

void
echo_data(void)
{
  for (;;)
  {
    int i, func_num, ret;
    double d;
    char str[MSG_MAX_LEN];

    func_num = nrpc_get_function();
    wlog("func_num = %d\n", func_num);

    if (func_num == NRPC_EXIT)
    {
      printf("Exit command rcvd.\n");
      nrpc_close();
      exit(0);
    }
    if (func_num == NRPC_REVERSE)
    {
      printf("--\nReverse command rcvd.\n--\n");

      printf("Sending (int) 512\n");
      test_send_int(512);

      printf("Sending (double) -3.2662\n");
      test_send_double(-3.2662);

      printf("Sending a string.\n");
      test_send_string("This test is another very long string!");

      nrpc_exit();
      nrpc_close();
      exit(0);
    }
    else if (func_num == SEND_INT)
    {
      ret = msg_get_int();
      printf("rcvd = %d\n", ret);
      nrpc_std_response();
    }
    else if (func_num == SEND_DBL)
    {
      d = msg_get_double();
      printf("rcvd = %f\n", d);
      nrpc_std_response();
    }
    else if (func_num == SEND_STR)
    {
      msg_get_string(str);
      i = test_string(str);

      msg_reset();
      msg_put_int(i);
      nrpc_send_response();
    }
    else if (func_num == COMBO)
    {
      i = msg_get_int();
      d = msg_get_double();
      msg_get_string(str);

//      printf("i = %d\n", i);
//      printf("d = %f\n", d);
//      printf("str = %s\n", str);

      do_combo(i, d, str);

      nrpc_std_response();
    }
    else
    {
      printf("bad function number = %d\n", func_num);
      nrpc_close();
      return;
    }
  }
}

int
test_string(char *s)
{
  printf("s = %s\n", s);

  return(0);
}

int
do_combo(int i, double d, char *s)
{
  int j;

//  printf("do_combo(): s = %s\n", s);

  for (j = 0; j < i; j++)
    printf ("%s%.2f\n", s, d);
  
  return(0);
}

int
test_send_int(int i)
{
  int ret_code;

  nrpc_set_function(SEND_INT);
  msg_put_int(i);
  nrpc_send_message();
  ret_code = msg_get_int();

//  printf("Return Code: %d\n", ret_code);

  return(ret_code);
}

int
test_send_double(double d)
{
  int ret_code;

  nrpc_set_function(SEND_DBL);
  msg_put_double(d);
  nrpc_send_message();
  ret_code = msg_get_int();

//  printf("Return Code: %d\n", ret_code);

  return(ret_code);
}

int
test_send_string(char *s)
{
  int ret_code;

  nrpc_set_function(SEND_STR);
  msg_put_string(s);
  nrpc_send_message();
  ret_code = msg_get_int();

//  printf("Return Code: %d\n", i);

  return(ret_code);
}

int
test_combo(int i, double d, char *s)
{
  int ret_code;

//  printf("test_combo(): s = %s\n", s);

  nrpc_set_function(COMBO);
  msg_put_int(i);
  msg_put_double(d);
  msg_put_string(s);
  nrpc_send_message();
  ret_code = msg_get_int();

//  printf("Return Code: %d\n", ret_code);

  return(ret_code);
}

