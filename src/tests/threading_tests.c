/*
 * threading_tests.c
 *
 *  Created on: 3 Jan 2016
 *      Author: stuart
 */

#include <stulibc.h>

int numbers[8] = {0,1,2,3,4,5,6,7};

void* thread_function(void* param)
{
	int* ptrToValueAtParam = (int*)param;
	int oldval = DEREF_TO_INT(param);

	*ptrToValueAtParam = 100;

	PRINT("thread '%d', DONE (0:%d,1:%d,2:%d,3:%d,4:%d,5:%d,6:%d,7:%d)\n",
			oldval,
			numbers[0],
			numbers[1],
			numbers[2],
			numbers[3],
			numbers[4],
			numbers[5],
			numbers[6],
			numbers[7]);

	return NULL;
}

void test_THREAD_RunAndForget()
{
	PRINT("About to run thread\n");
		srand(time(NULL));
		for(int i = 0 ; i < sizeof(numbers)/sizeof(numbers[0]); i++) {
			if(THREAD_RunAndForget(thread_function, numbers+i)) {
				ERR_Print("Problem running thread", YES);
			}
		}

#ifdef __linux__
		pthread_exit(NULL);  //wait for all threads to finish
#endif
#ifdef _WIN32
		sleep(2); //wait for all threads to finish
#endif

		for( int i = 0; i < 7;i++){
			assert(numbers[i] == 100);
		}


}

int main(int argc, char** argv)
{
	LIB_Init();
	struct TestDefinition tests[] = {
		TEST(test_THREAD_RunAndForget),
	};
	RUN_TESTS(tests);
	LIB_Uninit();
}

