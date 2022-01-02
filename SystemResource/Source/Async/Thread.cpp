#include "Thread.h"

BF::Thread::Thread()
{
	ThreadHandle = ThreadIDUnused;
}

void BF::Thread::Run(ThreadFunction threadFunction, void* parameter)
{
	Thread::Run(ThreadHandle, threadFunction, parameter);
}

void BF::Thread::Run(ThreadID& threadID, ThreadFunction threadFunction, void* parameter)
{
#ifdef OSUnix
	threadID = pthread_create(&threadID, 0, threadFunction, parameter);
#elif defined(OSWindows)
	const LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
	const SIZE_T dwStackSize = NULL;
	const LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)threadFunction;
	const LPVOID lpParameter = parameter;
	const DWORD dwCreationFlags = NULL;
	const LPDWORD lpThreadId = NULL;

	threadID = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
#endif
}

void BF::Thread::WaitForFinish()
{
#ifdef OSUnix
    //pthread_join(thread->ID, NULL);
#elif defined(OSWindows)
	
#endif 
}