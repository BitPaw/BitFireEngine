#include "Library.h"

/*
dlopen() - gain access to an executable object file
dclose() - close a dlopen object
dlsym() - obtain the address of a symbol from a dlopen object
dlvsym() - Programming interface to dynamic linking loader.
dlerror() - get diagnostic information
*/

bool BF::Library::Open(const char* filePath)
{
#ifdef defined(OSUnix)
#elif defined(OSWindows)	
	const LibraryHandle libraryHandle = LoadLibraryA(filePath);
	const bool sucessful = libraryHandle != nullptr;
#endif

	Handle = libraryHandle;

	return sucessful;
}

bool BF::Library::Open(const wchar_t* filePath)
{
#ifdef defined(OSUnix)
#elif defined(OSWindows)	
	const LibraryHandle libraryHandle = LoadLibraryW(filePath);
	const bool sucessful = libraryHandle != nullptr;
#endif

	Handle = libraryHandle;

	return sucessful;
}

bool BF::Library::Close()
{
#ifdef defined(OSUnix)
	const bool result = dlclose(Handle);
#elif defined(OSWindows)	
	const bool result = FreeLibrary(Handle);
#endif

	Handle = nullptr;

	return result;
}

LibraryFunction BF::Library::GetSymbol(const char* symbol)
{
#ifdef defined(OSUnix)
	const LibraryFunction functionPointer = (LibraryFunction*)dlsym(libraryHandle, symbol);
	const char* errorString = dlerror();
	const bool successful = errorString;
#elif defined(OSWindows)	
	const LibraryFunction functionPointer = GetProcAddress(Handle, symbol);
	const bool successful = functionPointer;
#endif

	return functionPointer;
}

BF::ErrorCode BF::Library::SearchDirectoryAdd(const wchar_t* directoryPath, LibraryDirectoryID& libraryDirectoryID)
{
#ifdef defined(OSUnix)
#elif defined(OSWindows)	
	const DLL_DIRECTORY_COOKIE cookie = AddDllDirectory(directoryPath);
	const bool successful = cookie != 0;

	if (!successful)
	{
		const ErrorCode errorCode = GetCurrentError();

		return errorCode;
	}

	libraryDirectoryID = cookie;
#endif

	return ErrorCode::Successful;
}

BF::ErrorCode BF::Library::SearchDirectoryRemove(LibraryDirectoryID& libraryDirectoryID)
{
#ifdef defined(OSUnix)
#elif defined(OSWindows)	
	const bool successful = RemoveDllDirectory(libraryDirectoryID);

	if (!successful)
	{
		const ErrorCode errorCode = GetCurrentError();

		return errorCode;
	}

	libraryDirectoryID = 0;
#endif	

	return ErrorCode::Successful;
}