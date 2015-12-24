/**
 * @file strings.h
 * @brief String library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with string functionality in the library.
 * This includes creating, copying, manipulating strings.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page libstring Strings
This is a narative on this part of the library
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
 * Dynamically allocates space for the two strings and then joins them together, copying them to this space.
 *
 * @param string1
 * @param string2
 * @return char* as location of the joined strings in memory.
 * @note The caller needs to deallocate the memory, or it will be deallocated automatically
 * when the program exists ie. this is not a memory performant routine in TSR based or long running applications.
 */
LIBRARY_API char* STR_Join(const char* s1,const char* s2);


/** \brief Creates a string in a memory buffer
 *
 * \param string char*
 * \return LIBRARY_API char* the address of the memory buffer
 * \note the caller is expected to free the memory buffer
 */
LIBRARY_API char* STR_CreateString( char* string);

/** \brief Appends 2 strings together and returns a pointer to it.
 *
 * \param first char*
 * \param second char*
 * \return LIBRARY_API char*
 * \note A new string is automatically allocated and its up to the caller to free it.
 *
 */
LIBRARY_API char* STR_AppendStrings( char* first, char* second);

/***
 * Checks to see if the string begins with any of the possibilities
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

/** \brief copies the string without the specified substring in it.
 *
 * \param without_str char* string to be removed from the source string
 * \param string char* the source string
 * \param string char* theresult of removing the substring from the source
 * \return LIBRARY_API char* the result
 *
 */
LIBRARY_API char* STR_Without( const char* without_str, const char* string, char* result);

/** \brief Determines if the string contains the provided character or not
 *
 * \param lookfor char*
 * \param orig char*
 * \return LIBRARY_API bool
 *
 */
LIBRARY_API bool STR_Contains( char* lookfor, char* orig);

/** \brief Determins if the string ends with provided character or not.
 *
 * \param endsWith char*
 * \param string char*
 * \return LIBRARY_API bool
 *
 */
LIBRARY_API bool STR_EndsWith( char* endsWith, char* string);

/** \brief Determines if the the string ends with any of the possibly characters provided.
 *
 * \param endsWithPossibilities[] char*
 * \param string char* returns the possibility found or an empty string
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API char* STR_EndsWithEither( char* endsWithPossibilities[], char* string);

/** \brief Copies the remaining characters from the last detected occurance of specified character into a buffer
 *
 * \param last char*
 * \param string char*
 * \param resultBuffer char*
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API char* STR_FromLast( const char* last, const char* string, char* resultBuffer);

/** \brief Determines if the string contains alphabetic characters
 *
 * \param string char* the string that needs to be checked
 * \param len int the length of the string
 * \return LIBRARY_API bool true if string contains only alphabetic characters
 *
 */
LIBRARY_API bool STR_IsAlpha( const char* string, int len);

/** \brief Reverse a string
 * 
 * \param string char* the string to reverse
 * \return the reversed string
 */
LIBRARY_API char* STR_Reverse( char* string );

/***
 * Compares two strings to see if they are the sameor not
 * @param string1
 * @param string2
 * @note Will trim the strings before comparing.
 */
LIBRARY_API bool STR_Equals(char* string1, char* string2 );
/**
 * Trims the whitespace from the string
 * @param str string to modify
 * \remark modifies string in place
 */
LIBRARY_API size_t STR_Trim(char *str);

/**
 * Trims the whitespace from the right of string
 * @param str string to modify
 * \remark modifies string in place
 */
LIBRARY_API size_t STR_Rtrim(char *str);

/**
 * Trims the whitespace from the left of string
 * @param str string to modify
 * \remark modifies string in place
 */
LIBRARY_API size_t STR_Ltrim(char *str);

/***
 * Compares two strings independant of there case for equality
 * @param string1
 * @param string2
 * @return
 */
LIBRARY_API bool STR_EqualsIgnoreCase( const char* string1, const char* string2 );

#endif // STULIBC_STRING_H
