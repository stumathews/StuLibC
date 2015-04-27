#include <stulibc.h>

void printMe( struct node* myNode )
{
    PRINT( "%d\n",*(int*)(myNode->data));
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
    
}
