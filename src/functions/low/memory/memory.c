/**
 * @file memory.h
 * @brief Memory function prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the various memory management functions defined in the library.
 * These typically involve interating with memory
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page memory memory functionality
This is a narative on this part of the library
*/

#ifndef STULIBC_MEMORY_H
#define STULIBC_MEMORY_H
#include <stdio.h>
#include <debugging.h>
#include <stdlib.h>
#include <memory.h>

struct Address {
	void* mem_loc;
	struct Address* next;
} mem_addrs = {};

void track_buffer(void* buffer)
{
  
}

void* MEM_Alloc(size_t size)
{
  void* buffer = malloc(size);
  track_buffer(buffer);
DBG("Allocated buffer %p\n",buffer);
  if( buffer != NULL ){
    return buffer;
  }
  else
    DBG("MEM_Alloc(): Could not allocate buffer.\n");
}

void MEM_DeAlloc(void* buffer, char* buffer_name)
{
  if( buffer == NULL )
  {
    DBG("Attempted to deallocated null pointer, '%s'. ignored.",buffer_name);
    return;
  }
  else
  {
    DBG("Attemping to free pointer %p\n", buffer);
    free(buffer);
  }
}

void MEM_CheckAllocated( void* buffer,char* name, char* filename, int line)
{
  if( buffer != NULL ){
    // we dont have to report anything as nothing seems to be allocated
    return;
  }
  else
  {
    DBG("Memory could not be allocated for buffer named '%s' in source file %s:%d", name, filename, line);
  }
}

#endif
