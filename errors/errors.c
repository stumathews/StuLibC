#include "errors.h"
#include "../logging/logging.h"

void ERR_Print(const char* error, int log)
{
	fprintf(stderr, error);
	if( log > 0)
		LOG(error,stderr, "Generic error logging.");

}
