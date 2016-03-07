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
	unsigned dwThreadId;
	HANDLE hThread;
	//TODO: We need a way to be able to wait for the threads all to finish like pthread_exit()
	if((hThread = (HANDLE)_beginthreadex(NULL, 8096 * 1024, func,(void*)threadparam, 0, &dwThreadId)) == NULL) {
		ERR_Print("Could not create thread.\n", YES);
		return -1;
	}else { return 0; }

#endif
}

LIBRARY_API void MakeLock(LockPtr* lock)
{
	DBG("MakeLock() Entry\n");
#ifdef __linux__
	pthread_mutex_init(*lock, NULL);
#endif

#ifdef _WIN32
	*lock = CreateMutex(NULL,FALSE,NULL);
	if(*lock == NULL) {
		printf("CreateMutex error: %d\n", GetLastError());
	}
#endif
	DBG("MakeLock() Exit\n");
}

LIBRARY_API bool AquireLock(LockPtr *lock)
{
	DBG("Aquiring/Waiting for ownership of Lock\n");

#ifdef __linux__
	pthread_mutex_lock(*lock);
	DBG("Got ownership of Lock\n");
#endif

#ifdef _WIN32
	 DWORD dwWaitResult = WaitForSingleObject(*lock, INFINITE);
	 switch (dwWaitResult)
	 {
		 // The thread got ownership of the mutex
		 case WAIT_OBJECT_0:
			 DBG("Got ownership of Lock\n");
		 return true;
		 break;
		 case WAIT_ABANDONED:
			 DBG("The thread got ownership of an abandoned mutex\n");
			 break;
		 case WAIT_TIMEOUT:
			 DBG("The time-out interval elapsed, and the object's state is nonsignaled.\n");
			 break;
		 case WAIT_FAILED:
			 DBG("WaitForSingleObject failed with error: %d\n", GetLastError());
			 break;
		 default:
			 DBG("(default cause matched)WaitForSingleObject error: %d\n", GetLastError());
			 break;
	 }
	 return false;

#endif
}

LIBRARY_API void ReleaseAndDestroyLock(LockPtr *lock)
{
	DBG("ReleaseAndDestroyLock() Entry\n");
#ifdef __linux__
	pthread_mutex_unlock(*lock);
	pthread_mutex_destroy(*lock);
#endif

#ifdef _WIN32
	// Release ownership of the mutex object
	ReleaseMutex(*lock);
	CloseHandle(*lock);
#endif
	DBG("ReleaseAndDestroyLock() Exit\n");
}

LIBRARY_API void ReleaseLock(LockPtr *lock)
{
	DBG("ReleaseLock() Entry\n");
#ifdef __linux__
	pthread_mutex_unlock(*lock);
#endif

#ifdef _WIN32
	// Release ownership of the mutex object
	ReleaseMutex(*lock);
#endif
	DBG("ReleaseLock() Exit\n");
}



