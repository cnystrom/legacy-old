#the compiler
CC = gcc

#compiler options

# Linux
COPTS = -O3 -g -Wall $(shell sdl-config --cflags)
# Solaris
#COPTS = -O3 -g -Wall -I/usr/local/include/SDL -D_REENTRANT -Wno-deprecated 

#header files
INCLUDES = \
	-I../nio_lib \
	-I../new_rpc \
	-I../ssh_lib \
	-I. \
	$(NULL)

#library directories
LIBDIRS = \
	$(NULL)

SSH_LIB = ../ssh_lib/ssh_lib.a
NRPC_LIB = ../new_rpc/new_rpc.a
NIO_LIB = ../nio_lib/nio_lib.a

#libraries to link with
LIBS = \
	-lutil \
	-lSDL_ttf \
	-lSDL_image \
	-lSDL_mixer \
	$(NRPC_LIB) \
	$(NIO_LIB) \
	$(SSH_LIB) \
	$(NULL)

#all compiler flags
CFLAGS = $(COPTS) $(INCLUDES) -DUNIX

#all linker options and libs
LFLAGS = $(LIBDIRS) $(shell sdl-config --libs) -lSDL_mixer

#default compilation rules
%.o:	%.c
	$(CC) -c $< $(CFLAGS) -o $@

#local headers to depend on
HEADERS = \
	$(NULL)

#files to compile
CCFILES = \
	screen.c \
	misc_io.c \
	images.c \
	home_dir.c \
	file_xfr.c \
	nio_sdl.c \
	mouse.c \
	keyboard.c \
	url.c \
	misc.c \
	term.c \
	rpc.c \
	loop.c \
	main.c \
	text_box.c \
	$(NULL)

#all local .o files
OBJS =  ${CCFILES:.c=.o}

default: nlogin

nlogin: $(OBJS) $(HEADERS) 
	$(CC) $(LFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	rm -f core $(OBJS) nlogin *~

new: clean default

