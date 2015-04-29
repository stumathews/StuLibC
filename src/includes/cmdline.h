/**
 * @file cmdline.h
 * @brief Command line handling routines
 * @author Stuart Mathews
 * @date 10 January 2014
 *
 * This header contains the function and type declarations for dealing with handling command line stuff in the library.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page cmdline Command Line
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
    char name[20]; // move-forward
    char display[20]; // move-forwardby <number>
    char description[80]; // moves the player forward
    bool isMandatory; // must be given
    bool isValueMandatory; // value must be given
    void (*handler)(char*); //function to call 

};

/**
 * Enumeration that represents the result of the parsing of a single registed command line argument
 */
enum ParseResult { EXPECTED_VALUE, NO_HANDLER, PARSE_SUCCESS  };


/** \brief Add a single argument to be tracked by the library.
 *
 * \param argument struct NewArgument* a single argument
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void CMD_AddArgument( struct Argument* argument );


/** \brief Parses the provided cmd line arguments and executes the argument handlers for them.
 *
 * \param argc int the number of argument strings passed in
 * \param argv char** the pointer to an array of strings that represent the raw string arguments
 * \param skip_first_arg bool indicates if we should skip processing the first arg - in most cases is the name of a program
 * \return LIBRARY_API void
 *
 */
LIBRARY_API enum ParseResult CMD_Parse(int argc, char** argv, bool skip_first_arg);


/** \brief Shows a tag line and then all the arguments registered
 *
 *  \param tagline char* first line to show in the usages - normall should include the program name
 */
LIBRARY_API void CMD_ShowUsages(char* tagline);


/** \brief Convenience function that creates a Argument structure from a function call
 * \param name char* name of argument
 * \param display char* the display of the argument when showing usages
 * \param description char* the textual description of this argument shown in usages
 * \param isMandatory bool true if this argument must be supplied to the user
 * \param isValueMandatory bool true if a single value must be provided after the argument is supplied
 * \param handler void (*)(char* arg) function to call then this argument is found, an optional argument is allowed
 */
LIBRARY_API struct Argument* CMD_CreateNewArgument( char* name, char* display, char* description, bool isMandatory, bool isValueMandatory, void (*handler)(char* arg));


/** \brief Uninitialises the cmd handling routine.
 *  Its recommended that you call this when you're finished with CMD_Parse.
 * \return LIBRARY_API void
 *
 */
LIBRARY_API void CMD_Uninit();

#endif
