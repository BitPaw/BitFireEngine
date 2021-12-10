#ifndef AsyncLockIncluded
#define AsyncLockIncluded

#include "../OSDefine.h"

#ifdef OSUnix
#include <semaphore.h>
#define AsyncLockID sem_t
#elif defined(OSWindows)
typedef struct IUnknown IUnknown;
#include <windows.h>
//#include <process.h>
#define AsyncLockID HANDLE
#endif 

namespace BF
{
	class AsyncLock
	{
		private:
		AsyncLockID HandleID;

		public:
		AsyncLock();

		int Create();
		int Delete();
		int Lock();
		int Release();
	};
}

#endif