#ifndef AsyncLockIncluded
#define AsyncLockIncluded

#include <OS/OSDefine.h>

#if defined(OSUnix)
#include <semaphore.h>
#define AsyncLockID sem_t
#elif defined(OSWindows)
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
		~AsyncLock();

		int Create();
		int Delete();
		int Lock();
		int Release();
	};
}

#endif
