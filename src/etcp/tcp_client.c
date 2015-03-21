#include <etcp.h>

/* tcp_client - set up for a TCP client */
SOCKET tcp_client( char *hname, char *sname )
{
	struct sockaddr_in peer;
	SOCKET s;

	set_address( hname, sname, &peer, "tcp" );
    // obtain a socket
	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( !isvalidsock( s ) )
		error( 1, errno, "socket call failed" );
    
    // Connect returns on a successfull connection and thereafter socket can be used 
    // as an established connection to send/recv network data
	if ( connect( s, ( struct sockaddr * )&peer,sizeof( peer ) ) )
		error( 1, errno, "connect failed" );

	return s;
}
