#include "Memory.h"

#include <Math/Math.h>

#include <stdlib.h>
#include <malloc.h>

#if defined(OSUnix)

#include <sys/mman.h>

#define ProtectionIDRead PROT_READ
#define ProtectionIDWrite PROT_WRITE
#define ProtectionIDReadWrite PROT_READ | PROT_WRITE

#elif defined(OSWindows)

#include <Windows.h>

#define ProtectionIDRead PAGE_READONLY
#define ProtectionIDWrite PAGE_READWRITE
#define ProtectionIDReadWrite PAGE_READWRITE

#endif

#include "Math.h"

#define MemoryAssertEnable 1
#define MemoryDebug 0
#define MemoryUseSystemFunction 0
#define MemorySanitise 1


#if MemoryAssertEnable
#include <assert.h>
#endif 

void MemorySet(void* __restrict bufferA, const size_t bufferASize, const unsigned char value)
{
//#if MemoryAssertEnable
//	assert(bufferA);
//#endif 

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Set to %2x\n", bufferA, length, value);
#endif

	if(!bufferA)
	{
		return;
	}

#if MemoryUseSystemFunction
	memset(bufferA, value, bufferASize);
#else
	for(size_t i = 0; i < bufferASize; ++i)
	{
		((unsigned char*)bufferA)[i] = value;
	}
#endif
}

unsigned char MemoryCompare(const void* __restrict bufferA, const size_t bufferASize, const void* __restrict bufferB, const size_t bufferBSize)
{
#if MemoryAssertEnable
	assert(bufferA);
	assert(bufferB);
#endif 

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Compare to 0x%p\n", a, length, b);
#endif

#if MemoryUseSystemFunction
	return memcmp(a, b, length) == 0;
#else

	const size_t bufferSize = MathMinimum(bufferASize, bufferBSize);
	size_t counter = bufferSize;
	size_t equalSum = 0;

	while(counter--)
	{
		equalSum += ((unsigned char*)bufferA)[counter] == ((unsigned char*)bufferB)[counter];
	}

	return equalSum == bufferSize;
#endif
}

size_t MemoryCopy(const void* __restrict inputBuffer, const size_t inputBufferSize, void* outputBuffer, const size_t outputBufferSize)
{
#if MemoryAssertEnable
	assert(inputBuffer);
	assert(outputBuffer);
#endif 

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Copy to 0x%p\n", bufferA, bufferSize, bufferB);
#endif

	const size_t bufferSize = MathMinimum(inputBufferSize, outputBufferSize);
	size_t index = bufferSize;

	while(index--)
	{
		const unsigned char* inputByte = ((unsigned char*)inputBuffer) + index;
		unsigned char* outputByte = ((unsigned char*)outputBuffer) + index;

		*outputByte = *inputByte;
	}	

	return bufferSize;
}

void* MemoryAllocate(const size_t size)
{
	if(!size)
	{
		return 0;
	}

	const void* adress = malloc(size);

#if MemorySanitise
	MemorySet(adress, size, '#');
#endif

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Allocate\n", adress, requestedBytes);
#endif

	return adress;
}

void* MemoryReallocate(void* adress, const size_t size)
{
	const void* adressReallocated = realloc(adress, size);

#if MemoryDebug
	const unsigned char hasChanged = adress != adressReallocated;

	if(hasChanged)
	{
		printf("[#][Memory] 0x%p (%10zi B) Reallocate to 0x%p\n", adress, requestedBytes, adressReallocated);
	}
	else
	{
		printf("[#][Memory] 0x%p (%10zi B) Reallocate (No Change)\n", adress, requestedBytes);
	}
#endif

	return adressReallocated;
}

void MemoryRelease(const void* adress, const size_t size)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Free\n", adress, size);
#endif

#if MemorySanitise
	MemorySet(adress, size, '#');
#endif

	free(adress);
}

void* MemoryVirtualAllocate(const size_t size, const MemoryProtectionMode memoryProtectionMode)
{
	const void* addressPrefered = 0;
	const MemoryProtectionModeType protectionModeID = ConvertFromMemoryProtectionMode(memoryProtectionMode);

#if defined(OSUnix)
	const int flags = MAP_PRIVATE | MAP_POPULATE | MAP_ANONYMOUS;
	const int fileDescriptor = -1;
	const off_t offset = 0;

	const void* addressAllocated = mmap
	(
		(void*)addressPrefered,
		size,
		protectionModeID,
		flags,
		fileDescriptor,
		offset
	);

	// Check if mmap was sucessful
	{
		const bool sucessful = addressAllocated != MAP_FAILED;

		if(!sucessful)
		{
			return nullptr;
		}
	}

#elif defined(OSWindows)
	DWORD allocationType = MEM_COMMIT | MEM_RESERVE;

	const void* addressAllocated = VirtualAlloc((void*)addressPrefered, size, allocationType, protectionModeID);
#endif

#if MemoryDebug
	const char* readMode;

	switch(memoryProtectionMode)
	{
		case MemoryProtectionMode::WriteOnly:
			readMode = "Write only";
			break;

		case MemoryProtectionMode::ReadOnly:
			readMode = "Read only";
			break;

		case MemoryProtectionMode::ReadAndWrite:
			readMode = "Read & Write";
			break;

		default:
			readMode = "???";
			break;
	}

	printf("[#][Memory] 0x%p (%10zi B) Virtual allocation [%s]\n", addressAllocated, size, readMode);
#endif

	return (void*)addressAllocated;
}

void MemoryVirtualPrefetch(const void* adress, const size_t size)
{
#if defined(OSUnix)
#elif defined(OSWindows)
#if defined(WindowsAtleast8)
	const HANDLE process = GetCurrentProcess();
	const size_t numberOfEntries = 2;
	WIN32_MEMORY_RANGE_ENTRY memoryRangeEntry;
	const size_t flags = 0; // reserved and needs to be 0

	memoryRangeEntry.VirtualAddress = (void*)adress;
	memoryRangeEntry.NumberOfBytes = size;

	//const bool prefetchResult = PrefetchVirtualMemory(process, numberOfEntries, &memoryRangeEntry, flags);

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Pre-Fetched\n", adress, size);
#endif

#endif // defined(WindowsAtleast8)
#else

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Pre-Fetched [NOT SUPPORTED] Skipped...\n", adress, size);
#endif
#endif
}

void MemoryVirtualRelease(const void* adress, const size_t size)
{
#if defined(OSUnix)
	const bool result = true;

#elif defined(OSWindows)
	DWORD freeType = MEM_RELEASE;
	const unsigned char result = VirtualFree((void*)adress, 0, freeType);
#endif

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Virtual free\n", adress, size);
#endif

	return result;
}

MemoryProtectionModeType ConvertFromMemoryProtectionMode(const MemoryProtectionMode memoryProtectionMode)
{
	switch(memoryProtectionMode)
	{
		case MemoryReadOnly:
			return ProtectionIDRead;

		case MemoryWriteOnly: 
			return ProtectionIDWrite;

		case MemoryReadAndWrite: 
			return ProtectionIDReadWrite;

		default:
			return MemoryInvalid;
	}
}