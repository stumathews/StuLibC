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

/** \page memory Memory managment functionality
This is a narative on this part of the library
*/

#ifndef STULIBC_MEMORY_MANAGMENT_H
#define STULIBC_MEMORY_MANAGEMENT_H

// Common memory related functions like allocating memory or filling memory and freeing it etc.

#define MEM_allocate(size) malloc((size)
#define MEM_resize(ptr,size) realloc( (ptr),(size))
#define MEM_zero_allocate(nelem,elsize) calloc((nelem),(elsize))
#define MEM_free(ptr) free((ptr))

#endif
