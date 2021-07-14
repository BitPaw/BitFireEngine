#ifndef ThreadInclude
#define ThreadInclude

#include "OSDefine.h"

#ifdef OSUnix
#include <pthread.h>
#elif defined(OSWindows)
typedef struct IUnknown IUnknown;
#include <windows.h>
#endif 

typedef struct Thread_
{
#ifdef OSUnix
	pthread_t ThreadHandle;
#elif defined(OSWindows)
	HANDLE ThreadHandle;
#endif
}Thread;

#ifdef OSUnix
void ThreadCreate(Thread* thread, void* (*threadTask)(void* data), void* parameter);
#elif defined(OSWindows)
void ThreadCreate(Thread* thread, unsigned long (*threadTask)(void* data), void* parameter);
#endif

void ThreadWaitForFinish(Thread* thread);
#endif
