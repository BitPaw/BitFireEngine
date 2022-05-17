#pragma once

#include <Window/Window.h>
#include <OS/OSDefine.h>

namespace BF
{
	struct Monitor
	{
		public:

#if defined(OSUnix)
#elif defined(OSWindows)
		bool FetchInfo(HMONITOR hMonitor);
		bool FetchInfo(const WindowID windowID);

		static BOOL CALLBACK MonitorListCallBack(HMONITOR monitorHandle, HDC hdcMonitor, LPRECT rectangle, LPARAM data);

		static void List();
#endif


	};
}