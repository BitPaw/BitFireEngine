#ifndef LockInclude
#define LockInclude

#include <OS/OSVersion.h>

#if defined(OSUnix)
#include <semaphore.h>
#define LockID sem_t
#define LockNotSet 0
#elif defined(OSWindows)
#include <windows.h>
//#include <process.h>
#define LockID HANDLE
#define LockNotSet 0
#endif


#ifdef __cplusplus
extern "C"
{
#endif
	extern int LockCreate(LockID* asyncLockID);
	extern int LockDelete(LockID* asyncLockID);
	extern int LockLock(LockID* asyncLockID);
	extern int LockRelease(LockID* asyncLockID);
#ifdef __cplusplus
}
#endif

#endif