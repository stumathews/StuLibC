#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../keyboard.h"

#define MAX_LINE_LENGTH 5

int main()
{
    printf("The buffer contains: %s", kbd_GetLine(MAX_LINE_LENGTH));

    return 0;
}
