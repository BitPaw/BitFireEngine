#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "MemoryUsage.h"

#include <OS/OSDefine.h>
#include <ErrorCode.h>

#if defined(OSUnix)
#include <sys/mman.h>
#elif defined(OSWindows)
#include <Windows.h>
#endif
#include <File/FileCachingMode.h>
#include <File/FileActionResult.hpp>

#define MemoryDebug 0

namespace BF
{
    class Memory
    {
        public:
        static bool Scan(MemoryUsage& memoryUsage);

        static int Compare(const void* a, const void* b, const size_t length);

        static bool VirtualMemoryPrefetch(const void* adress, const size_t size);
        static bool VirtualMemoryAllocate();
        static bool VirtualMemoryRelease();
        static FileActionResult VirtualMemoryFileMap(const char* filePath, HANDLE& fileHandle, HANDLE& mappingHandle, void** fileData, size_t& fileSize);
        static FileActionResult VirtualMemoryFileMap(const wchar_t* filePath, HANDLE& fileHandle, HANDLE& mappingHandle, void** fileData, size_t& fileSize);
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

        static bool Advise(const void* adress, const size_t length, const FileCachingMode fileCachingMode)
        {
            const int cachingModeID = ConvertFileCachingMode(fileCachingMode);

#if defined(OSUnix)    
            const int result = madvise(adress, length, cachingModeID);
            const ErrorCode errorCode = ConvertErrorCode(result);
            const bool successful = errorCode == ErrorCode::Successful;

            return successful;

#elif defined(OSWindows)
            return true;
#endif                 
        }

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
    };
}