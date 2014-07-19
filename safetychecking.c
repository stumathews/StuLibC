#include "safetychecking.h"
#include "filemanagement.h"
#include <stdlib.h> // exit()
#include <stdio.h>  // sprintf()

#define MAX_LOG_LINE_LENGTH 80

static char* safetyfile = "safety.txt";

void CHK_ResultExitIf(void* result, int condition)
{
    if(condition)
    {
        FILE_AppendText("Check_ResultIf not implemented yet", safetyfile);
        exit(1);
    }
}
void CHK_ResultLogIf(void* result,int condition)
{
    if(condition)
            FILE_AppendText("Check_ResultIf not implemented yet", safetyfile);
}

void CHK_ResultLog(char* result, char* functionName,int lineNumber, char* resultContext)
{
    char buffer[MAX_LOG_LINE_LENGTH];

    sprintf(buffer,"Result %s at function %s:%d - %s\n",result, functionName, lineNumber,resultContext);
    FILE_AppendText( buffer, safetyfile);
}
