/**
 * @file safetychecking.h
 * @brief Safety checking library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with safety functionality in the library.
 * This includes ensuring bounds are not overflowed, and that where restrictions are enforced, these are upheld.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page safetychecking Trying to be safe in your program
This is a narative on this part of the library
*/

#ifndef SAFETY_CHECKING_H
#define SAFETY_CHECKING_H

// bounds checking on data structures and other sanity checks
void CHK_ExitIf(int condition, char* message, char* resultContext);
int CHK_LogIf(int condition, char* message, char* resultContext);
void CHK_Log(char* functionName,int lineNumber, char* resultContext);

#endif
