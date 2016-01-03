/**
 * @file threading.h
 * @brief Threading functionality
 * @author Stuart Mathews
 * @date 3 Jan 2016
 *
 * This header contains the function prototypes for access tothe threading functionlity within the library
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page threads Threading
Put stuff about this threading functionality in here.
\include threading.h
*/


#ifndef THREADING_H
#define THREADING_H
#include <constants.h>

#ifdef __linux__
#include <pthread.h>
#endif

typedef void* (*threadfunc)(void* param);

/** \brief Runs a function in its own thread
 * Creates a new thread and runs the provided user function within it. *
 * @param func user defined function that accepts adn returns a void* type
 * @param threadparam the parameter to the user defined thread function
 * \warning This function does not wait for the function/thread to finish.
 * \returns 0 on success, any other value on failure
 */
LIBRARY_API int THREAD_RunAndForget(threadfunc func, void* threadparam);

#endif /* THREADING_H */
