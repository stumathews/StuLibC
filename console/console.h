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
#include "common.h"
#include <stdio.h>

#define console(message) CNS_Print((message))
#define console_printline(message) CNS_PrintLine((message))
/* Functions that do useful things wit the console */

LIBRARY_API void CNS_PrintLine(char* message);
void CNS_Print( char* message );

void table(const char *title, const char *mode);
#endif
