#include <files.h>
#include <testing.h>
#include <assert.h>
#include <debugging.h>
#include <safetychecking.h>
#include <console.h>
#include <ini.h>


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

static void printSetting( GenericListItem* LinkedListNode )
{
	struct KeyValuePair *kvp = (struct KeyValuePair*)(LinkedListNode->data);
	PRINT( "setting: %s, value: %s \n", kvp->key, kvp->value);
}

void test_FILE_IniParse()
{
	List settings = {0};

	int res = INI_IniParse("test.ini", &settings);
	if( res != 0)
	{
		ERR_Print("INI_IniParse() failed.\n", true );
	}

	char* setting = INI_GetSetting(&settings, "Network", "hostname");
	assert( setting != null);
	assert( STR_Equals(setting, "My Computer") == true);

	setting = INI_GetSetting(&settings, "owner", "organization");
	assert( setting != null);
	assert( STR_Equals(setting, "Acme Widgets Inc.") == true);

	setting = INI_GetSetting(&settings, "database", "server");
	assert( setting != null);
	assert( STR_Equals(setting, "192.0.2.62") == true);

	// These dont exist and are expected to fail lookup .ie return null
	setting = INI_GetSetting(&settings, "database", "server1");
	assert( setting == null);

	setting = INI_GetSetting(&settings, "unknown", "unknown");
	assert( setting == null);

}

int main( int arvc, char** argv )
{
 struct TestDefinition tests[] = {
		TEST(test_FILE_Exists),
		TEST(test_FILE_Delete),
		TEST(test_FILE_Rename),
		TEST(test_FILE_ContainsString),
		TEST(test_FILE_IniParse)
  };
 run_tests(tests,5);
  DBG_DeleteLog();

  return 0;
}

