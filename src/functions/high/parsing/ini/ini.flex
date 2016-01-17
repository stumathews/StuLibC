%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stulibc.h>
#define YY_DECL int iniscan(List* list)
%}


HEADER    \[([^\]]+)\]
KEYVALUE  .+\s*=\s*.+

%%

{HEADER}	{
				typedef	struct KeyValuePair	Header;
				typedef struct KeyValuePair Setting;
				typedef 	   Node			GenericListItem;

				char headerName[80] = {0};
				Header *thisHeader = null;

				// found a header in file, extract it into header variable
				sscanf( yytext, "[%99[^] ] ]", headerName);
				
				DBG("Found header: %s", headerName);
				
				// Search through list of headers to see if we know about it already
				GenericListItem *item = list->head;
				while(item != null && list->size > 0)
				{
					GenericListItem* next = item->next;
					Header* currentHeader = (Header*) item->data;
					// do we already 'know/have' this header in our list of headers?
					if(STR_Equals(currentHeader->key, headerName) == true){
						thisHeader = currentHeader;
						break;
					}
					item = next;
				}

				// Store this new header if we don't already have reference to it
				if(thisHeader == null ){
					thisHeader = (Header*) malloc(sizeof(Header));
					strcpy(thisHeader->key, headerName );

					//and make space for a list of settings for it
					thisHeader->value = malloc(sizeof(List));
					LIST_Push( list, (void*) thisHeader );
				}
			}

{KEYVALUE}	{
	       		// A KeyValuePair type is used for representing a header(heading) and setting(key=value)
				typedef	struct KeyValuePair	Header;
				typedef struct KeyValuePair Setting;

				char key[80] = {0};
	       		char value[80] = {0};
	       		Header *currentHeader = null;
				List* currentHeaderSettings = null;
				Setting* setting = null;

				// Found a key-value pair, extract it into key/value
				sscanf(yytext, "%[^=]= %[^\n]", key, value);   

				currentHeader = (Header*) list->tail->data;
				currentHeaderSettings = (List*)currentHeader->value;

				// Turn the key/value into a setting
				setting = (Setting *) malloc(sizeof(Setting));
				setting->value = (char*) malloc(sizeof(char) * 20);

				strcpy(setting->key, key);
				strcpy(setting->value, value);
				
				DBG("Found %s key/value: %s/%s", currentHeader->key, key, value);

				// Add this setting to this header's list of settings
				LIST_Push( currentHeaderSettings, (void*) setting);
			}
;.*	
.	       printf( "Unrecognized character: %s\n", yytext );	   
%%
