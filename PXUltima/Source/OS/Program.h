#ifndef ExecutableInclude
#define ExecutableInclude

#include <OS/OSVersion.h>

#include <stddef.h>
#include <Error/ActionResult.h>
#include <Async/Thread.h>

#if defined(OSUnix)
#include <unistd.h>
#define ProcessHandle pid_t
#define ProcessID unsigned int
#elif defined(OSWindows)
#include <windows.h>
#define ProcessHandle HANDLE
#define ProcessID DWORD
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	typedef void (*ProgramExecutedEvent)(const unsigned char succesful, size_t returnResult, const ActionResult errorCode);

	typedef struct Program_
	{
		ProcessHandle Handle;

		wchar_t FilePath[260];

		ProgramExecutedEvent ProgramExecutedCallBack;

		size_t ParameterListSize;
		char** ParameterList;

		ThreadID WorkingThread;
		size_t ReturnValue;
		unsigned char ExecutionSuccessfull;
	}
	Program;

	extern ThreadResult  ProgramExecuteThreadFunction(void* data);

	// Execute function Asyncroinusly in another Thread.
	extern ActionResult ProgramExecuteAS(Program* program, const char* programPath, const char* parameterString, ProgramExecutedEvent* callback);
	extern ActionResult ProgramExecuteAL(Program* program, const char* programPath, const char** parameterList, size_t parameterListSize, ProgramExecutedEvent* callback);

	extern ActionResult ProgramExecuteWS(Program* program, const wchar_t* programPath, const wchar_t* parameterList, ProgramExecutedEvent* callback);


	extern ProcessHandle ProgramCurrentProcess();
	extern ProcessID ProgramCurrentProcessID();

	extern void ProgramAttach(Program* program);
	extern void ProgramDetach(Program* program);
	extern void ProgramReadMemory(Program* program);

#ifdef __cplusplus
}
#endif

#endif
