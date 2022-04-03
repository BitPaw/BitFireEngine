#include "Program.h"

#include <OS/OSDefine.h>
#include <ErrorCode.h>

#include <stdio.h>
#include <thread>

#if defined(OSUnix)
#include <unistd.h>
#include <spawn.h>
#include <wait.h>
#define ExecuteProgram spawnv
#elif defined(OSWindows)
#include <windows.h>
#include <process.h>
#define ExecuteProgram _spawnv
#endif

#include <cstring>

#include "ProgramExecuteInfo.h"

ThreadFunctionReturnType BF::Program::ExecuteThreadFunction(void* data)
{
    ProgramExecuteInfo* info = (ProgramExecuteInfo*)data;
    int programReturnresult = 0;
    bool programExecutionSuccesfull = 0;
    ErrorCode errorCode = ErrorCode::Successful;


    #if defined(OSUnix)
    pid_t pID = 0;
    char** envirument = 0;
    int creationResult = posix_spawn(&pID,  info->FilePath, NULL, NULL, info->ParameterList,envirument);
    bool creationSucessful = creationResult == 0;


    if (creationSucessful)
    {
       pid_t resultProcessID = waitpid(pID, &programReturnresult, 0);
        bool exxecutionSuessful = resultProcessID != -1;

        programExecutionSuccesfull =exxecutionSuessful && programReturnresult == 0;
    }
    
    
    #elif defined(OSWindows)
        intptr_t programReturnresultP = ExecuteProgram(_P_WAIT, info->FilePath, (const char* const*)info->ParameterList);
        programReturnresult = (int)programReturnresultP;
   
         programExecutionSuccesfull = programReturnresult == 0;
    #endif

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
    strncpy(programExecuteInfo->FilePath, programPath, 260);   

    programExecuteInfo->ParameterListSize = 1;
    programExecuteInfo->ParameterList = (char**)malloc(3 * sizeof(char*));

    programExecuteInfo->ParameterList[0] = (char*)malloc(260 * sizeof(char));
    programExecuteInfo->ParameterList[1] = (char*)malloc(1024 * sizeof(char));
    programExecuteInfo->ParameterList[2] = nullptr;

    sprintf(programExecuteInfo->ParameterList[0], "\"%s\"", programPath);
    strncpy(programExecuteInfo->ParameterList[1], parameterString, 1024);

    if (callback)
    {          
        programExecuteInfo->CallBack = callback;    

        ThreadID threadID = Thread::Run(Program::ExecuteThreadFunction, programExecuteInfo);
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

    strncpy(programExecuteInfo->FilePath, programPath, paramaterMaxLength);
    

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

    strncpy(programExecuteInfo->ParameterList[infoIndex++], programPath, paramaterMaxLength);

    for (size_t i = 0; i < parameterListSize; i++)
    {        
        const char* source = parameterList[i];
        char* destination = programExecuteInfo->ParameterList[infoIndex++];

        strncpy(destination, source, paramaterMaxLength);
    }

    programExecuteInfo->ParameterList[infoIndex++] = nullptr;

    if (callback)
    {
        programExecuteInfo->CallBack = callback;

        ThreadID threadID = Thread::Run(Program::ExecuteThreadFunction, programExecuteInfo);
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
        #if defined(OSUnix)
        return 0;
    #elif defined(OSWindows)
    return GetCurrentProcess();
        #endif
}

size_t BF::Program::CurrentProcessID()
{
        #if defined(OSUnix)
                return 0;
    #elif defined(OSWindows)
    return GetCurrentProcessId();
        #endif
}

void BF::Program::Attach()
{
    #if defined(OSUnix)
    #elif defined(OSWindows)
     DWORD dwDesiredAccess = 0;
    BOOL bInheritHandle = 0;
    DWORD dwProcessID = 0;
    HANDLE handleID = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessID);
    #endif
   
}

void BF::Program::Detach()
{
    #if defined(OSUnix)
    #elif defined(OSWindows)

    HANDLE handleID = 0;

    CloseHandle(handleID);
    #endif

}

void BF::Program::ReadMemory()
{
  #if defined(OSUnix)
    #elif defined(OSWindows)
    HANDLE hProcess = 0;
    LPCVOID lpBaseAddress = 0;
    LPVOID* lpBuffer = 0;
    SIZE_T nSize = 0;
    SIZE_T* lpNumberOfBytesRead = 0;

    bool successful = ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
    #endif


}
