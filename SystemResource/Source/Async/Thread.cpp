#include "Thread.h"

#ifdef OSUnix
void BF::Thread::ThreadCreate(ThreadFunction threadFunction, void* parameter)
{
	int result = pthread_create(&thread->ThreadHandle, 0, threadTask, parameter);
}
#elif defined(OSWindows)
void BF::Thread::Create(ThreadFunction threadFunction, void* parameter)
{
	const LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
	const SIZE_T dwStackSize = NULL;
	const LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)threadFunction;
	const LPVOID lpParameter = parameter;
	const DWORD dwCreationFlags = NULL;
	const LPDWORD lpThreadId = NULL;

	ThreadHandle = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}
#endif

void BF::Thread::WaitForFinish()
{
#ifdef OSUnix
    //pthread_join(thread->ID, NULL);
#elif defined(OSWindows)
	
#endif 

}