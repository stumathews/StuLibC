#include <logging.h>
#include <files.h>

#define LOG_MAX_LINE_LENGTH 160

static char buffer[LOG_MAX_LINE_LENGTH];
static char* DEFAULT_LOG_FILE_NAME = "default.log";
static char* DEFAULT_LOG_FMT = "%s\t%s\n";


void  LOG_DeleteLog()
{
  FILE_Delete( LOG_GetDefaultLogFileName() );
}

char* LOG_GetDefaultLogFileName()
{ 
  return DEFAULT_LOG_FILE_NAME; 
}

int LOG_If(int condition_result, char* message)
{
    if(condition_result)
        LOG_Log(message);
    return condition_result;
}

void LOG_LogToStream(char* message, FILE* stream)
{
    sprintf(buffer,DEFAULT_LOG_FMT,TIM_GetDateTimeStr(), message);
    FILE_AppendTextToStream(buffer,stream);
}



void LOG_Log(char* message)
{
    FILE* LogFileStream = fopen(DEFAULT_LOG_FILE_NAME,"a");

    LOG_LogToStream(message,LogFileStream);

    fclose(LogFileStream);
}

void LOG_LogLineToFile( char* message,char* filename )
{
    FILE* LogFileStream = fopen( filename, "a");
    LOG_LogToStream( message, LogFileStream );
    fclose( LogFileStream );
}


