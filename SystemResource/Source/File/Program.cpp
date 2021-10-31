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

BF::FileActionResult BF::Program::Execute(const char* programPath, const char* parameterList, ProgramExecuteResultListener* callback)
{
    if (callback)
    {
        std::thread* modelLoaderThread = new std::thread([](const char* programPath, const char* parameterList, ProgramExecuteResultListener* callback)
        {
            size_t programReturnresult = ExecuteProgram(_P_NOWAIT, programPath, programPath, parameterList);
            bool programExecutionSuccesfull = programReturnresult != -1;
            ErrorCode errorCode = ErrorCode::UnkownError;

            if (!programExecutionSuccesfull)
            {
                errorCode = ConvertErrorCode(errno);
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
            errorCode = ConvertErrorCode(errno);
        }

        printf("[Extrenal Program] <%s> returned with <%i>.\n", programPath, programReturnresult);
    }   

    return FileActionResult::Successful;
}

BF::FileActionResult BF::Program::Execute(const wchar_t* programPath, const char* parameterList, ProgramExecuteResultListener* callback)
{
    return FileActionResult::Successful;
}
