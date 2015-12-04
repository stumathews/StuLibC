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

char* STR_Without(const char* without, const char* source, char* result)
{    
    short withoutLength = strlen(without);
    short sourceLength = strlen(source);
    strcpy(result, source);
    char* ptrFound;
	while ((ptrFound = strstr(result, without)) != NULL) {
		strcpy(ptrFound, ptrFound + withoutLength);
    }
	DBG("source '%s' without '%s' is '%s'", source, without, result);
	return result;
}

bool STR_Contains(char* lookfor, char* orig)
{
    if( lookfor == null || strlen(lookfor) == 0 ) DBG("Bad juju 1\n");
    if( orig == null || strlen(orig) == 0 ) DBG("Bad juju 2\n");
    return (strstr((const char*)orig, (const char*)lookfor) != NULL) ? true:false;
}

bool STR_EndsWith(char* endsWith, char* string)
{
    short lookForLength = strlen(endsWith);
    short stringLength = strlen(string);
    if(stringLength == 0 || lookForLength == 0 || stringLength < lookForLength)
        return false;
    if(strcmp(string + (stringLength - lookForLength), endsWith) == 0)    // compare end of string with endsWith
        return true;
    else
        return false;
}

char* STR_FromLast(const char* lookfor, const char* string, char* result_buffer)
{
    short lookForLength = strlen(lookfor);
    short stringLength = strlen(string);

    strcpy(result_buffer,string);
    char* occurance = NULL;
    char* last_occurance = NULL;

    while((occurance = strstr(result_buffer,lookfor)) != NULL) {
        strcpy(occurance,occurance+lookForLength);
        last_occurance = occurance;
    }

    strcpy(result_buffer, last_occurance);
    return result_buffer;
}

char* STR_Join(char* s1, char* s2)
{
    char *s0 = Alloc(strlen(s1)+strlen(s2)+1);
    strcpy(s0, s1);
    strcat(s0, s2);
    return s0;
}

char* STR_AppendStrings(char* first, char* second)
{
    return STR_Join(first,second);
}

void STR_ToLower(char* string, int strlen)
{
	for( int i = 0; i < strlen -1;i++ ) { tolower(string[i]); }
}

bool STR_IsNullOrEmpty(char* string)
{ 
    if( string == NULL )
    {
        return true;
    }

    if( string[0] == '\0')
    {
        return true;
    }
    return false;
}

bool STR_IsAlpha(char* string, int size)
{
    CHECK_STRING( string, IS_NOT_EMPTY );

    bool isAlphaString = true;
    DBG("Entering %s() with string as '%s' and size is %d",__func__, string, size);
    for( int i = 0; i < size ; i++)
    {
        if( !(islower(string[i]) || isupper(string[i])) )
        {
            isAlphaString = false; break;
        }		

    }
    return isAlphaString;

}

char* STR_Reverse(char* string )
{
    int length = strlen(string);

    int i;
    for( i = 0 ; i < (length/2); i++)
    {
        char tmp = string[i];        
        int rightpos = (length-1)-i;
        string[i] = string[rightpos];
        string[rightpos] = tmp;
    }
    return string;
}

void STR_Rtrim(char *str)
{
  size_t n;
  n = strlen(str);
  while (n > 0 && isspace((unsigned char)str[n - 1])) {
    n--;
  }
  str[n] = '\0';
}

void STR_Ltrim(char *str)
{
  size_t n;
  n = 0;
  while (str[n] != '\0' && isspace((unsigned char)str[n])) {
    n++;
  }
  memmove(str, str + n, strlen(str) - n + 1);
}

void STR_Trim(char *str)
{
  STR_Rtrim(str);
  STR_Ltrim(str);
}

bool STR_Equals( char* string1, char* string2 )
{
	char string1_cpy[strlen(string1)+1];
	strcpy(string1_cpy, string1);
	char string2_cpy[strlen(string2)+1];
	strcpy(string2_cpy, string2);

	STR_Trim(string1_cpy);
	STR_Trim(string2_cpy);

    if( strcmp( string1_cpy, string2_cpy ) == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool STR_EqualsIgnoreCase( char* string1, char* string2 )
{
	int len1 = strlen(string1);
	int len2 = strlen(string2);
	char string1_cpy[len1+1];
	char string2_cpy[len2+1];
	
	strcpy(string2_cpy, string2);
	strcpy(string1_cpy, string1);
	
	STR_ToLower(string1_cpy, len1);
	STR_ToLower(string2_cpy, len2);


	if( strcmp( string1, string2 ) == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}


