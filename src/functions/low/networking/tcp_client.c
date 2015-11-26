#include <etcp.h>

/* tcp_client - set up for a TCP client */
SOCKET netTcpClient( char *hname, char *sname )
{
	struct sockaddr_in peer;
	SOCKET s;

	netSetAddress( hname, sname, &peer, "tcp" );
    // obtain a socket
	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( !isvalidsock( s ) )
		netError( 1, errno, "socket call failed" );
    
    // Connect returns on a successfull connection and thereafter socket can be used 
    // as an established connection to send/recv network data
	if ( connect( s, ( struct sockaddr * )&peer,sizeof( peer ) ) )
		netError( 1, errno, "connect failed" );

	return s;
}
