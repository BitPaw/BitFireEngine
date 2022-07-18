#ifndef AsyncLockIncluded
#define AsyncLockIncluded

#include <Async/Lock.h>

namespace BF
{
	class AsyncLock
	{
		private:
		LockID _lockID;

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