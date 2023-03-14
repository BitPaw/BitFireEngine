#ifndef PXProcessINCLUDE
#define PXProcessINCLUDE

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <OS/Time/PXTime.h>

#if OSUnix
#include <unistd.h>
#elif OSWindows
#include <windows.h>
#endif

#if OSUnix
typedef __pid_t PXProcessID;
typedef unsigned int PXProcessThreadID;
#elif OSWindows
typedef HANDLE PXProcessHandle;
typedef DWORD PXProcessID;
typedef HANDLE PXProcessThreadHandle;
typedef DWORD PXProcessThreadID;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXProcess_
	{
		PXProcessHandle ProcessHandle;
		PXProcessID ProcessID; // Context
		PXProcessThreadHandle ThreadHandle;
		PXProcessThreadID ThreadID;
	}
	PXProcess;

	typedef struct PXProcessMemoryInfo_
	{
		PXTime ExecuteStartTime;
		PXTime ExecuteTimeUser;
		PXTime ExecuteTimeKernel;

		// RAM
		long PageReclaims; // soft page fault
		long PageFaults; // hard page fault
		long IOOperationRead;
		long IOOperationWrite;
		long ContextSwapVoluntary;
		long ContextSwapInvoluntary;


		PXSize PeakWorkingSetSize; // The peak working set size, in bytes.
		PXSize WorkingSetSize; // The current working set size, in bytes.
		PXSize QuotaPeakPagedPoolUsage; // The peak paged pool usage, in bytes.
		PXSize QuotaPagedPoolUsage; // The current paged pool usage, in bytes.
		PXSize QuotaPeakNonPagedPoolUsage; // The peak nonpaged pool usage, in bytes.
		PXSize QuotaNonPagedPoolUsage; // The peak value in bytes of the Commit Charge during the lifetime of this process.
		PXSize PagefileUsage;
		PXSize PeakPagefileUsage; // The peak value in bytes of the Commit Charge during the lifetime of this process.
		PXSize PrivateUsage; // Windows new value
	}
	PXProcessMemoryInfo;


	PXPublic void PXProcessConstruct(PXProcess* const pxProcess);

	PXPublic void PXProcessCurrent(PXProcess* const pxProcess);
	PXPublic void PXProcessParent(PXProcess* const pxProcess);

	typedef enum PXProcessCreationMode_
	{
		PXProcessCreationModeInvalid,
		PXProcessCreationModeBREAKAWAY_FROM_JOB,
		PXProcessCreationModeDEFAULT_ERROR_MODE,
		PXProcessCreationModeNEW_CONSOLE,
		PXProcessCreationModeNEW_PROCESS_GROUP,
		PXProcessCreationModeWindowless,
		PXProcessCreationModePROTECTED_PROCESS,
		PXProcessCreationModePRESERVE_CODE_AUTHZ_LEVEL,
		PXProcessCreationModeSECURE_PROCESS,
		PXProcessCreationModeSEPARATE_WOW_VDM,
		PXProcessCreationModeSHARED_WOW_VDM,
		PXProcessCreationModeSuspended, // Process created but does not start.
		PXProcessCreationModeUNICODE_ENVIRONMENT,
		PXProcessCreationModeDebugProcessOnly, // Debug only this process, ignored
		PXProcessCreationModeDebugAll, // Debug this process and every child and more.
		PXProcessCreationModeDETACHED_PROCESS,
		PXProcessCreationModeEXTENDED_STARTUPINFO_PRESENT,
		PXProcessCreationModeINHERIT_PARENT_AFFINITY
	}
	PXProcessCreationMode;

	PXPublic PXActionResult PXProcessCreateA(PXProcess* const pxProcess, const PXTextASCII programmPath, const PXProcessCreationMode mode);
	PXPublic PXActionResult PXProcessCreateW(PXProcess* const pxProcess, const PXTextUNICODE programmPath, const PXProcessCreationMode mode);

	PXPublic PXActionResult PXProcessOpen(PXProcess* const pxProcess);
	PXPublic PXActionResult PXProcessClose(PXProcess* const pxProcess);

	PXPublic PXSize PXProcessMemoryWrite(const PXProcess* const pxProcess, const void* const targetAdress, const void* const buffer, const PXSize bufferSize);
	PXPublic PXSize PXProcessMemoryRead(const PXProcess* const pxProcess, const void* const targetAdress, const void* const buffer, const PXSize bufferSize);

	PXPublic PXActionResult PXProcessMemoryInfoFetch(PXProcessMemoryInfo* const pxProcessMemoryInfo);

#ifdef __cplusplus
}
#endif

#endif
