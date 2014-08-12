/**
 * @file common.h
 * @brief common declarations used by the library.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the various declarations defined in the library.
 * These typically are used/shared across the library.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page common Using shared declarations
This is a narative on this part of the library
*/
#ifndef STULIBC_COMMON_H
#define STULIBC_COMMON_H

// We expose some functions in a windows run-time link library by exposing __declspec
// for function we expose in the library.
// other platforms will not resolve LIBRARY_API to __declspec
#ifdef _WIN32
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API
#endif

#endif // STULIBC_STRING_H


