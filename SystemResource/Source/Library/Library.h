#pragma once

#include "../OSDefine.h"

#ifdef defined(OSUnix)
#include <sys/types.h>
#include <dlfcn.h>
/*
dlopen() - gain access to an executable object file
dclose() - close a dlopen object
dlsym() - obtain the address of a symbol from a dlopen object
dlvsym() - Programming interface to dynamic linking loader.
dlerror() - get diagnostic information
*/
#define LibraryHandle void*
#define LibraryFunction func_t*

#elif defined(OSWindows)	
#include <windows.h>

#define LibraryHandle HMODULE // HINSTANCE (semms is also okey)
#define LibraryFunction FARPROC
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
    };
}