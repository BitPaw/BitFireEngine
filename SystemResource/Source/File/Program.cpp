#include "Program.h"
#include "../OSDefine.h"
#include "../ErrorCode.h"

#include <stdio.h>
#include <thread>

#if defined(OSUnix)
#include <unistd.h>
#define ExecuteProgram spawnl
#elif defined(OSWindows)
#include <Windows.h>
#include <process.h>
#define ExecuteProgram _spawnl
#endif

BF::FileActionResult BF::Program::Execute(const char* programPath, const char* parameterList, ProgramExecuteResultListener* callback)
{
    if (callback)
    {
        std::thread* modelLoaderThread = new std::thread([](const char* programPath, const char* parameterList, ProgramExecuteResultListener* callback)
        {
            size_t programReturnresult = ExecuteProgram(_P_WAIT, programPath, programPath, parameterList);
            bool programExecutionSuccesfull = programReturnresult >= 0;
            ErrorCode errorCode = ErrorCode::Successful;

            if (!programExecutionSuccesfull)
            {
                errorCode = GetCurrentError();
            }     

            callback->OnProgramExecuted(programExecutionSuccesfull, programReturnresult, errorCode);

        }, programPath, parameterList, callback);
    }
    else
    {
        size_t programReturnresult = ExecuteProgram(_P_WAIT, programPath, programPath, parameterList);
        bool programExecutionSuccesfull = programReturnresult != -1;
        ErrorCode errorCode = ErrorCode::UnkownError;

        if (!programExecutionSuccesfull)
        {
            errorCode = GetCurrentError();
        }

        printf("[Extrenal Program] <%s> returned with <%i>.\n", programPath, programReturnresult);
    }   

    return FileActionResult::Successful;
}

BF::FileActionResult BF::Program::Execute(const wchar_t* programPath, const char* parameterList, ProgramExecuteResultListener* callback)
{
    return FileActionResult::Successful;
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
