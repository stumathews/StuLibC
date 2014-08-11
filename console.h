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

/* Functions that do useful things wit the console */

LIBRARY_API void CNS_Say(char* message);

#endif
