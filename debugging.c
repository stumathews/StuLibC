#include "debugging.h"
#include "timing.h"
#include "filemanagement.h"

void DBG_WriteLineExtra(char* prefix, char* message,char* suffix, char* filename, enum Severity severity)
{
    const int max_buff_size = 80;
    char* buffer[max_buff_size];

    int result = sprintf(buffer,"%s\t%s\t%s\t%s\n", TM_GetDateTimeStr(), (prefix?prefix:""), message, (suffix?suffix:""));
    FILE_AppendText(buffer,filename);
}

void DBG_WriteLine( char* message, char* filename, enum Severity severity)
{
    printf("%s\t%s\n", TM_GetDateTimeStr(), message);
}
