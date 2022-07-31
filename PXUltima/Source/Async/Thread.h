#ifndef ThreadInclude
#define ThreadInclude

#include <OS/OSVersion.h>

#ifdef OSUnix
#include <pthread.h>
#include <unistd.h>
#define ThreadResult void*
#define ThreadSucessful nullptr
#define ThreadID pthread_t
#define ThreadIDUnused 0
#elif defined(OSWindows)
#include <windows.h>
#define ThreadResult unsigned long
#define ThreadSucessful 0
#define ThreadID HANDLE
#define ThreadIDUnused nullptr
#if defined(OSWindowsXP)
typedef struct IUnknown IUnknown;
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	typedef ThreadResult(*ThreadFunction)(void* data);

	extern ThreadID ThreadRun(const ThreadFunction threadFunction, const void* parameter);

	extern size_t ThreadCurrentID();
	extern ThreadID ThreadCurrentGet();

	extern void ThreadWaitForFinish(const ThreadID threadID);	

#ifdef __cplusplus
}
#endif

#endif