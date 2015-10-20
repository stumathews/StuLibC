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
    LIST_Insert( &myStringList, one);
    LIST_Insert( &myStringList, two);
    LIST_Insert( &myStringList, three);

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

int main( int argc, char** argv )
{
   struct TestDefinition tests[] = 
   {
        testIntList,"testIntList",
        testStringList,"testStringList",
       // testLinuxList, "testLinuxList"
   };
   run_tests(tests,2);
   return 0;
}
