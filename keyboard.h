#ifndef SCREEN_H
#define SCREEN_H

// sending/receiving and manipulating text to from screen

/** @brief Waits for input from keyboard and returns what is on stdin when the newline is sent to keyboard.
 *
 * @param buffer char* The memory location to store the fetched line.
 * @return char* The memory location of the fetch line data.
 *
 */
char* kbd_GetLine(char* buffer);

#endif
