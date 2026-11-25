//
//   ssh_lib.c
//
//   12/03/04 - Chris Nystrom <cnystrom@gmail.com>
//

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>
#include <pty.h>     // Linux
//#include <util.h>    // OS X
#include <sys/ioctl.h>
#include "../misc_lib/uio.h"
#include "ssh_lib.h"

#ifndef NEWLINE
#define NEWLINE  (10);
#endif

int  get_master(void);
void get_slave(void);
void set_tty(void);
void fail(void);
int  passwd_prompt(char *s);

int master;
int slave;
int child;

struct termios tt;
struct winsize win;

char progname[BUFSIZ];

int
call_ssh(char *username, char *hostname, char *command)
{
  int ret;

  ret =  get_master();

  if (ret < 0) {
    return(ret);
  }

  set_tty();
  child = fork();

  if (child < 0) {
    perror("fork");
    fail();
  }

  if (child == 0) {
    get_slave();
    close(master);
    dup2(slave, STDIN_FILENO);
    dup2(slave, STDOUT_FILENO);
    dup2(slave, STDERR_FILENO);
    close(slave);
    execl("/usr/bin/ssh", "/usr/bin/ssh", "-e", "none", "-l", username,
      hostname, command, 0);
    perror("execl failed");
    fail();
    return 0;
  }

  strncpy(progname, command, strlen(command));

  close(slave);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &tt);
  return(master);
}

int
get_master(void)
{
  int ret;
  tcgetattr(STDIN_FILENO, &tt);
  ioctl(STDIN_FILENO, TIOCGWINSZ, (char *) &win);

  ret = openpty(&master, &slave, NULL, &tt, &win);

  if (ret < 0) {
    fprintf(stderr, "openpty failed\n");
//    wlog("openpty failed\n");
    fail();
  }

  return(ret);
}

void
get_slave(void)
{
  setsid();
  ioctl(slave, TIOCSCTTY, 0);
}

void
set_tty(void)
{
  struct termios rtt;

  rtt = tt;
  cfmakeraw(&rtt);
  rtt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &rtt);
}

void
fail(void)
{
  kill(0, SIGTERM);
  done_ssh();
}

void
done_ssh(void)
{
  if (child) {
    close(master);
  } else {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tt);
  }
}

int
read_ssh(byte *buf, int count, int uio)
{
  int ret;

//  wlog("--\nentering read_ssh()...\n");

  if (uio) {
//    printf("using uio.\n");
    ret = uio_get_line(master, buf, count);
  }
  else {
//    printf("not using uio.\n");
    ret = read(master, buf, count);
  }

  if (ret < 0) {
    *buf = '\0';
  }
  else {
    *(buf + ret) = '\0';
  }

//  wlog("read_ssh(): buf = |%s|\n\n", buf);

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

//  wlog("read_ssh(): ret = %d\n", ret);
//  wlog("exiting read_ssh()...\n\n");

  return(ret);
}

int
write_ssh(byte *ibuf)
{
  int i;
  int count = 0;
  int ret = 0;
  byte tempBuf[BUFSIZ] = {0};

//  wlog("write_ssh(): ibuf = |%s|\n", (char *) ibuf);

  count = strlen(ibuf);

  if (count > (BUFSIZ - 1)) {
    count = (BUFSIZ - 1);
//    wlog("count adjusted.\n");
  }

//  wlog("--\nwrite_ssh(): count = %d\n", count);

  for (i = 0; i < count; i++) {
    tempBuf[i] = *(ibuf + i);
  }

  tempBuf[i++] = NEWLINE;
  count++;

  tempBuf[i] = 0;

//  wlog("write_ssh(): tempBuf = |%s|\n", tempBuf);

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

  ret = uio_put_line(master, tempBuf);

//  ret = write(master, tempBuf, (count + 2));
//  ret = write(master, ibuf, count);

//  wlog("count = %d\n", count);
//  wlog("ret   = %d\n", ret);

  if (ret != count) {
//    wlog("write_ssh(): write error.\n");
//    wlog("(count + 2) = %d\n", (count + 2));
//    wlog("ret = %d\n", ret);
    fprintf(stderr, "write_ssh(): write error.\n");
    fprintf(stderr, "write_ssh(): count = %d.\n", count);
    fprintf(stderr, "write_ssh(): ret = %d.\n", ret);
    fprintf(stderr, "write_ssh(): ibuf = |%s|.\n", ibuf);
    fprintf(stderr, "write_ssh(): tempBuf = |%s|.\n", tempBuf);
  }

//  wlog("--\n");

  return(ret);
}

int
write_sshf(byte *format, ...)
{
  int ret = 0;
  byte l[BUFSIZ] = {0};
  va_list ap;

  va_start(ap, format);
  vsprintf(l, format, ap);
  va_end(ap);

  ret = write_ssh(l);

  return(ret);
}

void
display_ssh(void)
{
  int cc = 0;    // char count
  int flag = 1;  // flag for login check
  int ret = 0;
  char buf[BUFSIZ] = {0};

  cc = read_ssh(buf, BUFSIZ, USE_UIO);

  while(cc > 0) {

    if (flag) {
      ret = check_login(buf);

      if (ret == LOGIN_BAD) {
        printf("error(): login bad.\n");
        done_ssh();
        return;
      }
      else if (ret == NO_PROG) {
        printf("error(): program missing.\n");
        done_ssh();
        return;
      }
      else {
        flag = 0;
      }
    }

    printf(buf);
    cc = read_ssh(buf, BUFSIZ, USE_UIO);
  }

  done_ssh();
}

int
verify_passwd(char *passwd)
{
  int cc = 0;  // char count
  char buf[BUFSIZ] = {0};

//  wlog("passwd = %s\n", passwd);

  cc = read_ssh(buf, BUFSIZ, USE_READ);

//  wlog("ssh cc # = %d\n", cc);

  while (cc > 0) {

    buf[cc] = 0;

//    wlog("buf = |%s|\n", buf);

    if (passwd_prompt(buf)) {
//      wlog("password prompt recieved.\n");
      write_ssh(passwd);
//      wlog("password sent.\n");
      return 0;
    }

    cc = read_ssh(buf, BUFSIZ, USE_READ);
  }

//  wlog("password verification failed\n");
  done_ssh();
  return (-1);
}

//
// Function
//
int
passwd_prompt(char *s)
{
  int len;
 
  len = strlen(s);
//  wlog("len = %d\n", len);
 
  if (len <= 9) {
//    wlog("-= no password match =- 1\n");
    return 0;
  }

  if (strncmp(s + len - 9, "assword: ", 9) == 0) {
//    wlog("-= password prompt =-\n");
    return 1;
  }
  else {
//    wlog("-= not password prompt =- 2\n");
    return 0;
  }
}

int
check_login(char *buf)
{
//  wlog("passwd_failed(): buf = |%s|\n", buf);

  if (strncmp(buf, "Permission denied", 17) == 0) {
//    wlog("password failed\n");
    return LOGIN_BAD;
  }
  else if (strncmp(buf, "bash", 4) == 0) {
//    wlog("program not there.\n");
    return NO_PROG;
  }
  else {
//    wlog("password ok\n");
    return 0;
  }
}

