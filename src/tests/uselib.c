#include <stulibc.h>

int main( int argc, char** argv)
{
#if INSPECT_ERRORS
	CNS_PrintLine("CNS_PrintLine: hello world!");
#endif
    LIB_Init();

    LIB_Uninit();

	return 0;
}
