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
Linked list data structure and functionality.
The default one is LIST_* functions and the other is
taken from the linux kernel and is more mature.
A list looks like this
 {List
 	 head -> node
 	 tail -> node
 	 size
 }

 A node looks like this:
 {Node
 	 data
 	 previous
 	 next
 	 list
  }

  Node(Head) -- Node -- Node -- Node(Tail)

Simple List:
\include list.h
Advanced List:
\include linuxlist.h
*/
#ifndef LIST_H
#define LIST_H
#include <constants.h>
#include <stdio.h>
#include <stdlib.h>

#define LIST_Remove( list, node ) LIST_DeleteNode( list, node )
#define LIST_Add( list, data ) LIST_Push( list, data )
#define LIST_Clear( list ) LIST_Deallocate( list )

/**
 * Represents a single node in the list. The node can contain any data.
 * Each node knows about what list it is in.
 */
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
typedef void ( *ActOnNodeFn )( Node* LinkedListNode );

/**
 * Top level list that holds reference to the head and tail of the list
 * along with other list overall attributes such as the size
 */
typedef struct LinkedList {
    struct LinkedListNode* head;
    struct LinkedListNode* tail;
    int size;
    ActOnNodeFn fnPrint;
    
} List;

LIBRARY_API void LIST_ForEach( List* list, ActOnNodeFn fn );

/**
 * Gets the n-th item in the linked list
 * @param list
 * @param n
 * @return
 */
LIBRARY_API Node* LIST_Get( List* list, int n );

/**
 * Adds a new item to the list
 * @param list
 * @param data
 * @return Node* the added node
 */
LIBRARY_API Node* LIST_Push( List* list, void *data );

/**
 * Add to the list before a specified node
 * @param list
 * @param data
 * @param beforeThisNode
 */
LIBRARY_API void  LIST_InsertBefore( List* list, void* data, Node* beforeThisNode );

/**
 * Adds to the list after the specified node in the list
 * @param list
 * @param data
 * @param afterThisNode
 */
LIBRARY_API void  LIST_InsertAfter( List* list, void* data, Node* afterThisNode );

/**
 * Returns the last item in the list and removes it from the list
 * @param list
 * @return the last item in the list
 */
LIBRARY_API Node* LIST_Pop( List* list );

/**
 * Deletes a node in the list
 * @param list
 * @param nodeToDelete
 * @return
 */
LIBRARY_API int   LIST_DeleteNode( List* list, Node* nodeToDelete );
/**
 * Finds the first node in the list with the data provided
 * @param list
 * @param data
 * @return the node that houses that data in the list
 */
LIBRARY_API Node* LIST_FindData( List* list, void* data );

/** \brief Zeros a list contents
 *  \param list struct list* the list to initialize
 *  \return nothing
 */
LIBRARY_API void LIST_Init( List* list );

/** \brief Uses provided print function to print the contents of the list
 *  
 *  The function needs tp be compatible with the data within the linked list.
 *  \param list struct* list* the list to print
 *  \return void
 */
LIBRARY_API void LIST_Print( List* list );

/**
 * Deallocates all items in the list and sets the list size to 0
 * @param list the list to free up
 */
LIBRARY_API void LIST_Deallocate( List* list );

#endif
