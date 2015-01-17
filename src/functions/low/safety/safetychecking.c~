#include "safetychecking.h"
#include "..\filemanagement\filemanagement.h"
#include <stdlib.h> // exit()
#include <stdio.h>  // sprintf()

#define MAX_LOG_LINE_LENGTH 255

static char* DEFAULT_FILE_NAME = "safety.txt";
static char* COMMON_CHK_RESULT_FORMAT = "[SAFETY] %s (%s)\n";
static char buffer[MAX_LOG_LINE_LENGTH];


void CHK_ExitIf(int condition_result, char* message, char* resultContext)
{
    if(condition_result)
    {
        sprintf(buffer,COMMON_CHK_RESULT_FORMAT,message, resultContext);
        FILE_AppendText(buffer, DEFAULT_FILE_NAME);
        exit(1);
    }
}
