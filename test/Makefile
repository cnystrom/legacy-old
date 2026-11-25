#
CC =  gcc
BIN = server
LIB = -lnsl  # Linux
#LIB = -lnsl -lsocket # Solaris

CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX

all: $(BIN)

server:		server.o ../misc_lib/misc_lib.a
		$(CC) -o $@ server.o ../misc_lib/misc_lib.a $(LIB)

new_rpc.a:	new_rpc.o buffer.o sock_lib.o
		ar rcs new_rpc.a new_rpc.o sock_lib.o buffer.o
		ranlib new_rpc.a

buffer.o:	buffer.c buffer.h types.h
		$(CC) $(CFLAGS) -c buffer.c

new_rpc.o:	new_rpc.c new_rpc.h buffer.h sock_lib.h
		$(CC) $(CFLAGS) -c new_rpc.c

example.o:	example.c example.h
		$(CC) $(CFLAGS) -c example.c

server.o:	server.c 
		$(CC) $(CFLAGS) -c server.c

client.o:	client.c example.h new_rpc.h sock_lib.h
		$(CC) $(CFLAGS) -c client.c

install:
		cp *.a ..

new:		clean all

clean:
		rm -f *.o *.a *.log a.out $(BIN) core

