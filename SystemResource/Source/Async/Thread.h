#ifndef ThreadInclude
#define ThreadInclude

#include "../OSDefine.h"

#ifdef OSUnix
#include <pthread.h>
#define ThreadFunctionReturnType void*
#define ThreadID pthread_t
#elif defined(OSWindows)
#include <windows.h>
#define ThreadFunctionReturnType unsigned long
#define ThreadID HANDLE
typedef struct IUnknown IUnknown;
#endif

namespace BF
{
	typedef ThreadFunctionReturnType(*ThreadFunction)(void* data);

	class Thread
	{
		private:
		ThreadID ThreadHandle;

		public:
		void Create(ThreadFunction threadFunction, void* parameter);

		void WaitForFinish();
	};
}
#endif