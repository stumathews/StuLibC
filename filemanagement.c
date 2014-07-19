#include "filemanagement.h"
#include <stdio.h>

void FILE_AppendText(char* text, char* filename)
{
    FILE* theFile = fopen( filename, "a");
    fputs(text, theFile );
    fclose(theFile);
}
