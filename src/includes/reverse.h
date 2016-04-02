/*
 * reverse.h
 *
 *  Created on: 25 Mar 2016
 *  Author: https://www.rosettacode.org/wiki/Reverse_a_string#C
 */

#ifndef SRC_INCLUDES_REVERSE_H_
#define SRC_INCLUDES_REVERSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

int is_comb(wchar_t c);
wchar_t* mb_to_wchar(const char *s);
wchar_t* ws_reverse(const wchar_t* u);
char *mb_reverse(const char *in);

#endif /* SRC_INCLUDES_REVERSE_H_ */
