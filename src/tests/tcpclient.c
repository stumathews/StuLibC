#include <etcp.h>

char *program_name;


// socket s represents an established connection(connect already called),
// peerp represents the server that the connection was established with
static void client( SOCKET s, struct sockaddr_in *peerp )
{
    int rc;
    char buf[120];

    for(;;)
    {
        // read from the server until the server sends an EOF
        rc = recv( s, buf, sizeof(buf),0);
        if( rc <= 0 )
            break;
        // write what we got to stdout
        write(1, buf, rc );
    }
}

/* main - connect to the server */
int main( int argc, char **argv )
{
	struct sockaddr_in peer;
	SOCKET s;

	INIT();
    
    // Establish a connection(calls connect) and return the socket that represents that connection.
	s = netTcpClient("localhost","9000");
    // call blocking network functions
	client( s, &peer );
	EXIT( 0 );
}
