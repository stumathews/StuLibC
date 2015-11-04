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
These functions describe various operations that the library can perform on files. 
This includes basics such as deleting, renaming and checking the existance of files.
##Tasks
Task orientated approach to the functionality offered in this header
###File basics
- [Delete a file](@ref FILE_Delete)
- [Rename a file](@ref FILE_Rename)
- [Check existance of file](@ref FILE_Exists)

###Appending characters
- [Append characters to the end of a file](@ref FILE_AppendText)
- [Append characters to the end of a stream](@ref FILE_AppendTextToStream)
- [Detect a string in a file](@ref FILE_ContainsString);)

###Writing to configuration files
###Writing records to files (write datafiles)
###Undocumented functions
 - Getting the file size

##Library Interface
This describes the function prototypes
\include files.h

*/
#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <constants.h>
#include <stdbool.h>


/** \brief Appends characters to the end of a named file
  \param text char* The text to be appended to the file.
  \param filename char* The filename of the file.
  \return nothing
  \remarks This opens and closes the file on each fall
  \warning This does _not_ append a newline  the end of the file.
*/
void FILE_AppendText(char* text, char* filename);
/** \brief Appends characters tothe end of a stream
 \param text char* characters to append
 \param stream FILE* stream to append to
 */
LIBRARY_API void FILE_AppendTextToStream(char* text, FILE* stream);
/** \brief Determines if a file constains a string
    \param file FILE* file stream
    \param string char* text to look for
*/
LIBRARY_API _Bool FILE_ContainsString( FILE* file, char* string);
/** @brief Deletes a file
Deletes a file. Simple.
Here is a code snipit
@code
char errors = 0;
const char* filename = "file_exists_test.txt";

FILE* file = fopen( filename, "w");

assert( file != NULL );
assert( FILE_Exists( filename) );

fclose(file);  

FILE_Delete( filename );
@endcode
    @param filename const char* filename to delete
*/
LIBRARY_API void FILE_Delete(const char* filename);
/** @brief Renames a file
@param originalname const char* original name
@param newname const char* newname 
*/
LIBRARY_API void FILE_Rename(const char* originalname, const char* newname);
/** \brief Determines if a file exists
    \param filename const char* filename
*/
LIBRARY_API short FILE_Exists( const char* filename );
long tFileSize( const char* filename);
long FILE_GetFileSize(const char *filename);

LIBRARY_API void FILE_IniParse(const char* filename);

#endif
