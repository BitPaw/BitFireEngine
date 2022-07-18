#pragma once

#include <OS/OSVersion.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>
#include <mmeapi.h>
#define AudioDeviceInputHandle HWAVEIN
#endif

namespace BF
{
	struct AudioDeviceInput
	{
		AudioDeviceInputHandle Handle;
	};
}