//
//   ssh_lib.h
//
//   12/06/04 - Chris Nystrom <cnystrom@gmail.com>
//
//   Inspired by script.c in RedHat FC2
//

#ifndef UIO
#include "uio.h"
#endif

#define USE_READ  (0)
#define USE_UIO   (1)

#define LOGIN_BAD  (1)
#define NO_PROG    (2)

#ifndef BUFSIZ
#define BUFSIZ (8192)
#endif

int  call_ssh(char *username, char *hostname, char *command);
int  call_scp(char *from_file, char *to_file);

int  read_ssh(byte *obuf, int count, int uio);
int  read_stdin(byte *obuf, int count);
int  write_ssh(byte *buf);
int  write_sshf(byte *format, ...);
int  write_stdout(byte *buf);
int  write_stdoutf(byte *format, ...);

void display_ssh(void);

int  verify_passwd(char *passwd);
int  passwd_prompt(char *buf);
int  check_login(char *buf);

void done_ssh(void);

