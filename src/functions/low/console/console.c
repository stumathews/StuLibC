#include <console.h>
#include <safetychecking.h>

void CNS_PrintLine(char* message)
{
	CHECK_STRING( message, IS_NOT_EMPTY );
    puts(message);
}

void CNS_Print( char* message )
{
	printf("%s", message);
}

void CNS_PrintFile( char* filename )
{
    CHECK_STRING(filename, IS_NOT_EMPTY);
    
    if(!FILE_Exists(filename))
    {
        PRINT("File does not exist: %s", filename);
        return;
    }
    CHK_ExitIf(1,"not implemented yet","CNS_PrintFile");
}

