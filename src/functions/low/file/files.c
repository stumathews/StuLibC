#include <files.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <debugging.h>
#include <stdbool.h>
#include <safetychecking.h>
#include <list.h>
#include <console.h>


_Bool FILE_ContainsString(FILE* file, char* string)
{
	CHECK_STRING( string, IS_NOT_EMPTY );
	
    int MAX = 80;         // ASSUNMPTION: that a file as at least 80 characters per line.
    char buffer[MAX];
    while(fgets(buffer, MAX, file) != NULL) {
        if(strstr((const char*) buffer, (const char*)string) != NULL)
            return true;
    }
    return false;
}

void FILE_AppendText(char* text, char* filename)
{
	CHECK_STRING( filename, IS_NOT_EMPTY );
	
    FILE* theFile = fopen(filename, "a");
    FILE_AppendTextToStream(text,theFile);
    fclose(theFile);
}

void FILE_AppendTextToStream(char* text, FILE* stream)
{
	CHECK_STRING( text, IS_NOT_EMPTY );
    fputs((const char*) text, stream);
    if(ferror(stream)) {
        perror("Failed to send text to stream");
    }
}


long FILE_GetFileSize(const char *filename)
{
	CHECK_STRING( (char*)filename, IS_NOT_EMPTY );
	
    long result;
    FILE *fh = fopen(filename, "rb");
    fseek(fh, 0, SEEK_END);
    result = ftell(fh);
    fclose(fh);
    return result;
}

void FILE_Delete(const char* filename)
{
	CHECK_STRING( (char*)filename, IS_NOT_EMPTY );
	
    if(!FILE_Exists(filename))
        return;
    if(remove(filename) != 0) {
        perror("Unable to remove file");
    }
}

void FILE_Rename(const char* originalname, const char* newname)
{
	CHECK_STRING( (char*) originalname, IS_NOT_EMPTY );
	CHECK_STRING( (char*) newname, IS_NOT_EMPTY );
	
    int result = rename(originalname, newname);
    if(result != 0)
        perror("failed to rename file");
}

short FILE_Exists(const char* filename)
{
	CHECK_STRING( (char*) filename, IS_NOT_EMPTY );
	
    FILE* file = fopen(filename, "r");
    if(file == NULL || ferror(file) != 0) {
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}


