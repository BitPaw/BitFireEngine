#include "User.h"

#include <OS/OSDefine.h>

#if defined(OSUnix)

#elif defined(OSWindows)
#include <Windows.h>
#endif

bool BF::User::Name(wchar_t* name, const size_t nameSizeMax, size_t& nameSizeWritten)
{
#if defined(OSUnix)

	return false;

#elif defined(OSWindows)
	DWORD size = nameSizeMax;

	const bool sucessful = GetComputerNameW(name, &size);
	
	nameSizeWritten = sucessful * size;

	return sucessful;
#endif
}
