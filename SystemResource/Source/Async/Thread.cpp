#include "Thread.h"

BF::Thread::Thread()
{
	ThreadHandle = ThreadIDUnused;
}

ThreadID BF::Thread::Run(const ThreadFunction threadFunction, const void* parameter)
{
#ifdef OSUnix
	const ThreadID threadID = pthread_create(&threadID, 0, threadFunction, parameter);
#elif defined(OSWindows)
	const LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
	const SIZE_T dwStackSize = NULL;
	const LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)threadFunction;
	const LPVOID lpParameter = (const LPVOID)parameter;
	const DWORD dwCreationFlags = NULL;
	const LPDWORD lpThreadId = NULL;
	const ThreadID threadID = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
#endif

	return threadID;
}

void BF::Thread::WaitForFinish()
{
#ifdef OSUnix
    //pthread_join(thread->ID, NULL);
#elif defined(OSWindows)
	
#endif 
}