#ifndef TIMING_TESTS_H
#define TIMING_TESTS_H
#include <time.h>
#include "..\console\console.h"
void test_TIM_GetDateTimeStr()
{
	console((char*)TIM_GetDateTimeStr());
}

#endif
