#ifndef STULIBC_MEMORY_H
#define STULIBC_MEMORY_H

#include <stdio.h>
#include <debugging.h>
#include <stdlib.h>
#include <memory.h>
#include <linuxlist.h>

struct Address mem_addrs;
struct Address* tmp;
struct list_head *pos, *q;

void MEM_Init()
{
    INIT_LIST_HEAD(&mem_addrs.list);
}
void MEM_Uninit()
{
    MEM_DeAllocAll();
}

// track this buffer as being allocated by MEM_Alloc.
static void track_buffer(void* buffer)
{
  struct Address* tmp = (struct Address*) malloc(sizeof(struct Address));
  tmp->mem_loc = buffer;
  list_add(&(tmp->list), &(mem_addrs.list));
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
	struct Address* tmp;
	struct list_head *pos;
	int count = 0;
	tmp = malloc(sizeof(struct Address));

	list_for_each(pos, &mem_addrs.list){
		tmp = list_entry(pos, struct Address, list);
		count++;
	}
  
  return count;
}

void print_tracked()
{

	int count = 0;

	tmp = malloc(sizeof(struct Address));

	list_for_each(pos, &mem_addrs.list){
		tmp = list_entry(pos, struct Address, list);
		DBG("(%d)%p\n", count++, tmp->mem_loc);
	}

	if (!count) { DBG("No tracked buffers.\n"); return; }
}


static struct Address* find( void* buffer)
{
	struct Address* tmp;
	struct list_head *pos;
	int count = 0;

	tmp = malloc(sizeof(struct Address));

	list_for_each(pos, &mem_addrs.list){
		tmp = list_entry(pos, struct Address, list);
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
	list_for_each_safe(pos, q, &mem_addrs.list){
		tmp = list_entry(pos, struct Address, list);
		list_del(pos);
		free(tmp);
		count++;
	}

  DBG("Deallocated %d tracked buffers.", count);
}

bool MEM_DeAlloc(void* buffer, char* buffer_name)
{
	int count = 0;
	list_for_each_safe(pos, q, &mem_addrs.list){
		tmp = list_entry(pos, struct Address, list);
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

  struct Address* tracked_buffer = find( buffer);
  if( buffer != NULL )
  {
    return true;
  }

  return false;
}

#endif
