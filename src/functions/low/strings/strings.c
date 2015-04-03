#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <constants.h>
#include <errors.h>
#include <debugging.h>
#include <stdbool.h>
#include <memory.h>
#include <ctype.h>
#include <safetychecking.h>


char* STR_CreateString(char* string)
{
    //char* str = (char*) malloc(strlen(string) + 1);
    char* str = MEM_Alloc( strlen(string) + 1 );

    MEM_CheckAllocated(str,"str", __FILE__,__LINE__);
    strcpy(str, string);
    // this seems wrong, allocated memory and assuming the caller will free it
    return str;
}

bool STR_BeginsWith(char* beginsWith, char* string)
{
    if(beginsWith == NULL || string == NULL || strlen(beginsWith) == 0 || strlen(string) == 0) return false;
    if(strlen(string) < strlen(beginsWith)  || strncmp(string, beginsWith, strlen(beginsWith)) != 0) return false;
    return true;
}

char* STR_BeginsWithEither(char* possibilities[], char* string)
{
    // loop through all the possibilities ie. {"--","/","-"}
    for(int i = 0; possibilities[i] != NULL; i++) {
        if(STR_BeginsWith(possibilities[i], string) == true)
            return possibilities[i];
    }
    return ""; // None of te possibilities were found.
}

char* STR_EndsWithEither(char* endsWithPossibilities[], char* string)
{
DBG("Enter STR_EndsWithEither()\n");
    // loop through all the possibilities
    for(int i = 0; endsWithPossibilities[i] != NULL; i++) {
        if(STR_EndsWith(endsWithPossibilities[i], string) == true)
            return endsWithPossibilities[i];
    }
DBG("Finish STR_EndsWithEither()\n");
    return "";
}

char* STR_Without(char* without, char* source)
{
    //  "peter stuart mathews 1 stuart" should become "peter  mathews 1 " as we've removed all references to stuart
    // "--help" becomes "help" without --
    // "Stuart Mathews" becomes "Stuart" without " Mathews"
    short withoutLength = strlen(without);
    short sourceLength = strlen(source);
    char* buffer = (char*) malloc(sizeof(char) * (sourceLength +1));
    MEM_CheckAllocated(buffer, "buffer", __FILE__,__LINE__);
    strcpy(buffer, source);
    char* occurance;
    while((occurance = strstr(buffer,without)) != NULL) {
        // modify buffer and rerun loop.
        // note that occurance is a pointer to the buffer set via strstr ( copyinginto occurance, effectvly copies into the buffer )
        strcpy(occurance,occurance+withoutLength);
    }

    return buffer;
}

bool STR_Contains(char* lookfor, char* orig)
{
    //Saftychecking candidates
    if( lookfor == null || strlen(lookfor) == 0 ) ERR("Bad juju 1\n");
    if( orig == null || strlen(orig) == 0 ) ERR("Bad juju 1\n");
    return (strstr((const char*)orig, (const char*)lookfor) != NULL) ? true:false;
}

bool STR_EndsWith(char* endsWith, char* string)
{
    short lookForLength = strlen(endsWith);
    short stringLength = strlen(string);
    if(stringLength == 0 || lookForLength == 0 || stringLength < lookForLength)
        return false;
    // stuart__xx becomes yes it ends with __x
    // 1234567890
    if(strcmp(string + (stringLength - lookForLength), endsWith) == 0)    // compare end of string with endsWith
        return true;
    else
        return false;
}

char* STR_FromLast(char* lookfor, char* string, char* result_buffer)
{
    short lookForLength = strlen(lookfor);
    short stringLength = strlen(string);
    char* buffer = (char*) malloc(sizeof(char) * (stringLength +1));
    MEM_CheckAllocated(buffer,"buffer",__FILE__, __LINE__);
    // copy into a backup buffer for local modification
    strcpy(buffer,string);
    char* occurance = NULL;
    char* last_occurance = NULL;
    //erase each occurancein the copy of the orignal string
    while((occurance = strstr(buffer,lookfor)) != NULL) {
        strcpy(occurance,occurance+lookForLength);
        last_occurance = occurance;
    }
    // copy pointer to last occurance to result_buffer and prepare for returning it.
    strcpy(result_buffer, last_occurance);
    MEM_DeAlloc(buffer, "buffer");
    return result_buffer;
}

char* STR_Join(char* s1, char* s2)
{
  char *s0 = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(s0, s1);
  strcat(s0, s2);
   return s0;
}

char* STR_AppendStrings(char* first, char* second)
{
    return STR_Join(first,second);
}


bool STR_IsNullOrEmpty(char* string)
{
    if(string == NULL || strlen(string) == 0)
        return true;
    else
        return false;
}

bool STR_IsAlpha(char* string, int size)
{
	CHECK_STRING( string, IS_NOT_EMPTY );
	
	bool isAlphaString = true;
	DBG("Entering %s() with string as '%s' and size is %d",__func__, string, size);
	for( int i = 0; i < size ; i++)
	{
		DBG("testing char '%c'",string[i]);
		
		if( !(islower(string[i]) || isupper(string[i])) )
		{
		 	isAlphaString = false; break;
		}		
							
	}
	return isAlphaString;

}

