#ifndef MonitorInclude
#define MonitorInclude

#include <stddef.h>

#include <OS/OSVersion.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define MonitorNameLength 32

	typedef struct Monitor_
	{
		unsigned short X;
		unsigned short Y;
		unsigned short Width;
		unsigned short Height;
		wchar_t Name[MonitorNameLength];
	}
	Monitor;

#if defined(OSUnix)
#elif defined(OSWindows)
	static BOOL _stdcall MonitorListCallBack(HMONITOR monitorHandle, HDC hdcMonitor, LPRECT rectangle, LPARAM data);
#endif

	extern void MonitorFetchAll(Monitor* monitorList, const size_t monitorListSizeMax, const size_t monitorListSize);

	extern void MonitorGetSize(unsigned int* width, unsigned int* height);

#ifdef __cplusplus
}
#endif

#endif