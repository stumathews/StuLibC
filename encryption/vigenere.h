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
