/**
 * @file files.h
 * @brief File management library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with file management functionality in the library.
 * This includes writing text to files, binary data to files and records etc.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page filemanagement File management
This is a narative on this part of the library
*/
#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <constants.h>
#include <stdbool.h>

void FILE_AppendText(char* text, char* filename);
LIBRARY_API void FILE_AppendTextToStream(char* text, FILE* stream);
LIBRARY_API _Bool FILE_ContainsString( FILE* file, char* string);

// writing to config files

// writing to records

// binary reading/writing/serialisation

long FILE_GetFileSize(const char *filename);
LIBRARY_API void FILE_Delete(const char* filename);
LIBRARY_API void FILE_Rename(const char* originalname, const char* newname);
long tFileSize( const char* filename);
LIBRARY_API short FILE_Exists( const char* filename );

#endif
