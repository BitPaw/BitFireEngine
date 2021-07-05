#include "Thread.h"

#ifdef OSUnix
void ThreadCreate(Thread* thread, void* (*threadTask)(void* data), void* parameter)
{
	int result = pthread_create(&thread->ThreadHandle, 0, threadTask, parameter);
}
#elif defined(OSWindows)
void ThreadCreate(Thread* thread, unsigned long (*threadTask)(void* data), void* parameter)
{
	const LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
	const SIZE_T dwStackSize = NULL;
	const LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)threadTask;
	const LPVOID lpParameter = parameter;
	const DWORD dwCreationFlags = NULL;
	const LPDWORD lpThreadId = NULL;

	thread->ThreadHandle = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}
#endif

void ThreadWaitForFinish(Thread* thread)
{
#ifdef OSUnix
    //pthread_join(thread->ID, NULL);
#endif 

}