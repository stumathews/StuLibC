AC_INIT([libstuc], [0.0.1], [stumathews@gmail.com])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(src/includes/config.h:config.hin)
AC_PROG_CC
AC_PROG_CC_STDC
AC_C_CONST
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL
AC_CHECK_FUNCS(_open)
AM_INIT_AUTOMAKE([subdir-objects])
LIBSTU_DLL_IMPORT=
case "$host" in
	*-*-cygwin | *-*-mingw )
          if test X"$enable_shared" = Xyes; then
		AC_TRY_LINK_FUNC([libstu_is_dll],
				 [LIBSTU_DLL_IMPORT=-DLIBSTU_DLL_IMPORT])
	  fi
	  ;;
esac

AC_ARG_WITH(inspect,
								    [  --with-inspect           Inspect test suite errors],
										[ AC_DEFINE(INSPECT_ERRORS, 1, "Inspect test suite errors")],
										[ AC_DEFINE(INSPECT_ERRORS, 0, "Inspect test suite errors")])
AC_SUBST(LIBSTU_DLL_IMPORT)
AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([doc/Doxyfile])])

# Check system type - found at https://gnunet.org/svn/libmicrohttpd/configure.ac
AC_MSG_CHECKING([[for target host OS]])
case "$host_os" in
*darwin* | *rhapsody* | *macosx*)
     AC_DEFINE_UNQUOTED(__APPLE__,1,[This is an OS X system])     
     AC_MSG_RESULT([[$mhd_host_os]])
     CFLAGS="-no-cpp-precomp -fno-common $CFLAGS"
     mhd_host_os='Darwin'
     ;;
*linux*)
     AC_DEFINE_UNQUOTED(__linux__,1,[This is a Linux kernel])
     AC_DEFINE_UNQUOTED(HAVE_LISTEN_SHUTDOWN,1,[can use shutdown on listen sockets])   
     AC_MSG_RESULT([[$mhd_host_os]])
     AC_CHECK_HEADERS([sys/socket.h],[],AC_MSG_ERROR([Need socket library but not found]),[])
     mhd_host_os='Linux'
     AC_CHECK_LIB(pthread, pthread_create,[])
     LIBS="$LIBS -lpthread"
     ;;
*mingw*)     
     AC_DEFINE_UNQUOTED(_WIN32,1,[This is a Windows system])
     AC_DEFINE_UNQUOTED(MINGW,1,[This is a MinGW system])     
     AC_MSG_RESULT([[$mhd_host_os]])
     AC_CHECK_HEADERS(windows.h,[],AC_MSG_ERROR([Windows header flies not found]),[])
     AC_CHECK_HEADERS(ws2tcpip.h windows.h winsock2.h,[],AC_MSG_ERROR([Winsock2 headers are required for W32]),[])
     AC_CHECK_LIB([ws2_32],[main])
     LIBS="$LIBS -lws2_32"
     os_is_windows=yes
     os_is_native_w32=yes
     mhd_host_os='Windows (MinGW)'
     ;;
*)
     AC_MSG_RESULT([[$mhd_host_os]])
     AC_MSG_WARN([Unrecognised OS $host_os])
     AC_DEFINE_UNQUOTED(OTHEROS,1,[Some strange OS])
     mhd_host_os='unrecognised OS'
#    You might want to find out if your OS supports shutdown on listen sockets,
#    and extend the switch statement; if we do not have 'HAVE_LISTEN_SHUTDOWN',
#    pipes are used instead to signal 'select'.
#    AC_DEFINE_UNQUOTED(HAVE_LISTEN_SHUTDOWN,1,[can use shutdown on listen sockets])
;;
esac

AC_OUTPUT(Makefile src/Makefile doc/Makefile examples/Makefile scripts/Makefile src/tests/Makefile)
