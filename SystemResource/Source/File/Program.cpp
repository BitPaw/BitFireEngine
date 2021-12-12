#include "Program.h"
#include "../OSDefine.h"
#include "../ErrorCode.h"

#include <stdio.h>
#include <thread>

#if defined(OSUnix)
#include <unistd.h>
#define ExecuteProgram spawnl
#elif defined(OSWindows)
#include <windows.h>
#include <process.h>
#define ExecuteProgram _spawnl
#endif

#include "ProgramExecuteInfo.h"

ThreadFunctionReturnType BF::Program::ExecuteThreadFunction(void* data)
{
    ProgramExecuteInfo* info = (ProgramExecuteInfo*)data;

    intptr_t programReturnresult = ExecuteProgram(_P_WAIT, info->FilePath, info->FilePath, info->ParameterList, nullptr);
    bool programExecutionSuccesfull = programReturnresult == 0;
    ErrorCode errorCode = ErrorCode::Successful;

    if (!programExecutionSuccesfull)
    {
        errorCode = GetCurrentError();
    }

    if (info->CallBack)
    {
        info->CallBack->OnProgramExecuted(programExecutionSuccesfull, programReturnresult, errorCode);
    }

    delete info;
 
    return 0;
}

BF::FileActionResult BF::Program::Execute(const char* programPath, const char* parameterList, ProgramExecuteResultListener* callback)
{
    ProgramExecuteInfo* programExecuteInfo = new ProgramExecuteInfo();

    strncpy_s(programExecuteInfo->FilePath, programPath, 260);
    strncpy_s(programExecuteInfo->ParameterList, parameterList, 1024);

    if (callback)
    {       
        ThreadID threadID;

        programExecuteInfo->CallBack = callback;    

        Thread::Run(threadID, Program::ExecuteThreadFunction, programExecuteInfo);
    }
    else
    {
        Program::ExecuteThreadFunction(programExecuteInfo);
    }   

    return FileActionResult::Successful;
}

BF::FileActionResult BF::Program::Execute(const wchar_t* programPath, const wchar_t* parameterList, ProgramExecuteResultListener* callback)
{
    char programPathA[1024];
    char parameterListA[1024];

    wcstombs(programPathA, programPath, 1024);
    wcstombs(parameterListA, parameterList, 1024);

    return Program::Execute(programPathA, parameterListA, callback);
}

void* BF::Program::CurrentProcess()
{
    return GetCurrentProcess();
}

size_t BF::Program::CurrentProcessID()
{
    return GetCurrentProcessId();
}

void BF::Program::Attach()
{
    DWORD dwDesiredAccess = 0;
    BOOL bInheritHandle = 0;
    DWORD dwProcessID = 0;
    HANDLE handleID = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessID);
}

void BF::Program::Detach()
{
    HANDLE handleID = 0;

    CloseHandle(handleID);
}

void BF::Program::ReadMemory()
{
    HANDLE hProcess = 0;
    LPCVOID lpBaseAddress = 0;
    LPVOID* lpBuffer = 0;
    SIZE_T nSize = 0;
    SIZE_T* lpNumberOfBytesRead = 0;

    bool successful = ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}
