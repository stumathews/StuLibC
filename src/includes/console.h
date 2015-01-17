/**
 * @file console.h
 * @brief Console handling routines
 * @author Stuart Mathews
 * @date 10 January 2014
 *
 * This header contains console stuff
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page console Console handling in the library
these are the console handling routines
*/

#ifndef STULIBC_CONSOLE_H
#define STULIBC_CONSOLE_H

#include <constants.h>
#include <stdio.h>

#define console(message) CNS_Print((char*)(message))
#define console_printline(message) CNS_PrintLine((char*)(message))

/** \brief Prints a line of text to the console, including the newline character
 *
 * \param message char*
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void CNS_PrintLine(char* message);


/** \brief Prints a line of text to the console, not including the newline character
 *
 * \param message char*
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void CNS_Print( char* message );

#endif
