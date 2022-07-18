#include "User.h"

#include <OS/OSVersion.h>

#if defined(OSUnix)

#elif defined(OSWindows)
#include <Windows.h>
#endif

unsigned char UserNameGetA(char* name, const size_t nameSizeMax, size_t* nameSizeWritten)
{
#if defined(OSUnix)

	return 0;

#elif defined(OSWindows)
	DWORD size = nameSizeMax;

	const unsigned char sucessful = GetComputerNameA(name, &size);

	nameSizeWritten = sucessful * size;

	return sucessful;
#endif
}

unsigned char UserNameGetW(wchar_t* name, const size_t nameSizeMax, size_t* nameSizeWritten)
{
#if defined(OSUnix)

	return 0;

#elif defined(OSWindows)
	DWORD size = nameSizeMax;

	const unsigned char sucessful = GetComputerNameW(name, &size);

	nameSizeWritten = sucessful * size;

	return sucessful;
#endif
}