
/**
 * @file stulibc.h
 * @brief Main include file
 * @author Stuart Mathews
 * @date 10 January 2014
 *
 * This header contains header declarations in the library.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page stulibc Main Header
Make it easy to consume the library functionality by just including one file. This file.
*/
/*! \mainpage libstuc - library of useful c routines
~~~~~~~~~~~~~~~{.c}
         _         _ _ _           
     ___| |_ _   _| (_) |__   ___  
    / __| __| | | | | | '_ \ / __| 
    \__ \ |_| |_| | | | |_) | (__  
    |___/\__|\__,_|_|_|_.__/ \___| 

    Stuart's Librray of C Functions
~~~~~~~~~~~~~~~
\section intro_sec Introduction
This is my library of useful c functions.

\section topic_coverage Library functionality coverage
A break down of the structure of the functionality

##Basic, low-level routines
- Writing to files
- Encryption - to obsuscate data
- Compression - to make certain structures smaller
- Screen/Console
- Memory management
- Safety checking
- Debugging routines
- string management
- Timing functions
- Data structures 
- Inter process communication between programs - this might be OS specific.
- Validation and testing routines to implement generic unit testing and generic assertions etc..
- C language Syntax referenceusages to remind you how to eg. declare a pointer to a pointer
 
##Higher-level routines
- Graphics
- Database
- Internet
- Parsing 1.Command line parsing

- Networking and protocols
- Regex
- Threading
- Interpreters
- Internationalization
- Windowed applications/forms
- Application design and patterns
  
##Environment dependant functionality

  There will be times when you invest heavily in implementing a routine that functions only within a limited set of criteria such as operating system, dependant software such as 3rd party libraries:
- Windows only
- Posix only
- Other only
   
##Why implement a library?
- To help not having to reinvent the wheel for common programming tasks each time.
- To help one remember how to do a certain task - like a knowledge base of saved practise.
- To reuse in new projects to help increase the time it takes to write new software.
- Structure code into library files in the same way that you'd consume other library files.
- Make your code readable by abstracting difficult/complex routines into descriptive function names.

##How will this project be consumed?
- A linkable library is required to reuse the routines in the library. This will allow anyone who want to link against it to benefit from using the library eg. other developers not including myself
- It will need to be well designed and structured so that aspects of it are easily found, and make sense.
- Documentation needs to be considered. How will this be handled. 
- Will the library be distributed in its binary linkable form or will/can it be distributed in source form?
- Are we over-thinking the library?
- What will it be used for? System programming, GUI programming etc.
    A lof

[The link text](@ref debugging)[NewArgument]

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

#ifndef LIBSTU_H
#define LIBSTU_H
#if HAVE_CONFIG_H
#include <config.h>
#endif
#include <debugging.h>
#include <console.h>
#include <errors.h>
#include <constants.h>
#include <memory.h>
#include <cmdline.h>
#include <etcp.h>
#include <logging.h>
#include <safetychecking.h>
#include <stack.h>
#include <testing.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <list.h>
#include <linuxlist.h>
// .. include others for an all-includeive #incude <libstu.h> to pull in all functions

LIBRARY_API void LIB_Init();
LIBRARY_API void LIB_Uninit();


#endif
