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
                    functions/low/memory/memory.c
#                    functions/low/networking/wincompat.c


libstu_la_LDFLAGS = -no-undefined -version-info 0:0:0



