CC=gcc
CFLAGS=-I. -I arch\win32 -I datastructures -I encryption -I parsing -I strings
OBJS=main.o console\console.o datastructures\datastructures.o debugging\debugging.o encryption\encryption.o \
filemanagement\filemanagement.o keyboard\keyboard.o strings\libstring.o logging\logging.o memory\memory.o \
safety\safetychecking.o testing\testing.o timing\timing.o strings/substring.o encryption/isaac.o \
encryption/vigenere.o datastructures\simple_hashtable.o encryption\caesar.o
DEPS=main.c console\console.h datastructures\datastructures.h debugging\debugging.h encryption\encryption.h \
filemanagment\filemanagement.h keyboard\keyboard.h strings\libstring.h logging\logging.h memory\memory.h \
safety\safetychecking.h testing\testing.h timing\timing.h datastructures\binary_tree.h \
encryption\vigenere.h encryption\isaac.h strings\tokenizer.h strings\substring.h \
datastructures\simple_hashtable.h encryption\caesar.h


# .c files depend on .h files (these changes should recompile .c files)
%.o: %.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

#Make Win32 run-time library
stulibc.dll: $(OBJS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ -Wl,--out-implib,stulibc.lib $(CFLAGS)
	


clean:
	rm  *.o
	rm  arch/win32/*.o
	rm *.exe
	rm *.dll
	rm *.lib 
