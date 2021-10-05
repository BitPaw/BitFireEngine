//-----------------------------------------------------------------------------
#include "../../BitFireEngine/Source/System/BitFireEngine.h"
#include "../../SystemResource/Source/OSDefine.h"
#include <stdio.h>
#include <exception>
#include "ZEEGameSystem.h"
//-----------------------------------------------------------------------------

#if !defined(_DEBUG) && defined(OSWindows5)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif  
{
    printf("[i][Core] Working Directory : %s\n", parameter[0]);

    try
    {
        //printf("[i][Core] Working Directory <%s>\n", parameter[0]);

        ZEE::ZEEGameSystem zeeGameSystem;

        zeeGameSystem.GameSystem.Start();

        while (zeeGameSystem.GameSystem.IsRunning)
        {
            zeeGameSystem.GameSystem.Update();
        }

        zeeGameSystem.GameSystem.Stop();
    }
    catch (const std::exception& exception)
    {
        printf("[x][Core] System colapsed. Reason : \n%s", exception.what());
        return 1;
    }

    return 0;
}
//-----------------------------------------------------------------------------