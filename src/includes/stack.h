/**
 * @file stack.h
 * @brief Generic stack data structure handling routines
 * @author Stuart Mathews
 * @date 10 January 2014
 *
 * This header contains the function and type declarations for dealing with generic stack datastructures in the library.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page stack Stacks
Generic stacks and how they are used in the library
\include stack.h
*/
#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <constants.h>
#include <string.h>

typedef struct Stack Stack;

struct Stack
{
    int counter;
    int max;
    void** container;
};

/***
* newStack - allocates space and sets up stack
* @size: the desired default container size (5 minimum)
*
**/
LIBRARY_API Stack* newStack(int size);
/***
* freeStack - frees container and stack memory
* @stack: target stack
*
**/
LIBRARY_API void freeStack(Stack* stack);
/***
* getSize - returns current stack counter position
* @stack: target stack
*
**/
LIBRARY_API int getSize(Stack* stack);
/***
* getMax - returns the current max stack size
* @stack: target stack
*
**/
LIBRARY_API int getMax(Stack* stack);
/***
* isEmpty - returns 1 if stack is empty, 0 if not
* @stack: target stack
*
**/
LIBRARY_API int isEmpty(Stack* stack);
/***
* resizeContainer - expands container to 2*max
* @stack: target stack
*
**/
LIBRARY_API void** resizeContainer(Stack* stack);
/***
* trace - prints the current stack layout
* @stack: target stack
*
**/
LIBRARY_API void trace(Stack* stack);
/***
* search - searches for value in stack and returns index of the found value
* or returns -1 if not found.
* @value: target value
* @stack: target stack
*
**/
LIBRARY_API int search(void* value, Stack* stack);
/***
* peek - returns top of the stack without removing it
* @stack: target stack
*
**/
LIBRARY_API void* peek(Stack* stack);
/***
* push - pushes an item onto a stack
* @item: target item
* @stack: target stack
*
**/
LIBRARY_API void push(void* item, Stack* stack);
/***
* pop - pops an item off the top of the target stack
* @stack: target stack
*
**/
LIBRARY_API void* pop(Stack* stack);
#endif /* STACK_H */

