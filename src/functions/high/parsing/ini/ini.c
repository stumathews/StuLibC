#include <ini.h>
#include <constants.h>
#include <stdbool.h>
#include <list.h>
#include <iniscanner.h>
#include <safetychecking.h>
#include <errors.h>

void INI_IniParse(const char* filename, List* settings)
{
	CHECK_STRING( filename, IS_NOT_EMPTY );

	yyin = fopen( filename, "r" );
	if(yyin == null){
		ERR_Print("Could not open .ini file", true);
	}

	iniscan(settings);

	fclose(yyin);
}
