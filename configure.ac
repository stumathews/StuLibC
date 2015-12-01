AC_INIT([libstuc], [0.0.1], [stumathews@gmail.com])
AM_INIT_AUTOMAKE([libstuc], [0.0.1])
AM_CONFIG_HEADER(src/includes/config.h:config.hin)
AC_PROG_CC
AC_PROG_CC_STDC
AC_C_CONST
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL
AC_CHECK_HEADERS([sys/socket.h])
AC_CHECK_HEADERS([winsock2.h])
AC_CHECK_HEADERS([windows.h])
AC_CHECK_LIB([ws2_32],[main])
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
AC_OUTPUT(Makefile src/Makefile doc/Makefile examples/Makefile man/Makefile scripts/Makefile src/tests/Makefile)
