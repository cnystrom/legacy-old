#
CC =  gcc
BIN = client server server2
#LIB = # -lutil
LIB = -lutil  # Linux
 
CFLAGS = -I../ssh_lib -O -Wall -g -DDEBUG -DUNIX
 
all: $(BIN)
 
server:		server.o new_rpc.a ../ssh_lib/ssh_lib.a ../misc_lib/misc_lib.a
		$(CC) -o $@ server.o new_rpc.a ../ssh_lib/ssh_lib.a ../misc_lib/misc_lib.a $(LIB)
 
server2:		server2.o new_rpc.a ../ssh_lib/ssh_lib.a ../misc_lib/misc_lib.a
		$(CC) -o $@ server2.o new_rpc.a ../ssh_lib/ssh_lib.a ../misc_lib/misc_lib.a $(LIB)

client:		client.o new_rpc.a ../ssh_lib/ssh_lib.a ../misc_lib/misc_lib.a
		$(CC) -o $@ client.o new_rpc.a ../ssh_lib/ssh_lib.a ../misc_lib/misc_lib.a $(LIB)

new_rpc.a:	new_rpc.o msg_lib.o 
		ar rcs new_rpc.a new_rpc.o msg_lib.o 
		ranlib new_rpc.a

msg_lib.o:	msg_lib.c msg_lib.h
		$(CC) $(CFLAGS) -c msg_lib.c

new_rpc.o:	new_rpc.c new_rpc.h msg_lib.h
		$(CC) $(CFLAGS) -c new_rpc.c

example.o:	example.c example.h
		$(CC) $(CFLAGS) -c example.c

server.o:	server.c new_rpc.h
		$(CC) $(CFLAGS) -c server.c

server2.o:	server2.c new_rpc.h
		$(CC) $(CFLAGS) -c server2.c

client.o:	client.c new_rpc.h
		$(CC) $(CFLAGS) -c client.c

install:
		cp *.a ..

new:
		make clean
		make all
 
clean:
		rm -f *.o *.a *.log $(BIN) core a.out ../../*.log
 
