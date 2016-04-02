#Build the library from source files
#Uncomment this to check warnings and treat them as errors
#AM_CPPFLAGS = -Wall -Werror

lib_LTLIBRARIES = libstu.la
libstu_la_SOURCES = functions/private/stulibc.c \
	  	    functions/low/debugging/debugging.c \
		    functions/low/timing/timing.c \
		    functions/low/safety/safetychecking.c \
		    functions/low/logging/logging.c \
		    functions/low/file/files.c \
		    functions/low/console/console.c \
		    functions/low/error/errors.c \
	        functions/low/strings/strings.c \
	        functions/low/strings/reverse.c \
        	functions/low/testing/testing.c \
           	functions/high/parsing/cmdline/cmdline.c \
            functions/low/memory/memory.c \
			functions/low/networking/error.c \
			functions/low/networking/readcrlf.c \
			functions/low/networking/readline.c \
			functions/low/networking/readn.c \
			functions/low/networking/readvrec.c \
			functions/low/networking/set_address.c \
			functions/low/networking/tcp_client.c \
			functions/low/networking/tcp_server.c \
			functions/low/networking/udp_client.c \
			functions/low/networking/udp_server.c \
			functions/low/networking/wincompat.c \
            functions/high/structures/list.c \
            functions/high/structures/linuxlist.c \
            functions/high/parsing/ini/iniscanner.c \
            functions/high/parsing/ini/ini.c \
            functions/low/threading/threading.c
libstu_la_LDFLAGS = -no-undefined -version-info 0:0:0



