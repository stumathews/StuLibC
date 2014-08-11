CC=gcc
CFLAGS=-I. -I arch\win32
OBJS=main.o console.o datastructures.o debugging.o encryption.o filemanagement.o keyboard.o libstring.o logging.o memory.o safetychecking.o testing.o timing.o 
DEPS=main.c console.h datastructures.h debugging.h encryption.h filemanagement.h keyboard.h libstring.h logging.h memory.h safetychecking.h testing.h timing.h 


# .c files depend on .h files (these changes should recompile .c files)
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

stulibc.dll: $(OBJS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ -Wl,--out-implib,stulibc.lib $(CFLAGS)
	
clean:
	rm  *.o
	rm  arch/win32/*.o
	rm *.exe
	rm *.dll 