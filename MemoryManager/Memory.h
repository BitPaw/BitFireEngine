#pragma once

#ifndef MemoryManager
#define MemoryManager

#define EnableAllocationLogging 0

#include <stdio.h>

static const char* filePath = "BitFireEngine - AllocationDump.txt";
static unsigned int spaceAllocatedWholeInBytes = 0;
static unsigned int spaceAllocationsWhole = 0;
static unsigned int spaceAllocationsCurrent = 0;

static unsigned int counterMemAllocation = 0;
static unsigned int counterMemDeAllocation = 0;
static unsigned int counterMemResize = 0;
static unsigned int counterMemCopy = 0;
static unsigned int counterMemSet = 0;

static FILE* file;

void EnableDebug();
void SetDebugOption(unsigned char option, bool enable);

void FileOpen();
void PushToFile(char* buffer, int length);
void FileClose();

void* MemoryAllocate(unsigned int sizeOfBlock); // malloc
void* MemoryAllocateCleared(unsigned int amountOfObjects, unsigned int sizeOfElement); // malloc
void MemoryRelease(void* adress); // free
void* MemoryResize(void* currentAdress, unsigned int newSize);
void MemoryCopy(void* destination, void* source, unsigned int length); // memCopy
void MemorySet(void* adress, char value, unsigned int length);


//void* operator new(size_t sizeOfDataBlock);
//void operator delete(void* adressToDelete);

#endif // !MemoryManager