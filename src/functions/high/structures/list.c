#include <list.h>
#include <console.h>
#include <stdbool.h>
#include <memory.h>

void freeNode(Node* node);

void LIST_ForEach( List* list,  ActOnNodeFn fn )
{
	Node *node = list->head;
	while(node != null && list->size > 0)
	{
		Node* next = node->next;
		fn(node);
		node = next;
	}
}

Node* LIST_Pop(List* list)
{
	if( list->size == 0 || list->tail == NULL)
		return NULL;

	Node* oldTail = list->tail;

	if( oldTail->previous != NULL){
		oldTail->previous->next = NULL;
		list->size--;
		list->tail = oldTail->previous;
	}

	return oldTail;
}

Node* LIST_Get( List* list, int index)
{
	Node *node = list->head;
	int count = 0;
	while(node != null && list->size > 0)
	{
		Node* next = node->next;
		if( count == index){
			return node;
		}
		node = next;
		count++;
	}
	return NULL;
}

Node* LIST_Push( List* list, void *data)
{
	if( list->head == NULL )
	{
		Node *head = MEM_Alloc( sizeof(Node));

		head->data = data;
		head->next = NULL;
		head->previous = NULL;

		list->head = head;
		list->tail = head;

		head->list = (struct LinkedList*) list;
		list->size++;
		return head;
	}
	else
	{
		Node* newNode = MEM_Alloc( sizeof(Node) );
		Node* previous = list->tail;

		newNode->data = data;
		newNode->next = NULL;
		newNode->previous = previous;
		newNode->list = (struct LinkedList*) list;

		previous->next = newNode;

		list->tail = newNode;
		list->size++;
		return newNode;

	}

}

int LIST_DeleteNode( List* list, Node* nodeToDelete)
{
	Node *node = list->head;
	bool found = false;
	while(node != null && list->size > 0)
	{
		Node* next = node->next;
		if (nodeToDelete == node)
		{
			found = true;
			break;
		}
		node = next;
	}

	if(found){
		Node* previous = nodeToDelete->previous;
		Node* next = nodeToDelete->next;

		previous->next = next;
		next->previous = previous;

		freeNode(nodeToDelete);
		list->size--;
		return 0;
	}

	return -1;
}

Node* LIST_FindData( List* list, void* data )
{
	Node *node = list->head;
	while(node != null && list->size > 0)
	{
		Node* next = node->next;
		if( node->data == data) return node;
		node = next;
		list->size--;
	}
	return NULL;
}

void LIST_InsertBefore( List* list, void* data, Node* beforeThisNode)
{
	Node* newNode = MEM_Alloc(sizeof(struct LinkedListNode));
	newNode->data = data;
	newNode->list = list;
	newNode->previous = beforeThisNode->previous;
	newNode->previous->next = newNode;
	newNode->next = beforeThisNode;

	beforeThisNode->previous = newNode;
	list->size++;
}

void LIST_InsertAfter( List* list, void* data, Node* afterThisNode)
{
	struct LinkedListNode* newNode = malloc(sizeof(struct LinkedListNode));
	newNode->data = data;
	newNode->list = list;
	newNode->next = afterThisNode->next;
	newNode->previous = afterThisNode;

	afterThisNode->next = newNode;
	newNode->next->previous = newNode;
	list->size++;

}

void LIST_Deallocate( List* list )
{
    Node *node = list->head;
    while(node != null && list->size > 0)
    {
        Node* next = node->next;
        freeNode(node);
        node = next;
        list->size--;
    }
}

void freeNode(Node* node){
	free(node->data);
	free(node);
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
    	if( list->fnPrint != NULL)
    		list->fnPrint(current);
    	else
    		PRINTLINE("%d",current->data);
        current = current->next;
    }
}
