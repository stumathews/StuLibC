#ifndef STULIBC_MEMORY_H
#define STULIBC_MEMORY_H

#include <stdio.h>
#include <debugging.h>
#include <stdlib.h>
#include <memory.h>
#include <stulibc.h> // for LIB_*

void* MEM_Alloc(size_t size)
{
	void* buffer = malloc(size);
	memset(buffer,0,size);
	return buffer;
}

bool MEM_DeAlloc(void* buffer)
{
	free(buffer);
	buffer = NULL;
	return true;
}

bool MEM_CheckAllocated(void* buffer)
{
  return buffer != NULL;
}

#endif
