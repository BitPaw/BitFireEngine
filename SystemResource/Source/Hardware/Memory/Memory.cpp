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
	printf("[#][Memory] 0x%p (%10zi B) Virtual allocation\n", adress, size);
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

BF::FileActionResult BF::Memory::VirtualMemoryFileMap(const char* filePath, FileMappingInfo& fileMappingInfo)
{
#if defined(OSUnix)
    void* preferedAdress = nullptr;
    size_t length = 0;
    int memoryProtectionMode = PROT_READ;
    int flags = MAP_SHARED;
    int fileDiscriptor = open(filePath, O_RDONLY);
    __off64_t offset = 0;

    struct stat sb;
    fstat(fileDiscriptor, &sb); // FIleSize
    length = sb.st_size;

    void* mappedAdress = mmap64
    (
        preferedAdress,
        length,
        memoryProtectionMode,
        flags,
        fileDiscriptor,
        offset
    );

    fileMappingInfo.ID = fileDiscriptor;
    fileMappingInfo.Size = length;
    fileMappingInfo.Data = mappedAdress;

#elif defined(OSWindows)
#endif

	return FileActionResult::Successful;
}

BF::FileActionResult BF::Memory::VirtualMemoryFileMap(const wchar_t* filePath, FileMappingInfo& fileMappingInfo)
{
#if defined(OSUnix)
    char filePathA[PathMaxSize];

    Text::Copy(filePathA, filePath, PathMaxSize);

    return VirtualMemoryFileMap(filePathA, fileMappingInfo);

#elif defined(OSWindows)

	// Open file
	{
		const FileActionResult openResult = File::Open(fileMappingInfo.ID, filePath, FileOpenMode::Read, FileCachingMode::Sequential);
		const bool openSuccess = openResult == FileActionResult::Successful;

		if(!openSuccess)
		{
			return openResult; //openResult;
		}
	}

	{
		LARGE_INTEGER largeInt{0};

		const bool sizeResult = GetFileSizeEx(fileMappingInfo.ID, &largeInt);

		fileMappingInfo.Size = largeInt.QuadPart;
	}

	// Create mapping
	{
		SECURITY_ATTRIBUTES	fileMappingAttributes{ 0 };
		DWORD				flProtect = PAGE_READONLY;
		DWORD				dwMaximumSizeHigh = 0;
		DWORD				dwMaximumSizeLow = 0; // Problem if file is 0 Length
		wchar_t* name = nullptr;

		const HANDLE fileMappingHandleResult = CreateFileMappingW
		(
			fileMappingInfo.ID,
			nullptr,
			flProtect,
			dwMaximumSizeHigh,
			dwMaximumSizeLow,
			name
		);
		const bool successful = fileMappingHandleResult;

		if(!successful)
		{
			return FileActionResult::FileMemoryMappingFailed;
		}

		fileMappingInfo.IDMapping = fileMappingHandleResult;
	}

	{
		DWORD desiredAccess = FILE_MAP_READ;//  FILE_MAP_ALL_ACCESS; FILE_MAP_WRITE
		DWORD fileOffsetHigh = 0;
		DWORD fileOffsetLow = 0;
		size_t numberOfBytesToMap = 0;
		void* baseAddressTarget = nullptr;
		DWORD  numaNodePreferred = NUMA_NO_PREFERRED_NODE;

		void* fileMapped = MapViewOfFileExNuma
		(
			fileMappingInfo.IDMapping,
			desiredAccess,
			fileOffsetHigh,
			fileOffsetLow,
			numberOfBytesToMap,
			baseAddressTarget,
			numaNodePreferred
		);

		fileMappingInfo.Data = fileMapped;

		VirtualMemoryPrefetch(fileMapped, fileMappingInfo.Size);
	}
#endif

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP %ls\n", fileMappingInfo.Data, fileMappingInfo.Size, filePath);
#endif

	return FileActionResult::Successful;
}

bool BF::Memory::VirtualMemoryFileUnmap(FileMappingInfo& fileMappingInfo)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP-Release\n", fileMappingInfo.Data, fileMappingInfo.Size);
#endif

#if defined(OSUnix)
	const int result = munmap(fileMappingInfo.Data, fileMappingInfo.Size);
	const bool sucessful = result != -1;

	if(!sucessful)
	{
		const ErrorCode errorCode = GetCurrentError();

		return false;
	}

	fileMappingInfo.ID = 0;
	fileMappingInfo.Size = 0;
	fileMappingInfo.Data = 0;

	return true;

#elif defined(OSWindows)
{
		void* data = fileMappingInfo.Data;
		const bool unmappingSucessful = UnmapViewOfFile(data);

		if(!unmappingSucessful)
		{
			const ErrorCode error = GetCurrentError();

			return false;// FileActionResult::Invalid; // TODO: fix this
		}

		fileMappingInfo.Data = nullptr;
	}

	{
		const bool closeMappingSucessful = CloseHandle(fileMappingInfo.IDMapping);

		if(!closeMappingSucessful)
		{
			return false;// FileActionResult::Invalid; // TODO: fix this
		}

		fileMappingInfo.IDMapping = 0;
	}

	const FileActionResult closeFile = File::Close(fileMappingInfo.ID);

	return true;
#endif
}
