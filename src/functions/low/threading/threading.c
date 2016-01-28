/*
 * threading.c
 *
 *  Created on: 3 Jan 2016
 *      Author: stuart
 */

#include <threading.h>
#include <errors.h>
#include <safetychecking.h>
#include <stulibc.h>
int THREAD_RunAndForget(threadfunc func, void* threadparam)
{
#ifdef __linux__

	CHK_ExitIf(func == (void*)0, "thread function cannot be null", "THREAD_RunAndForget");

	pthread_t thread;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	int rc = pthread_create(&thread, NULL, func, threadparam);

	pthread_attr_destroy(&attr);
	if(rc) {
		ERR_Print("Could not create thread.\n", YES);
		return rc;
	} else { return 0; };

#endif

#ifdef _WIN32
	unsigned long dwThreadId;
	HANDLE hThread;
	//TODO: We need a way to be able to wait for the threads all to finish like pthread_exit()
	if((hThread = _beginthreadex(NULL, 0, (threadfunc)func,(void*)threadparam, 0, &dwThreadId)) == NULL) {
		ERR_Print("Could not create thread.\n", YES);
		return -1;
	}else { return 0;
	}

#endif
}



