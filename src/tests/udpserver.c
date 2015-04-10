#include <etcp.h>

char *program_name;

/* server - place holder for server */
static void server( SOCKET s, struct sockaddr_in *localp )
{
    struct sockaddr_in* peer;
    int peerlen;
    char buf[1];

    for(;;)
    {
        peerlen = sizeof(peer);

        // receive 1 bit from client/peer
        if( recvfrom( s, buf, sizeof(buf),0, (struct sockaddr*) &peer, &peerlen) < 0)
            netError(1, errno, "recvfrom failed");

        // send string data to peer(client) 
        if( sendto( s, "Hello World\n",13,0, (struct sockaddr*) &peer, peerlen) < 0)
            netError( 1, errno, "sendto failed");
    }
}

/* main - UDP setup */
int main( int argc, char **argv )
{
	struct sockaddr_in local;
	char *hname = "localhost";
	char *sname = "9000";
	SOCKET s;

	INIT();

    // get udp socket bound this this address
    s = netUdpServer( hname, sname );
    // server loop
	server( s, &local );
	EXIT( 0 );
}
