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
#include <constants.h>

/** \brief Returns the current time as indicated by a clock_t data structure
 *
 * \return LIBRARY_API clock_t
 *
 */
LIBRARY_API clock_t TIME_StartCPURecord();
/** \brief Returns the current time as indicated by a clock_t data structure
 *
 * \return LIBRARY_API clock_t
 *
 */
LIBRARY_API clock_t TIME_StopCPURecord();
/** \brief Calculates the time in seconds between to points in time
 *
 * \param startTime clock_t start point in time
 * \param endTime clock_t end point in time
 * \return LIBRARY_API clock_t the number of seconds between the two points (elapsed time)
 *
 */
LIBRARY_API clock_t TIME_GetCPUTimeTakenInSeconds(clock_t startTime, clock_t endTime);
/** \brief Returns the number of CPU clock units elapsed between two points in time
 *
 * \param startTime clock_t first point in time
 * \param endTime clock_t second point in time
 * \return LIBRARY_API clock_t number of cpu units elapsed between the two points
 *
 */
LIBRARY_API clock_t TIME_GetCPUTimeTakenInUnits(clock_t startTime, clock_t endTime);


char* TIM_GetDateTimeStr();

/* Calculate day of week in proleptic Gregorian calendar. Sunday == 0. */
int TIM_DayOfWeek( int year, int month, int day);
#endif
