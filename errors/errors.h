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

void ERR_Print(const char* error);

#endif
