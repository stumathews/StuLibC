#include <stulibc.h>
#include <linuxlist.h>



extern struct Address mem_addrs;

LIBRARY_API void LIB_Init()
{
    DBG("Initializing library");
	INIT_LIST_HEAD(&mem_addrs.list);
}

LIBRARY_API void LIB_Uninit()
{
    DBG("Uninitializing library.");
    MEM_DeAllocAll();
    CMD_Uninit();
}
