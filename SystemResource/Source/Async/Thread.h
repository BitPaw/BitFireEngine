#ifndef ThreadInclude
#define ThreadInclude

#include "../OSDefine.h"

#ifdef OSUnix
#include <pthread.h>
#define ThreadFunctionReturnType void*
#define ThreadID pthread_t
#define ThreadIDUnused 0
#elif defined(OSWindows)
#include <windows.h>
#define ThreadFunctionReturnType unsigned long
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

		void Run(ThreadFunction threadFunction, void* parameter);
		static void Run(ThreadID& threadID, ThreadFunction threadFunction, void* parameter);

		void WaitForFinish();
	};
}
#endif