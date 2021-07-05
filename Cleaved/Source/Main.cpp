//-----------------------------------------------------------------------------
#include "../../BitFireEngine/Source/System/GameSystem.h"
#include <math.h>
//-----------------------------------------------------------------------------
int main(int amountOFParameters, char** parameter)
{   
    printf("Working Directory <%s>\n", parameter[0]);

    BF::GameSystem system;
   
    system.Start();

    while (system.IsRunning())
    {
        system.Update();
    }

    system.Stop();

    return 0;    
}
//-----------------------------------------------------------------------------