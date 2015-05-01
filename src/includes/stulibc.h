
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
\include stulibc.h
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
This is my library of useful c routines. The purposes of this library are:
- Write common and useful functions that I can reuse in other programs.
- I just need to link to the library.
- Use this as reference material for future code lookups to help me remember how to do a certain thing

The intention is also to have it as portable as possible to work in Linux and Windows.
This will mean that the library can build unchanged across these platforms.
Where OS specific functionality is needed in the library, this should be disabled/enabled based on the platform we are builing on.

##Library functionality coverage
I've broken down the library down into functional areas. This encompases a low-level API such as moving/managing memory.

##Basic, low-level routines
- [Writing to files](@ref filemanagement) 
- [Screen/Console](@ref console)
- [Memory management](@ref memory)
- [Safety checking](@ref safetychecking)
- [Debugging routines](@ref debugging)
- [String management](@ref libstring)
- [Timing functions](@ref timing)
- [Validation and testing routines](@ref testing)
- Not yet implemented/TODO
  + Data structures
  + Encryption
  + Compression
  + IPC

##Higher-level routines
- Graphics
- Database
- Internet
- Parsing 
+ [Command line parsing](@ref cmdline)
- Networking and protocols
- Regex
- Threading
- Interpreters
- Internationalization
- Windowed applications/forms
- Application design and patterns

##Resources
This is currently hosted on my [devel server](http://devel.stuartmathews.com/projects/my-c-library)

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
#include <stdbool.h>
// .. include others for an all-includeive #incude <libstu.h> to pull in all functions

LIBRARY_API void LIB_Init();
LIBRARY_API void LIB_Uninit();
bool LIB_IsInit();


#endif
