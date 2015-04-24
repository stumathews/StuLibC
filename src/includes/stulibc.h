/*! \mainpage libstuc - library of useful c routines

\section intro_sec Introduction

This is the introduction.
[The link text](@ref debugging)
[NewArgument]

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
#include <stack.h>
#include <testing.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
// .. include others for an all-includeive #incude <libstu.h> to pull in all functions

LIBRARY_API void LIB_Init();
LIBRARY_API void LIB_Uninit();


#endif
