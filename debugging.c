#include "debugging.h"
#include "timing.h"
#include "filemanagement.h"
#include "safetychecking.h"
#include "logging.h"
#include <string.h>
#include <stdio.h>

#define MAX_DBG_LINE_LENGTH 512
static char* DEFAULT_DEBUG_FILENAME = "debug.txt";
static char line_buffer[MAX_DBG_LINE_LENGTH];
#define ERROR 1



void DBG_LogIf(int condition, char* message, char* otherwise)
{
    if(condition)
        DBG_WriteLineToFile(message,DEFAULT_DEBUG_FILENAME,UNSPECIFIED);
    else
        DBG_WriteLineToFile(otherwise,DEFAULT_DEBUG_FILENAME,UNSPECIFIED);
}

// What we need is a DBG_LogIfSeverity() so that other DBG_LogIf() doesn't need to automatically
// provide a default severity of UNSPECIFIED.

void DBG_LogIfToStream( int condition, FILE* stream, char* message, char* otherwise)
{
    if(condition)
        DBG_WriteLineToStream(message,stream,UNSPECIFIED);
    else
        DBG_WriteLineToStream(otherwise,stream,UNSPECIFIED);
}

void DBG_WriteLineToFileExtra(char* prefix, char* message,char* suffix, char* filename, enum Severity severity)
{
    int ok = LOG_If( (strlen(message) == 0), "Debug message is empty", "argument passed DBG_WriteLineToFileExtra()" );
    if(ok != 0)
    {
        return;
    }

    sprintf(line_buffer,"%s\t[%s] %s\t%s\t%s\n", TM_GetDateTimeStr(),DBG_GetSeverityAsString(severity), (prefix?prefix:""), message, (suffix?suffix:""));
    FILE_AppendText(line_buffer,filename);
}

void DBG_WriteLineToFile( char* message, char* filename, enum Severity severity)
{
    int result;

    result = LOG_If( message == NULL || strlen(message) == 0, "Debug message is empty", "argument passed DBG_WriteLineToFile()" );
    result = LOG_If( filename == NULL || strlen(filename) == 0,"No filename specified","filename argument to DBG_WriteLineToFile to write message to");
    if( result == ERROR )
        return;

    sprintf(line_buffer,"%s\t[%s] %s\n", TM_GetDateTimeStr(), DBG_GetSeverityAsString(severity), message);
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

void DBG_WriteLineToStream(char* message, FILE* stream, enum Severity severity)
{
    int result;

    result = LOG_If( message == NULL || strlen(message) == 0, "Debug message is empty", "argument passed DBG_WriteLineToFile()" );
    result = LOG_If( stream == NULL,"No stream specified","stream argument to DBG_WriteLineToFile to write message to");
    if( result == ERROR )
        return;

    sprintf(line_buffer,"%s\t[%s] %s\n", TM_GetDateTimeStr(), DBG_GetSeverityAsString(severity), message);
    fputs(message,stream);

    if(ferror(stream))
        fclose(stream);
}


