#include <stulibc.h>
#include <linuxlist.h>
#include <stdbool.h>

extern struct Address mem_addrs;

bool IsLibraryInitialized = false;

LIBRARY_API void LIB_Init()
{
	if (!LIB_IsInit())
	{
		DBG("Initializing library");
		INIT_LIST_HEAD(&mem_addrs.list);
		IsLibraryInitialized = true;
	}
}

LIBRARY_API void LIB_Uninit()
{
	if (LIB_IsInit())
	{
		DBG("Uninitializing library.");
		MEM_DeAllocAll();
		CMD_Uninit();
		IsLibraryInitialized = false;
	}
}

bool LIB_IsInit()
{
	return IsLibraryInitialized;
}
