/**
 * @file libstring.h
 * @brief String library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with string functionality in the library.
 * This includes creating, copying, manipulating strings.
 * @see http://devel.stuartmathews.com/stulibc
 */
 #ifndef STULIBC_STRING_H
 #define STULIBC_STRING_H

 // things to do with string management
char* STR_FromInt(int number);

// from K&R2 book
void itoa(int n, char s[]);
 /* reverse:  reverse string s in place */
void reverse(char s[]);

 #endif // STULIBC_STRING_H
