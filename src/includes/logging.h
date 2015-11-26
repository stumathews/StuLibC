/**
 * @file logging.h
 * @brief Useful logging library function prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with logging functionality in the library.
 * This includes appending log messages to text file etc..
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page logging Logging
This is a narative on this part of the library
\include logging.h
*/

#ifndef STULIBC_LOGGING_H
#define STULIBC_LOGGING_H

#include <stdio.h>
#include <stdarg.h>
#include <timing.h>
#include <files.h>
#include <constants.h>

#define LOG(format, ...) do {\
			char buffer[256];\
			snprintf( buffer,256,  "LOG: %s-%d %s(): " format , __FILE__, __LINE__, __func__,##__VA_ARGS__);  \
			printf( "LOG: %s-%d %s(): " format "\n" , __FILE__, __LINE__,__func__,##__VA_ARGS__);  \
            LOG_Log(buffer); \
} while (0)
#define logif(cr,m,c) LOG_If(cr,m,c)

/** \brief Logs a message to the standard log file if the condition is true
 *
 * \param condition_result int
 * \param message char*
 * \return LIBRARY_API int
 *
 */
LIBRARY_API int   LOG_If(int condition_result, char* message);
/** \brief Write a string to the default log file
 *
 * \param message char*
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  LOG_Log(char* message);
/** \brief Write a log string to a stream
 *
 * \param message char*
 * \param stream FILE*
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  LOG_LogToStream(char* message, FILE* stream);
/** \brief Delete the default log file.
 *
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  LOG_DeleteLog();
/** \brief Get the default log file name
 *
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API char* LOG_GetDefaultLogFileName();

/** \brief Write a string to a named log file
 *
 * \param message char* messag to log
 * \param filename char* filename to log to (will create the file if it does not exist)
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void LOG_LogLineToFile( char* message, char* filename );



#endif // STULIBC_LOGGING_H
