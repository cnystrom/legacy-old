#
CC =  gcc
BIN = test1 test2 test2b
#LIB = # -lutil # OS X
LIB = -lutil  # Linux
 
CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX
 
all: $(BIN)
 
test1:		test1.o ssh_cmd.o ssh_lib.a ../misc_lib/misc_lib.a
		$(CC) -o $@ test1.o ssh_cmd.o ssh_lib.a ../misc_lib/misc_lib.a $(LIB)
 
test2:		test2.o ssh_lib.a ../misc_lib/misc_lib.a
		$(CC) -o $@ test2.o ssh_lib.a ../misc_lib/misc_lib.a $(LIB)
 
test2b:		test2b.o stdio_lib.o ../misc_lib/misc_lib.a 
		$(CC) -o $@ test2b.o stdio_lib.o ../misc_lib/misc_lib.a $(LIB)

ssh_lib.a:	ssh_lib.o ssh_cmd.o
		ar rcs ssh_lib.a ssh_lib.o ssh_cmd.o
		ranlib ssh_lib.a

test1.o:	test1.c ssh_cmd.h
		$(CC) $(CFLAGS) -c test1.c

test2.o:	test2.c
		$(CC) $(CFLAGS) -c test2.c

test2b.o:	test2b.c
		$(CC) $(CFLAGS) -c test2b.c

ssh_lib.o:	ssh_lib.c ssh_lib.h
		$(CC) $(CFLAGS) -c ssh_lib.c

stdio_lib.o:	stdio_lib.c stdio_lib.h
		$(CC) $(CFLAGS) -c stdio_lib.c

ssh_cmd.o:	ssh_cmd.c ssh_cmd.h ssh_lib.c ssh_lib.h
		$(CC) $(CFLAGS) -c ssh_cmd.c

install:
		cp *.a ..

new:
		make clean
		make all
 
clean:
		rm -f *.o *.a *.log $(BIN) core a.out
 
