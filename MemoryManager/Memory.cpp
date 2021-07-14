#include "Memory.h"

#include <stdio.h>
#include <malloc.h>
#include <crtdbg.h>
#include <string>

void SetDebugOption(unsigned char option, bool enable)
{
    int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

    if (enable)
    {
        tmpFlag |= option;
    }
    else
    {
        tmpFlag &= ~option;
    }

    _CrtSetDbgFlag(tmpFlag);
}


void FileOpen()
{
#ifdef _DEBUG
    file = fopen(filePath, "w");
#endif
}

void PushToFile(char* buffer, int length)
{ 
#ifdef _DEBUG
    fwrite(buffer, 1, length, file);

    //printf("%s", buffer);    
#endif
}

void FileClose()
{
#ifdef _DEBUG
    char buffer[200];
    
    int amount = sprintf
    (
        buffer,
        "\n\n\n"
        "Memory Allocations   : %i\n"
        "Memory DeAllocations : %i\n"
        "Memory Realloc       : %i\n"
        "Memory Copy          : %i\n",
        "Memory Set           : %i\n",
        counterMemAllocation,
        counterMemDeAllocation,
        counterMemResize,
        counterMemCopy,
        counterMemSet
    );

    PushToFile(buffer, amount);

    fclose(file);
#endif
}


void EnableDebug()
{
    SetDebugOption(_CRTDBG_ALLOC_MEM_DF, true); // Turn on debug allocation
    SetDebugOption(_CRTDBG_DELAY_FREE_MEM_DF, true); // Don't actually free memory
    //SetDebugOption(_CRTDBG_CHECK_ALWAYS_DF, true); // Check heap every alloc/dealloc
    //SetDebugOption(_CRTDBG_RESERVED_DF, true); // Reserved - do not use
    SetDebugOption(_CRTDBG_CHECK_CRT_DF, true); // Leak check/diff CRT blocks
    SetDebugOption(_CRTDBG_LEAK_CHECK_DF, true); // Leak check at program exit
}





void* MemoryAllocate(unsigned int sizeOfBlock)
{
    void* newBlock = malloc(sizeOfBlock);

#ifdef _DEBUG
    spaceAllocatedWholeInBytes += sizeOfBlock;
    spaceAllocationsWhole++;
    spaceAllocationsCurrent++;
    
    counterMemAllocation++;

    char buffer[100];
    int amountOfChars = sprintf(buffer, "[MALOC] <%p> Allocation (%i Bytes)\n", newBlock, sizeOfBlock);

    PushToFile(buffer, amountOfChars);
#endif

    return newBlock;
}

void* MemoryAllocateCleared(unsigned int amountOfObjects, unsigned int sizeOfElement)
{
    void* newBlock = calloc(amountOfObjects, sizeOfElement);
    
#ifdef _DEBUG
    char buffer[100];
    int amountOfChars = sprintf(buffer, "[CALOC] <%p> Cleared Allocate x%i (%i Bytes)\n", newBlock, amountOfObjects, amountOfObjects * sizeOfElement);

    PushToFile(buffer, amountOfChars);
#endif

    return newBlock;
}

void MemoryRelease(void* adress)
{
#ifdef _DEBUG
    char buffer[100];
    int amountOfChars = sprintf(buffer, "[DELOC] <%p>\n", adress);

    PushToFile(buffer, amountOfChars);

    counterMemDeAllocation++;

    spaceAllocationsCurrent--;
#endif

    free(adress);
}

void* MemoryResize(void* currentAdress, unsigned int newSize)
{
    if (currentAdress == nullptr)
    {
        return MemoryAllocate(newSize);
    }

    void* newAdress = realloc(currentAdress, newSize);

#ifdef _DEBUG
    bool hasChanged = currentAdress != newAdress;
    char buffer[100];
    int amountOfChars;

    counterMemResize++;

    if (hasChanged)
    {
        amountOfChars = sprintf(buffer, "[RELOC] <%p> reallocated (%i Bytes)\n", currentAdress, newSize);
    }
    else
    {
        amountOfChars = sprintf(buffer, "[RELOC] <%p> size expanded (%i Bytes) [No Allocation]\n", currentAdress, newSize);
    }

    PushToFile(buffer, amountOfChars);
#endif

    return newAdress;
}

void MemoryCopy(void* destination, void* source, unsigned int length)
{
#ifdef _DEBUG
    char buffer[100];
    int amountOfChars = sprintf(buffer, "[MCOPY] <%p> -> <%p> (%i Bytes)\n", destination, source, length);

    PushToFile(buffer, amountOfChars);
    
    counterMemCopy++;
#endif

    memcpy(destination, source, length);
}

void MemorySet(void* adress, char value, unsigned int length)
{
#ifdef _DEBUG
    char buffer[100];
    int amountOfChars = sprintf(buffer, "[MESET] <%p> set to <%i>(% i Bytes)\n", adress, value, length);

    PushToFile(buffer, amountOfChars);

    counterMemSet++;
#endif

    memset(adress, value, length);
}
/*

void* operator new(size_t sizeOfDataBlock)
{
    return MemoryAllocate(sizeOfDataBlock);
}

void operator delete(void* adressToDelete)
{
    MemoryRelease(adressToDelete);
}*/