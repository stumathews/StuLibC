#include <etcp.h>

int main( int argc, char **argv )
{
	struct sockaddr_in peer;
	SOCKET s;
	SOCKET s1;
	int peerlen = sizeof( peer );
	int n;
	char buf[ 10 ];

	INIT();
	s = tcp_server( "localhost", "9000" );
	s1 = accept( s, ( struct sockaddr * )&peer, &peerlen );
	if ( !isvalidsock( s1 ) )
		error( 1, errno, "accept failed" );

    // connection made and accepted, keep reading on the socket
    // and writing to stdout the data we get
	for ( ;; )
	{
        // read a record, but we dont know how bit it is, though
        // it will be at most 10 bytes long
        // and we'll wait for it to be that if its not...
        // the data will be written into buf
		n = readvrec( s1, buf, sizeof( buf ) );
		if ( n < 0 )
			error( 0, errno, "readvrec returned error" );
		else if ( n == 0 )
			error( 1, 0, "client disconnected\n" );
		else
			write( 1, buf, n ); // Write the bytes that were put into buf
	}
	EXIT( 0 );		/* not reached */
}
