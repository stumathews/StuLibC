#include <safetychecking.h>
#include <testing.h>


bool IsAgeValid(int* age )
{
	DBG("chec,ing my age...\n");
  // my age is 25;
  if( *age != 25 )
    return true;
  else
    return false;
}

void rectifyAge(int* data)
{
  DBG("rec my age\n");
  while( !IsAgeValid(data)){ DBG("rectifying\n"); *data = *data + 1;}
}

void test_CHK_int()
{
  int age = 20;
  CHK_int( IsAgeValid, &age,"my age", rectifyAge );
}

int main( int argc, char* argv[])
{
  struct TestDefinition tests[] = {
    TEST(test_CHK_int),
  };
  RUN_TESTS(tests);
  return 0;
}
