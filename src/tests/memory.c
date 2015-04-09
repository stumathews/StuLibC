#include <memory.h>
#include <stdio.h>
#include <constants.h>
#include <testing.h>
#include <assert.h>
#include <debugging.h>

int* aIntPtr = NULL;
int number = 25;
void print_tracked();

void test_Alloc()
{
  aIntPtr = MEM_Alloc( SIZEOFINT);
  assert( aIntPtr != NULL );
  
  // try and deallocate a buffer not tracked/created by MEM_Alloc
  int* ptr = Alloc( sizeof(int) );
  assert( MEM_DeAlloc(ptr,"ptr") == true);
  
  int* a = alloc(SIZEOFINT);
  assert( MEM_DeAlloc( a, "a") == true);
 
  int* b = alloc(SIZEOFINT);
  int* c = alloc(SIZEOFINT);
  // create 10 random buffers 
  for( int i = 0; i < 10;i++)
  { 
      void* buffer = alloc( SIZEOFINT);
  }
  assert(  MEM_GetTrackedCount() == 13);
  //print_tracked();
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
