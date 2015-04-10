#include <etcp.h>

/* udp_client - set up a UDP client */
SOCKET netUdpClient( char *hname, char *sname, struct sockaddr_in *sap )
{
	SOCKET s;

	netSetAddress( hname, sname, sap, "udp" );
	s = socket( AF_INET, SOCK_DGRAM, 0 );
	if ( !isvalidsock( s ) )
		netError( 1, errno, "socket call failed" );
	return s;
}
