#include "Thread.h"

BF::Thread::Thread()
{
	ThreadHandle = ThreadIDUnused;
}

ThreadID BF::Thread::Run(const ThreadFunction threadFunction, const void* parameter)
{
#ifdef OSUnix
    ThreadID threadID = 0;
	const int result = pthread_create(&threadID, 0, threadFunction, (void*)parameter);
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

void BF::Thread::WaitForFinish(const ThreadID threadID)
{
#ifdef OSUnix
    //pthread_join(thread->ID, NULL);
#elif defined(OSWindows)
	DWORD exitCode = 0;

	do
	{
		GetExitCodeThread(threadID, &exitCode);
	}
	while (exitCode == STILL_ACTIVE);
#endif
}
