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
*/

#ifndef STULIBC_MEMORY_MANAGEMENT_H
#define STULIBC_MEMORY_MANAGEMENT_H
#include <stdlib.h>
#include <stdbool.h>
#include <constants.h>

// Common memory related functions like allocating memory or filling memory and freeing it etc.

#define MEM_allocate(size) malloc((size)
#define MEM_resize(ptr,size) realloc( (ptr),(size))
#define MEM_zero_allocate(nelem,elsize) calloc((nelem),(elsize))
#define MEM_free(ptr) free((ptr))
#define MEM_copy(s,ct,n) memcpy((s),(ct),(n))
#define MEM_move(s,ct,n) memmove((s),(ct),(n))
#define MEM_compare(cs,ct,n) memcmp((cs),(ct),(n))
#define MEM_get_first_char(cs,c,n) memchr((cs),(c),(n))
#define MEM_set(s,c,n) memset((s),(c),(n))
#define alloc(s) MEM_Alloc((s)) 

/** \brief Detect empty pointers
 *
 * \param buffer void* pointer to the pointer returned by malloc
 * \param buffer_name char* the identifier of this buffer (include purpose)
 * \param filename char* the filename that this pointer is used in.(use __file__)
 * \param line int the line that this occures on (use __LINE__)
 * \return LIBRARY_API bool true if is allocated or false if not
 *
 */
LIBRARY_API bool MEM_CheckAllocated( void* buffer, char* buffer_name, char* filename, int line);
/** \brief Calls free() on the provided buffer, provided the buffer can be freed.
 *
 * \param buffer void*
 * \param buffer_name char*
 * \return LIBRARY_API void
 *
 */
LIBRARY_API bool MEM_DeAlloc(void* buffer, char* buffer_name);
#define MEM_Alloc(a) Alloc(a)

// Not a library function to be used externally only internall by LIB_Uninit()
void MEM_DeAllocAll();


/** \brief Allocate a size amount of memory
 *
 * \param size size_t
 * \return LIBRARY_API void*
 *
 *
 */
LIBRARY_API void* MEM_Alloc(size_t size);

/** \brief Gets the number of tracked buffers by the library.
 *
 * \return LIBRARY_API int, the count of the number of tracked buffers
 *
 */
LIBRARY_API int MEM_GetTrackedCount();
#endif
