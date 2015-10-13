/**
 * @file keyboard.c
 * @brief Keyboard library function definitions.
 * @author Stuart Mathews
 * @date 12 July 2013
 *
 * This headers contains the various keyboard management functions defined in the library.
 * These typically involve reading from the keyboard in various ways
 * @see keyboard.h
 */
#ifndef STULIBC_KEYBOARD_MANAGEMENT_H
#define STULIBC_KEYBOARD_MANAGEMENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* KBD_GetLine(int max_line_length)
{
    int c, chars_read = 0;
    char* buf = (char*) Alloc( sizeof(char) * max_line_length );

    while( (c = getchar()) != EOF && (c != '\n') && (chars_read < max_line_length) )
        buf[chars_read++] = c;

    return buf;
}

#endif // SCREEN_C_INCLUDED
