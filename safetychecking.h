/**
 * @file safetychecking.h
 * @brief Encryption library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with safety functionality in the library.
 * This includes ensuring bounds are not overflowed, and that where restrictions are enforced, these are upheld.
 * @see http://devel.stuartmathews.com/stulibc
 */
#ifndef SAFETY_CHECKING_H
#define SAFETY_CHECKING_H

// bounds checking on data structures and other sanity checks
void CHK_ResultExitIf(void* result, int condition);
void CHK_ResultLogIf(void* result,int condition);
void CHK_ResultLog(void* result, char* functionName,int lineNumber);

#endif
