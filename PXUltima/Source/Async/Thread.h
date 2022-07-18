#ifndef ThreadInclude
#define ThreadInclude

#include <OS/OSVersion.h>

#ifdef OSUnix
#include <pthread.h>
#include <unistd.h>
#define ThreadFunctionReturnType void*
#define ThreadFunctionReturnValue nullptr
#define ThreadID pthread_t
#define ThreadIDUnused 0
#elif defined(OSWindows)
#include <windows.h>
#define ThreadFunctionReturnType unsigned long
#define ThreadFunctionReturnValue 0
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

	typedef ThreadFunctionReturnType(*ThreadFunction)(void* data);


	extern ThreadID ThreadRun(const ThreadFunction threadFunction, const void* parameter);

	extern size_t ThreadCurrentID();

	extern void ThreadWaitForFinish(const ThreadID threadID);	

#ifdef __cplusplus
}
#endif

#endif