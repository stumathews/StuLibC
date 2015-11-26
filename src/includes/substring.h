/**
 * @file substring.h
 * @brief String substring functionality.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the substring functions defined in the library.
 * These typically involve checking for the existance of strings within other strings.
 * @see http://devel.stuartmathews.com/stulibc
 */

#ifndef STUIBC_STUBSTRING_H
#define STUIBC_STUBSTRING_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST(A) do {		\
    char *r = (A);		\
    if (NULL == r)		\
      puts("--error--");	\
    else {			\
      puts(r);			\
      free(r);			\
    }				\
  } while(0)

char *substring(const char *s, size_t n, ptrdiff_t m);
char *str_wholeless1(const char *s);
char *str_fromch(const char *s, int ch, ptrdiff_t m);
char *str_fromstr(const char *s, char *in, ptrdiff_t m);

#endif
