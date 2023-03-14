#ifndef RegistryINCLUDE
#define RegistryINCLUDE

#include <Format/Type.h>

#if OSUnix
typedef unsigned int RegistryID;

#elif OSWindows
#include <Windows.h>
#include <winreg.h>

typedef HKEY RegistryID;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum RegistryResult_
	{
		RegistryResultInvalid,
		RegistryResultSucessful
	}
	RegistryResult;

	typedef enum RegistrySpace_
	{
		RegistrySpaceInvalid,
		RegistrySpaceLocalMachine,
		RegistrySpacePerformanceData,
		RegistrySpaceUsers
	}
	RegistrySpace;

	typedef struct Registry_
	{
		RegistryID ID;
	}
	Registry;

	PXPublic RegistryResult RegistryConnectSpace(Registry* const registry, const RegistrySpace registrySpace);
	PXPublic RegistryResult RegistryConnectRemote(Registry* const registry, const wchar_t* computerName, const RegistrySpace registrySpace);

	PXPublic void RegistryClose(Registry* const registry);

	PXPublic void RegistryKeyCreate(Registry* const registry);
	PXPublic void RegistryKeyLoad(Registry* const registry, const wchar_t* file);
	PXPublic void RegistryKeySave(Registry* const registry);
	PXPublic void RegistryKeyDelete(Registry* const registry);

#ifdef __cplusplus
}
#endif

#endif