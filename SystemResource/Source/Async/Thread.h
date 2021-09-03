#ifndef ThreadInclude
#define ThreadInclude

#include "../OSDefine.h"

#ifdef OSUnix
#include <pthread.h>
#elif defined(OSWindows)
typedef struct IUnknown IUnknown;
#include <windows.h>
#endif 

namespace BF
{
#ifdef OSUnix
	typedef void* (*ThreadFunction)(void* data);
#elif defined(OSWindows)
	typedef unsigned long (*ThreadFunction)(void* data);
#endif

	class Thread
	{
		private:
#ifdef OSUnix
		pthread_t ThreadHandle;
#elif defined(OSWindows)
		HANDLE ThreadHandle;
#endif

		public:
		void Create(ThreadFunction threadFunction, void* parameter);

		void WaitForFinish();
	};
}
#endif
