#if !defined(MemoryInclude)
#define MemoryInclude

#include <stddef.h>

#include <OS/OSVersion.h>

#if defined(OSUnix)
#define MemoryProtectionModeType int
#elif defined(OSWindows)
#define MemoryProtectionModeType unsigned long // DWORD
#endif

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
		size_t PercentInUse;
		size_t PhysicalTotal;
		size_t PhysicalAvailable;
		size_t VirtualTotal;
		size_t VirtualAvailable;
		size_t PageFileTotal;
		size_t PageFileAvailable;
		size_t ExtendedVirtualAvailable;
	}
	MemoryUsage;


	extern unsigned char MemoryScan(MemoryUsage* memoryUsage);


	extern void MemorySet(void* __restrict bufferA, const size_t bufferASize, const unsigned char value);
	
	// Returns 1 if correct, 0 if not.
	// This function is not like memcmp that returns -1, 0, and 1!
	extern unsigned char MemoryCompare(const void* __restrict bufferA, const size_t bufferASize, const void* __restrict bufferB, const size_t bufferBSize);

	extern size_t MemoryCopy(const void* __restrict inputBuffer, const size_t inputBufferSize, void* outputBuffer, const size_t outputBufferSize);

	//extern char MemoryAdvice(const void* adress, const size_t length, const FileCachingMode fileCachingMode);

	extern void* MemoryAllocate(const size_t size);
	extern void* MemoryReallocate(void* adress, const size_t size);
	extern void MemoryRelease(const void* adress, const size_t size);

	// Allocate memory in virtual memory space.
	// The minimal size will be a pagefile (4KB) as the size will be rounded up to the next page boundary.
	// Only use for bigger datablocks as thic has very hi overhead.
	extern void* MemoryVirtualAllocate(const size_t size, const MemoryProtectionMode memoryProtectionMode);
	extern void MemoryVirtualPrefetch(const void* adress, const size_t size);
	extern void MemoryVirtualRelease(const void* adress, const size_t size);


	static MemoryProtectionModeType ConvertFromMemoryProtectionMode(const MemoryProtectionMode memoryProtectionMode);

#ifdef __cplusplus
}
#endif

#endif