#include "Lock.h"

#include <Memory/Memory.h>

extern void LockClear(LockID* const asyncLockID)
{
#if defined(OSUnix)
    MemorySet(asyncLockID, sizeof(LockID), 0);
#elif defined(OSWindows)
    *asyncLockID = 0;
#endif
}

ActionResult LockCreate(LockID* const asyncLockID)
{
#if defined(OSUnix)
	int sharedPointer = 0;
	unsigned int value = 1;

	const int resultID = sem_init(asyncLockID, sharedPointer, value);
	const unsigned char sucessful = resultID == 0; // 0=sucessful, -1=Error

#elif defined(OSWindows)
	LPSECURITY_ATTRIBUTES lpSemaphoreAttributes = 0;
	LONG lInitialCount = 1;
	LONG lMaximumCount = 1;
	LPCWSTR lpName = L"BFE_ASYNC_LOCK";

	const HANDLE handle = CreateSemaphoreW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
	const unsigned char sucessful = handle != 0;

	*asyncLockID = handle;
#endif

	if (!sucessful)
	{
        const ActionResult actionResult = GetCurrentError();

        LockClear(asyncLockID);

        return actionResult;
	}

	return ResultSuccessful;
}

ActionResult LockDelete(LockID* const asyncLockID)
{
	int closingResult = -1;

#if defined(OSUnix)
	closingResult = sem_destroy(asyncLockID);
#elif defined(OSWindows)
	closingResult = CloseHandle(asyncLockID);
#endif

    LockClear(asyncLockID);

	return closingResult;
}

ActionResult LockLock(LockID* const asyncLockID)
{
	int lockResult = -1;

#if defined(OSUnix)
	lockResult = sem_wait(asyncLockID);
#elif defined(OSWindows)
	lockResult = WaitForSingleObject(*asyncLockID, INFINITE);
#endif

	return lockResult;
}

ActionResult LockRelease(LockID* const asyncLockID)
{
	int releaseResult = -1;

#if defined(OSUnix)
	releaseResult = sem_post(asyncLockID);
#elif defined(OSWindows)
	releaseResult = ReleaseSemaphore(*asyncLockID, 1, 0);
#endif

	return releaseResult;
}
