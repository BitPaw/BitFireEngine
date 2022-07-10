#include "Memory.h"

#include <OS/OSDefine.h>

#if defined(OSUnix)
#include <sys/stat.h>
#include <fcntl.h>
#elif defined(WindowsAtleastXP)
#include <Windows.h>
#endif

#include <Text/Text.h>
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

void* BF::Memory::VirtualMemoryAllocate(const size_t size, const MemoryProtectionMode memoryProtectionMode)
{
	const void* addressPrefered = nullptr;
	const MemoryProtectionModeType protectionModeID = ConvertMemoryProtectionMode(memoryProtectionMode);

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

        if (!sucessful)
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

bool BF::Memory::Advise(const void* adress, const size_t length, const FileCachingMode fileCachingMode)
{
	const int cachingModeID = ConvertFileCachingMode(fileCachingMode);

#if defined(OSUnix)
	const int result = madvise((void*)adress, length, cachingModeID);
	const ErrorCode errorCode = ConvertErrorCode(result);
	const bool successful = errorCode == ErrorCode::Successful;

	return successful;

#elif defined(OSWindows)
	return true;
#endif
}

void BF::Memory::Release(void* adress, const size_t size)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Free\n", adress, size);
#endif

	free(adress);
}

void BF::Memory::Set(void* target, const unsigned char value, const size_t size)
{
	assert(target);

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Set with %x\n", target, size, value);
#endif    

#if MemoryUseSystemCalls
	memset(target, value, size);
#else
	for(size_t i = 0; i < size; ++i)
	{
		((unsigned char*)target)[i] = value;
	}
#endif
}

void BF::Memory::Copy(void* target, const void* source, const size_t size)
{
	assert(target);
	assert(source);

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Copy from 0x%p\n", target, size, source);
#endif

#if MemoryUseSystemCalls
	memcpy(target, source, size);
#else
	for(size_t i = 0; i < size; ++i)
	{
		((unsigned char*)target)[i] = ((unsigned char*)source)[i];
	}
#endif
}