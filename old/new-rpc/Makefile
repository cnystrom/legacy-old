#
CC =  gcc
BIN = server client
LIB = -lnsl  # Linux
#LIB = -lnsl -lsocket # Solaris

CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX

all: $(BIN)

server:		server.o example.o new_rpc.a
		$(CC) -o $@ server.o example.o new_rpc.o msg_lib.o sock_lib.o $(LIB)

client:		client.o example.o new_rpc.a
		$(CC) -o $@ client.o example.o new_rpc.o msg_lib.o  sock_lib.o $(LIB)

new_rpc.a:	new_rpc.o msg_lib.o sock_lib.o
		ar rcs new_rpc.a new_rpc.o sock_lib.o msg_lib.o
		ranlib new_rpc.a

sock_lib.o:	sock_lib.c sock_lib.h
		$(CC) $(CFLAGS) -c sock_lib.c

msg_lib.o:	msg_lib.c msg_lib.h
		$(CC) $(CFLAGS) -c msg_lib.c

new_rpc.o:	new_rpc.c new_rpc.h msg_lib.h sock_lib.h
		$(CC) $(CFLAGS) -c new_rpc.c

example.o:	example.c example.h
		$(CC) $(CFLAGS) -c example.c

server.o:	server.c example.h new_rpc.h sock_lib.h
		$(CC) $(CFLAGS) -c server.c

client.o:	client.c example.h new_rpc.h sock_lib.h
		$(CC) $(CFLAGS) -c client.c

install:
		cp *.a ..

new:		clean all

clean:
		rm -f *.o *.a $(BIN) core

