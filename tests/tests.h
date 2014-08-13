#ifndef STULIBC_TESTS_H
#define STULIBC_TESTS_H

#include "console_tests.h"
#include "timing_tests.h"
#include "libstring_tests.h"
#include "encryption_tests.h"
#include "datastructures_tests.h"
#include "..\strings\libstring.h"

void run(char* message, void (*test_fn)())
{
	console("\n**");
	console_printline( message);
	test_fn();
}

void run_debugging_tests()
{

}
void run_encryption_tests()
{
	run("test_vigenere_cipher...",test_vigenere_cipher);
	run("test_isaac_cipher...",test_isaac_cipher);
	run("test_caesar_cipher...",test_caesar_cipher);

}
void run_filemanagement_tests()
{

}
void run_keyboard_tests()
{

}
void run_libstring_tests()
{
	console_printline("Running libstring tests...");
	run("test_string_tokenizer...", test_string_tokenizer);
	run("test_substring...", test_substring);
	run("test_ltrim...", test_ltrim);
	run("test_rtrim...", test_rtrim);
	run("test_trim...", test_trim);
	run("test_startsWith...",test_startsWith);
	run("test_endsWith...",test_endsWith);
	run("test_doesContain...",test_doesContain);
	run("test_compare...",test_compare);
	run("test_comparecase...",test_comparecase);
}
void run_logging_tests()
{

}

void run_safetychecking_tests()
{

}

void run_timing_tests()
{
	console_printline("Running timing tests...");
	run("test_TIM_GetDateTimeStr", test_TIM_GetDateTimeStr);
}

void run_console_tests()
{
    puts("Running console tests...");
    //test_coloured_text();
}

void run_datastructure_tests()
{
	run("test_array_concat...",test_array_concat);
	run("test_simple_hashtable...",test_simple_hashtable);
}


#endif // STULIBC_TESTS_H
