#include <errors.h>
#include <constants.h>
#include <logging.h>
#include <testing.h>

void test_ERR_Print()
{
#if INSPECT_ERRORS
			 	ERR_Print("ERR_Print: Hello this is a test error", YES);
#endif
}
int main(int argc, char** argv )
{
  struct TestDefinition tests[] = {test_ERR_Print,"test_ERR_Print"};
  run_tests(tests,1);
  LOG_DeleteLog();
  return 0;
}
