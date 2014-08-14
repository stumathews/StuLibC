/**
 * @file Vigenère.h
 * @brief a Vigenère cypher, both encryption and decryption
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the Vigenère functions defined in the library.
 * Vigenère cypher, both encryption and decryption
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page xxxx Using xxxx functionality
xxxx
*/
#ifndef STULIBC_VIGENERE_H
#define STULIBC_VIGENERE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "..\strings\libstring.h"

//Implement a Vigenère cypher, both encryption and decryption
char* vigenere_encipher(const char *src, char *key, int is_encode);

#endif
