#ifndef ControllerInclude
#define ControllerInclude

#define ControllerAxisX 0
#define ControllerAxisY 1
#define ControllerAxisZ 2
#define ControllerAxisR 3
#define ControllerAxisU 4
#define ControllerAxisV 5

typedef unsigned int ControllerID;

#include <OS/System/OSVersion.h>
#include <OS/Window/PXWindow.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct Controller_
	{
		ControllerID ID;

		unsigned int Axis[6];  // X,Y,Z,R,U,V
		unsigned int ButtonPressedBitList;
		unsigned int ButtonAmountPressed;        // current button number pressed
		unsigned int ControlPad;
	}
	Controller;

	typedef void (*NewControllerDetectedCallback)(ControllerID controllerID);

	PXPublic PXBool ControllerScanDevices(NewControllerDetectedCallback callback);
	PXPublic PXBool ControllerDataGet(Controller* controller);
	PXPublic PXBool ControllerAttachToWindow(const ControllerID controllerID, const PXWindowID PXWindowID);
	PXPublic PXBool ControllerDetachToWindow(const ControllerID controllerID);

#ifdef __cplusplus
}
#endif

#endif