#include "Lock.h"

int LockCreate(LockID* asyncLockID)
{
	int createResult = -1;

#if defined(OSUnix)
	int sharedPointer = 0;
	unsigned int value = 1;

	//HandleID = 0;

	createResult = sem_init(&HandleID, sharedPointer, value);
#elif defined(OSWindows)
	LPSECURITY_ATTRIBUTES lpSemaphoreAttributes = 0;
	LONG lInitialCount = 1;
	LONG lMaximumCount = 1;
	LPCWSTR lpName = L"BFE_ASYNC_LOCK";

	createResult = 0;
	asyncLockID = CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
#endif

	return createResult;
}

int LockDelete(LockID* asyncLockID)
{
	int closingResult = -1;

#if defined(OSUnix)
	closingResult = sem_destroy(&asyncLockID);
#elif defined(OSWindows)
	closingResult = CloseHandle(asyncLockID);
#endif

	*asyncLockID = LockNotSet;

	return closingResult;
}

int LockLock(LockID* asyncLockID)
{
	int lockResult = -1;

#if defined(OSUnix)
	lockResult = sem_wait(&asyncLockID);
#elif defined(OSWindows)
	lockResult = WaitForSingleObject(asyncLockID, INFINITE);
#endif

	return lockResult;
}

int LockRelease(LockID* asyncLockID)
{
	int releaseResult = -1;

#if defined(OSUnix)
	releaseResult = sem_post(&asyncLockID);
#elif defined(OSWindows)
	releaseResult = ReleaseSemaphore(asyncLockID, 1, 0);
#endif

	return releaseResult;
}