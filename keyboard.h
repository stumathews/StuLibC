#ifndef SCREEN_H
#define SCREEN_H

/** @brief Waits for input from keyboard and returns what is on stdin when the newline is sent to keyboard.
 *
 * @return char* pointer to character array of line read
 *
 */
int kbd_GetLine(char* buf);

#endif
