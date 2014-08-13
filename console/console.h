/**
 * @file Console.h
 * @brief Console function prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the various console management functions defined in the library.
 * These typically involve reading and writing to and from the console in various ways
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page console Using console functionality
This is a narative on this part of the library
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
