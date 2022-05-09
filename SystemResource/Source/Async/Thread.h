#ifndef ThreadInclude
#define ThreadInclude

#include <OS/OSDefine.h>

#ifdef OSUnix
#include <pthread.h>
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

namespace BF
{
	typedef ThreadFunctionReturnType(*ThreadFunction)(void* data);

	class Thread
	{
		private:
		ThreadID ThreadHandle;

		public:
		Thread();

		static ThreadID Run(const ThreadFunction threadFunction, const void* parameter);

		static void WaitForFinish(const ThreadID threadID);
	};
}
#endif
