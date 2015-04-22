#include <stulibc.h>


void test_AllInOneTests()
{
    Stack* intStack = newStack(10);
    int x = 100, y = 200, z = 300;
    
    // This stack is empty right now... 
    assert( isEmpty(intStack));
    
    push(&x, intStack);
    push(&y, intStack);
    push(&z, intStack);
    
    // this stack is not empty right now
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

    // this should not be empty
    assert( !isEmpty(stringStack) );
    assert( strcmp( (char*)pop(stringStack), goodbye) == 0 );
    assert( strcmp( (char*)pop(stringStack), hello) == 0 );
    
    freeStack(intStack);
    freeStack(stringStack);
}

int main( int argc, char** argv)
{
  struct TestDefinition tests[] = {
      test_AllInOneTests,"test_AllInOneTests"
  };
  
  run_tests(tests,1);  

  return 0;
}
