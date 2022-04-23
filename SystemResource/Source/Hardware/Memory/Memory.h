#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "MemoryUsage.h"

#include <OS/OSDefine.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>
#endif

#define MemoryDebug 0

namespace BF
{
    class Memory
    {
        public:
        static bool Scan(MemoryUsage& memoryUsage);

        static int Compare(const void* a, const void* b, const size_t length);

        static bool VirtualMemoryAllocate();
        static bool VirtualMemoryRelease();
        static bool VirtualMemoryFileMap(const char* filePath, HANDLE& fileHandle, HANDLE& mappingHandle, void** fileData, size_t& fileSize);
        static bool VirtualMemoryFileMap(const wchar_t* filePath, HANDLE& fileHandle, HANDLE& mappingHandle, void** fileData, size_t& fileSize);
        static bool VirtualMemoryFileUnmap(HANDLE& fileHandle, HANDLE& mappingHandle, void** fileData, size_t& fileSize);

        template<typename T>
        static T* Rellocate(T* adress, const size_t size)
        {
            const size_t sizeInBytes = size * sizeof(T);
            T* reallocatedAdress = (T*)realloc(adress, sizeInBytes);

#if MemoryDebug
            printf("[#][Memory] 0x%p (%10zi B) Reallocate to 0x%p\n", adress, size, reallocatedAdress);
#endif     

            return reallocatedAdress;
        }

        static bool Advise(void* adress, const size_t length)
        {
            return true;
        }

        // Allocates memory on the HEAP.
        // Returns NULL if systems is "out of memory"
        template<typename T>
        static T* Allocate(const size_t size)
        {
            const size_t requestedBytes = size * sizeof(T);
            T* adress = (T*)malloc(requestedBytes);

#if MemoryDebug
            printf("[#][Memory] 0x%p (%10zi B) Alloc\n", adress, requestedBytes);
#endif      

            return adress;
        }

        static void Release(void* adress, const size_t size)
        {
#if MemoryDebug
            printf("[#][Memory] 0x%p (%10zi B) Free\n", adress, size);
#endif       

            return free(adress);
        }

        static void Set(void* target, const unsigned char value, const size_t size)
        {
#if MemoryDebug
            printf("[#][Memory] 0x%p (%10zi B) Set with %x\n", target, size, value);
#endif   
            memset(target, value, size);
        }

        static void Copy(void* target, const void* source, const size_t size)
        {
#if MemoryDebug
            printf("[#][Memory] 0x%p (%10zi B) Copy from 0x%p\n", target, size, source);
#endif 
            memcpy(target, source, size);
        }
        //static void* Realloc();
    };
}