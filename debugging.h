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
This is a narative on this part of the library
*/

#ifndef STULIBC_DEBUGGING_H
#define STULIBC_DEBUGGING_H

#define debug(m,f,s) DBG_WriteLineToFile((m),(f),(s))
#define debugif(c,m,s) DBG_LogIf((c),(m),(s))
#define debugf(m,f,s) DBG_WriteLineToFile((m),(f),(s))
#define debugs(m,f,s) DBG_WriteLineToStream((m),(f),(s))

#include <stdio.h>


// Debugging functionality like writing to trace files, log files etc.
enum Severity
{
    MINOR,/**< Not very important */
    NORMAL, /**< Normal */
    CRITICAL, /**< Catestrophic  */
    UNSPECIFIED /**< Unsure */
};


/** @brief Writes a debug line to file.
 *
 * @param message char* message to write
 * @param filename char* file to write it to
 * @param severity enum Severity the severity of the debug line
 * @return void
 * @remarks The current date and time is prepended to message.
 */
void DBG_WriteLineToFile(char* message, char* filename, enum Severity severity);

/** @brief Writes a message to a file.
 *
 * @param prefix char* A prefix to tag the message if any or null
 * @param message char* the message to write
 * @param suffix char* the suffix to add to the message or null
 * @param filename char* the file to write the message to
 * @param severity SEVERITY An indication of the error
 * @return void
 * @remarks Adds the date and time to all messages. And appends to the end of @param filename
 *
 */
void DBG_WriteLineToFileExtra(char* prefix, char* message,char* suffix, char* filename, enum Severity severity);

/** @brief Returns a string representation of the severity enumeration
 *
 * @param severity enum Severity
 * @return char* the enumeration value as a string.
 *
 */
char* DBG_GetSeverityAsString(enum Severity severity);
void DBG_WriteLineToStream(char* message, FILE* stream, enum Severity severity);
void DBG_LogIfToStream( int condition, FILE* stream, char* message, char* otherwise);
void DBG_LogIf(int condition, char* message, char* otherwise);

#endif // STULIBC_DEBUGGING_H
