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

/** \page logging Logging things
This is a narative on this part of the library
*/

#ifndef STULIBC_LOGGING_H
#define STULIBC_LOGGING_H

#include <stdio.h>

#define log(x,c) LOG_It(x,c)
#define logif(cr,m,c) LOG_If(cr,m,c)

int LOG_If(int condition_result, char* message, char* context);
void LOG_It(char* message,char* context);
static void LOG(char* message, FILE* stream, char* context);


#endif // STULIBC_LOGGING_H
