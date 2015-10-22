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
    LIST_Add( &myStringList, one);
    LIST_Add( &myStringList, two);
    LIST_Add( &myStringList, three);

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
	Node* one = LIST_Add(&list, 1);
	Node* two = LIST_Add(&list, 2);

	LIST_InsertBefore(&list,3,two);
	Node* result = LIST_Get(&list,1);
	assert( result->data == 3 );
	assert( result->next == two );
	assert( result->previous == one);
	LIST_Print(&list);
	LIST_Deallocate(&list);

}

void testLISTPop()
{
	List list = {0};
	LIST_Init(&list);
	Node* alpha = LIST_Push(&list, "alpha");
	Node* beta = LIST_Push(&list, "beta");
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
	Node* one = LIST_Add(&list, 1);
	Node* two = LIST_Add(&list, 2);
	Node* three = LIST_Add(&list, 3);

	int data = 4;
	LIST_InsertAfter(&list,data,two);
	Node* result = LIST_Get(&list,2);
	assert( result->data == data );
	assert( result->next == three );
	assert( result->previous == two);
	LIST_Print(&list);
	LIST_Deallocate(&list);

}

void testLIST_FindData()
{
	List list = {0};
	LIST_Init(&list);
	LIST_Push(&list, 1);
	LIST_Push(&list, 2);
	Node* three = LIST_Push(&list, 3);
	Node* result = LIST_FindData(&list, 3);
	assert( result == three);
	assert( list.size == 2);

}

void testLIST_Get()
{
	const char* strMmathews = "Mathews";
	List list = {0};
	LIST_Init(&list);
	LIST_Push(&list, "Stuart");
	LIST_Push(&list, strMmathews);
	Node* mathews = LIST_Get(&list,1);
	assert( STR_Equals((char*)mathews->data, (char*)strMmathews) == true );
	LIST_Deallocate(&list);
}
int main( int argc, char** argv )
{
   struct TestDefinition tests[] = 
   {
        testIntList,"testIntList",
        testStringList,"testStringList",
        testLinuxList, "testLinuxList",
		testLIST_Get, "testLIST_Get",
		testInsertBefore, "testInsertBefore",
		testInsertAfter,"testInsertAfter",
		testLISTPop, "testLISTPop",
		testLIST_FindData, "testLIST_FindData"

   };
   run_tests(tests,7);
   return 0;
}
