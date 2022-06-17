#include "Memory.h"

#include <OS/OSDefine.h>
#include <Text/Text.h>

#if defined(OSUnix)
#include <sys/stat.h>
#include <fcntl.h>
#elif defined(WindowsAtleastXP)
#include <Windows.h>
#endif

#include <ErrorCode.h>
#include <ClipBoard/ClipBoard.cpp>
#include <File/File.h>


void* operator new(const size_t size)
{
	void* adress = malloc(size);

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Allocate (new)\n", adress, size);
#endif

	return adress;
}

/*
void* operator new[](const size_t size)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Compare to 0x%p\n", a, length, b);
#endif
}*/

void operator delete(void* adress)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p free (delete)\n", adress);
#endif

	free(adress);
}

/*
void operator delete[](void* adress)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Compare to 0x%p\n", a, length, b);
#endif
}*/


bool BF::Memory::Scan(MemoryUsage& memoryUsage)
{
#if defined(OSUnix)
#elif defined(WindowsAtleastXP)
	// MEMORYSTATUS won't work on >4GB Systems

	MEMORYSTATUSEX memoryStatus{ 0 };
	memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);

	bool result = GlobalMemoryStatusEx(&memoryStatus);

	if (result)
	{
		memoryUsage.PercentInUse = memoryStatus.dwMemoryLoad;
		memoryUsage.PhysicalTotal = memoryStatus.ullTotalPhys;
		memoryUsage.PhysicalAvailable = memoryStatus.ullAvailPhys;
		memoryUsage.PageFileTotal = memoryStatus.ullTotalPageFile;
		memoryUsage.PageFileAvailable = memoryStatus.ullAvailPageFile;
		memoryUsage.VirtualTotal = memoryStatus.ullTotalVirtual;
		memoryUsage.VirtualAvailable = memoryStatus.ullAvailVirtual;
		memoryUsage.ExtendedVirtualAvailable = memoryStatus.ullAvailExtendedVirtual;
	}

	return result;
#endif
}

int BF::Memory::Compare(const void* a, const void* b, const size_t length)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Compare to 0x%p\n", a, length, b);
#endif

	return memcmp(a, b, length);
}

bool BF::Memory::VirtualMemoryPrefetch(const void* adress, const size_t size)
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

	return false;
}

void* BF::Memory::VirtualMemoryAllocate(const size_t size)
{
	void* address = nullptr;

#if defined(OSUnix)

#elif defined(OSWindows)
	DWORD allocationType = MEM_COMMIT | MEM_RESERVE;
	DWORD protect = PAGE_READWRITE;

	address = VirtualAlloc(address, size, allocationType, protect);
#endif

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Virtual allocation\n", address, size);
#endif

	return address;
}

bool BF::Memory::VirtualMemoryRelease(const void* adress, const size_t size)
{
#if defined(OSUnix)
	const bool result = true;

#elif defined(OSWindows)
	DWORD freeType = MEM_RELEASE;
	const bool result = VirtualFree((void*)adress, 0, freeType);
#endif

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Virtual free\n", adress, size);
#endif

	return result;
}
