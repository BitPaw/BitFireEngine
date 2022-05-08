#include "AsyncLock.h"

BF::AsyncLock::AsyncLock()
{
	//HandleID = 0;
}

BF::AsyncLock::~AsyncLock()
{
	Delete();
}

int BF::AsyncLock::Create()
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
	HandleID = CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
#endif

	return createResult;
}

int BF::AsyncLock::Delete()
{
	int closingResult = -1;

#if defined(OSUnix)
	closingResult = sem_destroy(&HandleID);
#elif defined(OSWindows)
	closingResult = CloseHandle(HandleID);
#endif

	//HandleID = 0;

	return closingResult;
}

int BF::AsyncLock::Lock()
{
	int lockResult = -1;

#if defined(OSUnix)
	lockResult = sem_wait(&HandleID);
#elif defined(OSWindows)
	lockResult = WaitForSingleObject(HandleID, INFINITE);
#endif

	return lockResult;
}

int BF::AsyncLock::Release()
{
	int releaseResult = -1;

#if defined(OSUnix)
	releaseResult = sem_post(&HandleID);
#elif defined(OSWindows)
	releaseResult = ReleaseSemaphore(HandleID, 1, 0);
#endif

	return releaseResult;
}
