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
    LOG_It("Entering atmosphere...");
    LOG_If( 1> 0, "one is greater than zero", "simple conditional check");
    LOG_It("All systems shutdown.");
    DBG_WriteLineToFile("Goodbye captain.","crew.log", NORMAL);
    return 0;
}
