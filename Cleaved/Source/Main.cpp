//-----------------------------------------------------------------------------
#include "../../BitFireEngine/Source/System/GameSystem.h"
#include <stdio.h>
//-----------------------------------------------------------------------------
int main(int amountOFParameters, char** parameter)
{   
    FileOpen();

    printf("Working Directory <%s>\n", parameter[0]);

    BF::GameSystem system;

    system.Start();

    FileClose();

    while (system.IsRunning())
    {
        system.Update();
    }

    system.Stop();

    return 0;
    
}
//-----------------------------------------------------------------------------