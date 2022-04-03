#include "Registry.h"

#if defined(OSWindows)

#include <winerror.h> 

// Advapi32.lib

BF::RegistryResult BF::Registry::Connect(const RegistrySpace registrySpace, RegistryID& registryID)
{
	return Connect(nullptr, registrySpace, registryID);
}

BF::RegistryResult BF::Registry::Connect(const wchar_t* computerName, const RegistrySpace registrySpace, RegistryID& registryID)
{
	HKEY hKey = 0;

	switch (registrySpace)
	{
		default:
		case BF::RegistrySpace::Invalid:
			break;
		
		case BF::RegistrySpace::LocalMachine:
			hKey = HKEY_LOCAL_MACHINE;
			break;

		case BF::RegistrySpace::PerformanceData:
			hKey = HKEY_PERFORMANCE_DATA;
			break;

		case BF::RegistrySpace::Users:
			hKey = HKEY_USERS;
			break;
	}


	const LSTATUS status = RegConnectRegistryW(computerName, hKey, &registryID);
	const bool sucessful = status == ERROR_SUCCESS;

	if (!sucessful)
	{
		// DO stuff;
		return RegistryResult::Invalid;
	}

	return RegistryResult::Sucessful;
}

void BF::Registry::Close(RegistryID& registryID)
{
	RegCloseKey(registryID);

	registryID = 0;
}

void BF::Registry::KeyCreate()
{
	HKEY hKey = 0;
	LPCWSTR lpSubKey = 0;
	DWORD Reserved = 0;
	LPWSTR lpClass = 0;
	DWORD dwOptions = 0;
	REGSAM samDesired = 0;
	SECURITY_ATTRIBUTES securityAttributes{0};
	PHKEY phkResult = 0;
	DWORD dwDisposition = 0;

	const LSTATUS status = RegCreateKeyExW
	(
		hKey,
		lpSubKey,
		Reserved,
		lpClass,
		dwOptions,
		samDesired,
		&securityAttributes,
		phkResult,
		&dwDisposition
	);
}
void BF::Registry::KeyLoad(const wchar_t* file)
{
	HKEY hKey = 0;
	SECURITY_ATTRIBUTES securityAttributes{0};
	DWORD Flags = 0;

	const LSTATUS status = RegSaveKeyExW(hKey, file, &securityAttributes, Flags);
}
void BF::Registry::KeySave()
{
	
}
void BF::Registry::KeyDelete()
{
}
#endif