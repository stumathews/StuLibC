#include <files.h>
#include <testing.h>
#include <assert.h>
#include <debugging.h>
#include <safetychecking.h>


void test_FILE_Exists()
{
  char errors = 0;
  const char* filename = "file_exists_test.txt";
  FILE* file = fopen( filename, "w");

  assert( file != NULL );
  assert( FILE_Exists( filename) );
    
  fclose(file);  

  FILE_Delete( filename );
}

void test_FILE_Rename()
{
  char* filename = "filename.txt";
  char* new_filename = "new.txt";
  FILE* old = fopen(filename,"w");

  assert( old != NULL );
  fclose(old);

  assert( FILE_Exists(filename));    
  
  if( FILE_Exists( new_filename ))
    FILE_Delete( new_filename);

  FILE_Rename( filename, new_filename);

  assert( !FILE_Exists(filename));
  assert( FILE_Exists( new_filename));

  FILE_Delete( new_filename );
  
  
}

void test_FILE_Delete()
{
    FILE* file = fopen("filea.txt", "w");
    
    assert( file != NULL );
    fclose(file);
    
    FILE_Delete("filea.txt");

    assert( !FILE_Exists("filea.txt"));

}

void test_FILE_read_ini()
{
	FILE* stream = fopen( "test.ini", "r" );
	assert(stream != NULL );
	CHK_ExitIf( stream == NULL,"could not open file", "fopen");

	if( stream != NULL) {fclose(stream);}
}

void test_FILE_ContainsString()
{
  char* string = "hello mate";
  char* filename = "ContainsString.txt";
  
  // create the file if it doesn't exist
  FILE* mate_file = fopen( filename, "w");
  assert( mate_file != NULL);
  
  FILE_AppendTextToStream(string,mate_file); 

  fclose(mate_file);
  assert( FILE_Exists( filename ) );

  // open for reading
  mate_file = fopen( filename, "r" );
  char* lookfor = "hello";

  assert( FILE_ContainsString( mate_file, lookfor));
  
  fclose(mate_file);
  
  FILE_Delete( filename);  
  

}


int main( int arvc, char** argv )
{
 struct TestDefinition tests[] = {
		TEST(test_FILE_Exists),
		TEST(test_FILE_Delete),
		TEST(test_FILE_Rename),
		TEST(test_FILE_ContainsString),
		TEST(test_FILE_read_ini),
  };
 run_tests(tests,5);
  DBG_DeleteLog();

  return 0;
}

