#include <stulibc.h>

bool IsLibraryInitialized = false;

LIBRARY_API void LIB_Init()
{
	if (!LIB_IsInit())
	{			
        NETINIT();
		DBG("Initializing library");

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
		IsLibraryInitialized = false;
		DBG("Uninitialized library.");

#ifdef __linux__
	pthread_exit(NULL);
#endif

		PRINT("Suppressing calls to CMD_Uninit() and MEM_Uninit() as they are broken and should be fixed before reinstating");
		//CMD_Uninit();
        //MEM_Uninit();


	}
}

bool LIB_IsInit()
{
	return IsLibraryInitialized;
}
