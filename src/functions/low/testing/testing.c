#ifndef LIBSTU_TESTING_H
#include <testing.h>
#include <console.h>
#include <strings.h>
#include <stdio.h>

LIBRARY_API void run_tests(struct TestDefinition* tests, int num_tests)
{

  for( int i = 0; i < num_tests ; i++)
  {
    DBG("- Running test '%s' ...\n",tests[i].name);
    // run the function
    tests[i].function();
  }
}


#endif //LIBSTU_TESTING_H
