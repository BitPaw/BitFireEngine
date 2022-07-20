#include "Monitor.h"

#include <Memory/Memory.h>

#if defined(OSUnix)
#elif defined(OSWindows)
BOOL MonitorListCallBack(HMONITOR monitorHandle, HDC hdcMonitor, LPRECT rectangle, LPARAM data)
{
	MONITORINFOEXW monitorInfo;

	monitorInfo.cbSize = sizeof(monitorInfo);

	const unsigned char result = GetMonitorInfoW(monitorHandle, &monitorInfo);

	if(!result)
	{
		return 1;
	}

	Monitor monitor;
	monitor.X = monitorInfo.rcMonitor.left;
	monitor.Y = monitorInfo.rcMonitor.top;
	monitor.Width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	monitor.Height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

	TextCopyW(monitorInfo.szDevice, 32, monitor.Name, MonitorNameLength);

	printf
	(
		"[Monitor] %p <%ls> %ix%i\n",
		monitorHandle,
		monitorInfo.szDevice,
		monitor.Width,
		monitor.Height
	);

	return 1;
}
#endif

void MonitorFetchAll(Monitor* monitorList, const size_t monitorListSizeMax, const size_t monitorListSize)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	HDC             hdc = 0;
	RECT         rectangleClip;
	MONITORENUMPROC lpfnEnum = MonitorListCallBack;
	LPARAM          dwData = 0;

	MemorySet(&rectangleClip, sizeof(RECT), 0);

	while(EnumDisplayMonitors(hdc, &rectangleClip, lpfnEnum, dwData));


	DISPLAY_DEVICEW displayDevice;
	DWORD            dwFlags = 0;

	MemorySet(&displayDevice, sizeof(DISPLAY_DEVICEW), 0);

	displayDevice.cb = sizeof(DISPLAY_DEVICEW);

	for(size_t deviceID = 0; EnumDisplayDevicesW(0, deviceID, &displayDevice, dwFlags); deviceID++)
	{
		printf
		(
			"+------------------------\n"
			"| DeviceName   : %-10ls |\n"
			"| DeviceString : %-10ls |\n"
			"| StateFlags   : %-10i |\n"
			"| DeviceID     : %-10ls |\n"
			"| DeviceKey    : %-10ls |\n"
			"+------------------------\n",
			displayDevice.DeviceName,
			displayDevice.DeviceString,
			displayDevice.StateFlags,
			displayDevice.DeviceID,
			displayDevice.DeviceKey

		);
	}
#endif
}

void MonitorGetSize(unsigned int* width, unsigned int* height)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	RECT desktop;

	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();

	if(hDesktop)
	{
		// Get the size of screen to the variable desktop
		GetWindowRect(hDesktop, &desktop);

		// The top left corner will have coordinates (0,0)
		// and the bottom right corner will have coordinates
		// (horizontal, vertical)
		*width = desktop.right;
		*height = desktop.bottom;
	}	
#endif
}
