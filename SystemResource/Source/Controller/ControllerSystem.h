#pragma once

#include "ControllerData.h"

#include <Windows.h>

#define ControllerID unsigned int
#define WindowID HWND

namespace BF
{
	typedef void (*NewControllerDetectedCallback)(ControllerID controllerID);

	class ControllerSystem
	{
		public:
		static void ControllerScanDevices(NewControllerDetectedCallback callback);
		static bool ControllerDataGet(const ControllerID controllerID, ControllerData& controller);
		static bool ControllerAttachToWindow(const ControllerID controllerID, const WindowID windowID);
		static bool ControllerDetachToWindow(const ControllerID controllerID);
	};
}