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


    DBG_WriteLineExtra("[PROGRAM]","Unable to parse file","[FINISHED]","afile.txt", MINOR);
    CHK_ResultLog(STR_FromInt(53290),"main",12,"My favourite number.");

    return 0;
}
