#include <stulibc.h>

LIBRARY_API void LIB_Init()
{

}

LIBRARY_API void LIB_Uninit()
{
    MEM_DeAllocAll();
}
