/**
 * @file list.h
 * @brief List handling routines
 * @author Stuart Mathews
 * @date 27 April 2015
 *
 * This header contains the function and type declarations for dealing with handling lists  in the library.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page list Lists
Various linked list implementations. The default one is LIST_* functions and the other is
taken from the linux kernel and is more mature.
\include list.h
\include linuxlist.h
*/
#ifndef LIST_H
#define LIST_H
#include <constants.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    void* data;
    struct node* next;
    struct node* previous; 
    struct list* list;
} Node;

typedef void (*PrintDataFunc)(Node* node);

typedef struct list {
    struct node* head;
    struct node* tail;
    int size;
    PrintDataFunc fnPrint;
    
} List;


// insert data into list
LIBRARY_API void LIST_Insert( List* list, void* data); 

/** \brief Zeros a list contents
 *  \param list struct list* the list to initialize
 *  \return nothing
 */
LIBRARY_API void LIST_Init( List* list);

/** \brief Uses provided print function to print the contents of the list
 *  
 *  The function needs tp be compatible with the data within the linked list.
 *  \param list struct* list* the list to print
 *  \return void
 */
LIBRARY_API void LIST_Print( List* list);

/**
 * Deallocates all items in the list and sets the list size to 0
 * @param list the list to free up
 */
LIBRARY_API void LIST_Deallocate( List* list);

/* TODO:
 * int LIST_Find( List* list, void* value, int )
 * int LIST_Pop( List* list, int )
 * int LIST_Push( List* list, int )
 * int LIST_InsertBefore( List* list, int, Node* beforeMe )
 * int LIST_InsertAfter( List* list, int, Node* afterMe )
 * int LIST_Remove( List* list, void* value, int, all|first|last )
 * sorting a generic list with void*, possible? safe?
 * */

#define LIST_H

#endif
