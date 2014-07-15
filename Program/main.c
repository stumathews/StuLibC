#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../keyboard.h"

#define MAX_LINE_LENGTH 5

int main()
{
    char* line = kbd_GetLine(MAX_LINE_LENGTH);
    printf("The buffer contains: %s", line);
    free(line);

    return 0;
}
