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
  aIntPtr = MEM_Alloc( SIZEOFINT);
  assert( aIntPtr != NULL );
  // try and deallocate a buffer not tracked/created by MEM_Alloc
  int* ptr = malloc( sizeof(int) );
  assert(  MEM_DeAlloc(ptr,"ptr") == false);
}

void test_DeAlloc()
{
  MEM_DeAlloc(aIntPtr,"aIntPtr");
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
