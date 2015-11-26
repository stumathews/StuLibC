#include <etcp.h>

/* udp_server - set up a UDP server */
SOCKET netUdpServer( char *hname, char *sname )
{
	SOCKET s;
	struct sockaddr_in local;

	netSetAddress( hname, sname, &local, "udp" );
	s = socket( AF_INET, SOCK_DGRAM, 0 );
	if ( !isvalidsock( s ) )
		netError( 1, errno, "socket call failed" );
	if ( bind( s, ( struct sockaddr * ) &local,
		 sizeof( local ) ) )
		netError( 1, errno, "bind failed" );
	return s;
}
