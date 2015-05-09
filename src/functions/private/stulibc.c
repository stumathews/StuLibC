#include <stulibc.h>

extern struct Address mem_addrs;

bool IsLibraryInitialized = false;

LIBRARY_API void LIB_Init()
{
	if (!LIB_IsInit())
	{
		DBG("Initializing library");
        CMD_Init();
        MEM_Init();
		DBG("Initialized library");
		IsLibraryInitialized = true;
	}
}

LIBRARY_API void LIB_Uninit()
{
	if (LIB_IsInit())
	{
		DBG("Uninitializing library.");
        MEM_Uninit();
		CMD_Uninit();
		IsLibraryInitialized = false;
		DBG("Uninitialized library.");
	}
}

bool LIB_IsInit()
{
	return IsLibraryInitialized;
}
