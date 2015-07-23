#ifndef STULIBC_WINCOMPAT_H
#define STULIBC_WINCOMPAT_H
#ifdef HAVE_WINSOCK2_H 
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <config.h>
int inet_aton( const char *cp, struct in_addr *pin )
{
    int rc;
	 
	rc = inet_addr( cp );
	if ( rc == -1 && strcmp( cp, "255.255.255.255" ) )
		return 0;
	pin->s_addr = rc;
	return 1;
}
#endif // HAVE_WINSOCK2_H
#endif
