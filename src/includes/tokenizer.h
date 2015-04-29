/**
 * @file tokenizer.h
 * @brief String tokentizer functionality.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the tokenizer functions defined in the library.
 * These typically involve supplying a delimited string, an a delimiter. For each substring a call back is called. *
 * @see http://devel.stuartmathews.com/stulibc
 */

#ifndef STULIBC_TOKENIZER_H
#define STULIBC_TOKENIZER_H

#include <stdio.h>

typedef void (callbackfunc)(const char *);


void tokenize(char *s, char delim, callbackfunc *cb)
{
	char *olds = s;
	char olddelim = delim;
	while(olddelim && *s) {
		while(*s && (delim != *s)) s++;
		*s ^= olddelim = *s; // olddelim = *s; *s = 0;
		cb(olds);
		*s++ ^= olddelim; // *s = olddelim; s++;
		olds = s;
	}
}

#endif
