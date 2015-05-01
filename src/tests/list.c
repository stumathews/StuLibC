#include <stulibc.h>

void printMe( struct node* myNode )
{
    PRINT( "%d\n",*(int*)(myNode->data));
}
void strPrint( struct node* myNode )
{
    PRINT( "%s\n",(char*)(myNode->data));
}

void testIntList()
{

    struct list myList;
    int x = 0, y = 1, z = 2;

    LIST_Init( &myList );
    LIST_Insert( &myList, &x );
    LIST_Insert( &myList, &y );
    LIST_Insert( &myList, &z );
    myList.fnPrint = printMe;
    PRINT("LIst size is %d\n", myList.size);
}

void testStringList()
{

    LinkedList myStringList;
    char* one = "one";
    char* two = "two";
    char* three = "three";

    LIST_Init( &myStringList );
    LIST_Insert( &myStringList, one);
    LIST_Insert( &myStringList, two);
    LIST_Insert( &myStringList, three);

    myStringList.fnPrint = strPrint;
    LIST_Print( &myStringList );
}

void testLinuxList()
{
    struct MyLinuxList
    {
        int myNumber;
        struct list_head list;
    };

    struct MyLinuxList myList;

    INIT_LIST_HEAD( &myList.list );

    struct MyLinuxList* next = (struct MyLinuxList*) malloc( sizeof( struct MyLinuxList ));
	struct list_head *pos, *q;

	// Add a new item
	list_add( &(next->list), &(myList.list));

	// List each time
    list_for_each(pos, &myList.list){
		next = list_entry(pos, struct MyLinuxList, list);
        printf("number is %d\n", next->myNumber);
    }

	// Delete each item
    list_for_each_safe(pos, q, &myList.list)
	{
		next = list_entry(pos, struct MyLinuxList, list);
        printf("freeing item myNumber= %d\n", next->myNumber);
        list_del(pos);
        free(next);
    }

}

int main( int argc, char** argv )
{
   struct TestDefinition tests[] = 
   {
        testIntList,"testIntList",
        testStringList,"testStringList",
        testLinuxList, "testLinuxList"
   };
   run_tests(tests,3);
   return 0;
}
