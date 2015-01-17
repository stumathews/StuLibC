#include <memory.h>
#include <stdio.h>
#include <constants.h>
#include <testing.h>
#include <assert.h>
#include <debugging.h>

int* aIntPtr = NULL;
int number = 25;

void test_Alloc()
{
DBG("Entering test_Alloc()\n");
  aIntPtr = MEM_Alloc( SIZEOFINT);
DBG("performing first assert\n");
  assert( aIntPtr != NULL );

  aIntPtr = &number;
  assert( *aIntPtr == number );
  assert( &number == aIntPtr );
}

void test_DeAlloc()
{
  DBG("1");
  int address = (int) aIntPtr;
  DBG("2");
  int value = (int) *aIntPtr;
  DBG("3");

  MEM_DeAlloc(aIntPtr,"aIntPtr");
  DBG("4");
}
  

int main(int argc, char* argv[] )
{
  struct TestDefinition tests[] = {
    test_Alloc, "MEM_Alloc()",
    test_DeAlloc, "MEM_DeAlloc()",
  };

  run_tests(tests,2);
  return 0;
}
