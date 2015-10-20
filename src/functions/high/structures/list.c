#include <list.h>
#include <console.h>

/*
 List:
 	 -head: Node*
 	 -tail: Node*
 	 -size
 	 -fnPrint

 Node
 	 - data
 	 - next
 	 - previous
 */

void LIST_Insert( List* list, void* data )
{
    if( list->head == NULL )
    {
        Node *head = malloc( sizeof(Node));

        head->data = data;
        head->next = NULL;
        head->previous = NULL;

        list->head = head;
        list->tail = head;

        head->list = (struct list*) list;
    }
    else
    {
        Node* newNode = malloc( sizeof(Node) );
        Node* previous = list->tail;

        newNode->data = data;
        newNode->next = NULL;
        newNode->previous = previous;
        newNode->list = (struct list*) list;

        previous->next = newNode;

        list->tail = newNode;

    }
    list->size++;
}

void LIST_Deallocate( List* list )
{
    Node *node = list->head;
    while(node != null && list->size > 0)
    {
        Node* next = node->next;
        free(node->data);
        free(node);
        node = next;
        list->size--;
    }
}


void LIST_Init( List* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->fnPrint = NULL;
}

void LIST_Print( List* list )
{
    PRINT("Printing the list:\n");
    Node* current = list->head;

    while(current != null && list->size > 0)
    {
        list->fnPrint(current);
        current = current->next;
    }
}
