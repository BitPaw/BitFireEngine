#include "Monitor.h"

#include <stdio.h>



#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>


bool BF::Monitor::FetchInfo(HMONITOR hMonitor)
{
	//HMONITOR hMonitor;
	MONITORINFOEXW monitorInfo{ 0 };

	monitorInfo.cbSize = sizeof(monitorInfo);

	bool result = GetMonitorInfoW(hMonitor, &monitorInfo);

	unsigned int width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	unsigned int height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

	printf
	(
		"[Monitor] %p <%ls> %ix%i\n",
		hMonitor,
		monitorInfo.szDevice,
		width,
		height
	);

	return true;
}

bool BF::Monitor::FetchInfo(const WindowID windowID)
{

	// MONITOR_DEFAULTTONEAREST // Returns a handle to the display monitor that is nearest to the window.
	// MONITOR_DEFAULTTONULL //		Returns NULL.
	// MONITOR_DEFAULTTOPRIMARY //	Returns a handle to the primary display monitor.

	const unsigned int flags = MONITOR_DEFAULTTONEAREST;

	HMONITOR monitorHandle = MonitorFromWindow(windowID, flags);

	return false;
}

BOOL BF::Monitor::MonitorListCallBack(HMONITOR monitorHandle, HDC hdcMonitor, LPRECT rectangle, LPARAM data)
{
	Monitor monitor;

	monitor.FetchInfo(monitorHandle);

	//printf("[Monitor] %p\n", monitorHandle);

	return 0;
}

void BF::Monitor::List()
{
	HDC             hdc = nullptr;
	RECT         rectangleClip;
	MONITORENUMPROC lpfnEnum = Monitor::MonitorListCallBack;
	LPARAM          dwData = 0;




	while(EnumDisplayMonitors(nullptr, nullptr, lpfnEnum, dwData));









	DISPLAY_DEVICEW displayDevice{ 0 };
	DWORD            dwFlags = 0;

	displayDevice.cb = sizeof(DISPLAY_DEVICEW);

	for(size_t deviceID = 0; EnumDisplayDevicesW(nullptr, deviceID, &displayDevice, dwFlags); deviceID++)
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
}
#endif