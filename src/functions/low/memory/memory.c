#ifndef STULIBC_MEMORY_H
#define STULIBC_MEMORY_H

#include <stdio.h>
#include <debugging.h>
#include <stdlib.h>
#include <memory.h>
#include <stulibc.h> // for LIB_*


static void track_buffer(void* buffer, List* mem_pool)
{
  if(buffer == NULL) {
	PRINT("Cant allocated null buffer:%p\n", buffer);
  }

  if(mem_pool == NULL) {
     PRINT("Memory subsystem not initialised. doing it now");
     exit(1);
  }
  LIST_Add(mem_pool, buffer);
}

void* MEM_Alloc(size_t size, List* mem_pool)
{
	DBG("MEM_Alloc()\n");
	void* buffer = malloc(size);

	if(buffer == NULL) {
		DBG("Failed to malloc \n");
		return NULL;
	}

	memset(buffer,0,size);

	if(buffer != NULL) {
	    track_buffer(buffer, mem_pool);
    	    return buffer;
  	} else {
    		DBG("MEM_Alloc(): Could not allocate buffer.\n");
		exit(1);
  	}
}

int MEM_GetTrackedCount(List* mem_addrs)
{
  return mem_addrs->size;
}

static void* find(void* buffer, List* mem_addrs)
{
	Node* result = LIST_FindData((const List*)mem_addrs, buffer);
	return result != NULL ? result->data : NULL;
}

static int dealloc_count = 0;
static void freeBuffer(Node* node)
{
	free(node->data);
	dealloc_count++;
}

void MEM_DeAllocAll(List* mem_addrs)
{
  LIST_ForEach((const List*)mem_addrs, freeBuffer);
}

bool MEM_DeAlloc(void* buffer, char* buffer_name, List* mem_addrs)
{
	Node* result = LIST_FindData((const List*)mem_addrs, buffer);
	
	if(result == NULL || result->data == NULL ) {
		DBG("Could not find buffer %p, mem_addrs size is %d\n", buffer, mem_addrs->size);
		 return false; 
	}


	LIST_DeleteNode(mem_addrs, result);
	//freeBuffer(result);

	return true;
}

bool MEM_CheckAllocated( void* buffer,char* name, char* filename, int line, List* mem_addrs)
{
  void* tracked_buffer = find( buffer, mem_addrs);
  if(tracked_buffer != NULL)  {
    return true;
  }

  return false;
}

#endif
