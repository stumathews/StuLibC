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


    DBG_WriteLine("Hellow World","debug.txt",MINOR);
    DBG_WriteLineExtra("Init","Creating startup files...","ben is sleeping","afile.txt", CRITICAL);

    return 0;
}
