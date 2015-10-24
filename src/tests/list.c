#include <stulibc.h>

void printMe( struct LinkedListNode* myNode )
{
    PRINT( "%d\n",*(int*)(myNode->data));
}
void strPrint( struct LinkedListNode* myNode )
{
    PRINT( "%s\n",(char*)(myNode->data));
}

void testIntList()
{

    struct LinkedList myList;
    int x = 0, y = 1, z = 2;

    LIST_Init( &myList );
    LIST_Add( &myList, &x );
    LIST_Add( &myList, &y );
    LIST_Add( &myList, &z );
    myList.fnPrint = printMe;
    LIST_Print( &myList );
    PRINT("LIst size is %d\n", myList.size);
}

void testStringList()
{

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
    LIST_Deallocate( &myStringList );

    assert( myStringList.size == 0);

    LIST_Print( &myStringList );

}

struct MyLinuxList
{
	int myNumber;
	struct list_head list;
};
struct MyLinuxList myList = {0};

void testLinuxList()
{
   

    
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

void testInsertBefore()
{
	List list = {0};
	LIST_Init(&list);
	Node* one = LIST_Add(&list, (void*)1);
	Node* two = LIST_Add(&list, (void*)2);

	LIST_InsertBefore(&list,(void*)3,two);
	Node* result = LIST_Get(&list,1);
	assert( result->data == (void*)3 );
	assert( result->next == two );
	assert( result->previous == one);
	LIST_Print(&list);
	LIST_Deallocate(&list);

}

void testLISTPop()
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

}

void testInsertAfter()
{
	List list = {0};
	LIST_Init(&list);
	Node* one = LIST_Add(&list, (void*)1);
	Node* two = LIST_Add(&list, (void*)2);
	Node* three = LIST_Add(&list, (void*)3);

	int data = 4;
	LIST_InsertAfter(&list,(void*)data,two);
	Node* result = LIST_Get(&list,2);
	assert( result->data == (void*)data );
	assert( result->next == three );
	assert( result->previous == two);
	LIST_Print(&list);
	LIST_Deallocate(&list);

}

void addTen( struct LinkedListNode* node)
{
	int* integer = (int*)node->data;
	*integer +=1;
}

void testLIST_ForEach()
{
	List list = {0};
DBG("foreach1");
	LIST_Init(&list);

	LIST_Add(&list,(void*)10);
	LIST_Add(&list,(void*)10);
	LIST_Add(&list,(void*)10);
	LIST_Add(&list,(void*)10);
	LIST_Add(&list,(void*)10);
	DBG("foreach2");
	LIST_ForEach(&list, addTen);
	assert( list.size == 5);
	DBG("foreach3");
	for( int i = 0; i < list.size;i++)
	{
		DBG("foreach4");
		Node* got = LIST_Get(&list,i);
		int* data = (int*)got->data;
		DBG("foreach5");
		PRINTLINE("data is '%d'", data);
		assert( *data == 11);
		DBG("foreach6");
	}
}

void testLIST_DeleteNode()
{
	List list = {0};

	LIST_Init(&list);

	LIST_Add(&list,(void*)1);
	LIST_Add(&list,(void*)2);

	Node* three = LIST_Add(&list,(void*)3);
	Node* four = LIST_Add(&list,(void*)4);
	Node* five = LIST_Add(&list,(void*)5);

	assert( list.size == 5);

	LIST_DeleteNode(&list, three);

	assert( list.size == 4);

	Node* res1 = LIST_Get(&list, 2);
	assert( res1 == four );

	Node* res2 = LIST_Get(&list, 3);
	assert( res2 == five);
	assert( list.size == 4);

	//assert( (int) *(int*)(LIST_Get(&list,0)->data) == 1 );
	//assert( (int) *(int*)(LIST_Get(&list,1)->data) == 2 );
	//assert( (int) *((int*)three->data) == 3 );
	//assert( (int) *((int*)four->data) == 4 );
	//assert( (int) *((int*)five->data) == 5 );

}

void testLIST_FindData()
{
	List list = {0};

	LIST_Init(&list);
	LIST_Push(&list, (void*)1);
	LIST_Push(&list, (void*)2);

	Node* three = LIST_Push(&list, (void*)3);
	Node* result = LIST_FindData(&list, (void*)3);

	assert( result == three);
	assert( list.size == 3);

}

void testLIST_Get()
{
	const char* strMmathews = "Mathews";

	List list = {0};
	LIST_Init(&list);
	LIST_Push(&list, (void*)"Stuart");
	LIST_Push(&list, (void*)strMmathews);

	assert( list.size == 2);

	Node* mathews = LIST_Get(&list,1);

	assert( list.size == 2);
	assert( STR_Equals((char*)mathews->data, (char*)strMmathews) == true );

	LIST_Deallocate(&list);
	assert( list.size == 0);
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
		TEST(testLIST_ForEach)

   };
   run_tests(tests,10);
   return 0;
}
