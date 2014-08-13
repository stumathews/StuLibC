#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyboard\keyboard.h"
#include "debugging\debugging.h"
#include "filemanagement\filemanagement.h"
#include "safety\safetychecking.h"
#include "strings\libstring.h"
#include "logging\logging.h"
#include "encryption\encryption.h"

#ifndef USE_AS_LIBRARY
#include "tests/tests.h"

int main() // This is a test harness for the library
{
    run_console_tests();
    run_debugging_tests();
    run_encryption_tests();
    run_filemanagement_tests();
    run_keyboard_tests();
    run_libstring_tests();
    run_logging_tests();
    run_safetychecking_tests();
    run_timing_tests();
    run_datastructure_tests();
}

#endif
