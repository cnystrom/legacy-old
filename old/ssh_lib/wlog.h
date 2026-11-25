/*
 * wlog.h
 *
 * write log: basic logging mechanism
 *
 * Chris Nystrom
 *
 * (c) 2004
 *
 */

int  wlog_init_file(char *pathname);
void wlog_init_fd(int fd_in);
int  wlog(const char *format, ...);
int  wlog_close(void);

