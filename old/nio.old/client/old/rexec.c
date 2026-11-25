/*
	rexec.c

	Modified from KipTOOLS - (C) Angel Ortega
*/

#ifdef UNIX
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif

#ifdef WIN32

#include <winsock.h>

WSADATA wsadata;

#endif

#define REXEC   512

int
buildcmd(char *buf, char *name, char *pass, char *cmd)
{
  *buf=0;
  buf++;

  strcpy(buf,name);
  buf+=strlen(name)+1;
  strcpy(buf,pass);
  buf+=strlen(pass)+1;
  strcpy(buf,cmd);

  return(4+strlen(name)+strlen(pass)+strlen(cmd));
}

int
my_rexec(char *host, char *user, char *password, char *command)
{
//  int c;
  int l, s, cmdlen;
  struct hostent *h;
  struct sockaddr_in server;
  char cmd[300] = "";
  char str[4096];

/*
  printf("host    = %s\n", host);
  printf("user    = %s\n", user);
  printf("passwd  = %s\n", password);
  printf("command = %s\n", command);
*/

#ifdef WIN32
  if(WSAStartup(0x0101, &wsadata))
  {
    WSACleanup();

    printf("my_rexec() error: init failed\n");
    return(-1);
  }
#endif

  if((h = gethostbyname(host)) == NULL)
  {
#ifdef WIN32
    WSACleanup();
#endif

    printf("my_rexec() error: host not found\n");
    return(-1);
  }

  memcpy((char *) &server.sin_addr, (char *)h-> h_addr, h->h_length);

  server.sin_family = AF_INET;
  server.sin_port = htons(REXEC);

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
#ifdef WIN32
    WSACleanup();
#endif

    printf("my_rexec() error: socket failed\n");
    return(-1);
  }

  if ((connect(s, (struct sockaddr *) &server, sizeof(server))) == -1)
  {
#ifdef WIN32
    WSACleanup();
#endif

    printf("my_rexec() error: connect failed\n");
    return(-1);
  }

  cmdlen = buildcmd(cmd, user, password, command);

  send(s, cmd, cmdlen, 0);

  if((l = recv(s, str, sizeof(str) - 1, 0)) == -1)
  { 
#ifdef WIN32
    WSACleanup();
#endif

    printf("my_rexec() error: rexec failed\n");
    return(-1);
  }

  if (l == 0)
  {
#ifdef WIN32
    WSACleanup();
#endif

    printf("my_rexec() error: login failed\n");
    return(-1);
  }

  str[l] = 0;

  if(str[0] == 1)
  {
#ifdef WIN32
    WSACleanup();
#endif

    printf("my_rexec() error: rexec error\n");
    return(-1);
  }

  if (close(s) == -1)
  {
#ifdef WIN32
    WSACleanup();
#endif

    printf("my_rexec() error: close failed\n");
    return(-1);
  }

  return(0);
}

