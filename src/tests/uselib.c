
#include <libstu.h>

int main( int argc, char** argv)
{
#if INSPECT_ERRORS
	CNS_PrintLine("CNS_PrintLine: hello world!");
#endif

	return 0;
}
