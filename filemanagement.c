#include "filemanagement.h"
#include <stdio.h>

void FILE_AppendText(char* text, char* filename)
{
    //open file to appending text and append text
    FILE* theFile = fopen( filename, "a");
    fputs(text, theFile );
    fclose(theFile);
}
