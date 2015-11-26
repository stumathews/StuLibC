#include <ini.h>
#include <constants.h>
#include <stdbool.h>
#include <list.h>
#include <iniscanner.h>
#include <safetychecking.h>
#include <errors.h>

int INI_IniParse(const char* filename, List* settings)
{
	CHECK_STRING( filename, IS_NOT_EMPTY );
	yyin = fopen( filename, "r" );
	if(yyin == null){
		ERR_Print("Could not open .ini file", true);
		return -1;
	}

	iniscan(settings);

	fclose(yyin);
	return 0;
}

char* INI_GetSetting(List* settings, char* section, char* setting)
{
	// Scan each section
	for( int i = 0; i < settings->size; i++){
		struct KeyValuePair* section = (struct KeyValuePair*) LIST_Get(settings, i)->data;
		if( STR_Equals(section->key, section) == true )
		{
			List* section_settings = (List*) section->value;
			for( int j = 0; j < section_settings->size;j++)
			{
				struct KeyValuePair* current_setting = (struct KeyValuePair*) LIST_Get(section_settings, j)->data;
				if( STR_Equals(setting, current_setting->key ) == true )
				{
					return (char*) current_setting->value;
				}
			}
		}
	}
	return null;
}
