#include <etcp.h>

int main( int argc, char **argv )
{
	SOCKET s;
	int n;
	struct
	{
		u_int32_t reclen;
		char buf[ 128 ];
	} packet;

	INIT();

	s = netTcpClient( "localhost", "9000" );
    // for each string we get from the keyboard, send it to the server. Put it into buffer
	while ( fgets( packet.buf, sizeof( packet.buf ), stdin ) != NULL )
	{
        // how long was the data retrieved from the keyboard this time?
		n = strlen( packet.buf );

        // OK, thats how long our data will be, so set the data length to that
        // the server will be expecting the data length first anyway...
		packet.reclen = htonl( n );

        // send the length and data to the server
		if ( send( s, ( char * )&packet, n + sizeof( packet.reclen ), 0 ) < 0 )
			netError( 1, errno, "send failure" );
	}
	EXIT( 0 );
}
