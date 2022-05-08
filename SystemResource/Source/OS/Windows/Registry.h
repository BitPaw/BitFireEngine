#pragma once

#include "../OSDefine.h"

#if defined(OSWindows)
#include <Windows.h>
#include <winreg.h>

#define RegistryID HKEY

namespace BF
{
	enum class RegistryResult
	{
		Invalid,

		Sucessful
	};

	enum class RegistrySpace
	{
		Invalid,

		LocalMachine,
		PerformanceData,
		Users
	};

	class Registry
	{
		public:
		static RegistryResult Connect(const RegistrySpace registrySpace, RegistryID& registryID);
		static RegistryResult Connect(const wchar_t* computerName, const RegistrySpace registrySpace, RegistryID& registryID);

		static void Close(RegistryID& registryID);

		static void KeyCreate();
		static void KeyLoad(const wchar_t* file);
		static void KeySave();
		static void KeyDelete();
	};
}
#else
//#error Windows Regestry does not exist under non-Windows Systems
#endif // defined(OSWindows)
