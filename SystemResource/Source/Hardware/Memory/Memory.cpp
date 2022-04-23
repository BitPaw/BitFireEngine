#include "Memory.h"

#include <OS/OSDefine.h>

#if defined(OSUnix)
#elif defined(WindowsAtleastXP)
#include <Windows.h>
#endif

#include <ErrorCode.h>
#include <ClipBoard/ClipBoard.cpp>
#include <File/File.h>

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

bool BF::Memory::VirtualMemoryAllocate()
{
	return false;
}

bool BF::Memory::VirtualMemoryRelease()
{
	return false;
}

bool BF::Memory::VirtualMemoryFileMap(const char* filePath, HANDLE& fileHandle, HANDLE& mappingHandle, void** fileData, size_t& fileSize)
{
	return false;
}

bool BF::Memory::VirtualMemoryFileMap(const wchar_t* filePath, HANDLE& fileHandle, HANDLE& mappingHandle, void** fileData, size_t& fileSize)
{
	fileHandle = 0;
	mappingHandle = 0;
	(*fileData) = 0;

	// Open file
	{
		const FileActionResult openResult = File::Open(fileHandle, filePath, FileOpenMode::Read, FileCachingMode::Sequential);
		const bool openSuccess = openResult == FileActionResult::Successful;

		if(!openSuccess)
		{
			return false; //openResult;
		}
	}

#if defined(OSUnix)

#elif defined(OSWindows)

	{
		LARGE_INTEGER largeInt{0};

		const bool sizeResult = GetFileSizeEx(fileHandle, &largeInt);

		fileSize = largeInt.QuadPart;
	}




	// Create mapping
	{
		SECURITY_ATTRIBUTES fileMappingAttributes{ 0 };
		DWORD                 flProtect = PAGE_READONLY;
		DWORD                 dwMaximumSizeHigh = 0;
		DWORD                 dwMaximumSizeLow = 0; // Problem if file is 0 Length
		wchar_t* name = nullptr;

		const HANDLE fileMappingHandleResult = CreateFileMappingW
		(
			fileHandle,
			nullptr,
			flProtect,
			dwMaximumSizeHigh,
			dwMaximumSizeLow,
			name
		);
		const bool successful = fileMappingHandleResult;

		if(!successful)
		{
			return false;// FileActionResult::FileMemoryMappingFailed;
		}

		mappingHandle = fileMappingHandleResult;
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
			mappingHandle,
			desiredAccess,
			fileOffsetHigh,
			fileOffsetLow,
			numberOfBytesToMap,
			baseAddressTarget,
			numaNodePreferred
		);

		{
			const HANDLE process = GetCurrentProcess();
			const size_t numberOfEntries = 2;
			WIN32_MEMORY_RANGE_ENTRY memoryRangeEntry;
			const size_t flags = 0; // reserved and needs to be 0

			memoryRangeEntry.VirtualAddress = fileMapped;
			memoryRangeEntry.NumberOfBytes = fileSize;

			const bool prefetchResult = PrefetchVirtualMemory(process, numberOfEntries, &memoryRangeEntry, flags);
		}

	

		(*fileData) = fileMapped;
	}
#endif


#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP %ls\n", (*fileData), fileSize, filePath);
#endif    
}

bool BF::Memory::VirtualMemoryFileUnmap(HANDLE& fileHandle, HANDLE& mappingHandle, void** fileData, size_t& fileSize)
{

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) MMAP-Release\n", (*fileData), fileSize);
#endif    

	{
		void* data = (*fileData);
		const bool unmappingSucessful = UnmapViewOfFile(data);

		if(!unmappingSucessful)
		{
			const ErrorCode error = GetCurrentError();

			return false;// FileActionResult::Invalid; // TODO: fix this
		}

		(*fileData) = nullptr;
	}


	{
		const bool closeMappingSucessful = CloseHandle(mappingHandle);

		if(!closeMappingSucessful)
		{
			return false;// FileActionResult::Invalid; // TODO: fix this
		}

		mappingHandle = 0;
	}

	const FileActionResult closeFile = File::Close(fileHandle);

	return true;
}