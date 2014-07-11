#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../keyboard.h"

int main()
{
    char* buf;
    int chars_read = kbd_GetLine(buf);
    printf("Wrote %d characters to buffer: %s\n",  chars_read, buf);
    return 0;
}
