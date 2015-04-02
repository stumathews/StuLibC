#include <debugging.h>
#include <files.h>
#include <strings.h>
#include <logging.h>
#include <stdarg.h>
#include <assert.h>
#include <safetychecking.h>

#define MAX_DBG_LINE_LENGTH 512
#define ERROR 1

static char* DEFAULT_DEBUG_FILENAME = "debug.txt";
static char line_buffer[MAX_DBG_LINE_LENGTH];

void DBG_Log(char* message)
{
  CHECK_STRING( message, IS_NOT_EMPTY );
  
  DBG_WriteLineToFile(message, DEFAULT_DEBUG_FILENAME, UNSPECIFIED);
}

void DBG_DeleteLog()
{
  if( FILE_Exists( DEFAULT_DEBUG_FILENAME ))
    FILE_Delete( DEFAULT_DEBUG_FILENAME );

}

char* DBG_GetDefaultLogFileName()
{
  return DEFAULT_DEBUG_FILENAME;
}

void DBG_LogIf(int condition, char* message, char* otherwise)
{
	CHECK_STRING( message, IS_NOT_EMPTY );
    if(condition)
    {
        DBG_WriteLineToFile(message,DEFAULT_DEBUG_FILENAME,UNSPECIFIED);
    }
    else
    {
    	CHECK_STRING( otherwise, IS_NOT_EMPTY );
        DBG_WriteLineToFile(otherwise,DEFAULT_DEBUG_FILENAME,UNSPECIFIED);
    }
}

// What we need is a DBG_LogIfSeverity() so that other DBG_LogIf() doesn't need to automatically
// provide a default severity of UNSPECIFIED.

void DBG_LogIfToStream( int condition, FILE* stream, char* message, char* otherwise)
{
	CHECK_STRING( message, IS_NOT_EMPTY );
    if(condition)
    {
        DBG_WriteLineToStream(message,stream,UNSPECIFIED);
    }
    else
    {
    	CHECK_STRING( otherwise, IS_NOT_EMPTY );
        DBG_WriteLineToStream(otherwise,stream,UNSPECIFIED);
    }
}

void DBG_WriteLineToFileExtra(char* prefix, char* message,char* suffix, char* filename, enum Severity severity)
{
	CHECK_STRING( message, IS_NOT_EMPTY );
	CHECK_STRING( prefix, IS_NOT_EMPTY );
	CHECK_STRING( suffix, IS_NOT_EMPTY );
	CHECK_STRING( filename, IS_NOT_EMPTY );

    int ok = LOG_If( (strlen(message) == 0), "Debug message is empty" );
    if(ok != 0)
    {
        return;
    }

    sprintf(line_buffer,"%s\t[%s] %s\t%s\t%s\n", TIM_GetDateTimeStr(),DBG_GetSeverityAsString(severity), (prefix?prefix:""), message, (suffix?suffix:""));
    FILE_AppendText(line_buffer,filename);
}

void DBG_WriteLineToFile( char* message, char* filename, enum Severity severity)
{

	CHECK_STRING( message, IS_NOT_EMPTY );
	CHECK_STRING( filename, IS_NOT_EMPTY );
	
    int result;

    result = LOG_If( message == NULL || strlen(message) == 0, "Debug message is empty");
    result = LOG_If( filename == NULL || strlen(filename) == 0,"No filename specified");
    if( result == ERROR )
        return;

    sprintf(line_buffer,"%s\t[%s] %s\n", TIM_GetDateTimeStr(), DBG_GetSeverityAsString(severity), message);
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
	CHECK_STRING( message, IS_NOT_EMPTY );
	
    int result;

    result = LOG_If( message == NULL || strlen(message) == 0, "Debug message is empty" );
    result = LOG_If( stream == NULL,"No stream specified");
    if( result == ERROR )
        return;

    sprintf(line_buffer,"%s\t[%s] %s\n", TIM_GetDateTimeStr(), DBG_GetSeverityAsString(severity), message);
    fputs(message,stream);

    if(ferror(stream))
        fclose(stream);
}

void DBG_Fail( char* message )
{
  CHECK_STRING( message, IS_NOT_EMPTY );
  DBG("Assertion failed: %s\n", message);
  DBG_Log(message);

  assert( 1 < 0 );
}



