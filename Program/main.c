#include <stdio.h>
#include <stdlib.h>
#include "../keyboard.h"

int main()
{
    char buffer[80];
    kbd_GetLine(buffer);
    puts(buffer);
    return 0;
}
