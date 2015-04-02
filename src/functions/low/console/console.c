#include <console.h>
#include <safetychecking.h>

void CNS_PrintLine(char* message)
{
	CHECK_STRING( message, IS_NOT_EMPTY );
    puts(message);
}

void CNS_Print( char* message )
{
	CHECK_STRING( message, IS_NOT_EMPTY );
	printf("%s", message);
}

