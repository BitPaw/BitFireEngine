//-----------------------------------------------------------------------------
#include "../../BitFireEngine/Source/System/GameSystem.h"
#include <stdio.h>
//-----------------------------------------------------------------------------
int main(int amountOFParameters, char** parameter)
{   
    try
    {
        FileOpen();

        printf("[i][Core] Working Directory <%s>\n", parameter[0]);

        BF::GameSystem system;

        system.Start();

        FileClose();

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