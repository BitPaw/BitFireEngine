#include <stdio.h>
#include <malloc.h>

#define EnableAllocationLogging 0

#if EnableAllocationLogging
unsigned int spaceAllocatedWholeInBytes = 0;
unsigned int spaceAllocationsWhole = 0;
unsigned int spaceAllocationsCurrent = 0;

void* operator new(unsigned int sizeOfDataBlock)
{
    void* newAdress = malloc(sizeOfDataBlock);

    spaceAllocatedWholeInBytes += sizeOfDataBlock;
    spaceAllocationsWhole++;
    spaceAllocationsCurrent++;

    printf(">>> [+] <%p> [%6u B] - (Current: %6i Total:%6i)\n", newAdress, sizeOfDataBlock, spaceAllocationsCurrent, spaceAllocatedWholeInBytes);

    return newAdress;
}

void operator delete(void* adressToDelete)
{
    printf(">>> [-] <%p>\n", adressToDelete);
  
    spaceAllocationsCurrent--;

    free(adressToDelete);
}
#endif 