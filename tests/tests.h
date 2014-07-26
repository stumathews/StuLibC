#ifndef STULIBC_TESTS_H
#define STULIBC_TESTS_H
#include "console_tests.h"

void run_debugging_tests() {}
void run_encryption_tests() {}
void run_filemanagement_tests() {}
void run_keyboard_tests() {}
void run_libstring_tests() {}
void run_logging_tests() {}
void run_safetychecking_tests() {}
void run_timing_tests() {}

void run_console_tests()
{
    test_CNS_Say();
}


#endif // STULIBC_TESTS_H
