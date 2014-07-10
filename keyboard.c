#ifndef KBD_C_INCLUDED
#define KBD_C_INCLUDED
#include <stdio.h>



char* kbd_GetLine(char* buffer)
{
    // could call a sanity check to report on how big the buffer is
    // and how likely it is to have overflowed etc..
    return gets(buffer);
}

#endif // SCREEN_C_INCLUDED
