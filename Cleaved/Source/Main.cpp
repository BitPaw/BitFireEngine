//-----------------------------------------------------------------------------
#include "../../BitFireEngine/Source/System/GameSystem.h"
#include "../../ResourceSystem/Source/OSDefine.h"
#include <stdio.h>
#include <windows.h>
//-----------------------------------------------------------------------------

#if !defined(_DEBUG) && defined(OSWindows)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif  
{
    try
    {
        // printf("[i][Core] Working Directory <%s>\n", parameter[0]);

        BF::GameSystem system;

        system.Start();

        while (system.IsRunning())
        {
            system.Update();
        }

        system.Stop();
    }
    catch (const std::exception& exception)
    {
        printf("[x][Core] System colapsed. Reason : \n%s", exception.what());
        return 1;
    }

    return 0;
}
//-----------------------------------------------------------------------------