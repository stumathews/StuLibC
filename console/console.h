/**
 * @file xxxx.h
 * @brief xxxx function prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the xxx functions defined in the library.
 * These typically involve xxx
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page xxxx Using xxxx functionality
xxxx
*/

#ifndef STULIBC_CONSOLE_H
#define STULIBC_CONSOLE_H

#include "..\common.h"
#include <stdio.h>

#define console(message) CNS_Print((char*)(message))
#define console_printline(message) CNS_PrintLine((char*)(message))

LIBRARY_API void CNS_PrintLine(char* message);
LIBRARY_API void CNS_Print( char* message );
LIBRARY_API void table(const char *title, const char *mode);

#endif
