#Build the library

lib_LTLIBRARIES = libstu.la
libstu_la_SOURCES = functions/low/debugging/debugging.c \
		    functions/low/timing/timing.c \
		    functions/low/safety/safetychecking.c \
		    functions/low/logging/logging.c \
		    functions/low/file/files.c \
		    functions/low/console/console.c \
		    functions/low/error/errors.c \
                    functions/low/strings/strings.c \
                    functions/low/testing/testing.c \
                    functions/high/parsing/cmdline/cmdline.c \
                    functions/low/memory/memory.c \
					etcp/error.c etcp/readcrlf.c etcp/readline.c etcp/readn.c etcp/readvrec.c etcp/set_address.c \
					etcp/tcp_client.c etcp/tcp_server.c etcp/udp_client.c etcp/udp_server.c
libstu_la_LDFLAGS = -no-undefined -version-info 0:0:0



