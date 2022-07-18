#pragma once

#include <OS/OSVersion.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>
#include <mmeapi.h>
#define AudioDeviceOutputHandle HWAVEOUT
#endif

namespace BF
{
	struct AudioDeviceOutput
	{
		AudioDeviceOutputHandle Handle;
	};
}