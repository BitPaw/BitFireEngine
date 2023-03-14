#ifndef PXMemoryINCLUDE
#define PXMemoryINCLUDE

#include <Format/Type.h>

#if OSUnix
typedef int MemoryProtectionModeType;
#elif OSWindows
typedef unsigned long MemoryProtectionModeType;// DWORD
#endif

//---<Settings>---
#define MemoryAssertEnable 0
#define MemoryDebugOutput 0
#define MemoryDebugLeakDetection 0
#define MemoryUseSystemFunction 0
#define MemorySanitise 0
//----------------

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum MemoryProtectionMode_
	{
		MemoryInvalid,
		MemoryNoReadWrite,
		MemoryReadOnly,
		MemoryWriteOnly,
		MemoryReadAndWrite
	}
	MemoryProtectionMode;

	typedef enum MemoryCachingMode_
	{
		MemoryCachingDefault,

		MemoryCachingRandom,  // Access data in a random order.
		MemoryCachingSequential, // Data sequentially from lower offsets to higher offsets.
		MemoryCachingTemporary, // File will not be saves to drive.
		MemoryCachingUseOnce, // Access the specified data once and then not reuse it again.

		// Windows only
		MemoryCachingWriteThrough,
		MemoryCachingNoBuffering, // No OS Caching, direct to Harddrive if supprted

		// UNIX only
		MemoryCachingNeedLater, // Data is not needed right now. "For later"[near future].
		MemoryCachingDontNeedNow // Data will not be cached. "I dont need it yet"
	}
	MemoryCachingMode;

	typedef struct MemoryUsage_
	{
		PXSize PhysicalRAMSize;

		PXSize PercentInUse;
		PXSize PhysicalTotal;
		PXSize PhysicalAvailable;
		PXSize VirtualTotal;
		PXSize VirtualAvailable;
		PXSize PageFileTotal;
		PXSize PageFileAvailable;
		PXSize ExtendedVirtualAvailable;
	}
	MemoryUsage;


	PXPublic PXBool MemoryScan(MemoryUsage* memoryUsage);


	PXPublic void MemoryClear(void* const __restrict bufferA, const PXSize bufferASize);
	PXPublic void MemorySet(void* const __restrict bufferA, const unsigned char value, const PXSize bufferSize);

	// Returns 1 if correct, 0 if not.
	// This function is not like memcmp that returns -1, 0, and 1!
	PXPublic PXBool MemoryCompare(const void* __restrict bufferA, const PXSize bufferASize, const void* __restrict bufferB, const PXSize bufferBSize);

	PXPublic PXSize MemoryCopy(const void* __restrict inputBuffer, const PXSize inputBufferSize, void* outputBuffer, const PXSize outputBufferSize);
	PXPublic PXSize MemoryMove(const void* inputBuffer, const PXSize inputBufferSize, void* outputBuffer, const PXSize outputBufferSize);

	//CPublic char MemoryAdvice(const void* adress, const PXSize length, const FileCachingMode fileCachingMode);

	// Allocates size bytes on the program stack.
	// The allocated space is automatically freed when the calling function exits
	// (not when the allocation merely passes out of scope).
	PXPublic void* MemoryStackAllocate(const PXSize size);
	//PXPublic void* MemoryStackRelease(void* const adress);

	PXPublic void* MemoryHeapAllocate(const PXSize size);
	PXPublic void* MemoryHeapAllocateDetailed(const PXSize size, const char* file, const char* function, const PXSize line);

	// Allocate memory and clear is after. Its just a combination of malloc and memset
	PXPublic void* MemoryAllocateClear(const PXSize size);

	PXPublic void* MemoryHeapReallocate(void* sourceAddress, const PXSize size);
	PXPublic void* MemoryHeapReallocateDetailed(void* sourceAddress, const PXSize size, const char* file, const char* function, const PXSize line);
	PXPublic void* MemoryHeapReallocateClear(const void* const adress, const PXSize sizeBefore, const PXSize sizeAfter);
	PXPublic void MemoryRelease(const void* adress, const PXSize size);

	// Allocate memory in virtual memory space.
	// The minimal size will be a pagefile (4KB) as the size will be rounded up to the next page boundary.
	// Only use for bigger datablocks as thic has very hi overhead.
	PXPublic void* MemoryVirtualAllocate(PXSize size, const MemoryProtectionMode memoryProtectionMode);
	PXPublic void MemoryVirtualPrefetch(const void* adress, const PXSize size);
	PXPublic void MemoryVirtualRelease(const void* adress, const PXSize size);
	PXPublic void* MemoryVirtualReallocate(const void* adress, const PXSize size);


	PXPublic MemoryProtectionModeType ConvertFromMemoryProtectionMode(const MemoryProtectionMode memoryProtectionMode);

#ifdef __cplusplus
}
#endif

#if 1 // Use default allocator

#if 0//_PX_DEBUG
#define MemoryReallocate(address, dataSize) MemoryHeapReallocateDetailed(address, dataSize, _PX_FILENAME_, _PX_FUNCTION_, _PX_LINE_)
#define MemoryAllocate(dataSize) MemoryHeapAllocateDetailed(dataSize, _PX_FILENAME_, _PX_FUNCTION_, _PX_LINE_)
#else
#define MemoryReallocate(address, dataSize) MemoryHeapReallocate(address, dataSize)
#define MemoryAllocate(dataSize) MemoryHeapAllocate(dataSize)
#endif

#else // Use virtual alloc

#define MemoryReallocate(address, dataSize) MemoryVirtualReallocate(address, dataSize)
#define MemoryAllocate(dataSize) MemoryVirtualAllocate(dataSize, MemoryReadAndWrite)
#endif


#endif