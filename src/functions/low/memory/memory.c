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
} *mem_addrs, *first;

void track_buffer(void* buffer)
{
  // track this buffer as being allocated by MEM_Alloc.
  if( mem_addrs == NULL )
  {
    mem_addrs = malloc( sizeof( struct Address ));
    mem_addrs->mem_loc = buffer;
    mem_addrs->next = NULL;
    first = mem_addrs;
    DBG("allocating buffer %p\n", buffer);
  }
  else
  {
    DBG("allocating new buffer %p\n", buffer);
    struct Address *tmp = malloc( sizeof(struct Address));
    tmp->mem_loc = buffer;
    tmp->next = NULL;
    
    mem_addrs->next = tmp;
    mem_addrs = tmp;
  }
  
}

void* MEM_Alloc(size_t size)
{
  void* buffer = malloc(size);
  track_buffer(buffer);
  if( buffer != NULL ){
    return buffer;
  }
  else
    DBG("MEM_Alloc(): Could not allocate buffer.\n");
}

void print_tracked()
{
  DBG("Printing all tracked buffers:\n");
  struct Address* addr = first;
  bool found = false;
  int count = 0;
  while( addr != NULL )
  { 
    count++;
    if( addr == first)
      DBG("(%d)%p",count,addr->mem_loc);
    else
     DBG("->(%d)%p",count,addr->mem_loc);
    addr = addr->next;
  }
printf("\n");
}

bool MEM_DeAlloc(void* buffer, char* buffer_name)
{
  struct Address* addr = first;
  bool found = false;
  while( addr != NULL )
  { 
    DBG("Trackded buffer %p\n",addr->mem_loc);
    if(addr->mem_loc == buffer)
    {
     found = true;
     // remove this link
     break;	
    }
    addr = addr->next;
  }
  if( buffer == NULL )
  {
    DBG("Attempted to deallocated null pointer, '%s'. ignored.",buffer_name);
    return false;
  }
  else
  {
    DBG("Attemping to free pointer %p\n", buffer);
    if( found )
    {
      free(buffer);
      return true;
    }
    else
    {
      DBG("Wont dealloc a buffer that wasnt created by MEM_Alloc\n");
      return false;
    }
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
