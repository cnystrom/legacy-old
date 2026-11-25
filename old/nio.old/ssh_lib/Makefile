#
CC =  gcc
BIN = test1 test2 test2b
#LIB = # -lutil # OS X
LIB = -lutil  # Linux
 
CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX
 
all: $(BIN)
 
test1:		test1.o scp_file.o ssh_cmd.o ssh_lib.a
		$(CC) -o $@ test1.o scp_file.o ssh_cmd.o ssh_lib.a $(LIB)
 
test2:		test2.o ssh_lib.a
		$(CC) -o $@ test2.o ssh_lib.a $(LIB)
 
test2b:		test2b.o ssh_lib.a
		$(CC) -o $@ test2b.o ssh_lib.a $(LIB)

ssh_lib.a:	ssh_lib.o uio.o wlog.o tty_echo.o
		ar rcs ssh_lib.a ssh_lib.o uio.o wlog.o tty_echo.o
		ranlib ssh_lib.a

test1.o:	test1.c scp_file.h ssh_cmd.h
		$(CC) $(CFLAGS) -c test1.c

test2.o:	test2.c
		$(CC) $(CFLAGS) -c test2.c

test2b.o:	test2b.c
		$(CC) $(CFLAGS) -c test2b.c

tty_echo.o:	tty_echo.c tty_echo.h
		$(CC) $(CFLAGS) -c tty_echo.c

uio.o:		uio.c uio.h
		$(CC) $(CFLAGS) -c uio.c

wlog.o:		wlog.c wlog.h
		$(CC) $(CFLAGS) -c wlog.c

ssh_lib.o:	ssh_lib.c ssh_lib.h
		$(CC) $(CFLAGS) -c ssh_lib.c

scp_file.o:	scp_file.c scp_file.h ssh_lib.c ssh_lib.h
		$(CC) $(CFLAGS) -c scp_file.c

ssh_cmd.o:	ssh_cmd.c ssh_cmd.h ssh_lib.c ssh_lib.h
		$(CC) $(CFLAGS) -c ssh_cmd.c

install:
		cp *.a ..

new:
		make clean
		make all
 
clean:
		rm -f *.o *.a *.log $(BIN) core a.out
 
