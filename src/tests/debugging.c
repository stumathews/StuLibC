#include <stulibc.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errors.h>
#include <strings.h>
#include <files.h>
#include <testing.h>



void test_DBG_WriteLineToFile()
{
  
  DBG_WriteLineToFile("Writing this to the file log.txt","log.txt", CRITICAL );
  assert( FILE_Exists("log.txt"));
  FILE_Delete( "log.txt" );

}

void test_DBG_WriteLineToFileExtra()
{
  if( FILE_Exists( "log.file"))
    FILE_Delete("log.file");
  
  DBG_WriteLineToFileExtra( "prefix", "message","suffix","log.file", CRITICAL );

  assert( FILE_Exists( "log.file" ));

  FILE_Delete("log.file");
}

void test_DBG_LogIf()
{
  int condition = 1 > 0;
  if( condition == 0 ) exit(1);

  DBG_LogIf( condition, "1 is greater than 0","1 is not creater than 0");

  assert( FILE_Exists( DBG_GetDefaultLogFileName() )); 
  
  DBG_DeleteLog();
}

int main( int argc, char** argv )
{
 struct TestDefinition tests[] = {
  test_DBG_WriteLineToFile,"test_DBG_WriteLineToFile()",
  test_DBG_WriteLineToFileExtra,"test_DBG_WriteLineToFileExtra()",
  test_DBG_LogIf,"test_DBG_LogIf()"
 };

  run_tests(tests,3);
  
 DBG_DeleteLog();
 return 0;
}
