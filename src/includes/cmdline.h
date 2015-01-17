/**
 * @file cmdline.h
 * @brief Command line handling routines
 * @author Stuart Mathews
 * @date 10 January 2014
 *
 * This header contains the function and type declarations for dealing with handling command line stuff in the library.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page cmdline Handling command line arguments
Command line arguments and dealing with these in a structured way
*/
#ifndef CMDLINE_H
#define CMDLINE_H
#include <constants.h>
#include <stdbool.h>

/** \brief Data structure representing a argument name
 */
struct Argument
{
    /** \brief The name of the argument.
     *
     *  extra
     */
    char name[20];
    char description[80];
    bool isMandatory;
    bool isValueMandatory;
    void (*handler)(char*);

};


/** \brief Add a single argument to be tracked by the library.
 *
 * \param argument struct NewArgument* a single argument
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void CMD_AddArgument( struct Argument* argument );
/** \brief Add an argument to be tracked.
 *
 * \param arguments[] struct NewArgument* NULL terminated array of arguments
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void CMD_AddArguments( struct Argument* arguments[]);
/** \brief Parses the provided cmd line arguments and executes the argument handlers for them.
 *
 * \param argc int the number of argument strings passed in
 * \param argv char** the pointer to an array of strings that represent the raw string arguments
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void CMD_Parse(int argc, char** argv);
/** \brief Uninitialises the cmd handling routine.
 *  Its recommended that you call this when you're finished with CMD_Parse.
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void CMD_Uninit();

#endif
