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

/** \page libstring Dealing with strings in C
This is a narative on this part of the library
*/

#ifndef STULIBC_STRING_H
#define STULIBC_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STREQ(A,B) (0==strcmp((A),(B)))
#define STRNE(A,B) (!STREQ(A,B))
#define STRLT(A,B) (strcmp((A),(B))<0)
#define STRLE(A,B) (strcmp((A),(B))<=0)
#define STRGT(A,B) STRLT(B,A)
#define STRGE(A,B) STRLE(B,A)

#define STRCEQ(A,B) (0==strcasecmp((A),(B)))
#define STRCNE(A,B) (!STRCEQ(A,B))
#define STRCLT(A,B) (strcasecmp((A),(B))<0)
#define STRCLE(A,B) (strcasecmp((A),(B))<=0)
#define STRCGT(A,B) STRCLT(B,A)
#define STRCGE(A,B) STRCLE(B,A)


size_t byte_length(char* string);
void upper_case(char *src);
char* rtrim(const char *s);
char* ltrim(const char *s);
char* trim(const char *s);
int startsWith(const char* container, const char* target);
int endsWith(const char* container, const char* target);
int doesContain(const char* container, const char* target);
char* concat(const char* s1, const char* s2);
void compare(const char*a, const char*b);
void comparecase(const char*a, const char*b);

#endif // STULIBC_STRING_H
