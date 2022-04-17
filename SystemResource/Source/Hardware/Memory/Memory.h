#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "MemoryUsage.h"

#define MemoryDebug 1

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
            T* adress = (T*)malloc(requestedBytes);

#if MemoryDebug
            printf("[#][Memory][Alloc] %p (Bytes %zi)\n", adress, requestedBytes);
#endif      

            return adress;
        }

        static void Release(void* adress, const size_t size)
        {
#if MemoryDebug
            printf("[#][Memory][Free ] %p (Bytes %zi)\n", adress, size);
#endif       

            return free(adress);
        }

        static void Set(void* target, const unsigned char value, const size_t size)
        {
#if MemoryDebug
            printf("[#][Memory][ Set ] %p with %x (Bytes %zi)\n", target, value, size);
#endif   
            memset(target, value, size);
        }

        static void Copy(void* target, const void* source, const size_t size)
        {
            printf("[#][Memory][Copy ] %p from %p (%zi Bytes)\n", target, source, size);

            memcpy(target, source, size);
        }
        //static void* Realloc();
    };
}