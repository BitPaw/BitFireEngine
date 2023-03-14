#ifndef PXThreadInclude
#define PXThreadInclude

#include <OS/System/OSVersion.h>
#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>

// Return IDs

#define PXThreadSucessful 0
#define PXThreadActionFailed (void*)1


#if OSUnix
#include <pthread.h>
#include <unistd.h>
typedef void* PXThreadResult;
typedef pthread_t PXThreadIDType;
#define PXThreadIDUnused 0  // Adress
#elif OSWindows
#include <windows.h>
typedef unsigned long PXThreadResult;
typedef HANDLE PXThreadIDType;
#define PXThreadIDUnused nullptr
#if OSWindowsXP
typedef struct IUnknown IUnknown;
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	typedef PXThreadResult(*ThreadFunction)(void* data);

	typedef struct PXThread_
	{
		PXThreadIDType ThreadID;
	}
	PXThread;	

	PXPublic PXActionResult PXThreadRun(PXThread* const pxThread, const ThreadFunction threadFunction, const void* parameter);


	PXPublic void PXThreadSuspend(PXThread* const pxThread);
	PXPublic void PXThreadResume(PXThread* const pxThread);

	PXPublic PXSize PXThreadCurrentID();
	PXPublic void PXThreadCurrentGet(PXThread* const pxThread);

	PXPublic void PXThreadWaitForFinish(PXThread* const pxThread);

#ifdef __cplusplus
}
#endif

#endif
