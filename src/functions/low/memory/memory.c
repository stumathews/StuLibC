#ifndef STULIBC_MEMORY_H
#define STULIBC_MEMORY_H

#include <stdio.h>
#include <debugging.h>
#include <stdlib.h>
#include <memory.h>
#include <linuxlist.h>
#include <stulibc.h> // for LIB_*

/**
 * All the tracked memory addresses
 */
struct TrackedAddress mem_addrs;
struct TrackedAddress* tmp;
struct list_head *pos, *q;

void MEM_Init()
{
    INIT_LIST_HEAD(&mem_addrs.list);
}
void MEM_Uninit()
{
    MEM_DeAllocAll();
}

static void track_buffer(void* buffer)
{
  struct TrackedAddress* tmp = (struct TrackedAddress*) malloc(sizeof(struct TrackedAddress));
  tmp->mem_loc = buffer;
  list_add(&(tmp->list), &(mem_addrs.list));
}

void* MEM_Alloc(size_t size)
{
  LIB_Check_Init();

  void* buffer = malloc(size);

  memset(buffer,0,size);

  if( buffer != NULL )
  {
    track_buffer(buffer);
    return buffer;
  }
  else
  {
    DBG("MEM_Alloc(): Could not allocate buffer.\n");
    exit(1);
  }
}

int MEM_GetTrackedCount()
{
	struct TrackedAddress* tmp;
	struct list_head *pos;
	int count = 0;
	tmp = malloc(sizeof(struct TrackedAddress));

	list_for_each(pos, &mem_addrs.list){
		tmp = list_entry(pos, struct TrackedAddress, list);
		count++;
	}
  
  return count;
}

static struct TrackedAddress* find( void* buffer)
{
	struct TrackedAddress* tmp;
	struct list_head *pos;

	list_for_each(pos, &mem_addrs.list)
	{
        tmp = list_entry(pos, struct TrackedAddress, list);
        if (tmp->mem_loc == buffer)
        {
            return tmp;
        }		
    }
	return NULL;
}

void MEM_DeAllocAll()
{
	int count = 0;
	list_for_each_safe(pos, q, &mem_addrs.list)
	{
		tmp = list_entry(pos, struct TrackedAddress, list);
		list_del(pos);
		free(tmp);
		count++;
	}

  DBG("Deallocated %d tracked buffers.", count);
}

bool MEM_DeAlloc(void* buffer, char* buffer_name)
{
	list_for_each_safe(pos, q, &mem_addrs.list)
	{
		tmp = list_entry(pos, struct TrackedAddress, list);
		if (buffer == tmp->mem_loc)
		{
			if (tmp->mem_loc == NULL)
			{
				DBG("found buffer unexpectantly set to NULL. ");
				return false;
			}
			else
			{
				free(tmp->mem_loc);
			}
			list_del(pos);
			free(tmp);
			return true;
		}
	}  
  return true; // nothing happened.
}

bool MEM_CheckAllocated( void* buffer,char* name, char* filename, int line)
{

  struct TrackedAddress* tracked_buffer = find( buffer);
  if( tracked_buffer != NULL )
  {
    return true;
  }

  return false;
}

#endif
