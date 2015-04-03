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

// track this buffer as being allocated by MEM_Alloc.
static void track_buffer(void* buffer)
{
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

        // Append the buffer to the end of the list
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
    DBG("Tracked new buffer %p", buffer);
    DBG("Currently %d tracked buffers.", MEM_GetTrackedCount());
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
    DBG("No tracked buffers.\n"); return;
  }
  while( addr != NULL )
  { 
    count++;
    DBG("(%d)%p\n",count,addr->mem_loc);
    addr = addr->next;
  }
}

static void remove_link(struct Address* current)
{
    if( current == first )
    {
        free(current);
        current = first = NULL;
        return;
    }

    //Note: doubly linked list structure is represented as : previous-current-next
    struct Address* previous = current->previous;
    struct Address* next = current->next;
    if( previous != NULL)
        previous->next = current->next;
    if( next != NULL )
        next->previous = current->previous;

    free(current);
}

static struct Address* find( void* buffer)
{
  struct Address* addr = first;

  // find this buffer in our tracked list of buffers...
  while( addr != NULL )
  { 
    if(addr->mem_loc == buffer)
    {
     return  addr;
     break;	
    }
    addr = addr->next;
  }

  return NULL;
}

bool MEM_DeAllocAll()
{
  struct Address* addr = first;
  int count = 0;

  while( addr != NULL )
  { 
        free(addr->mem_loc);
        struct Address* toRemove = addr;
        addr = addr->next;
        remove_link(toRemove);
        count++;
  }

  DBG("Deallocated %d tracked buffers.", count);

  return true;
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

  if( !found )
  {
    DBG("Wont dealloc a buffer that wasnt created by MEM_Alloc\n");
    return false;
  }

  if( found_buffer == NULL )
  {
     DBG("found buffer unexpectantly set to NULL. ");
     return false;
  }
    
   
  free(buffer);
  remove_link(found_buffer);
  return true;
}

bool MEM_CheckAllocated( void* buffer,char* name, char* filename, int line)
{

  struct Address* tracked_buffer = find( buffer);
  if( buffer != NULL )
  {
    return true;
  }

  return false;
}

#endif
