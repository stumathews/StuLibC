#include "safetychecking.h"
#include "filemanagement.h"
#include <stdlib.h> // exit()
#include <stdio.h>  // sprintf()

#define MAX_LOG_LINE_LENGTH 255

static char* safetyfile = "safety.txt";

void CHK_ResultExitIf(int condition, char* message, char* resultContext)
{
    char buffer[MAX_LOG_LINE_LENGTH];
    sprintf(buffer,"%s %s",resultContext,message);
    if(condition)
    {
        FILE_AppendText(buffer, safetyfile);
        exit(1);
    }
}
int CHK_ResultLogIf(int condition, char* message, char* resultContext)
{
    char buf[MAX_LOG_LINE_LENGTH];
    sprintf(buf,"%s (%s)",message,resultContext);

    if(condition == 1)
        FILE_AppendText(buf, safetyfile);
    return condition;
}

void CHK_ResultLog(char* functionName,int lineNumber, char* resultContext)
{
    char buffer[MAX_LOG_LINE_LENGTH];

    sprintf(buffer,"at function %s:%d - %s\n", functionName, lineNumber,resultContext);
    FILE_AppendText( buffer, safetyfile);
}
