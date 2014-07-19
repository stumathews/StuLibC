#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../keyboard.h"
#include "../debugging.h"
#include "../filemanagement.h"
#include "../safetychecking.h"
#include "../libstring.h"

#define MAX_LINE_LENGTH 5

int main()
{
    DBG_WriteLineToFile("The germans are coming!","phrases.txt", CRITICAL);
    DBG_WriteLineToFile("Russian intelligence? Are you mad!","phrases.txt", UNSPECIFIED);
    return 0;
}
