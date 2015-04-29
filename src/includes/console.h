/**
 * @file console.h
 * @brief Console handling routines
 * @author Stuart Mathews
 * @date 10 January 2014
 *
 * This header contains console stuff
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page console Console
these are the console handling routines
*/

#ifndef STULIBC_CONSOLE_H
#define STULIBC_CONSOLE_H

#include <constants.h>
#include <stdio.h>

#define console(message) CNS_Print((char*)(message))
#define console_printline(message) CNS_PrintLine((char*)(message))

#define PRINT(format, ...) do {\
			char buffer[256];\
			snprintf( buffer,256,  "DBG : %s-%d stulic::%s(): " format "\n", __FILE__, __LINE__,__func__,##__VA_ARGS__);  \
            printf("%s\n",buffer); \
} while (0)


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
