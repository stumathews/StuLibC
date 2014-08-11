


# This is so far a win32 platform specific makefile.
CC=gcc
CFLAGS=-I. -I arch/linux -I.. -fPIC -lc
OBJS=main.o console.o datastructures.o debugging.o encryption.o filemanagement.o keyboard.o libstring.o logging.o memory.o safetychecking.o testing.o timing.o
DEPS=main.c console.h datastructures.h debugging.h encryption.h filemanagement.h keyboard.h libstring.h logging.h memory.h safetychecking.h testing.h timing.h

# .c files depend on .h files (these changes should recompile .c files)
%.o: %.c $(DEPS)
	$(CC) -c $@ $< $(CFLAGS)

stulibc.so.1: $(OBJS)
	gcc -shared -Wl,-soname,$@ -o $@ $^ $(CFLAGS)