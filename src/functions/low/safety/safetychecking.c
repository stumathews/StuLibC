#include <safetychecking.h>
#include <stdbool.h>
#include <errors.h>
#include <debugging.h>
#include <assert.h>

#define MAX_LOG_LINE_LENGTH 255

static char* DEFAULT_FILE_NAME = "safety.txt";
static char* COMMON_CHK_RESULT_FORMAT = "[SAFETY] %s (%s)\n";
static char buffer[MAX_LOG_LINE_LENGTH];


void CHK_int( IsIntValidRoutine func_IsDataValid, int* data, char* data_label, FixIntRoutine func_FixData)
{
  if(!func_IsDataValid(data))
  {

    if( func_FixData == NULL)
    {
      ERR("Invalid data '%s' provided: '%d'\n",data_label, *data);
    }

    DBG("Attempting to fix data '%s'(%d)\n",data_label, *data);
    func_FixData(data);

    if( !func_IsDataValid(data) )
      ERR("Invalid data '%s' provided '%d' and it could not be fixed.\n",data_label, *data);
    else
      DBG("Data '%s' fixed to %d\n",data_label,*data);
  }
}

void CHK_ExitIf(int condition_result, char* message, char* resultContext)
{

    if(condition_result)
    {
        sprintf(buffer,COMMON_CHK_RESULT_FORMAT,message, resultContext);
        ERR(buffer, DEFAULT_FILE_NAME);
        exit(1);
    }
}

void CHK_str( char* string, enum StringChecks checks, char* functionName)
{
	if( (checks & IS_NOT_EMPTY) && (STR_IsNullOrEmpty(string)) )
	{
		DBG("Condition IS_NOT_EMPTY failed on string '%s' in caller funcion '%s'()",string, functionName);
		exit(1);	
	}
	
	if ( checks & CHARS_ONLY )
	{
		DBG("CHARS_ONLY");
	}
	
	if ( checks & ALL_LOWER )
	{
		DBG("CHARS_ONLY");
	}	
}
