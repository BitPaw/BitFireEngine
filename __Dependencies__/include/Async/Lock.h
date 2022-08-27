#ifndef LockInclude
#define LockInclude

#include <OS/OSVersion.h>
#include <Error/ActionResult.h>

#if defined(OSUnix)
#include <semaphore.h>
#define LockID sem_t // is union, cannot be defined as "sem_t" only -> compile error
#elif defined(OSWindows)
#include <windows.h>
//#include <process.h>
#define LockID HANDLE // same as void*
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    // Clear value of lock, sets internal data to 0.
    extern void LockClear(LockID* const asyncLockID);

	extern ActionResult LockCreate(LockID* const asyncLockID);
	extern ActionResult LockDelete(LockID* const asyncLockID);
	extern ActionResult LockLock(LockID* const asyncLockID);
	extern ActionResult LockRelease(LockID* const asyncLockID);
#ifdef __cplusplus
}
#endif

#endif
