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

#include <stdlib.h>
#include <stdio.h>

long FILE_GetFileSize(const char *filename)
{
  long result;
  FILE *fh = fopen(filename, "rb");
  fseek(fh, 0, SEEK_END);
  result = ftell(fh);
  fclose(fh);
  return result;
}

int main(void)
{
  printf("%ld\n", getFileSize("input.txt"));
  printf("%ld\n", getFileSize("/input.txt"));
  return 0;
}
