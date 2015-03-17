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
    struct Address* previous;
} *mem_addrs, *first = NULL;

static void track_buffer(void* buffer)
{
      // track this buffer as being allocated by MEM_Alloc.
      if( mem_addrs == NULL )
      {
        mem_addrs = malloc( sizeof( struct Address ));
        mem_addrs->mem_loc = buffer;
        mem_addrs->next = NULL;
        mem_addrs->previous = NULL;
        first = mem_addrs;
      }
      else
      {
       // traverse the linked linked list until the last node ois reached:
        while( mem_addrs->next != NULL )
            mem_addrs= mem_addrs->next;

        struct Address *tmp = malloc( sizeof(struct Address));
        tmp->mem_loc = buffer;
        tmp->next = NULL;
        tmp->previous = mem_addrs;

        mem_addrs->next = tmp;

      }
}

void* MEM_Alloc(size_t size)
{
  void* buffer = malloc(size);

  if( buffer != NULL )
  {
    track_buffer(buffer);
    return buffer;
  }
  else
  {
    DBG("MEM_Alloc(): Could not allocate buffer.\n");
  }
}

int MEM_GetTrackedCount()
{
    
  struct Address* addr = first;
  int count = 0;
  while( addr != NULL )
  { 
    count++;
    addr = addr->next;
  }
  return count;
}

void print_tracked()
{
  struct Address* addr = first;
  bool found = false;
  int count = 0;
  if( first == NULL )
  {
    DBG("no tracked buffers\n"); return;
  }
  while( addr != NULL )
  { 
    count++;
    DBG("(%d)%p\n",count,addr->mem_loc);
    addr = addr->next;
  }
  printf("\n");
}

// removes current link
static void remove_link(struct Address* current)
{
    if( current == first )
    {
        free(current);
        current = first = NULL;
        return;
    }
    //previous-current-next
    struct Address* previous = current->previous;
    struct Address* next = current->next;
    if( previous != NULL)
        previous->next = current->next;
    if( next != NULL )
        next->previous = current->previous;

    free(current);
}

bool MEM_DeAlloc(void* buffer, char* buffer_name)
{
  struct Address* addr = first;
  struct Address* found_buffer = NULL;
  bool found =false;

  // find this buffer in our tracked list of buffers...
  while( addr != NULL )
  { 
    if(addr->mem_loc == buffer)
    {
     found = true;
     found_buffer = addr;
     break;	
    }
    addr = addr->next;
  }

  // dont care about buffers that are NULL, they are already deallocated
  if( buffer == NULL )
  {
    DBG("Attempted to deallocated null pointer, '%s'. ignored.",buffer_name);
    return false;
  }
  else
  {
    if( found )
    {
      if( found_buffer != NULL )
      {
          free(buffer);
          remove_link(found_buffer);
      }
      else
      {
        DBG("found buffer unexpectantly set to NULL. ");
        return false;
      }
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
