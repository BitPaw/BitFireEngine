#pragma once

#include "MemoryUsage.h"
#include "MemoryProtectionMode.h"

#include <OS/OSDefine.h>
#include <ErrorCode.h>
#include <File/File.h>
#include <File/FileCachingMode.h>
#include <File/FileActionResult.hpp>

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define MemoryDebug 0
#define MemoryUseSystemCalls 0

namespace BF
{
    class Memory
    {
        public:
        static bool Scan(MemoryUsage& memoryUsage);

        static int Compare(const void* a, const void* b, const size_t length);

        static bool VirtualMemoryPrefetch(const void* adress, const size_t size);

        // Allocate memory in virtual memory space.
        // The minimal size will be a pagefile (4KB).
        // The size will be rounded up to the next page boundary.
        // Use only for bigger datablocks.
        static void* VirtualMemoryAllocate(const size_t size, const MemoryProtectionMode memoryProtectionMode);
        static bool VirtualMemoryRelease(const void* adress, const size_t size);

        static bool Advise(const void* adress, const size_t length, const FileCachingMode fileCachingMode);  
        static void Set(void* target, const unsigned char value, const size_t size);
        static void Copy(void* target, const void* source, const size_t size);

        // Give back memory that you allocated before.
        static void Release(void* adress, const size_t size);

        // Allocates memory on the HEAP.
        // Returns NULL if systems is "out of memory"
        template<typename T>
        static T* Allocate(const size_t size)
        {
            const size_t requestedBytes = size * sizeof(T);
            T* adress = (T*)malloc(requestedBytes);

#if MemoryDebug
            printf("[#][Memory] 0x%p (%10zi B) Allocate\n", adress, requestedBytes);
#endif

            return adress;
        }

        // Changes the size of a given byteblock.
        // The change maybe performed without moving the data and thus not changing the poniter.
        // The function will return NULL if the system is "out of memory".
        template<typename T>
        static T* Reallocate(T* adress, const size_t size)
        {
            const size_t requestedBytes = size * sizeof(T);
            T* adressReallocated = (T*)realloc(adress, requestedBytes);

#if MemoryDebug
            const bool hasChanged = adress != adressReallocated;

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
    };
}
