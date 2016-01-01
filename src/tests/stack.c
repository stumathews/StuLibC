#include <stulibc.h>


void test_AllInOneTests()
{
    Stack* intStack = newStack(10);
    int x = 100, y = 200, z = 300;
    
    assert(isEmpty(intStack));
    
    push(&x, intStack);
    push(&y, intStack);
    push(&z, intStack);
    
    assert( !isEmpty(intStack) );

#if INSPECT_ERRORS
    trace(intStack);
#endif 
    assert( *(int*)pop(intStack) == 300);
    assert( *(int*)pop(intStack) == 200);
    assert( *(int*)pop(intStack) == 100);

    assert( isEmpty(intStack) );
    Stack* stringStack = newStack(4);
    
    char* hello = "Hello world!";
    char* goodbye = "Goodbye cruel world!";
    push(hello, stringStack);
    push(goodbye, stringStack);

    assert( !isEmpty(stringStack) );
    assert( strcmp( (char*)pop(stringStack), goodbye) == 0 );
    assert( strcmp( (char*)pop(stringStack), hello) == 0 );
    
    freeStack(intStack);
    freeStack(stringStack);
}

int main( int argc, char** argv)
{
  struct TestDefinition tests[] = {
      TEST(test_AllInOneTests)
  };
  
  RUN_TESTS(tests);  

  return 0;
}
