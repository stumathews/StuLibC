#ifndef __SKEL_H__
#define __SKEL_H__

/*
 * Basic abstraction layer routines for tcp programming across linux and windows
 * */

#ifndef HAVE_WINSOCK2_H

/* UNIX version */

#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define INIT()			( program_name = \
						strrchr( argv[ 0 ], '/' ) ) ? \
						program_name++ : \
						( program_name = argv[ 0 ] )
#define EXIT(s)			exit( s )
#define CLOSE(s)		if ( close( s ) ) error( 1, errno, \
						"close failed" )
#define set_errno(e)	errno = ( e )
#define isvalidsock(s)	( ( s ) >= 0 )

typedef int SOCKET;

#else

#include <winsock2.h>
#include <windows.h>

struct timezone
{
	long tz_minuteswest;
	long tz_dsttime;
};
typedef unsigned int u_int32_t;

#define EMSGSIZE		WSAEMSGSIZE
#define INIT()			init( argv );
#define EXIT(s)			do { WSACleanup(); exit( ( s ) ); } \
						while ( 0 )
#define CLOSE(s)		if ( closesocket( s ) ) \
							error( 1, errno, "close failed" )
#define errno			( GetLastError() )
#define set_errno(e)	SetLastError( ( e ) )
#define isvalidsock(s)	( ( s ) != SOCKET_ERROR )
#define bzero(b,n)		memset( ( b ), 0, ( n ) )
#define sleep(t)		Sleep( ( t ) * 1000 )
#define WINDOWS

#endif /* HAVE_WINSOCK2_H */

#endif  /* __SKEL_H__ */
