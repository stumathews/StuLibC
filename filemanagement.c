#include "filemanagement.h"
#include <stdio.h>

void FILE_AppendText(char* text, char* filename)
{
    FILE* theFile = fopen( filename, "a");
    FILE_AppendTextToStream(text,theFile);
    fclose(theFile);
}

void FILE_AppendTextToStream(char* text, FILE* stream)
{
    fputs(text,stream);
    if(ferror(stream))
        fclose(stream);
}
