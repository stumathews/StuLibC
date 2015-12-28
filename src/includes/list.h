/**
 * @file list.h
 * @brief The List data structure and supporting functions.
 * @author Stuart Mathews
 * @date 27 April 2015
 *
 * This header contains the function and type declarations for dealing with handling lists in the library.
 * All functions are centred around a list object of type List.
 *
 * A list is made up on items that are represented as Node types. In this way a List has many node(items).
 * All functions are prefixed with LIST_*.
 * Here is an example storing simple strings:
@code
    List myStringList = {0};
    char* one = "one";
    char* two = "two";
    char* three = "three";

    LIST_Init( &myStringList );
    LIST_Add( &myStringList, (void*)one);
    LIST_Add( &myStringList, (void*)two);
    LIST_Add( &myStringList, (void*)three);

    assert( myStringList.size == 3);

    myStringList.fnPrint = strPrint;

    LIST_Print( &myStringList );
    LIST_Deallocate( &myStringList);
 @endcode
 * Here is an example storing integers:
@code
    struct LinkedList myList = {0};
    int x = 0, y = 1, z = 2;

    LIST_Init( &myList );
    LIST_Add( &myList, &x );
    LIST_Add( &myList, &y );
    LIST_Add( &myList, &z );
    myList.fnPrint = printMe;
    LIST_Print( &myList );
    PRINT("LIst size is %d\n", myList.size);
    LIST_Deallocate( &myList );
@endcode
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page list Lists
This page contains the function and type declarations for dealing with handling lists in the library.
There are currently two implementations - a simple list and an advanced list.

The simple list is the LIST_* of functions and the other is taken from the Linux kernel and its functions are preceded with list_*.
The latter is more mature.

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

/** \brief Convenience MACRO to removes a node from the list  */
#define LIST_Remove( list, node ) LIST_DeleteNode( list, node )

/** \brief Convenience MACRO to add raw data to list */
#define LIST_Add( list, data ) LIST_Push( list, data )

/** \brief Convenience MACRO to clear the contents of the list */
#define LIST_Clear( list ) LIST_Deallocate( list )

/** \brief Represents a single node in the list.
 *
 * This structure wraps raw data that actually represents the list.
 * The node can contain any data.
 * This encapsulation allows each node knows about what list it is in and who is next to it or behind it.
 */
typedef struct LinkedListNode {

	/** \brief The raw data that is wrapped within this LinkedListNode  */
    void* data;

    /** \brief  link to the next node - NULL if none exists  */
    struct LinkedListNode* next;

    /** \brief link to the previous item - NULL is none exists */
    struct LinkedListNode* previous;

    /** \brief Link to the list that contains the node. */
    struct LinkedList* list;
} Node;

/** \brief Any user defined function that will accept a LinkedListNode
 *
 * @param LinkedListNode the node to act on
 */
typedef void ( *ActOnNodeFn )(Node* LinkedListNode);

/** \brief Main list type. */
typedef struct LinkedList {

	/** \brief Pointer to the first item in the list */
    struct LinkedListNode* head;

    /** \brief Pointer to the current last item of this list */
    struct LinkedListNode* tail;

    /** \brief Current size of the list - maintained by LIST_* functions. */
    int size;

    /** \brief  User defined function to print the contents of the list. */
    ActOnNodeFn fnPrint;
    
} List;

/** \brief Puts provided user data at front of list.
 *
 * @param list
 * @param data
 * @note data effectively becomes new head and the previous head becomes afterwards (head-1) etc...
 * @remarks This is useful for putting things in front of the queue when the list is being used as one.
 */
LIBRARY_API void LIST_InsertBeforeHead(List* list, const void* data);

/** \brief Runs a user defined function on each node in the list.
 *
 * The function takes a single parameter of LinkedNode*.
 * The function is free to do whatever it wants with the data in the visited node.
 * @param list the list with nodes to visit
 * @param fn the user defined function
  */
LIBRARY_API void LIST_ForEach(const List* list, ActOnNodeFn fn);

/** \brief Gets the n-th item in the linked list.
 *
 * @param list the list to act on
 * @param n the index to fetch form the list
 * @return a pointer to the node, otherwise NULL if cant find or error
 * @note returns NULL is the list is empty or other error
 */
LIBRARY_API Node* LIST_Get(const List* list, int n);

/** \brief Adds a new item to the list.
 *
 * @param list that the item will be added to
 * @param raw user data item to be added
 * @note This is added to the end(tail) of the list aka becomes last item in list.
 * @return Node* the added node
 */
LIBRARY_API Node* LIST_Push(List* list, const void *data);

/** \brief Add to the list before a specified node.
 *
 * @param list to act on
 * @param data the raw user data to be added
 * @param beforeThisNode the specified node.
 */
LIBRARY_API void  LIST_InsertBefore(List* list, const void* data, Node* beforeThisNode);

/** \brief Adds to the list after the specified node in that list.
 *
 * @param list to add item to
 * @param data raw data to add after the specified node.
 * @param afterThisNode the specified node.
 */
LIBRARY_API void  LIST_InsertAfter(List* list, const void* data, Node* afterThisNode);

/** \brief Returns the last item in the list and removes it from the list.
 *
 * @param list to pop from
 * @return the last item in the list
 * @warning The last item node(not actual data) is not deallocated.
 */
LIBRARY_API Node* LIST_Pop(List* list);

/** \brief Deletes a node in the list.
 *
 * @param list
 * @param nodeToDelete
 * @note deallocates the node in memory, underlying wrapped user data's memory location is not affected.
 * @return true if successful, otherwise false
 */
LIBRARY_API int LIST_DeleteNode(List* list, Node* nodeToDelete);

/** \brief Finds the first node in the list with the same address(pointer) as data provided.
 *
 * @param list
 * @param data
 * @return the node that houses that data in the list, null otherwise
 * @note if the data is not found null is returned
 */
LIBRARY_API Node* LIST_FindData(const List* list, const void* data);

/** \brief Zeros a list contents.
 *
 *  @param list struct list* the list to initialise
 */
LIBRARY_API void LIST_Init(List* list);

/** \brief Uses set print function (@see LinkedList) to print the contents of the list.
 *
 *  The function needs to be compatible with the data within the linked list.
 *  @param list struct* list* the list to print
 *  @note if no function is defined, this function does nothing.
 */
LIBRARY_API void LIST_Print(const List* list);

/** \brief Deallocates all items in the list and sets the list size to 0.
 *
 * @param list the list to free up
 * @note the list itself is not freed, only the allocated memory each of the nodes
 */
LIBRARY_API void LIST_Deallocate(List* list);

/** \brief Creates a new List* type.
 *
 *	Example of usage:
 *  @code
    List* list = LIST_GetInstance();

	CHK_ExitIf(list == null,"list == null","testGetInstance");


	LIST_Add(list, "Stuart");
	LIST_Add(list, "Robert");
	LIST_Add(list, "Charles");

	CHK_ExitIf(list->size != 3,"list->size != 3","testGetInstance");

	list->fnPrint = strPrint;
	LIST_Print(list);

	LIST_FreeInstance(list);
	CHK_ExitIf(!list,"list is not null","testGetInstance");
@endcode
  * @note this object is dynamically allocated in memory and can be released by calling the LIST_FreeInstance() function accordingly
 */
LIBRARY_API List* LIST_GetInstance();

/** \brief Free previously created list instance.
 *
 *  @param list
 */
LIBRARY_API void LIST_FreeInstance(List* list);

#endif

/**
 These shows how to use lists in the library:
\example list.c
 */
