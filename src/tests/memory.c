#include <memory.h>
#include <stdio.h>
#include <constants.h>
#include <testing.h>
#include <assert.h>
#include <debugging.h>
#include <stulibc.h>

int* aIntPtr = NULL;
int number = 25;

void test_Alloc()
{
  List* mem_addrs = LIST_GetInstance();

  aIntPtr = MEM_Alloc(SIZEOFINT, mem_addrs);
  assert( aIntPtr != NULL );
  
  // try and deallocate a buffer not tracked/created by MEM_Alloc
  int* ptr = Alloc( sizeof(int), mem_addrs );
  assert( MEM_DeAlloc(ptr,"ptr", mem_addrs) == true);

  int* ptr1 = Alloc( sizeof(int), mem_addrs);
  assert( MEM_DeAlloc(ptr1,"ptr1", mem_addrs) == true);
  
  int* ptr2 = Alloc( sizeof(int), mem_addrs );
  assert( MEM_DeAlloc(ptr2,"ptr2", mem_addrs) == true);
  
  int* a = Alloc(sizeof(int), mem_addrs);
  assert( MEM_DeAlloc( a, "a", mem_addrs) == true);
 
  int* b = alloc(SIZEOFINT,mem_addrs);
  int* c = alloc(SIZEOFINT,mem_addrs);
  // create 10 random buffers 
  for( int i = 0; i < 10;i++)
  { 
      void* buffer = alloc( SIZEOFINT, mem_addrs);
  }
  assert(MEM_GetTrackedCount(mem_addrs) == 13);

  MEM_DeAllocAll(mem_addrs);
  LIST_Deallocate(mem_addrs);
}

void test_DeAlloc()
{
	List* mem_addrs = LIST_GetInstance();
	int* aIntPtr = MEM_Alloc(SIZEOFINT, mem_addrs);

	MEM_DeAlloc(aIntPtr,"aIntPtr",mem_addrs);
	LIST_Deallocate(mem_addrs);
}
  

int main(int argc, char* argv[] )
{
  LIB_Init();
  struct TestDefinition tests[] = {
    TEST(test_Alloc),
    TEST(test_DeAlloc),
  };

  RUN_TESTS(tests);
  LIB_Uninit();
  return 0;
}
