//-----------------------------------------------------------------------------
//#include "../../ResourceSystem/Source/Network/Client.h"

#include "../../BitFireEngine/Source/System/BitFireEngine.h"
#include "../../SystemResource/Source/OSDefine.h"
#include <stdio.h>
#include "CleavedGameSystem.h"
#include <signal.h>
//-----------------------------------------------------------------------------

void CallBackErrorOnError(int errorID)
{
    printf("\n\nKilled Process!\n\n");
}

#if !defined(_DEBUG) && defined(OSWindowsE)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif  
{
    //---<Error Callback>-----
    auto functionPointer = signal(SIGABRT, CallBackErrorOnError);
    bool validLinkage = functionPointer != SIG_ERR;

    if (!validLinkage)
    {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        return EXIT_FAILURE;
    }
    //---------------------------

    try
    {
        //printf("[i][Core] Working Directory <%s>\n", parameter[0]);

        Cleaved::CleavedGameSystem cleavedGameSystem;       

        cleavedGameSystem.GameSystem.Start();

        while (cleavedGameSystem.GameSystem.IsRunning)
        {
            cleavedGameSystem.GameSystem.Update();
        }

        cleavedGameSystem.GameSystem.Stop();
    }
    catch (const std::exception& exception)
    {
        printf("[x][Core] System colapsed. Reason : \n%s", exception.what());
        return 1;
    }

    return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------