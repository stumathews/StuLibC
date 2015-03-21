#include <etcp.h>
#include <skel.h>

char *program_name;

/* server - place holder for server */
static void server( SOCKET s, struct sockaddr_in *peerp )
{
    send( s, "Hello World\n",13,0);
}

/* main - TCP setup, listen, and accept */
int main( int argc, char **argv )
{
	struct sockaddr_in local;
	struct sockaddr_in peer;
	char *hname;
	char *sname;
	int peerlen;
	SOCKET s1;
	SOCKET s;
	const int on = 1;

	INIT();

    // get a socket, bound to this address thats configured to listen.
    // NB: This is always ever non-blocking 
    s = tcp_server("localhost","9000");

	do
	{
		peerlen = sizeof( peer );
        // wait/block on this listening socket...
		s1 = accept( s, ( struct sockaddr * )&peer, &peerlen );
		if ( !isvalidsock( s1 ) )
			error( 1, errno, "accept failed" );
        // do network functionality on this socket that now represents a connection with the peer (client) 
		server( s1, &peer );
		CLOSE( s1 );
	} while ( 1 );
	EXIT( 0 );
}
