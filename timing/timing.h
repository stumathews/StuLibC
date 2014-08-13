/**

 * @file timing.h
 * @brief Timing library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with timing functionality in the library.
 * This includes measuring time such as timing how long something takes or implementing a stopwatch or count down timer etc..
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page timing Timing functionality
This is a narative on this part of the library
*/

#ifndef TIMING_H
#define TIMING_H

#include <time.h>
#include <stdio.h>

char* TIM_GetDateTimeStr();

#endif
