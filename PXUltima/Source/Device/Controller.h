#ifndef ControllerInclude
#define ControllerInclude

#include <OS/OSVersion.h>
#include <OS/CWindow.h>

#define ControllerID unsigned int

#define ControllerAxisX 0
#define ControllerAxisY 1
#define ControllerAxisZ 2
#define ControllerAxisR 3
#define ControllerAxisU 4
#define ControllerAxisV 5

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

	extern unsigned char ControllerScanDevices(NewControllerDetectedCallback callback);
	extern unsigned char ControllerDataGet(Controller* controller);
	extern unsigned char ControllerAttachToWindow(const ControllerID controllerID, const CWindowID CWindowID);
	extern unsigned char ControllerDetachToWindow(const ControllerID controllerID);

#ifdef __cplusplus
}
#endif

#endif