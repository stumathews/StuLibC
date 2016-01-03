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

/** \page timing Timing
This is a narative on this part of the library
\include timing.h

\section install_sec Installation

\subsection step1 Step 1: Opening the box

\subsection step2 Step 2: Configuring it

This tells you about the installation.

#This is a level 1 header


##This is a level 2 header
###This is a level 3 header

> This is a block quote
> spanning multiple lines

here are some lists

- Item 1

More text for this item.

- Item 2
+ nested list item.
+ another nested item.
- Item 3

This a normal paragraph. but this is an `inline code fragment`

This is a code block

We continue with a normal paragraph again.

Here is some more code

*single asterisks*

_single underscores_

**double asterisks**

__double underscores__

[The link text](@ref MyClass)

[The link text](http://example.net/)
[The link text](http://example.net/ "Link title")
[The link text](/relative/path/to/index.html "Link title")
[The link text](somefile.html)
Now for some code, but in colour:

~~~~~~~~~~~~~~~{.c}
int func(int a,int b) { return a*b; }
~~~~~~~~~~~~~~~

etc.

*/

#ifndef TIMING_H
#define TIMING_H

#include <time.h>
#include <stdio.h>
#include <constants.h>

/** \brief Returns the current time as indicated by a clock_t data structure
 *
 * \return LIBRARY_API clock_t
 *
 */
LIBRARY_API clock_t TIME_StartCPURecord();
/** \brief Calculates the time in seconds between startTime and now
 * \param startTime clock_t the time to start from
 * \return LIBRARY_API clock_t the number of seconds between now and startTime
 *
 */
LIBRARY_API clock_t TIME_StopCPURecord(clock_t startTime);
/** \brief Calculates the time in seconds between to points in time
 *
 * \param startTime clock_t start point in time
 * \param endTime clock_t end point in time
 * \return LIBRARY_API clock_t the number of seconds between the two points (elapsed time)
 *
 */
LIBRARY_API clock_t TIME_GetCPUTimeTakenInSeconds(clock_t startTime, clock_t endTime);

/** \brief Calculates the time in milliseconds between to points in time
 *
 * \param startTime clock_t start point in time
 * \param endTime clock_t end point in time
 * \return LIBRARY_API clock_t the number of seconds between the two points (elapsed time)
 *
 */
LIBRARY_API clock_t TIME_GetCPUTimeTakenInMilliSeconds(clock_t startTime, clock_t endTime);
/** \brief Returns the number of CPU clock units elapsed between two points in time
 *
 * \param startTime clock_t first point in time
 * \param endTime clock_t second point in time
 * \return LIBRARY_API clock_t number of cpu units elapsed between the two points
 *
 */
LIBRARY_API clock_t TIME_GetCPUTimeTakenInUnits(clock_t startTime, clock_t endTime);

/** \brief Returns the time and date as a string 
 *
 * \return char* string date and time format
 */
LIBRARY_API char* TIM_GetDateTimeStr();

/** \brief Calculate day of week in proleptic Gregorian calendar. Sunday == 0.
 *  \param year int year
 *  \param month int month
 *  \param day int day
 *  \return int numeric representation of the day of the week (sunday=0, monday = 1 etc...)
 */
LIBRARY_API int TIM_DayOfWeek( int year, int month, int day);
#endif
