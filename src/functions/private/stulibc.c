#include <stulibc.h>

LIBRARY_API void LIB_Init()
{
    DBG("Initializing library");
}

LIBRARY_API void LIB_Uninit()
{
    DBG("Uninitializing library.");
    MEM_DeAllocAll();
}
