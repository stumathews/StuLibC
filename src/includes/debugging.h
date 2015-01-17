/**
 * @file debugging.h
 * @brief Debugging library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with debugging functionality in the library.
 * This includes tracing to logs, and reporting.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page debugging Debugging your program
Debugging functionality like writing to trace files, log files etc.
*/

#ifndef STULIBC_DEBUGGING_H
#define STULIBC_DEBUGGING_H

#define debug(m,f,s) DBG_WriteLineToFile((m),(f),(s))
#define debugif(c,m,s) DBG_LogIf((c),(m),(s))
#define debugf(m,f,s) DBG_WriteLineToFile((m),(f),(s))
#define debugs(m,f,s) DBG_WriteLineToStream((m),(f),(s))

#include <constants.h>
#include <stdio.h>

#ifndef NDEBUG
#define DBG(format, ...) do {\
      fprintf(stderr, "%s-%d: ", __FILE__, __LINE__);  \
      printf((format), ##__VA_ARGS__); \
} while (0)
#else
#define DBG(format, ...) do {\
      fprintf(stderr, "%s-%d: ", __FILE__, __LINE__);  \
} while (0)
#endif

/** \brief The severity of the aspect of debugging being identified.
 */
enum Severity
{
    MINOR,
    NORMAL,
    CRITICAL,
    UNSPECIFIED
};

// WriteLine functions
/** \brief Writes a message to a file, marking it with the provided severity
 *
 * \param message char* the message to write to the file
 * \param filename char* the file name to write the message to
 * \param severity enum Severity the severity of the message
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  DBG_WriteLineToFile(char* message, char* filename, enum Severity severity);
/** \brief Writes a message to a file, marking it with the provided severity and customised prefix
 *
 * \param prefix char*
 * \param message char*
 * \param suffix char*
 * \param filename char*
 * \param severity enum Severity
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  DBG_WriteLineToFileExtra(char* prefix, char* message,char* suffix, char* filename, enum Severity severity);
/** \brief Write a string to a stream.
 *
 * \param message char*
 * \param stream FILE*
 * \param severity enum Severity
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  DBG_WriteLineToStream(char* message, FILE* stream, enum Severity severity);
// Utility functions
/** \brief Deletes the default debugging log
 *
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  DBG_DeleteLog();
/** \brief Gets the name of the default debugging log
 *
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API char* DBG_GetDefaultLogFileName();
/** \brief Converts the numerical value of Severity to a friendly string
 *
 * \param severity enum Severity
 * \return LIBRARY_API char*
 *
 */
LIBRARY_API char* DBG_GetSeverityAsString(enum Severity severity);
// conditional logging
/** \brief Log a message to a file depending on the success of condition, or an alternative message on failure of condition
 *
 * \param condition int condition that needs to be true for the message to to be written to stream
 * \param stream FILE*
 * \param message char* the message if the condition is true
 * \param otherwise char* the message if the condition is false
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  DBG_LogIfToStream( int condition, FILE* stream, char* message, char* otherwise);
/** \brief Logs a message to the debugging log,if condition is met or provides an alternative message if condition is not met
 *
 * \param condition int
 * \param message char*
 * \param otherwise char*
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  DBG_LogIf(int condition, char* message, char* otherwise);
/** \brief Logs a message to the debugging log
 *
 * \param message char*
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  DBG_Log(char* message);
/** \brief Logs a failure message to the debugging log, and causes an assert to trigger.
 *
 * \param message char* message to log
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void  DBG_Fail(char* message);

#endif // STULIBC_DEBUGGING_H
