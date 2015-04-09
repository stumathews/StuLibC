#include <etcp.h>
#include <logging.h>

char *program_name;


// socket s represents an established connection(connect already called),
// peerp represents the server that the connection was established with
static void client( SOCKET s, struct sockaddr_in *peerp )
{
    char* msg = "Hello World\n";
    int rc = send( s, msg,strlen(msg),0);
    LOG( "send out %d bytes",rc);
}

/* main - connect to the server */
int main( int argc, char **argv )
{
	struct sockaddr_in peer;
	SOCKET s;

	INIT();
    
    // Establish a connection(calls connect) and return the socket that represents that connection.
	s = tcp_client("localhost","9000");
    // call blocking network functions
    LOG("about to write");
	client( s, &peer );
	EXIT( 0 );
}
