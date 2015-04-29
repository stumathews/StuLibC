/**
 * @file keyboard.h
 * @brief Keyboard library function prototypes.
 * @author Stuart Mathews
 * @date 12 July 2013
 *
 * This headers contains the various keyboard management functions defined in the library.
 * These typically involve reading from the keyboard in various ways
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page keyboard Keyboard
This is a narative on this part of the library
*/

#ifndef SCREEN_H
#define SCREEN_H

/** @brief  Reads all characters that are typed into the keyboard until the newline character.
 *
 * This function waits for each character that is type into the keyboard as it receives it.
 * This is saves it into a memory location, allocated by the function of at most @p max_line_length characters.
 * This memory location is returned as a pointer to it.
 * It also ensures that if no newline character is ever typed in, it then will only read at most @p max_line_length characters
 * and therefore promises that the returned string is at most @p max_line_length in size.
 * Here is a typical example of how to use it:
 * @code
 * char* buffer = kbd_GetLine(80);
 * printf("The following line was obtained from the keyboard: %s\n",buffer);
 * free(buffer);
 * @endcode
 * @param max_line_length int reads at most @p max_line_length characters from keyboard.
 * @return char* a pointer to the memory location containing the retrieved line.
 * @remarks None
 * @see http://devel.stuartmathews.com/stulibc
 * @note Be sure to free the memory that is allocated to the returned string, once you're done with it.
 * @warning Not freeing the memory will result in memory leaks.
 */
LIBRARY_API char* KBD_GetLine(int max_line_length);

#endif
