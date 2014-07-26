/**
 * @file filemanagement.h
 * @brief File management library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with file management functionality in the library.
 * This includes writing text to files, binary data to files and records etc.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page filemanagement File management and writing to files
This is a narative on this part of the library
*/
#ifndef FILE_H
#define FILE_H

#include <stdio.h>

// File managment functions

// writing to files

/** @brief Appends a piece of text to a file.
 *
 * @param text char* piece of text
 * @param filename char* piece of text to append to @param text
 * @return void
 * @remarks if the file doesnt exist, it is created.
 *
 */
void FILE_AppendText(char* text, char* filename);

/** @brief Appends a piece of text to a stream.
 *
 * @param text char* piece of text
 * @param stream FILE*
 * @return void
 *
 */
void FILE_AppendTextToStream(char* text, FILE* stream);
// writing to config files

// writing to records

// binary reading/writing/serialisation

#endif
