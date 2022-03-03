#include "Library.h"

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