#include <list.h>
#include <console.h>
#include <stdbool.h>
#include <memory.h>
#include <debugging.h>
#include <safetychecking.h>

static void freeNode(Node* node);
static void increase_list_size_by_one(List* list);
static void decrease_list_size_by_one(List* list);

List* LIST_GetInstance()
{
	List* list = MEM_Alloc( sizeof( struct LinkedList ));
	return list;
}
void LIST_FreeInstance(List* list)
{
	free(list);
	list = null;
}

void LIST_ForEach( List* list,  ActOnNodeFn fn )
{

	Node *node = list->head;
	if( list == NULL){
		DBG("list is null");
		return;
	}

	while(node != NULL && list->size > 0)
	{
		Node* next = node->next;
		if( fn == NULL )
		{
			return;
		}

		fn(node);

		node = next;
	}
}

Node* LIST_Pop(List* list)
{
	if( list == NULL)
	{
		DBG("List is empty\n");
		return NULL;
	}

	if( list->size == 0 || list->tail == NULL )
	{
		return NULL;
	}

	Node* oldTail = list->tail;

	if( oldTail->previous != NULL)
	{
		oldTail->previous->next = NULL;
		decrease_list_size_by_one(list);
		list->tail = oldTail->previous;
	}

	return oldTail;
}

Node* LIST_Get( List* list, int zero_index)
{
	if(list == NULL || list->size == 0)
	{
		DBG("List is empty\n");
		return NULL;
	}

	if( zero_index < 0)
	{
		DBG("List index is invalid : %d while size of list is %d\n", zero_index, list->size);
		return NULL;
	}

	Node *node = list->head;
	int count = 0;
	while(node != null && list->size > 0)
	{
		Node* next = node->next;
		if( count == zero_index)
		{
			return node;
		}
		node = next;
		count++;
	}
	return NULL;
}

Node* LIST_Push( List* list, void *data)
{
	Node *created = NULL;

	if( list->head == NULL )
	{
		Node *head = MEM_Alloc(sizeof(Node));

		head->data = data;
		head->next = NULL;
		head->previous = NULL;

		list->head = head;
		list->tail = head;

		head->list = (struct LinkedList*) list;

		created = head;
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

		created = newNode;
	}
	increase_list_size_by_one(list);
	return created;
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
		decrease_list_size_by_one(list);
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
	increase_list_size_by_one(list);
}

void LIST_InsertAfter( List* list, void* data, Node* afterThisNode)
{
	struct LinkedListNode* newNode = MEM_Alloc(sizeof(struct LinkedListNode));
	newNode->data = data;
	newNode->list = list;
	newNode->next = afterThisNode->next;
	newNode->previous = afterThisNode;

	afterThisNode->next = newNode;
	newNode->next->previous = newNode;
	increase_list_size_by_one(list);

}

void LIST_Deallocate( List* list )
{
    Node *node = list->head;
    while(node != null && list->size > 0)
    {
        Node* next = node->next;
        freeNode(node);
        node = next;
        decrease_list_size_by_one(list);
    }
}

static void freeNode(Node* node)
{
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
    Node* current = list->head;

    while(current != null && list->size > 0)
    {
    	if( list->fnPrint != NULL)
    	{
    		list->fnPrint(current);
    	}
        current = current->next;
    }
}

static void increase_list_size_by_one(List* list)
{
	list->size++;
}
static void decrease_list_size_by_one(List* list)
{
	list->size--;
}
