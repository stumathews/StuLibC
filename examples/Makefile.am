exampledir = $(datarootdir)/doc/@PACKAGE@
example_DATA = sample1.dat sample2.dat

AM_CPPFLAGS = -I$(top_builddir)/src/includes


bin_PROGRAMS	= listen \
				  say \
				  cmd

# Build tests - directly linking (not using the above @LIBSTU_DLL_IMPORT@

TESTS=$(check_PROGRAMS)

listen_SOURCES = listen.c
listen_LDADD = $(top_builddir)/src/libstu.la 

say_SOURCES = say.c
say_LDADD = $(top_builddir)/src/libstu.la 

cmd_SOURCES = cmd.c
cmd_LDADD = $(top_builddir)/src/libstu.la 

