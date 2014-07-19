#include "debugging.h"
#include "timing.h"
#include "filemanagement.h"

#define MAX_DBG_LINE_LENGTH 80


void DBG_WriteLineExtra(char* prefix, char* message,char* suffix, char* filename, enum Severity severity)
{
    static char* line_buffer[MAX_DBG_LINE_LENGTH];
    int result = sprintf(line_buffer,"%s\t[%s] %s\t%s\t%s\n", TM_GetDateTimeStr(),DBG_GetSeverityAsString(severity), (prefix?prefix:""), message, (suffix?suffix:""));
    FILE_AppendText(line_buffer,filename);
}

void DBG_WriteLine( char* message, char* filename, enum Severity severity)
{
    static char* line_buffer[MAX_DBG_LINE_LENGTH];

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
    default:
        return "Unknown Severity";

    }
}
