#include <stulibc.h>

extern struct Address mem_addrs;

bool IsLibraryInitialized = false;

LIBRARY_API void LIB_Init()
{
	if (!LIB_IsInit())
	{
        INIT();
		DBG("Initializing library");
        MEM_Init();
        CMD_Init();
		DBG("Initialized library");
		IsLibraryInitialized = true;
	}
}

void LIB_Check_Init()
{
  if( !LIB_IsInit() )
  { 
      PRINT("Library was not initialized. Recovering.\n");
      LIB_Init(); 
  }

}

LIBRARY_API void LIB_Uninit()
{
	if (LIB_IsInit())
	{
		DBG("Uninitializing library.");
        MEM_Uninit();
		CMD_Uninit();
        EXIT(0);
		IsLibraryInitialized = false;
		DBG("Uninitialized library.");
	}
}

bool LIB_IsInit()
{
	return IsLibraryInitialized;
}
