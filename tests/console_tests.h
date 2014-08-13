#ifndef STULIBC_CONSOLE_TESTS_H
#define STULIBC_CONSOLE_TESTS_H

#include "..\console\console.h"

void test_CNS_Print()
{
    CNS_Print("Hi");
    console("Hello");
}

void test_coloured_text()
{
	int fg, bg, blink, inverse;

	    	table("normal ( ESC[22m or ESC[m )", "22;");
	    	table("bold ( ESC[1m )", "1;");
	    	table("faint ( ESC[2m ), not well supported", "2;");
	    	table("italic ( ESC[3m ), not well supported", "3;");
	    	table("underline ( ESC[4m ), support varies", "4;");
	    	table("blink ( ESC[5m )", "5;");
	    	table("inverted ( ESC[7m )", "7;");
}

#endif
