#pragma once

#include <OS/OSDefine.h>
#include <ErrorCode.h>

#ifdef defined(OSUnix)
#include <sys/types.h>
#include <dlfcn.h>

#define LibraryHandle void*
#define LibraryFunction func_t*
#define LibraryDirectoryID void*

#elif defined(OSWindows)	
#include <windows.h>

#define LibraryHandle HMODULE // HINSTANCE (semms is also okey)
#define LibraryFunction FARPROC
#define LibraryDirectoryID DLL_DIRECTORY_COOKIE
#endif

namespace BF
{
    class Library
    {
        public:  
        LibraryHandle Handle;

        bool Open(const char* filePath); //  gain access to an executable object file. RTLD_LAZY
        bool Open(const wchar_t* filePath); //  gain access to an executable object file. RTLD_LAZY
        bool Close(); // close a dlopen object
        LibraryFunction GetSymbol(const char* symbolName); // obtain the address of a symbol from a dlopen object
       // void SymbolVector(); // Programming interface to dynamic linking loader.

        static ErrorCode SearchDirectoryAdd(const wchar_t* directoryPath, LibraryDirectoryID& libraryDirectoryID);
        static ErrorCode SearchDirectoryRemove(LibraryDirectoryID& libraryDirectoryID);
    };
}