//
//   stdio_lib.h
//
//   12/03/04 - Chris Nystrom <cnystrom@gmail.com>
//

#ifndef NEWLINE
#define NEWLINE  (10);
#endif

int read_stdin(byte *buf, int count);
int write_stdout(byte *ibuf);
int write_stdoutf(byte *format, ...);

