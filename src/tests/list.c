#include <stulibc.h>

void printMe( struct node* myNode )
{
    PRINT( "%d\n",*(int*)(myNode->data));
}
void strPrint( struct node* myNode )
{
    PRINT( "%s\n",(char*)(myNode->data));
}

int main( int argc, char** argv )
{
    struct list myList;
    int x = 0, y = 1, z = 2;

    LIST_Init( &myList );
    LIST_Insert( &myList, &x );
    LIST_Insert( &myList, &y );
    LIST_Insert( &myList, &z );
    myList.fnPrint = printMe;
    PRINT("LIst size is %d\n", myList.size);
    LIST_Print( &myList );

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
