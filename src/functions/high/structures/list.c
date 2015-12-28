#include <list.h>
#include <console.h>
#include <stdbool.h>
#include <memory.h>
#include <debugging.h>
#include <safetychecking.h>

static void freeNode(Node* node);
static void increase_list_size_by_one(List* list);
static void decrease_list_size_by_one(List* list);
static Node* makeNewNode(const void* data, Node* previous, Node* next, List* list);

List* LIST_GetInstance()
{
	List* list = MEM_Alloc(sizeof(struct LinkedList));
	if(list == NULL) {
		ERR_Print("could not allocate memory.", YES);
	}
	LIST_Init(list);
	return list;
}
void LIST_FreeInstance(List* list)
{
	free(list);
	list = null;
}

void LIST_ForEach(const List* list,  ActOnNodeFn fn)
{
	Node *node = list->head;
	if( list == NULL || fn == NULL) {
		return;
	}
	do {
		Node* next = node->next;
		fn(node);
		node = next;
	} while(node != NULL && list->size > 0);
}

Node* LIST_Pop(List* list)
{
	if(list == NULL || list->size == 0 || list->tail == NULL) {
		return NULL;
	}

	Node* oldTail = list->tail;

	if( oldTail->previous != NULL) {
		oldTail->previous->next = NULL;
		decrease_list_size_by_one(list);
		list->tail = oldTail->previous;
	}

	return oldTail;
}

Node* LIST_Get(const List* list, int zero_index)
{
	if(list == NULL || list->size == 0) {
		DBG("List is empty\n");
		return NULL;
	}

	if(zero_index < 0) 	{
		DBG("List index is invalid : %d while size of list is %d\n", zero_index, list->size);
		return NULL;
	}

	if(zero_index == 0) {
		return list->head;
	}

	Node *node = list->head;
	int count = 0;
	do {
		Node* next = node->next;
		if(count == zero_index) {
			return node;
		}
		node = next;
		count++;
	} while(node != null && list->size > 0);

	return NULL;
}

Node* LIST_Push(List* list, const void *data)
{
	Node *created = NULL;

	if(list->head == NULL) {
		Node* previous = NULL;
		Node*next = NULL;
		Node *head = makeNewNode(data, previous, next, list);
		list->head = head;
		list->tail = head;

		created = head;
	}
	else {
		Node* previous = list->tail;
		Node* newNode = makeNewNode(data, previous, NULL, list);
		previous->next = newNode;

		list->tail = newNode;

		created = newNode;
	}
	increase_list_size_by_one(list);
	return created;
}

int LIST_DeleteNode(List* list, Node* nodeToDelete)
{
	if( list == null ){ return -1; }

	Node *node = list->head;
	bool found = false;

	do {
		if (nodeToDelete == node)  {
			found = true;
			break;
		}
		node = node->next;
	} while(node != null || list->size > 0);


	if(found) {
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

Node* LIST_FindData(const List* list, const void* data)
{
	Node *node = list->head;

	do {
		Node* next = node->next;
		if(node->data == data) return node;
		node = next;
	} while(node != null && list->size > 0);

	return NULL;
}

void LIST_InsertBeforeHead(List* list, const void* data)
{
	Node* newNode = makeNewNode(data, NULL, list->head, list);

	list->head->previous = newNode;
	list->head = newNode;

	increase_list_size_by_one(list);
}

void LIST_InsertBefore(List* list, const void* data, Node* beforeThisNode)
{
	Node* newNode = makeNewNode(data, beforeThisNode->previous, beforeThisNode, list);

	newNode->previous->next = newNode;

	beforeThisNode->previous = newNode;

	increase_list_size_by_one(list);
}

void LIST_InsertAfter(List* list, const void* data, Node* afterThisNode)
{
	struct LinkedListNode* newNode = makeNewNode(data, afterThisNode,afterThisNode->next,list);

	afterThisNode->next = newNode;
	newNode->next->previous = newNode;

	increase_list_size_by_one(list);
}

void LIST_Deallocate(List* list)
{
    Node *node = list->head;

    do {
        Node* next = node->next;
        freeNode(node);
        node = next;
        decrease_list_size_by_one(list);
    } while(node != null && list->size > 0);

}

static void freeNode(Node* node)
{
	if(node == null) {return;}

	free(node);
}

void LIST_Init(List* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->fnPrint = NULL;
}


void LIST_Print(const List* list)
{
    Node* current = list->head;
    do {
		if( list->fnPrint != NULL) {
			list->fnPrint(current);
		}
		current = current->next;
    } while(current != null && list->size > 0);

}

static void increase_list_size_by_one(List* list)
{
	list->size++;
}
static void decrease_list_size_by_one(List* list)
{
	list->size--;
}

static Node* makeNewNode(const void* data, Node* previous, Node* next, List* list)
{
	Node* newNode = MEM_Alloc(sizeof(Node));
	newNode->data = data;
	newNode->next = next;
	newNode->previous = previous;
	newNode->list = (struct LinkedList*) list;
	return newNode;
}
