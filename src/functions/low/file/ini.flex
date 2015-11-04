%option noyywrap

%{
#define YY_DECL int iniscan()

%}


HEADER    \[.+\]
KEYVALUE  .+\s*=\s*.+

%%



{HEADER}    {
	       printf( "An header: %s (%d)\n", yytext);
}

{KEYVALUE}	       {
	       printf( "An keyvalue: %s (%d)\n", yytext);
}

.	       printf( "Unrecognized character: %s\n", yytext );

%%
