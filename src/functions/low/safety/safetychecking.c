#include <safetychecking.h>
#include <stdbool.h>
#include <errors.h>
#include <debugging.h>
#include <assert.h>
#include <strings.h>
#include <ctype.h>
#include <console.h>

/**
 * The max length of a line that we'll log to the safety log
 */
#define MAX_LOG_LINE_LENGTH 255

/**
 * How we will of the formatted message by default
 */
static char* COMMON_CHK_RESULT_FORMAT = "[SAFETY] %s (%s)\n";

void CHK_ExitIf(int condition_result, char* message, char* resultContext)
{
	char buffer[MAX_LOG_LINE_LENGTH];
	CHK_str(message, IS_NOT_EMPTY, (char*)__FUNCTION__);

    if(condition_result) {
        sprintf(buffer, COMMON_CHK_RESULT_FORMAT, message, resultContext);
        ERR_Print((const char*)buffer, YES);
        exit(1);
    }
}

void CHK_str( const char* string, enum StringChecks checks, const char* functionName)
{
	bool invalid = false;

	if(checks & IS_NOT_EMPTY) {
		if((invalid = STR_IsNullOrEmpty(string))) {
		    PRINT("Condition IS_NOT_EMPTY failed on string '%s' in caller function '%s'()",string, functionName);
			exit(1);
		}
	}

	if (checks & CHARS_ONLY) {
		for( int i = 0; i < strlen(string); i++) {
			 if(!isalpha(string[i])) {
				invalid = true;
				break;
			 }
		}
	}

	if (checks & ALL_LOWER) {
		for( int i = 0; i < strlen(string); i++) {
			 if(!islower(string[i])) {
				invalid = true;
				break;
			 }
		}
	}
}

// This allows you to determine if a int meets a requirement(IsIntValidRoutine) and fix it if it is
void CHK_int( IsIntValidRoutine fptrIsIntValid, int* data, char* data_label, FixIntRoutine fptrFixInt)
{
  if(!fptrIsIntValid(data)) {
	CHK_ExitIf(fptrFixInt == NULL,"Invalid data provided", "fptrIsIntValid");

    fptrFixInt(data);

    CHK_ExitIf(!fptrIsIntValid(data),"Invalid data provided cloud not be fixed", "fptrIsIntValid");
  }
}

/* Predefined IsIntValidRoutine comptible validation routines for Chk_int: */

bool isNotNegative( int integer )
{
	return integer >= 0;
}

void makeIntZero( int* integer)
{
	*integer = 0;
}


