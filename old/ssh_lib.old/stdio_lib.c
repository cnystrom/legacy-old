//
//   stdio_lib.c
//
//   12/03/04 - Chris Nystrom <cnystrom@gmail.com>
//

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "../misc_lib/uio.h"
//#include "wlog.h"
#include "stdio_lib.h"

int
read_stdin(byte *buf, int count)
{
  int ret = 0;

//  wlog("--\nentering read_stdin()...\n");

  ret = uio_get_line(STDIN, buf, count);

  if (ret < 0) {
    *buf = '\0';
  }
  else {
    *(buf + ret) = '\0';
  }

//  wlog("read_stdin(): buf = |%s|\n\n", buf);

/*
  if (ret > 0) {
    int i;

    for (i=0; i < ret; i++) {
      int n = *(buf + i);

      wlog("buf[%d] ", i);

      if (i < 100)
        wlog(" ");

      if (i < 10)
        wlog(" ");

      wlog("= %d ", n);

      if (n < 100)
        wlog(" ");

      if (n < 10)
        wlog(" ");

      wlog("%c\n", n);
    }
  }
*/

//  wlog("read_stdin(): ret = %d\n", ret);
//  wlog("exiting read_stdin()...\n\n");

  return(ret);
}

int
write_stdout(byte *ibuf)
{
  int i = 0;
  int count = 0;
  int ret = 0;
  byte tempBuf[BUFSIZ] = {0};

//  wlog("write_stdout(): ibuf = |%s|\n", (char *) ibuf);

  count = strlen(ibuf);

  if (count > (BUFSIZ - 1)) {
    count = (BUFSIZ - 1);
//    wlog("count adjusted.\n");
  }

//  wlog("--\nwrite_stdout(): count = %d\n", count);

  for (i = 0; i < count; i++) {
    tempBuf[i] = *(ibuf + i);
  }

  tempBuf[i++] = NEWLINE;
  count++;

  tempBuf[i] = 0;

//  wlog("write_stdout(): tempBuf = |%s|\n", tempBuf);

/*
  for (i=0; i < (count + 2); i++) {
    int n = *(tempBuf + i);

    wlog("tempBuf[%d] ", i);

    if (i < 100)
      wlog(" ");

    if (i < 10)
      wlog(" ");

    wlog("= %d ", n);

    if (n < 100)
      wlog(" ");

    if (n < 10)
      wlog(" ");

    wlog("%c\n", n);
  }
*/

  ret = uio_put_line(STDOUT, tempBuf);

//  ret = write(master, tempBuf, (count + 2));

//  wlog("count = %d\n", count);
//  wlog("ret   = %d\n", ret);

  if (ret != count) {
//    wlog("write_stdout(): write error.\n");
//    wlog("(count + 2) = %d\n", (count + 2));
//    wlog("ret = %d\n", ret);
    fprintf(stderr, "write_stdout(): write error.\n");
  }

//  wlog("--\n");

  return(ret);
}

int
write_stdoutf(byte *format, ...)
{
  int ret = 0;
  byte l[BUFSIZ] = {0};
  va_list ap;

  va_start(ap, format);
  vsprintf(l, format, ap);
  va_end(ap);

  ret = write_stdout(l);

  return(ret);
}

