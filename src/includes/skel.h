
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

#define INIT()			
#define EXIT(s)			exit( s )
#define CLOSE(s)		if ( close( s ) ) netError( 1, errno, \
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


inline void init( char **argv )
{
	WSADATA wsadata;
	
	WSAStartup( MAKEWORD( 2, 2 ), &wsadata );
}

/* inet_aton - version of inet_aton for SVr4 and Windows */
inline int inet_aton( char *cp, struct in_addr *pin )
{
    int rc;
	 
	rc = inet_addr( cp );
	if ( rc == -1 && strcmp( cp, "255.255.255.255" ) )
		return 0;
	pin->s_addr = rc;
	return 1;
}


#endif /* HAVE_WINSOCK2_H */

#endif  /* __SKEL_H__ */
