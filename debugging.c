#include "debugging.h"
#include "timing.h"
#include "filemanagement.h"
#include "safetychecking.h"
#include <string.h>
#include <stdio.h>

#define MAX_DBG_LINE_LENGTH 512
static char* DEFAULT_DEBUG_FILENAME = "debug.txt";


void DBG_LogIf(int condition, char* message, char* otherwise)
{
    if(condition)
        DBG_WriteLineToFile(message,DEFAULT_DEBUG_FILENAME,UNSPECIFIED);
    else
        DBG_WriteLineToFile(otherwise,DEFAULT_DEBUG_FILENAME,UNSPECIFIED);
}


void DBG_WriteLineToFileExtra(char* prefix, char* message,char* suffix, char* filename, enum Severity severity)
{

    int ok = CHK_ResultLogIf( (strlen(message) == 0), "Debug message is empty", "argument passed DBG_WriteLineToFileExtra()" );
    if(ok != 0){
        return;
    }

    //TODO: Can we allocate memory dynamically so we use less memory each time we call this function?
    char line_buffer[MAX_DBG_LINE_LENGTH];
    sprintf(line_buffer,"%s\t[%-12s] %s\t%s\t%s\n", TM_GetDateTimeStr(),DBG_GetSeverityAsString(severity), (prefix?prefix:""), message, (suffix?suffix:""));
    FILE_AppendText(line_buffer,filename);
}

void DBG_WriteLineToFile( char* message, char* filename, enum Severity severity)
{
    char line_buffer[MAX_DBG_LINE_LENGTH];

    sprintf(line_buffer,"%s\t[%-12s] %s\n", TM_GetDateTimeStr(), DBG_GetSeverityAsString(severity), message);
    FILE_AppendText(line_buffer, filename);
}



char* DBG_GetSeverityAsString(enum Severity severity)
{
    switch(severity)
    {
    case MINOR:
        return "Minor";
    case CRITICAL:
        return "Critical";
    case NORMAL:
        return "Normal";
    case UNSPECIFIED:
        return "Unspecified";
    default:
        return "Unknown Severity";

    }
}
