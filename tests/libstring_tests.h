
#ifndef STULIBC_STRING_TESTS_H
#define STULIBC_STRING_TESTS_H
#include "../strings/substring.h"
#include "../strings/tokenizer.h"
void doprint(const char *s) {
	printf("%s and ", s);
}

void test_string_tokenizer()
{
	char array[] = "Hello,How,Are,You,Today";
	tokenize(array, ',', doprint);
}

void test_substring()
{
	const char *s = "hello world shortest program";

	  TEST( substring(s, 12, 5) );		// get "short"
	  TEST( substring(s, 6, -1) );		// get "world shortest program"
	  TEST( str_wholeless1(s) );		// "... progra"
	  TEST( str_fromch(s, 'w', 5) );	// "world"
	  TEST( str_fromstr(s, "ro", 3) );	// "rog"

}

const char *a = "     this is a string      ";

void test_rtrim()
{
	char *b = rtrim(a);

	  printf("'%s'\n",b);

	  free(b);


}

void test_ltrim()
{
	 char *c = ltrim(a);
	 printf("'%s'\n",c);
	 free(c);
}

void test_trim()
{
	char *d = trim(a);
	printf("'%s'\n",d);
	free(d);
}

void test_startsWith(){
	printf("Starts with Test ( Hello,Hell ) : %d\n", startsWith("Hello","Hell"));
}

void test_endsWith(){
	printf("Ends with Test ( Code,ode ) : %d\n", endsWith("Code","ode"));
}

void test_doesContain(){
	printf("Contains Test ( Google,msn ) : %d\n", doesContain("Google","msn"));
}

void test_compare() {
	const char* a = "BLADE RUNNER";
	const char* b = "SkyWalker";
	puts("\teq , ne , gt , lt , ge , le");
	printf("%s%2d%2d%2d%2d%2d%2d %s\n",
	 a,
	 STREQ(a,b), STRNE(a,b), STRGT(a,b), STRLT(a,b), STRGE(a,b), STRLE(a,b),
	 b
	 );
}

void test_comparecase()
{
	const char* a = "BLADE RUNNER";
	const char* b = "SkyWalker";
	puts("\teq , ne , gt , lt , ge , le");
	printf("%s%2d%2d%2d%2d%2d%2d %s ignoring case\n",
	 a,
	 STRCEQ(a,b), STRCNE(a,b), STRCGT(a,b), STRCLT(a,b), STRCGE(a,b), STRCLE(a,b),
	 b
	 );
}

#endif // STULIBC_STRING_H
