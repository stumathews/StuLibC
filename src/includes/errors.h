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

/** \page Errors Using error handling functionality
This is a narative on this part of the library
*/

#ifndef STULIBC_ERRORS_H
#define STULIBC_ERRORS_H
#include <constants.h>
#include <stdlib.h>

#ifndef NDEBUG
#define ERR(format, ...) do {\
      fprintf(stderr, "%s-%d: ", __FILE__, __LINE__);  \
      printf((format), ##__VA_ARGS__); \
      exit(1); \
} while (0)
#else
#define ERR(format, ...) do {\
      fprintf(stderr, "%s-%d: ", __FILE__, __LINE__);  \
      exit(1); \
} while (0)
#endif
/** \brief Prints a standard error heading string attached to provided message and any last error message identified by the system and logs it.
 *
 * \param error const char* the message to log
 * \param should_log int should this be logged to te standard log file
 * \return LIBRARY_API void
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
