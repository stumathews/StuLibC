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

bool STR_BeginsWith(const char* beginsWith, const char* string)
{
	CHK_ExitIf(beginsWith == null, "begins with cannot == null", (char*) __func__);
	CHK_ExitIf(string == null, "string with cannot == null", (char*)__func__);

    if(strlen(string) < strlen(beginsWith))
    	return false;

    return strncmp(string, beginsWith, strlen(beginsWith)) == 0 ? true: false;
}

/***
 * Checks to see if the string begins with any of the possibilities
 * @param possibilities a pointer to an array of strings
 * @param string
 * @param max the number of possibilities
 * @return empty string if no possibilities match or the posibility that matched
 */
const char* STR_BeginsWithEither(const char* possibilities[], const char* string, int max)
{
	CHK_ExitIf(possibilities == NULL,"possibilities cannot be null", (char*)__func__);

    for(int i = 0; possibilities[i] != NULL && i < max; i++) {
        if(STR_BeginsWith(possibilities[i], string) == true) {
            return possibilities[i];
        }
    }
    return "";
}

char* STR_EndsWithEither(char* endsWithPossibilities[], char* string)
{
	CHK_ExitIf(endsWithPossibilities == null, "endsWithPossibilities cannot be null", (char*)__func__);

    for(int i = 0; endsWithPossibilities[i] != NULL; i++) {
        if(STR_EndsWith(endsWithPossibilities[i], string) == true)
            return endsWithPossibilities[i];
    }
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

/**
 * Dynamically allocates space for the two strings and then joins them together, copying them to this space.
 *
 * @param string1
 * @param string2
 * @return char* as location of the joined strings in memory.
 * @note The caller needs to deallocate the memory, or it will be deallocated automatically
 * when the program exists ie. this is not a memory performant routine in TSR based or long running applications.
 */
char* STR_Join(const char* string1, const char* string2)
{
    char *joined = Alloc(strlen(string1) + strlen(string2) + 1);
	CHK_ExitIf(joined == (void*)0, "Unable to allocate memory.", "STR_Join()");

    strcpy(joined, string1);
    strcat(joined, string2);
    return joined;
}

#define STR_AppendStrings(first, second) STR_Join((first),(second))

/**
 * Converts the string, in place, to its lower case equivalent.
 * @param string
 * @param strlen the length of the string to vaoid buffer overflow
 */
void STR_ToLower(char* string, int strlen)
{
	for( int i = 0; i < strlen -1;i++ ) { tolower(string[i]); }
}

bool STR_IsNullOrEmpty(const char* string)
{ 
	return (string == NULL || strlen(string) == 0) ? true : false;
}

/***
 * Determines if the string constains entirely alphabetic characters (a-zA-Z)
 * @param string
 * @param length
 * @return
 */
bool STR_IsAlpha(const char* string, int length)
{
    CHECK_STRING( string, IS_NOT_EMPTY );

    bool isAlphaString = true;

    for( int i = 0; i < length ; i++)
    {
        if(!(islower(string[i]) || isupper(string[i])))
        {
            isAlphaString = false;
            break;
        }		
    }
    return isAlphaString;

}

/***
 * Revereses a string in place.
 * @param string
 * @return the same location of the original string but with its contents reversed.
 */
char* STR_Reverse(char* string )
{
    int length = strlen(string);
    char tmp;
    for( int i = 0 ; i < (length/2); i++)
    {
        tmp = string[i];
        int endmost = (length-1)-i;
        string[i] = string[endmost];
        string[endmost] = tmp;
    }
    return string;
}

/***
 * Trims, in place, the string from the right of all whitespace.
 * @param str
 * @return size of the string now
 */
size_t STR_Rtrim(char *str)
{
  size_t n = strlen(str);
  while (n > 0 && isspace((unsigned char)str[n - 1])) {
    n--;
  }
  str[n] = '\0';
  return strlen(str);
}

/***
 * Trims the string, inplace, of whitespace from the left of the string.
 * @param str
 * @return length of resulting trimmed string
 */
size_t STR_Ltrim(char *str)
{
  size_t n = 0;
  while (str[n] != '\0' && isspace((unsigned char)str[n])) {
    n++;
  }
  memmove(str, str + n, strlen(str) - n + 1);
  return strlen(str);
}

/***
 * Trims the string, in place, of any whitespace to the left or right of the string
 * @param str
 * @return length of string after trimming
 */
size_t STR_Trim(char *str)
{
  STR_Rtrim(str);
  STR_Ltrim(str);
  return strlen(str);
}

/***
 * Compares two strings to see if they are the sameor not
 * @param string1
 * @param string2
 * @note Will trim the strings before comparing.
 */
bool STR_Equals( char* string1, char* string2 )
{
	char string1_cpy[strlen(string1)+1];
	strcpy(string1_cpy, string1);

	char string2_cpy[strlen(string2)+1];
	strcpy(string2_cpy, string2);

	STR_Trim(string1_cpy);
	STR_Trim(string2_cpy);

	return strcmp( string1_cpy, string2_cpy ) == 0 ? true : false;
}

/***
 * Compares two strings independant of there case for equality
 * @param string1
 * @param string2
 * @return
 */
bool STR_EqualsIgnoreCase( const char* string1, const char* string2 )
{
	int len1 = strlen(string1);
	int len2 = strlen(string2);
	
	char string1_cpy[len1 + 1];
	char string2_cpy[len2 + 1];

	strcpy(string2_cpy, string2);
	strcpy(string1_cpy, string1);
	
	STR_ToLower(string1_cpy, len1);
	STR_ToLower(string2_cpy, len2);

	return strcmp(string1, string2) == 0 ? true : false;
}
