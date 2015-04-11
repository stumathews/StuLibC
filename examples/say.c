#include <stulibc.h>

char *program_name;


// socket s represents an established connection(connect already called),
// peerp represents the server that the connection was established with
static void client( SOCKET s, struct sockaddr_in *peerp )
{
    char* msg = "Hello World";
    int rc = send( s, msg,strlen(msg),0);
    LOG( "send out %d bytes",rc);
}

static char port[20] = {0};

void setPortNumber(char* arg)
{
    CHECK_STRING(arg, IS_NOT_EMPTY);
    strncpy( port, arg, strlen(arg));
}


/* main - connect to the server */
int main( int argc, char **argv )
{
    LIB_Init();
    
    struct Argument* portNumber = CMD_CreateNewArgument("port","port <number>","Set the port to connect to", true, true, setPortNumber);
    CMD_AddArgument(portNumber);
    
    if( argc > 1 )
        CMD_Parse(argc,argv,true);
    else
    {
        CMD_ShowUsages("listen <options>");
        exit(0);
    }
	
    struct sockaddr_in peer;
	SOCKET s;

	INIT();
    
    // Establish a connection(calls connect) and return the socket that represents that connection.
	s = netTcpClient("localhost",port);
    // call blocking network functions
    LOG("about to write");
	client( s, &peer );
	EXIT( 0 );
}
