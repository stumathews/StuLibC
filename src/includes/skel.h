
/**
 * @file skel.h
 * @brief tcp/ip abstraction layer
 * @author Stuart Mathews
 * @date 22 march 2015
 *
 * This header contains the function and type declarations for the common networking functions in the library.
 * It allows winodws and linux platforms to use the same interface for these common routines, but diffirent implementations
 * @see http://devel.stuartmathews.com/stulibc
 */


#ifndef __SKEL_H__
#define __SKEL_H__
#include <constants.h>

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

#define NETINIT()			
#define EXIT(s)			exit( s )
#define NETCLOSE(s)		if ( close( s ) ) netError( 1, errno, \
						"close failed" )
#define set_errno(e)	errno = ( e )
#define isvalidsock(s)	( ( s ) >= 0 )

typedef int SOCKET;

#endif

#ifdef HAVE_WINSOCK2_H 

#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>

struct timezone
{
	long tz_minuteswest;
	long tz_dsttime;
};
typedef unsigned int u_int32_t;

#define EMSGSIZE		WSAEMSGSIZE

#define NETINIT()			do { WSADATA wsaData; WSAStartup(MAKEWORD(2,2), &wsaData); } while(0);
#define EXIT(s)			do { WSACleanup(); exit( ( s ) ); } \
						while ( 0 )
#define NETCLOSE(s)		CLOSE(s)
#define CLOSE(s)		if ( closesocket( s ) ) \
							netError( 1, errno, "close failed" )
#define errorno			( GetLastError() )
#define set_errno(e)	SetLastError( ( e ) )
#define isvalidsock(s)	( ( s ) != SOCKET_ERROR )
#define bzero(b,n)		memset( ( b ), 0, ( n ) )
#define sleep(t)		Sleep( ( t ) * 1000 )


LIBRARY_API void init();
LIBRARY_API int inet_aton( const char *cp, struct in_addr *pin );


#endif /* HAVE_WINSOCK2_H */

#endif  /* __SKEL_H__ */
