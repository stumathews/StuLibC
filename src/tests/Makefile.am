AM_CPPFLAGS = -I$(top_builddir)/src/includes

bin_PROGRAMS	= cmdline \
                  debugging \
                  strings \
                  files \
                  testing \
                  errors \
                  logging \
                  timing \
                  memory \
                  safetychecking \
                  uselib \
				  tcpclient \
                  tcpserver \
				  udpserver \
				  udpclient \
				  vrs \
				  vrc

#Build a test harness program

uselib_SOURCES	= uselib.c
uselib_LDADD	= $(top_builddir)/src/libstu.la

uselib.o: uselib.c
	$(COMPILE) @LIBSTU_DLL_IMPORT@ -c uselib.c

# Build tests - directly linking (not using the above @LIBSTU_DLL_IMPORT@

TESTS=$(check_PROGRAMS)
check_PROGRAMS= $(bin_PROGRAMS)

tcpserver_SOURCES = tcpserver.c
tcpserver_LDADD = $(top_builddir)/src/libstu.la 

udpserver_SOURCES = udpserver.c
udpserver_LDADD = $(top_builddir)/src/libstu.la 

tcpclient_SOURCES = tcpclient.c
tcpclient_LDADD = $(top_builddir)/src/libstu.la 

udpclient_SOURCES = udpclient.c
udpclient_LDADD = $(top_builddir)/src/libstu.la 

vrc_SOURCES = vrc.c
vrc_LDADD = $(top_builddir)/src/libstu.la 

vrs_SOURCES = vrs.c
vrs_LDADD = $(top_builddir)/src/libstu.la 

safetychecking_SOURCES = safetychecking.c
safetychecking_LDADD = $(top_builddir)/src/libstu.la

memory_SOURCES = memory.c
memory_LDADD = $(top_builddir)/src/libstu.la

cmdline_SOURCES = cmdline.c
cmdline_LDADD = $(top_builddir)/src/libstu.la

timing_SOURCES = timing.c
timing_LDADD = $(top_builddir)/src/libstu.la

logging_SOURCES = logging.c
logging_LDADD = $(top_builddir)/src/libstu.la
    
errors_SOURCES = errors.c
errors_LDADD = $(top_builddir)/src/libstu.la

debugging_SOURCES = debugging.c
debugging_LDADD = $(top_builddir)/src/libstu.la

strings_SOURCES = strings.c
strings_LDADD = $(top_builddir)/src/libstu.la

files_SOURCES = files.c
files_LDADD = $(top_builddir)/src/libstu.la

testing_SOURCES = testing.c
testing_LDADD = $(top_builddir)/src/libstu.la

