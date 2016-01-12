#ifndef STULIBC_MEMORY_H
#define STULIBC_MEMORY_H

#include <stdio.h>
#include <debugging.h>
#include <stdlib.h>
#include <memory.h>
#include <stulibc.h> // for LIB_*

/**
 * All the tracked memory addresses
 */
List* mem_addrs = 0;
void MEM_Init()
{
    mem_addrs = LIST_GetInstance();
}
void MEM_Uninit()
{
    MEM_DeAllocAll();
    LIST_FreeInstance(mem_addrs);
}

static void track_buffer(void* buffer)
{
  if(buffer == NULL) {
	DBG("Cant allocated null buffer:%p\n", buffer);
  }
  DBG("about to add it to internal list of addresses\n");
  if(mem_addrs == NULL) {
     DBG("Memmory subsystem not initialised. doing it now");
     MEM_Init();
  }
  LIST_Add(mem_addrs, buffer);
}

void* MEM_Alloc(size_t size)
{
	DBG("MEM_Alloc()\n");
	void* buffer = malloc(size);

	if(buffer == NULL) {
		DBG("Failed to malloc size %d\n", size);
		return NULL;
	}

	DBG("zeroing buffer");
	memset(buffer,0,size);

	if(buffer != NULL) {
	    track_buffer(buffer);
    	    return buffer;
  	} else {
    		DBG("MEM_Alloc(): Could not allocate buffer.\n");
		exit(1);
  	}
}

int MEM_GetTrackedCount()
{
  return mem_addrs->size;
}

static void* find(void* buffer)
{
DBG("find()\n");
	Node* result = LIST_FindData((const List*)mem_addrs, buffer);
	return result != NULL ? result->data : NULL;
}

static int dealloc_count = 0;
static void freeBuffer(Node* node)
{
DBG("freeBuffer()\n");
	free(node->data);
	dealloc_count++;
}

void MEM_DeAllocAll()
{
DBG("MEM_DeAllocAll(): prrinting mem locations in memaddrs(ptr: %d), size: %d\n", mem_addrs, mem_addrs->size);
  LIST_ForEach((const List*)mem_addrs, freeBuffer);
  DBG("Deallocated %d tracked buffers.", dealloc_count);
}

bool MEM_DeAlloc(void* buffer, char* buffer_name)
{
	DBG("before MEM_DeAlloc(%p): mem_addrs size: %d contents:\n", buffer,  mem_addrs->size);
	Node* result = LIST_FindData((const List*)mem_addrs, buffer);
	
	if(result == NULL || result->data == NULL ) {
		DBG("Could not find buffer %p, mem_addrs size is %d\n", buffer, mem_addrs->size);
		 return false; 
	}

	void* data = result->data;
	LIST_DeleteNode(mem_addrs, result);
	free(data);
	return true;
}

bool MEM_CheckAllocated( void* buffer,char* name, char* filename, int line)
{
DBG("MEM_CheckAllocated()\n");
  void* tracked_buffer = find( buffer);
  if(tracked_buffer != NULL)  {
    return true;
  }

  return false;
}

#endif
