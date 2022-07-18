#if !defined(LibraryInclude)
#define LibraryInclude

#include <OS/OSVersion.h>

#if defined(OSUnix)
#include <sys/types.h>
#include <dlfcn.h>

#define LibraryHandle void*
#define LibraryFunction void*
#define LibraryDirectoryID void*

#elif defined(OSWindows)
#include <windows.h>

#define LibraryHandle HMODULE // HINSTANCE (semms is also okey)
#define LibraryFunction FARPROC
#define LibraryDirectoryID DLL_DIRECTORY_COOKIE
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    extern unsigned char LibraryOpenA(LibraryHandle* handle, const char* filePath); //  gain access to an executable object file. RTLD_LAZY
    extern unsigned char LibraryOpenW(LibraryHandle* handle, const wchar_t* filePath); //  gain access to an executable object file. RTLD_LAZY
    extern unsigned char LibraryClose(LibraryHandle* handle); // close a dlopen object
    extern unsigned char LibraryGetSymbol(LibraryHandle* handle, LibraryFunction* libraryFunction, const char* symbolName); // obtain the address of a symbol from a dlopen object

   // void SymbolVector(); // Programming interface to dynamic linking loader.

    //static ErrorCode SearchDirectoryAdd(const wchar_t* directoryPath, LibraryDirectoryID& libraryDirectoryID);
    //static ErrorCode SearchDirectoryRemove(LibraryDirectoryID& libraryDirectoryID);

#ifdef __cplusplus
}
#endif

#endif