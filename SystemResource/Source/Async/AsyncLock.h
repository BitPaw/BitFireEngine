#ifndef AsyncLockIncluded
#define AsyncLockIncluded

#include "../OSDefine.h"

#ifdef OSUnix
#include <semaphore.h>
#elif defined(OSWindows)
typedef struct IUnknown IUnknown;
#include <windows.h>
//#include <process.h>
#endif 

namespace BF
{
	class AsyncLock
	{
		private:
#ifdef OSUnix
		sem_t HandleID;
#elif defined(OSWindows)
		HANDLE HandleID;
#endif
		public:
		int Create();
		int Delete();
		int Lock();
		int Release();
	};
}

#endif