#include <stulibc.h>

LIBRARY_API LIB_Init()
{

}

LIBRARY_API LIB_Uninit()
{
    MEM_DeAllocAll();
}
