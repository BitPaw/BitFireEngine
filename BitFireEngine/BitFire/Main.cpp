//-----------------------------------------------------------------------------
#include "System/GameSystem.h"

#include <iostream>
#include <filesystem>

#if 0
void* operator new(size_t size)
{
    void* p = malloc(size);

    printf(">>> [NEW] Allocated <%p> %u Byte\n", p, size);

    return p;
}

void operator delete(void* p)
{
    printf(">>> [DELETE] Removed <%p>\n", p);
    free(p);
}
#endif 

//-----------------------------------------------------------------------------
int main()
{    
    BF::GameSystem& system = BF::GameSystem::Instance();
    
    system.Start();

    while (system.IsRunning())
    {
        system.Update();
    }

    system.Stop();
    
    return 0;
}
//-----------------------------------------------------------------------------