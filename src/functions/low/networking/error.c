#include <etcp.h>
#include <debugging.h>


void netError( int status, int err, char *fmt, ... )
{
	va_list ap;

	va_start( ap, fmt );
	vfprintf( stderr, fmt, ap );
    DBG("%s", strerror(err));
	va_end( ap );
	if ( err )
		fprintf( stderr, ": %s (%d)\n", strerror( err ), err );
	if ( status )
		EXIT( status );
}
