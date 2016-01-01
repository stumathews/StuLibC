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
  struct TestDefinition tests[] = { TEST(test_ERR_Print)};
  RUN_TESTS(tests);
  LOG_DeleteLog();
  return 0;
}
