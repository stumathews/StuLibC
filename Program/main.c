#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../keyboard.h"
#include "../debugging.h"
#include "../filemanagement.h"
#include "../safetychecking.h"
#include "../libstring.h"
#include "../logging.h"


int main()
{
    log("Entering atmosphere...","spce shuttle log");
    logif( 1> 0, "one is greater than zero", "simple conditional check");
    log("All systems shutdown.","space shuttle log");
    DBG_WriteLineToFile("Goodbye captain.","crew.log", NORMAL);
    debugif(1,"It is true","boolean expression");
    log("hello world","general message");

    return 0;
}
