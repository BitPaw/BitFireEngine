#pragma once

#include <Memory/Memory.h>

namespace BF
{
    class Memory
    {
        public:
        // Allocates memory on the HEAP.
        // Returns NULL if systems is "out of memory"
        template<typename T>
        static T* Allocate(const size_t size)
        {
            const size_t requestedBytes = size * sizeof(T);
            T* adress = (T*)MemoryAllocate(requestedBytes);

            return adress;
        }

        // Changes the size of a given byteblock.knging the poniter.
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
