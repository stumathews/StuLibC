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
}

void test_DeAlloc()
{
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
