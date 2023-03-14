#ifndef MonitorInclude
#define MonitorInclude

#include <Format/Type.h>
#include <OS/System/OSVersion.h>

#if OSUnix
#elif OSWindows
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define MonitorNameLength 32

	typedef struct PXMonitor_
	{
		unsigned short X;
		unsigned short Y;
		unsigned short Width;
		unsigned short Height;
		PXByte Name[MonitorNameLength];
	}
	PXMonitor;

#if OSUnix
#elif OSWindows
	PXPrivate BOOL WINAPI PXMonitorListCallBack(HMONITOR monitorHandle, HDC hdcMonitor, LPRECT rectangle, LPARAM data);
#endif

	PXPublic void PXMonitorFetchAll(PXMonitor* const monitorList, const PXSize monitorListSizeMax, const PXSize monitorListSize);

	PXPublic void PXMonitorGetSize(unsigned int* width, unsigned int* height);

#ifdef __cplusplus
}
#endif

#endif