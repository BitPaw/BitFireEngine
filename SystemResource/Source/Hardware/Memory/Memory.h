#pragma once

#include "MemoryUsage.h"

#include <Memory/Memory.h>

#include <OS/OSVersion.h>
#include <ErrorCode.h>
#include <File/File.h>
#include <File/FileActionResult.hpp>

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>

namespace BF
{
    class Memory
    {
        public:
        static bool Scan(MemoryUsage& memoryUsage);

        // Allocates memory on the HEAP.
        // Returns NULL if systems is "out of memory"
        template<typename T>
        static T* Allocate(const size_t size)
        {
            const size_t requestedBytes = size * sizeof(T);
            T* adress = (T*)MemoryAllocate(requestedBytes);



            return adress;
        }

        // Changes the size of a given byteblock.
        // The change maybe performed without moving the data and thus not changing the poniter.
        // The function will return NULL if the system is "out of memory".
        template<typename T>
        static T* Reallocate(T* adress, const size_t size)
        {
            const size_t requestedBytes = size * sizeof(T);
            T* adressReallocated = (T*)MemoryReallocate(adress, requestedBytes);

            return adressReallocated;
        }
    };
}
