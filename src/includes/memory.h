/**
 * @file memory.h
 * @brief Memory management library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with memory functionality in the library.
 * This includes allocating dynamic memory to working with memory locations such as manipulating blocks of memory.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page memory Memory
This is a narative on this part of the library
\include memory.h
*/

#ifndef STULIBC_MEMORY_MANAGEMENT_H
#define STULIBC_MEMORY_MANAGEMENT_H
#include <stdlib.h>
#include <stdbool.h>
#include <constants.h>
#include <list.h>

// Common memory related functions like allocating memory or filling memory and freeing it etc.
LIBRARY_API bool MEM_DeAlloc(void* buffer);
LIBRARY_API void* MEM_Alloc(size_t size);
LIBRARY_API bool MEM_CheckAllocated(void* buffer);

#endif
