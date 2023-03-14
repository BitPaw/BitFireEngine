#ifndef ExecutableInclude
#define ExecutableInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <OS/Thread/PXThread.h>

#if OSUnix
#include <unistd.h>
typedef pid_t ProcessHandle;
typedef unsigned int ProcessID;
#elif OSWindows
#include <windows.h>
typedef HANDLE ProcessHandle;
typedef DWORD ProcessID;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	typedef void (*ProgramExecutedEvent)(const unsigned char succesful, PXSize returnResult, const PXActionResult errorCode);

	typedef struct Program_
	{
		ProcessHandle Handle;

		wchar_t FilePath[260];

		ProgramExecutedEvent ProgramExecutedCallBack;

		PXSize ParameterListSize;
		char** ParameterList;

		PXThread WorkingThread;
		PXSize ReturnValue;
		unsigned char ExecutionSuccessfull;
	}
	Program;

	PXPublic PXThreadResult  ProgramExecuteThreadFunction(void* data);

	PXPrivate PXActionResult ProgramExecute(Program* const program);

	// Execute function Asyncroinusly in another Thread.
	PXPublic PXActionResult ProgramExecuteAS(Program* program, const char* programPath, const char* parameterString, ProgramExecutedEvent* callback);
	PXPublic PXActionResult ProgramExecuteAL(Program* program, const char* programPath, const char** parameterList, PXSize parameterListSize, ProgramExecutedEvent* callback);

	PXPublic PXActionResult ProgramExecuteWS(Program* program, const wchar_t* programPath, const wchar_t* parameterList, ProgramExecutedEvent* callback);


	PXPublic ProcessHandle ProgramCurrentProcess();
	PXPublic ProcessID ProgramCurrentProcessID();

	PXPublic void ProgramAttach(Program* program);
	PXPublic void ProgramDetach(Program* program);
	PXPublic void ProgramReadMemory(Program* program);

#ifdef __cplusplus
}
#endif

#endif
