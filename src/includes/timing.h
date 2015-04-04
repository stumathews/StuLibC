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
