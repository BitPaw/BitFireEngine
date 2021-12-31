#include "Program.h"
#include "../OSDefine.h"
#include "../ErrorCode.h"

#include <stdio.h>
#include <thread>

#if defined(OSUnix)
#include <unistd.h>
#define ExecuteProgram spawnv
#elif defined(OSWindows)
#include <windows.h>
#include <process.h>
#define ExecuteProgram _spawnv
#endif

#include "ProgramExecuteInfo.h"

ThreadFunctionReturnType BF::Program::ExecuteThreadFunction(void* data)
{
    ProgramExecuteInfo* info = (ProgramExecuteInfo*)data;

    intptr_t programReturnresult = ExecuteProgram(_P_WAIT, info->FilePath, (const char* const*)info->ParameterList);
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

BF::FileActionResult BF::Program::Execute(const char* programPath, const char* parameterString, ProgramExecuteResultListener* callback)
{
    ProgramExecuteInfo* programExecuteInfo = new ProgramExecuteInfo();
    strncpy_s(programExecuteInfo->FilePath, programPath, 260);   

    programExecuteInfo->ParameterListSize = 1;
    programExecuteInfo->ParameterList = (char**)malloc(3 * sizeof(char*));

    programExecuteInfo->ParameterList[0] = (char*)malloc(260 * sizeof(char));
    programExecuteInfo->ParameterList[1] = (char*)malloc(1024 * sizeof(char));
    programExecuteInfo->ParameterList[2] = nullptr;

    sprintf_s(programExecuteInfo->ParameterList[0], 260,"\"%s\"", programPath);
    strncpy_s(programExecuteInfo->ParameterList[1], 1024, parameterString, 1024);

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

BF::FileActionResult BF::Program::Execute(const char* programPath, const char** parameterList, size_t parameterListSize, ProgramExecuteResultListener* callback)
{
    ProgramExecuteInfo* programExecuteInfo = new ProgramExecuteInfo();

    const size_t paramaterMaxLength = 260;

    strncpy_s(programExecuteInfo->FilePath, programPath, paramaterMaxLength);
    

    programExecuteInfo->ParameterListSize = parameterListSize+1;
    programExecuteInfo->ParameterList = (char**)malloc(programExecuteInfo->ParameterListSize +1 * sizeof(char*));
    //memset(programExecuteInfo->ParameterList, '#', programExecuteInfo->ParameterListSize + 1);

    for (size_t i = 0; i < programExecuteInfo->ParameterListSize; i++)
    {
        char* newData = (char*)malloc(paramaterMaxLength);

        programExecuteInfo->ParameterList[i] = newData;

        memset(newData, '#', paramaterMaxLength);
    }

    size_t infoIndex = 0;

    strncpy_s(programExecuteInfo->ParameterList[infoIndex++], paramaterMaxLength, programPath, paramaterMaxLength);

    for (size_t i = 0; i < parameterListSize; i++)
    {        
        const char* source = parameterList[i];
        char* destination = programExecuteInfo->ParameterList[infoIndex++];

        strncpy_s(destination, paramaterMaxLength, source, paramaterMaxLength);
    }

    programExecuteInfo->ParameterList[infoIndex++] = nullptr;

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

  //  return Program::Execute(programPathA, parameterListA, callback);

    return FileActionResult::FormatNotSupported;
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
