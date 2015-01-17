#include "logging.h"
#include <stdio.h>
#include <stdarg.h>
#include "..\timing\timing.h"
#include "..\filemanagement\filemanagement.h"

#define LOG_MAX_LINE_LENGTH 160

static char buffer[LOG_MAX_LINE_LENGTH];
static char* DEFAULT_LOG_FILE_NAME = "log.txt";
static char* DEFAULT_LOG_FMT = "%s\t%s (%s)\n";


int LOG_If(int condition_result, char* message, char* context)
{
    if(condition_result == 1)
    {
        FILE* LogFileStream = fopen(DEFAULT_LOG_FILE_NAME,"a");
        LOG(message,LogFileStream,context);
        fclose(LogFileStream);
    }
    return condition_result;
}

void LOG(char* message, FILE* stream, char* context)
{
    sprintf(buffer,DEFAULT_LOG_FMT,TIM_GetDateTimeStr(), message,context);
    FILE_AppendTextToStream(buffer,stream);
}



void LOG_It(char* message, char* context)
{
    FILE* LogFileStream = fopen(DEFAULT_LOG_FILE_NAME,"a");
    LOG(message,LogFileStream,(context)?context:"no context");
    fclose(LogFileStream);
}


