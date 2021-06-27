//-----------------------------------------------------------------------------
#include "../../BitFireEngine/Source/System/GameSystem.h"
#if 0
unsigned long long allocatedSpace = 0;

void* operator new(unsigned int sizeOfDataBlock)
{
    void* newAdress = malloc(sizeOfDataBlock);

    allocatedSpace += sizeOfDataBlock;

    printf(">>> [New] Allocated <%p> [%4u Byte] - %lu\n", newAdress, sizeOfDataBlock, allocatedSpace);

    return newAdress;
}

void operator delete(void* adressToDelete)
{
    printf(">>> [Delete] Removed <%p>\n", adressToDelete);
    free(adressToDelete);
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