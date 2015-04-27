/**
 * @file list.c
 * @brief List handling routines
 * @author Stuart Mathews
 * @date 27 April 2015
 *
 * This header contains the function and type declarations for dealing with handling lists  in the library.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page list Handling lists
Works with lists as a data structure to help you store information in an expanding way.
*/
#ifndef LIST_H
#define LIST_H
#include <stulibc.h>


typedef struct node {
    void* data;
    struct node* next;
    struct node* previous; 
} LinkedNode;

typedef void (*PrintDataFunc)(LinkedNode* node);

typedef struct list {
    struct node* head;
    struct node* tail;
    int size;
    PrintDataFunc fnPrint;
    
} LinkedList;


// insert data into list
LIBRARY_API void LIST_Insert( LinkedList* list, void* data); 

/** \brief Zeros a list contents
 *  \param list struct list* the list to initialize
 *  \return nothing
 */
LIBRARY_API void LIST_Init( LinkedList* list);

LIBRARY_API void LIST_Print( LinkedList* list);


#define LIST_H

#endif
