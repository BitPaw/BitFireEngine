#pragma once

#include <OS/OSDefine.h>

#if defined(OSUnix)
#define MemoryProtectionModeType int
#elif defined(OSWindows)
#define MemoryProtectionModeType unsigned long // DWORD
#endif

namespace BF
{
    enum class MemoryProtectionMode
    {
        Invalid,
        NoReadWrite,
        ReadOnly,
        WriteOnly,
        ReadAndWrite
    };

    MemoryProtectionModeType ConvertMemoryProtectionMode(const MemoryProtectionMode memoryProtectionMode);
}
