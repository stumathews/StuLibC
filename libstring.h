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


/** @brief Converts an integer into a string
 *
 * @param number int the number to represent as a string
 * @return char* the string that represents @param number
 *
 */
char* STR_FromInt(int number);


/** @brief from K&R2 book, converts a int a string
 *
 * @param n int number
 * @param s[] char string destination
 * @return void
 *
 */
void itoa(int n, char s[]);

/** @brief reverse string @param s in place
 *
 * @param s[] char
 * @return void
 *
 */
void reverse(char s[]);

 #endif // STULIBC_STRING_H
