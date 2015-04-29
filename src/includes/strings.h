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
*/

#ifndef STULIBC_STRING_H
#define STULIBC_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <constants.h>
#include <stdbool.h>

/** \brief Concatenates two strings
 *
 * \param s1 const char*
 * \param s2 const char*
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API char* STR_Join(char* s1,char* s2);


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

/** \brief Determines if a string begins with any possibilities provided
 *
 * \param posibilities[] char*
 * \param string char* the possibility found at the beginning or any empty string if it didnt begin with any of the provided possibilities
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API char* STR_BeginsWithEither( char* posibilities[], char* string);

/** \brief Determines if a string begins with a character
 *
 * \param beginsWith char*
 * \param string char*
 * \return LIBRARY_API bool
 *
 */
LIBRARY_API bool STR_BeginsWith( char* beginsWith, char* string );

/** \brief Determines if a string is empty or NULL
 *
 * \param string char*
 * \return LIBRARY_API bool
 *
 */
LIBRARY_API bool STR_IsNullOrEmpty(char* string);

/** \brief copies the string without the specified substring in it.
 *
 * \param without_str char* string to be removed from the source string
 * \param string char* the source string
 * \return LIBRARY_API char* the result
 *
 */
LIBRARY_API char* STR_Without( char* without_str, char* string);

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
LIBRARY_API char* STR_FromLast( char* last, char* string, char* resultBuffer);

/** \brief Determines if the string contains alphabetic characters
 *
 * \param string char* the string that needs to be checked
 * \param len int the length of the string
 * \return LIBRARY_API bool true if string contains only alphabetic characters
 *
 */
LIBRARY_API bool STR_IsAlpha( char* string, int len);

/** \brief Reverse a string
 * 
 * \param string char* the string to reverse
 * \return the reversed string
 */
LIBRARY_API char* STR_Reverse( char* string );


#endif // STULIBC_STRING_H
