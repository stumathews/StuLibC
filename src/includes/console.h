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
\include console.h
*/

#ifndef STULIBC_CONSOLE_H
#define STULIBC_CONSOLE_H

#include <constants.h>
#include <stdio.h>

#define BUFFER_MAX 256

/* The intention of the PRINT functions is to send text to the user */

/**
 * Print message to the user without a newline
 * @param message
 */
#define PRINT(format, ...) do {\
			char buffer[BUFFER_MAX];\
			snprintf( buffer, BUFFER_MAX,  "DBG : %s-%d stulibc::%s(): " format, __FILE__, __LINE__,__func__,##__VA_ARGS__);  \
            CNS_Print(buffer); \
} while (0)

/**
 * Prrint message to the user with a new line
 * @param message
 */
#define PRINTLINE(format, ...) do {\
			char buffer[BUFFER_MAX];\
			snprintf( buffer, BUFFER_MAX,  "DBG : %s-%d stulibc::%s(): " format "\n", __FILE__, __LINE__,__func__,##__VA_ARGS__);  \
            CNS_PrintLine(buffer); \
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
