/**
 * @file strings.h
 * @brief String library function prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with string functionality in the library.
 * This includes joining, trimming, converting & various checking functions.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page libstring Strings

Working with strings in C can often be laborious. Here are a few useful functions that can help.

In most cases all you need to do is either include string.h or stulibc.h and then the following functions
are at your disposal:
Function name  | Summary
------------- | -------------
STR_Join | Join two strings
STR_ToLower | Converts string to lower case
STR_BeginsWithEither | Does string begin with either list of possible strings
STR_BeginsWith | Does string begin with another
STR_IsNullOrEmpty | Is the string null or empty
STR_Without | Return string without substring
STR_Contains | Does string contain substring
STR_EndsWith | Does string end with another
STR_EndsWithEither | Does string end with possibilities
STR_FromLast | Return rest of string from last occurance
STR_IsAlpha | Is string only a-zA-Z
STR_Reverse | Reverse the string in place
STR_Equals | Is the string equal
STR_Trim | Remove whitespace on either side of string
STR_Rtrim | Remove whitespace on right of string
STR_Ltrim | Remove whitespace on left of string
STR_EqualsIgnoreCase | Are strings equal, ignore case

Function prototypes:

\include strings.h
*/

#ifndef STULIBC_STRING_H
#define STULIBC_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <constants.h>
#include <stdbool.h>

/**
 * @brief Joins two strings together
 *
 * Creates a new string by joining string1 and string2 together.
 * The new string will be allocated by the function.
 *
 * @b Note: This string is allocated by the function and needs to be deallocated by the @b caller.
 * Internally the following c runtime function are used
 * @verbatim
    strcpy(joined, string1);
    strcat(joined, string2);@endverbatim
 * Example of usage:
 * @code
    char expected[] = "one two";
    char* append_result = (char*) STR_Join( "one ", "two");
 * @endcode
 * @param string1 The first string
 * @param string2 The second string which will be appended to @p string1.
 * @return A new string allocated in memory with @p string2 appended to @p string1 *
 * @see http://www.stuartmathews.com
 * @note If the string cannot be allocated dynamically, the program exists
 * @warning This allocates memory from within and doesn't free it. This is probably not good use in a TSR or long running program
 */
LIBRARY_API char* STR_Join(const char* s1,const char* s2);

/** \brief Converts the string, in place, to its lower case equivalent.
 * @param string
 * @param strlen the length of the string to vaoid buffer overflow
 */
LIBRARY_API void STR_ToLower(char* string, int strlen);

/** \brief Checks to see if the string begins with any of the possibilities
 * @param possibilities a pointer to an array of strings
 * @param string
 * @param max the number of possibilities
 * @return
 */
LIBRARY_API const char* STR_BeginsWithEither(const char* posibilities[],const char* string, int max);

/** \brief Determines if a string begins with a character
 *
 * \param beginsWith char*
 * \param string char*
 * \return LIBRARY_API bool
 *
 */
LIBRARY_API bool STR_BeginsWith(const char* beginsWith, const char* string);

/** \brief Determines if a string is empty or NULL
 *
 * \param string char*
 * \return LIBRARY_API bool
 *
 */
LIBRARY_API bool STR_IsNullOrEmpty(const char* string);

/** \brief Removes the 'without' string from the source string and put the result in buffer
 * @param without
 * @param source
 * @param buffer
 * @return the buffer
 * @notes no source was harmed during the operation of this function
 */
LIBRARY_API char* STR_Without(const char* without_str, const char* string, char* result);

/** \brief Determines if the string contains the provided character or not
 *
 * \param lookfor char*
 * \param orig char*
 * \return LIBRARY_API bool
 *
 */
LIBRARY_API bool STR_Contains(char* lookfor, char* orig);

/** \brief Determins if the string ends with provided character or not.
 *
 * \param endsWith char*
 * \param string char*
 * \return LIBRARY_API bool
 *
 */
LIBRARY_API bool STR_EndsWith(const char* endsWith, const char* string);

/** \brief Determines if the the string ends with any of the possibly characters provided. *
 * \param endsWithPossibilities[] char*
 * \param string char* returns the possibility found or an empty string
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API const char* STR_EndsWithEither(char* endsWithPossibilities[], const char* string, int max);

/** \brief Copies the remaining characters from the last detected occurance of specified character into a buffer * \param last char*
 * \param string char*
 * \param resultBuffer char*
 * \param max size of the possibilities array *
 * \return LIBRARY_API char*
 * \note will check for NULL in endsWithPossibilities as signal to end processing it
 *
 */
LIBRARY_API char* STR_FromLast(const char* last, const char* string, char* resultBuffer);

/** \brief Determines if the string contains alphabetic characters
 *
 * \param string char* the string that needs to be checked
 * \param len int the length of the string
 * \return LIBRARY_API bool true if string contains only alphabetic characters
 *
 */
LIBRARY_API bool STR_IsAlpha(const char* string, int len);

/** \brief Reverse a string
 * 
 * \param string char* the string to reverse
 * \return the reversed string
 */
LIBRARY_API char* STR_Reverse(char* string );

/** \brief Compares two strings to see if they are the sameor not
 * @param string1
 * @param string2
 * @note Will trim the strings before comparing.
 */
LIBRARY_API bool STR_Equals(char* string1, char* string2 );

/** \brief Trims the whitespace from the string
 * @param str string to modify
 * \remark modifies string in place
 */
LIBRARY_API size_t STR_Trim(char *str);

/**  \brief Trims the whitespace from the right of string
 * @param str string to modify
 * \remark modifies string in place
 */
LIBRARY_API size_t STR_Rtrim(char *str);

/** \brief Trims the whitespace from the left of string
 * @param str string to modify
 * \remark modifies string in place
 */
LIBRARY_API size_t STR_Ltrim(char *str);

/** \brief Compares two strings independant of there case for equality
 * @param string1
 * @param string2
 * @return
 */
LIBRARY_API bool STR_EqualsIgnoreCase( const char* string1, const char* string2 );

#endif // STULIBC_STRING_H
