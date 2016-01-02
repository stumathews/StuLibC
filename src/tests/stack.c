#include <stulibc.h>


void test_AllInOneTests()
{
    Stack* intStack = LIST_GetInstance();
    int x = 100, y = 200, z = 300;
    
    assert(intStack->size == 0);
    
    LIST_Push(intStack, &x);
    LIST_Push(intStack, &y);
    LIST_Push(intStack, &z);
    
    assert(intStack->size != 0);

    assert(DEREF_TO_INT(LIST_Pop(intStack)->data) == 300);
    assert(DEREF_TO_INT(LIST_Pop(intStack)->data) == 200);
    assert(DEREF_TO_INT(LIST_Pop(intStack)->data) == 100);

    assert(intStack->size == 0);
    Stack* stringStack = LIST_GetInstance();
    
    char* hello = "Hello world!";
    char* goodbye = "Goodbye cruel world!";

    LIST_Push(stringStack, hello);
    LIST_Push(stringStack, goodbye);


    assert(stringStack->size != 0);
    assert(strcmp(DEREF_TO_STR(LIST_Pop(stringStack)->data), goodbye) == 0);
    assert(strcmp(DEREF_TO_STR(LIST_Pop(stringStack)->data), hello) == 0);
    
    LIST_FreeInstance(intStack);
    LIST_FreeInstance(stringStack);
}

int main( int argc, char** argv)
{
  struct TestDefinition tests[] = {
      TEST(test_AllInOneTests)
  };
  
  RUN_TESTS(tests);  

  return 0;
}
