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

#define LIST_Add( list, data) LIST_Push(list, data)

typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* previous; 
    struct LinkedList* list;
} Node;



/**
 * Any function that will print the contents of a LinkedListNode
 * @param LinkedListNode
 */
typedef void (*PrintDataFunc)(Node* LinkedListNode);

typedef struct LinkedList {
    struct LinkedListNode* head;
    struct LinkedListNode* tail;
    int size;
    PrintDataFunc fnPrint;
    
} List;

/**
 * Gets the n-th item in the linked list
 * @param list
 * @param n
 * @return
 */
LIBRARY_API Node* LIST_Get( List* list, int n);
/**
 * Adds a new item to the list
 * @param list
 * @param data
 * @return Node* the added node
 */
LIBRARY_API Node* LIST_Push( List* list, void *data);

/**
 * Add to the list before a specified node
 * @param list
 * @param data
 * @param beforeThisNode
 */
LIBRARY_API void  LIST_InsertBefore( List* list, void* data, Node* beforeThisNode);

/**
 * Adds to the list after the specified node in the list
 * @param list
 * @param data
 * @param afterThisNode
 */
LIBRARY_API void  LIST_InsertAfter( List* list, void* data, Node* afterThisNode);

/**
 * Returns the last item in the list and removes it from the list
 * @param list
 * @return the last item in the list
 */
LIBRARY_API Node* LIST_Pop(List* list);
int   LIST_DeleteNode( List* list, Node* nodeToDelete);
Node* LIST_FindData( List* list, void* data );

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
