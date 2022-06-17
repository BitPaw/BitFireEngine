#include "MemoryProtectionMode.h"

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

MemoryProtectionModeType BF::ConvertMemoryProtectionMode(const MemoryProtectionMode memoryProtectionMode)
{
	switch(memoryProtectionMode)
	{
		case MemoryProtectionMode::ReadOnly: return ProtectionIDRead;
		case MemoryProtectionMode::WriteOnly: return ProtectionIDRead;
		case MemoryProtectionMode::ReadAndWrite: return ProtectionIDRead;

		default: return 0;
	}
}