#include <stulibc.h>

static void printMe( struct LinkedListNode* myNode )
{
    PRINT( "%d\n",*(int*)(myNode->data));
}
static void strPrint( struct LinkedListNode* myNode )
{
    PRINT( "%s\n",(char*)(myNode->data));
}
static void printBuffer(Node* node)
{
	PRINT("%p<--%p\n", node->previous != NULL ? node->previous->data:0,
						  node != null ? node->data : 0);
						  //node->next != NULL ? node->next->data : 0);
}
static void addTen( struct LinkedListNode* node)
{
	DBG("addTen1");
	int* integer = (int*)node->data;
	DBG("addTen2");
	DBG("integer is '%d'", *integer);
	*integer +=1;
	DBG("addTe3");
}

static void testIntList()
{
    struct LinkedList myList = {0};
    int x = 0, y = 1, z = 2;

    LIST_Init(&myList);
    assert(myList.size == 0);
    LIST_Add(&myList, &x);
    assert(myList.size == 1);
    LIST_Add(&myList, &y);
    assert(myList.size == 2);
    LIST_Add(&myList, &z);

    assert(myList.size == 3);
    assert( 0 == DEREF_TO_INT(LIST_Get(&myList, 0)->data));
    assert( 1 == DEREF_TO_INT(LIST_Get(&myList, 1)->data));
    assert( 2 == DEREF_TO_INT(LIST_Get(&myList, 2)->data));

    myList.fnPrint = printMe;

    LIST_Print(&myList);

    PRINT("List size is %d\n", myList.size);

    LIST_Deallocate(&myList);
}
static void testStringList()
{

    List myStringList = {0};
    char* one = "one";
    char* two = "two";
    char* three = "three";

    LIST_Init( &myStringList );
    LIST_Add( &myStringList, DEREF_TO_STR(one));
    LIST_Add( &myStringList, DEREF_TO_STR(two));
    LIST_Add( &myStringList, DEREF_TO_STR(three));

    assert( myStringList.size == 3);

    myStringList.fnPrint = strPrint;

    LIST_Print( &myStringList );
    LIST_Deallocate( &myStringList);
}
static void testInsertBefore()
{
	List *list = LIST_GetInstance();
	int alpha = 101;
	int beta = 102;
	int theta = 103;

	Node* one = LIST_Add(list, (void*)&alpha);
	Node* two = LIST_Add(list, (void*)&beta);

	LIST_InsertBefore(list,(void*)&theta,two);

	Node* result = LIST_Get(list,1);

	assert( result->data == (void*)&theta );
	assert( result->next == two );
	assert( result->previous == one);

	LIST_Print(list);
	LIST_Deallocate( list);

}
static void testLISTPop()
{
	List list = {0};
	LIST_Init(&list);

	Node* alpha = LIST_Push(&list,(void*) "alpha");
	Node* beta = LIST_Push(&list,(void*) "beta");

	Node* shouldBeBeta = LIST_Pop(&list);

	assert( beta == shouldBeBeta);
	assert( LIST_Get(&list,0) == alpha );
	assert( list.tail->next == NULL );
	assert( list.tail == alpha);
	assert( list.size == 1);
	LIST_Clear(&list);

}
static void testInsertAfter()
{
	List list = {0};
	LIST_Init(&list);

	int alpha = 101;
	int beta = 102;
	int theta = 103;

	Node* one = LIST_Add(&list, (void*)&alpha);
	Node* two = LIST_Add(&list, (void*)&beta);
	Node* three = LIST_Add(&list, (void*)&theta);

	int data = 4;
	LIST_InsertAfter(&list,(void*)&data,two);

	Node* result = LIST_Get(&list,2);

	assert(result->data == (void*)&data);
	assert(result->next == three);
	assert(result->previous == two);
	assert(one == LIST_Get(&list,0));

	LIST_Print(&list);
	LIST_Clear(&list);

}
static void testLIST_ForEach()
{
	List list = {0};
	LIST_Init(&list);

	int numbers[] = {10,10,10,10,10,10};
	LIST_Add(&list, (void*)&numbers[0]);
	LIST_Add(&list,(void*)&numbers[1]);
	LIST_Add(&list,(void*)&numbers[2]);
	LIST_Add(&list,(void*)&numbers[3]);
	LIST_Add(&list,(void*)&numbers[4]);

	LIST_ForEach(&list, addTen);
	assert( list.size == 5);

	for( int i = 0; i < list.size;i++)
	{
		Node* got = LIST_Get(&list,i);
		int* data = (int*)got->data;
		assert( *data == 11);
	}
	LIST_Deallocate( &list);
}
static void testLIST_DeleteNode()
{
	List *actualList = LIST_GetInstance();
	List list = *actualList;
	int numbers[] = {1,2,3,4,5,6};

	LIST_Init(&list);

	LIST_Add(&list,(void*)&numbers[0]);
	LIST_Add(&list,(void*)&numbers[1]);

	Node* one = LIST_Get(&list,0);
	Node* two = LIST_Get(&list,1);
	Node* three = LIST_Add(&list,(void*)&numbers[2]);
	Node* four = LIST_Add(&list,(void*)&numbers[3]);
	Node* five = LIST_Add(&list,(void*)&numbers[4]);

	assert( list.size == 5);

	LIST_DeleteNode(&list, three);
	assert( list.size == 4);


	Node* res1 = LIST_Get(&list, 2);
	assert( res1 == four );

	Node* res2 = LIST_Get(&list, 3);
	assert( res2 == five);
	assert( list.size == 4);

	int *one_data = (int*)one->data;
	int* two_data = (int*)two->data;
	int* four_data = (int*)four->data;
	int* five_data = (int*)five->data;

	assert( *one_data == 1 );
	assert( *two_data == 2);
	assert( *four_data == 4);
	assert( *five_data == 5);

	LIST_Deallocate( &list);


}
static void testLIST_FindData()
{
	List list = {0};
	int numbers[] = {1,2,3,4,5,6};

	LIST_Init(&list);
	LIST_Push(&list, (void*)&numbers[0]);
	LIST_Push(&list, (void*)&numbers[1]);

	Node* three = LIST_Push(&list, (void*)&numbers[2]);
	Node* result = LIST_FindData(&list, (void*)&numbers[2]);

	assert( result == three);
	assert( list.size == 3);

}
static void testLIST_Get()
{
	const char* strMmathews = "Mathews";

	List *list = LIST_GetInstance();
	LIST_Init(list);
	LIST_Push(list, (void*)"Stuart");
	LIST_Push(list, (void*)strMmathews);

	assert( list->size == 2);

	Node* mathews = LIST_Get(list,1);

	assert( list->size == 2);
	assert( STR_Equals((char*)mathews->data, (char*)strMmathews) == true );

}
static void testGetInstance()
{
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

}
static void testLIST_InsertBeforeHead()
{
	List* names = LIST_GetInstance();

	LIST_Add(names, "Robert");
	LIST_Add(names, "Charles");

	LIST_InsertBeforeHead(names,"Stuart");

	Node* name = LIST_Get(names, 0);

	assert(STR_EqualsIgnoreCase((char*)name->data, "Stuart"));


}
static void testLinuxList()
{
	struct MyLinuxList
	{
		int myNumber;
		struct list_head list;
	};

	struct MyLinuxList myList = {0};

	struct list_head *pos, *q;
	struct MyLinuxList* tmp;

    INIT_LIST_HEAD( &myList.list );

	for (int i = 0; i < 20; i++)
	{
		tmp = (struct MyLinuxList*) malloc(sizeof(struct MyLinuxList));
		tmp->myNumber = i;
		list_add(&(tmp->list), &(myList.list));
	}

    list_for_each(pos, &myList.list){
		tmp = list_entry(pos, struct MyLinuxList, list);
		printf("number is %d\n", tmp->myNumber);
    }

    list_for_each_safe(pos, q, &myList.list)
	{
		tmp = list_entry(pos, struct MyLinuxList, list);
		printf("freeing item myNumber= %d\n", tmp->myNumber);
        list_del(pos);
		free(tmp);
    }

}
void testListOrder()
{
	List* names = LIST_GetInstance();
	names->fnPrint = printBuffer;

	Node* first = LIST_Push(names, "a");
	Node* second = LIST_Push(names, "b");
	Node* third = LIST_Push(names, "c");
	Node* fourth = LIST_Push(names, "d");

	LIST_DeleteNode(names, third);
	Node* popped = LIST_Pop(names);

	assert(names->size == 2);
	assert(strcmp(DEREF_TO_STR(names->tail->data), "b") == 0);

	LIST_Print((const List*)names);
	LIST_Clear(names);
	LIST_FreeInstance(names);



}

int main( int argc, char** argv )
{
   struct TestDefinition tests[] = 
   {
        TEST(testIntList),
		TEST(testStringList),
		TEST(testLinuxList),
		TEST(testLIST_Get),
		TEST(testInsertBefore),
		TEST(testInsertAfter),
		TEST(testLISTPop),
		TEST(testLIST_FindData),
		TEST(testLIST_DeleteNode),
		TEST(testLIST_ForEach),
		TEST(testGetInstance),
		TEST(testLIST_InsertBeforeHead),
		TEST(testListOrder)
   };
   RUN_TESTS(tests);
   return 0;
}
