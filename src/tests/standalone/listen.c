#include <etcp.h>
#include <logging.h>
#include <debugging.h>

char *program_name;

/* server - place holder for server */
static void server( SOCKET s, struct sockaddr_in *peerp )
{
    char buf[256];
    int rc =  readline(s, buf,256);
    LOG("Received data:%s",buf);
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
    fd_set readfds;
    FD_ZERO( &readfds);
    struct timeval timeout = {.tv_sec = 60, .tv_usec=0}; 
    DBG("timeout.tv_sec = %d timeout,tv_upsec = %d", timeout.tv_sec, timeout.tv_usec);


	INIT();
    /*
     int select(int nfds, fd_set *readfds, fd_set *writefds,
     fd_set *exceptfds, struct timeval *timeout);
     void FD_CLR(int fd, fd_set *set);
     int  FD_ISSET(int fd, fd_set *set);
     void FD_SET(int fd, fd_set *set);
     void FD_ZERO(fd_set *set);
     * */

    // get a socket, bound to this address thats configured to listen.
    // NB: This is always ever non-blocking 
    LOG( "Going to listen on port 9000...");
    s = tcp_server("localhost","9000");
    DBG( "got socket...");

	do
	{
        DBG("peerlen");
		peerlen = sizeof( peer );
        DBG("FD_SET...");
        FD_SET(s, &readfds);
        DBG("doing a select");
        // wait/block on this listening socket...
        int res = select( s+1, &readfds, NULL, NULL, &timeout);
        if( res == 0 )
        {
            LOG( "timeout");
            error(1,errno,"timeout!");
        }
        else if( res == -1 )
        {
            LOG("Select error!");
            error(1,errno,"select error!!");
        }
        else
        {

            if( FD_ISSET(s,&readfds ))
            {
                DBG("Accpeting");
    		    s1 = accept( s, ( struct sockaddr * )&peer, &peerlen );
            }
            else
            {
                DBG("not our socket. continuing");
                continue;
            }
        }
        DBG("done");

		if ( !isvalidsock( s1 ) )
			error( 1, errno, "accept failed" );
        // do network functionality on this socket that now represents a connection with the peer (client) 
		server( s1, &peer );
		CLOSE( s1 );
	} while ( 1 );
	EXIT( 0 );
}
