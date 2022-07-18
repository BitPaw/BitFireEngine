#include "ControllerSystem.h"

#include <OS/OSVersion.h>

#if defined(OSUnix)

#elif defined(OSWindows)
#include <Windows.h>
#include <joystickapi.h>

#pragma comment( lib, "winmm.lib" )
#endif

void BF::ControllerSystem::ControllerScanDevices(NewControllerDetectedCallback callback)
{
#if defined(OSUnix)
#elif defined(OSWindows)
const size_t amountOfJoySticksSupported = joyGetNumDevs();

	for (size_t i = 0; i < amountOfJoySticksSupported; i++)
	{
		const ControllerID joyID = i;
		JOYCAPSW pjc{ 0 };
		const unsigned int size = sizeof(JOYCAPSW);
		const MMRESULT devResult = joyGetDevCapsW(joyID, &pjc, size);
		const bool succesful = devResult == JOYERR_NOERROR;

		if (succesful)
		{
			if (callback)
			{
				callback(joyID);
			}
		}

		/*
		//JOYSTICKID1
		switch (devResult)
		{
			case MMSYSERR_BADDEVICEID: // Windows 95 / 98 / Me : The specified joystick identifier is invalid.
			{
				printf("MMSYSERR_BADDEVICEID\n");
				break;
			}
			case JOYERR_NOERROR:
			{




				printf("OK\n");

				break;
			}
			case MMSYSERR_NODRIVER://The joystick driver is not present.
			{
				printf("No Driver\n");
				break;
			}
			case MMSYSERR_INVALPARAM://An invalid parameter was passed.
			{
				printf("Invalid Paramerer\n");
				break;
			}
			case JOYERR_PARMS: //Windows NT / 2000 / XP : The specified joystick identifier is invalid.
			{
				printf("JOYERR_PARMS\n");
				break;
			}
			case JOYERR_UNPLUGGED: // The specified joystick is not connected to the system.
			{
				printf("JOYERR_UNPLUGGED\n");
				break;
			}

			default:
				break;
		}*/
	}
#endif
}

bool BF::ControllerSystem::ControllerDataGet(const ControllerID controllerID, ControllerData& controller)
{
#if defined(OSUnix)
    return false;

#elif defined(OSWindows)
#if (WINVER >= 0x0400) // newer than Windows NT 4.0
	JOYINFOEX joystickInfo{ 0 }; // must set the 'dwSize' and 'dwFlags' or joyGetPosEx will fail.

	joystickInfo.dwSize = sizeof(JOYINFOEX);
	joystickInfo.dwFlags = JOY_RETURNALL;

	// For devices that have four to six axes of movement a point-of-view control,
	// or more than four buttons, use the joyGetPosEx function. 'joyGetPos()'
	const MMRESULT positionInfoResult = joyGetPosEx(controllerID, &joystickInfo);
	const bool successful = positionInfoResult == 0;

	if (successful)
	{
		controller.Axis[0] = joystickInfo.dwXpos;
		controller.Axis[1] = joystickInfo.dwYpos;
		controller.Axis[2] = joystickInfo.dwZpos;
		controller.Axis[3] = joystickInfo.dwRpos;
		controller.Axis[4] = joystickInfo.dwUpos;
		controller.Axis[5] = joystickInfo.dwVpos;
		controller.ButtonPressedBitList = joystickInfo.dwButtons;
		controller.ButtonAmountPressed = joystickInfo.dwButtonNumber;
		controller.ControlPad = joystickInfo.dwPOV;
	}

	return successful;
#else
	JOYINFO joystickInfo{ 0 };

	const MMRESULT positionInfoResult = joyGetPos(controllerID, &joystickInfo);
	const bool successful = positionInfoResult == 0;

	if (successful)
	{
		controller.Axis[0] = joystickInfo.wXpos;
		controller.Axis[1] = joystickInfo.wYpos;
		controller.Axis[2] = joystickInfo.wZpos;
		controller.ButtonPressedBitList = joystickInfo.wButtons;
	}

	return successful;
#endif
#endif
}

bool BF::ControllerSystem::ControllerAttachToWindow(const ControllerID controllerID, const WindowID windowID)
{
#if defined(OSUnix)
    return false;

#elif defined(OSWindows)
	UINT uPeriod = 1;
	BOOL fChanged = true;

	const MMRESULT captureResult = joySetCapture(windowID, controllerID, uPeriod, fChanged);
	const bool successful = captureResult == JOYERR_NOERROR;

	return successful;
#endif
}

bool BF::ControllerSystem::ControllerDetachToWindow(const ControllerID controllerID)
{
#if defined(OSUnix)
    return false;

#elif defined(OSWindows)
const MMRESULT releaseResult = joyReleaseCapture(controllerID);
	const bool successful = releaseResult == JOYERR_NOERROR;

	return successful;
#endif
}
