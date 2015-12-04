/**
 * @file errors.h
 * @brief error handling function prototypes.
 * @author Stuart Mathews
 * @date 14 Aug 2013
 *
 * This headers contains the error handling functions defined in the library.
 * This deals with writing errors to correct places, handling error conditions etc...
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page Errors Error handling
This is a narative on this part of the library
\include errors.h
*/

#ifndef STULIBC_ERRORS_H
#define STULIBC_ERRORS_H
#include <constants.h>
#include <stdlib.h>

/** \brief Prints a standard error heading string attached to provided message and any last error message identified by the system and logs it.
 *
 * \param error const char* the message to log
 * \param should_log int should this be logged to te standard log file
 * \return LIBRARY_API void
 * \remark it does NOT exit the program
 *
 */
LIBRARY_API void ERR_Print(const char* error, int should_log);
/** \brief Gets a string representing the last error known by the system.
 *
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API char* ERR_GetLastError();

#endif
