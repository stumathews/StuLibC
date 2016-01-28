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
#define alloc(a,b) MEM_Alloc((a),(b))

/** \brief Detect empty pointers
 *
 * \param buffer void* pointer to the pointer returned by malloc
 * \param buffer_name char* the identifier of this buffer (include purpose)
 * \param filename char* the filename that this pointer is used in.(use __file__)
 * \param line int the line that this occures on (use __LINE__)
 * \param mem_pool List* local list used to track/scope allocated memory
 * \return LIBRARY_API bool true if is allocated or false if not
 *
 */
LIBRARY_API bool MEM_CheckAllocated( void* buffer, char* buffer_name, char* filename, int line, List* mem_addrs);
/** \brief Calls free() on the provided buffer, provided the buffer can be freed.
 *
 * Decrements the memory pool by one if buffer is found
 * \param buffer void*
 * \param buffer_name char*
 * \param mem_pool List* local list used to track/scope allocated memory
 * \return LIBRARY_API void
 *
 */
LIBRARY_API bool MEM_DeAlloc(void* buffer, char* buffer_name, List* mem_addrs);
#define MEM_Alloc(a, b) Alloc(a,b)

// Not a library function to be used externally only internall by LIB_Uninit()
LIBRARY_API void MEM_DeAllocAll(List* mem_pool);


/** \brief Allocate a size amount of memory
 *
 * \param size size_t
 * \param mem_pool List* local list to track/scope allocated memory
 * \return LIBRARY_API void*
 */
LIBRARY_API void* MEM_Alloc(size_t size, List* mem_pool);

/** \brief Gets the number of tracked buffers by the library.
 * \param mem_pool List* local list used to track/scope allocated memory
 * \return LIBRARY_API int, the count of the number of tracked buffers
 *
 */
LIBRARY_API int MEM_GetTrackedCount(List* mem_pool);
#endif
