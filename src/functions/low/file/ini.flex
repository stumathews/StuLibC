%option noyywrap

%{
#define YY_DECL int iniscan()
#include <stdio.h>
#include <stdlib.h> 
%}


HEADER    \[([^\]]+)\]
KEYVALUE  .+\s*=\s*.+

%%

{HEADER}	{
				char clean[80] = {0}; 
				sscanf( yytext, "[%99[^] ] ]", clean);   
				printf("header is '%s'\n", clean);
			}

{KEYVALUE}	{
	       		char key[80] = {0}; 
	       		char value[80] = {0};
				sscanf( yytext, "%[^=]= %[^\n]", key, value);   
				printf("key is '%s', value is '%s'\n", key, value);
			}
;.*	
.	       printf( "Unrecognized character: %s\n", yytext );	   
%%
