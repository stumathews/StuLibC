#include <etcp.h>

/* tcp_server - set up for a TCP server */
SOCKET netTcpServer( char *hname, char *sname )
{
    // This will hold the address that the server will use to listen on
	struct sockaddr_in local;
    // This is the socket the server will obtain and bind it to the address in the sockaddr_in structure
	SOCKET s;
	const int on = 1;

    // Construct the address : fill in the sockaddr_in structure
	netSetAddress( hname, sname, &local, "tcp" );
    
    // Obtain a socket for the server
	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( !isvalidsock( s ) )
		error( 1, errno, "socket call failed" );
    
    // Configure the socket so we can use it as a server socket
	if ( setsockopt( s, SOL_SOCKET, SO_REUSEADDR,
		( char * )&on, sizeof( on ) ) )
		error( 1, errno, "setsockopt failed" );

    // Bind the address to the socket
	if ( bind( s, ( struct sockaddr * ) &local,
		 sizeof( local ) ) )
		error( 1, errno, "bind failed" );

    // set listen state  on the socket, which is now bound to the address mentioned in sockaddr_in
    // Note: This only sets the socket state to listening, this doesn't block;
	if ( listen( s, NLISTEN ) )
		netError( 1, errno, "listen failed" );

    // Socket  
	return s;
}
