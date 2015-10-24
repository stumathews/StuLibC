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
- Make it so that I just need to link to the library in order to use the functionality provided.
- Use this as reference material for future code lookups to help me remember how to do a certain thing

The intention is also to have it as portable as possible to work in Linux and Windows.
This will mean that the library can build unchanged across these platforms.
Where OS specific functionality is needed in the library, this should be disabled/enabled based on the platform we are builing on.

\section functionality_coverage Functionality coverage

I've broken down the library down into functional areas. This encompases a low-level API such as moving/managing memory.

##Basic, low-level routines
- Storing and managing data
 - [Lists](@ref list)
- [Writing to files](@ref filemanagement) 
- [Writing to the console](@ref console)
- [Managing access to memory](@ref memory)
- [Safety checking your program](@ref safetychecking)
- [Debugging routines for tracing](@ref debugging)
- [Working with strings in general](@ref libstring)
- [Working with timing](@ref timing)
- [Validation and testing routines](@ref testing)
- Encryption
- Compression
- IPC

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

 */

#ifndef LIBSTU_H
#define LIBSTU_H
#include <config.h>
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
#include <strings.h>
#include <list.h>
#include <linuxlist.h>
#include <stdbool.h>
// .. include others for an all-includeive #incude <libstu.h> to pull in all functions

LIBRARY_API void LIB_Init();
LIBRARY_API void LIB_Uninit();
void LIB_Check_Init();
bool LIB_IsInit();


#endif
