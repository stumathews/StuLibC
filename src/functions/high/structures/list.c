#include <list.h>
#include <console.h>

void LIST_Insert( LinkedList* list, void* data )
{
    if( list->head == NULL )
    {
        list->head = malloc( sizeof(struct node));
        list->head->data = data;
        list->head->next = NULL;
        list->head->previous = NULL;

        list->tail = list->head;
    }
    else
    {
        struct node* tmpNode = malloc( sizeof(struct node) );
        tmpNode->data = data;
        tmpNode->next = NULL;
        tmpNode->previous = list->tail;

        list->tail->next = tmpNode;
        list->tail = tmpNode;
    }
    list->size++;

}

void LIST_Init( LinkedList* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->fnPrint = NULL;
}

void LIST_Print( LinkedList* list )
{
    PRINT("Printing the list:\n");
    LinkedNode* current = list->head;
    while( current != null )
    {
        list->fnPrint(current);
        current = current->next;
    }
}
