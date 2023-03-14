#ifndef PXWindowINCLUDE
#define PXWindowINCLUDE

#include <Format/Type.h>

#include <OS/System/OSVersion.h>

#if OSUnix

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>


typedef XID PXWindowID;// XID is PXWindow
typedef GLXContext OpenGLConextID;

#elif OSWindows
#include <Windows.h>
typedef HWND PXWindowID;
typedef HGLRC OpenGLConextID;
#endif

#include <Graphic/PXGraphic.h>
#include <Device/VirtualKey.h>
#include <Device/Mouse.h>
#include <Device/KeyBoard.h>
#include <OS/Process/PXProcess.h>
#include <OS/Thread/PXThread.h>

#define UseRawMouseData 1
#define PXWindowTitleSizeMax 256
#define PXWindowSizeDefault -1

#ifdef __cplusplus
extern "C"
{
#endif

	// The mode in which the mouse pointer will be.
	typedef enum PXWindowCursorMode_
	{
		PXWindowCursorIgnore, 	// Show the cursor but dont register any Input.
		PXWindowCursorShow, 	// Show the cursor and register Input as normal.
		PXWindowCursorInvisible, 	// Hide Cursor. You can still use it as normal. Not locked.
		PXWindowCursorLock,
		PXWindowCursorLockAndHide
	}
	PXWindowCursorMode;

	typedef enum ButtonState_
	{
		ButtonStateInvalid,
		ButtonStateDown,
		ButtonStateHold,
		ButtonStateRelease
	}
	ButtonState;

	typedef enum MouseButton_
	{
		MouseButtonInvalid,
		MouseButtonLeft,
		MouseButtonMiddle,
		MouseButtonRight,
		MouseButtonSpecialA,
		MouseButtonSpecialB,
		MouseButtonSpecialC,
		MouseButtonSpecialD,
		MouseButtonSpecialE,
	}
	MouseButton;

	typedef enum MouseScrollDirection_
	{
		MouseScrollDirectionInvalid,
		MouseScrollDirectionUp,
		MouseScrollDirectionDown,
		MouseScrollDirectionLeft,
		MouseScrollDirectionRight
	}
	MouseScrollDirection;

	typedef enum CursorIcon_
	{
		CursorIconInvalid,
		CursorIconNormal,
		CursorIconIBeam,
		CursorIconWait,
		CursorIconCross,
		CursorIconUp,
		CursorIconHand,
		CursorIconNotAllowed,
		CursorIconAppStarting,
		CursorIconResizeHorizontal,
		CursorIconResizeVertical,
		CursorIconResizeClockwise,
		CursorIconResizeClockwiseCounter,
		CursorIconResizeAll,
	}
	CursorIcon;

	typedef struct KeyBoardKeyInfo_
	{
		unsigned char KeyID;
		VirtualKey Key;
		ButtonState Mode;
		unsigned short Repeat; // Die Wiederholungsanzahl für die aktuelle Meldung.Der Wert gibt an, wie oft die Tastatureingabe automatisch angezeigt wird, wenn der Benutzer den Schlüssel hält.Die Wiederholungsanzahl ist immer 1 für eine WM _ KEYUP - Nachricht.
		unsigned short ScanCode;// Der Scancode.Der Wert hängt vom OEM ab.
		unsigned short SpecialKey;// Gibt an, ob es sich bei der Taste um eine erweiterte Taste handelt, z.B.die rechte ALT - und STRG - Taste, die auf einer erweiterten Tastatur mit 101 oder 102 Tasten angezeigt werden.Der Wert ist 1, wenn es sich um einen erweiterten Schlüssel handelt.andernfalls ist es 0.
		unsigned short KontextCode; // Der Kontextcode.Der Wert ist für eine WM _ KEYUP - Nachricht immer 0.
		unsigned short PreState; // Der vorherige Schlüsselzustand.Der Wert ist immer 1 für eine WM _ KEYUP - Nachricht.
		unsigned short GapState;
	}
	KeyBoardKeyInfo;

	typedef struct PXWindow_ PXWindow;

	// Mouse
	typedef void (*MouseScrollEvent)(const void* const receiver, const PXWindow* sender, const MouseScrollDirection mouseScrollDirection);
	typedef void (*MouseClickEvent)(const void* const receiver, const PXWindow* sender, const MouseButton mouseButton, const ButtonState buttonState);
	typedef void (*MouseClickDoubleEvent)(const void* const receiver, const PXWindow* sender, const MouseButton mouseButton);
	typedef void (*MouseMoveEvent)(const void* const receiver, const PXWindow* sender, const Mouse* mouse);
	typedef void (*MouseEnterEvent)(const void* const receiver, const PXWindow* sender);
	typedef void (*MouseLeaveEvent)(const void* const receiver, const PXWindow* sender);

	// Keyboard
	typedef void (*KeyBoardKeyEvent)(const void* const receiver, const PXWindow* sender, const KeyBoardKeyInfo keyBoardKeyInfo);

	typedef void (*FocusEnterEvent)(const void* const receiver, const PXWindow* sender);
	typedef void (*FocusLeaveEvent)(const void* const receiver, const PXWindow* sender);

	typedef void (*WindowCreatedEvent)(const void* const receiver, const PXWindow* sender);
	typedef void (*WindowSizeChangedEvent)(const void* const receiver, const PXWindow* sender, const PXSize width, const PXSize height);
	typedef void (*WindowClosingEvent)(const void* const receiver, const PXWindow* sender, PXBool* const allowClosing);
	typedef void (*WindowClosedEvent)(const void* const receiver, const PXWindow* sender);

	// 	static PXDictionary<PXWindowID, PXWindow*> _windowLookup;

	typedef struct PXWindow_
	{
		volatile PXBool IsRunning;
		PXWindowID ID;

		unsigned int X;
		unsigned int Y;
		unsigned int Width;
		unsigned int Height;

		wchar_t Title[PXWindowTitleSizeMax];


		// Live data
		PXBool HasSizeChanged;
		PXWindowCursorMode CursorModeCurrent;

		KeyBoard KeyBoardCurrentInput;
		Mouse MouseCurrentInput;



		PXGraphicContext GraphicInstance;

#if OSUnix
		Display* DisplayCurrent;
		PXWindowID WindowRoot;
#elif OSWindows
		HCURSOR CursorID;
		HDC HandleDeviceContext;
#endif

		// Interneal
		PXThread MessageThread;

		void* EventReceiver;

		MouseScrollEvent MouseScrollCallBack;
		MouseClickEvent MouseClickCallBack;
		MouseClickDoubleEvent MouseClickDoubleCallBack;
		MouseEnterEvent MouseEnterCallBack;
		MouseLeaveEvent MouseLeaveCallBack;
		MouseMoveEvent MouseMoveCallBack;

		KeyBoardKeyEvent KeyBoardKeyCallBack;

		FocusEnterEvent FocusEnterCallBack;
		FocusLeaveEvent FocusLeaveCallBack;
		WindowCreatedEvent WindowCreatedCallBack;
		WindowSizeChangedEvent WindowSizeChangedCallBack;
		WindowClosingEvent WindowClosingCallBack;
		WindowClosedEvent WindowClosedCallBack;
	}
	PXWindow;

#if OSUnix
	PXPrivate void PXWindowEventHandler(PXWindow* const pxWindow, const XEvent* const xEvent);
#elif OSWindows
	PXPrivate LRESULT CALLBACK PXWindowEventHandler(HWND PXWindowsID, UINT eventID, WPARAM wParam, LPARAM lParam);
#endif

	PXPrivate PXThreadResult PXWindowCreateThread(void* const PXWindowAdress);

	PXPublic void PXWindowConstruct(PXWindow* const window);

	// Create a window based on the OS implementation.
	// if a NULL pointer is used as a title, the window will be hidden.
	PXPublic void PXWindowCreateA(PXWindow* const window, const unsigned int width, const unsigned int height, const char* title, const PXBool async);
	PXPublic void PXWindowCreateW(PXWindow* const window, const unsigned int width, const unsigned int height, const wchar_t* title, const PXBool async);
	PXPublic void PXWindowCreateU(PXWindow* const window, const unsigned int width, const unsigned int height, const char* title, const PXBool async);
	PXPublic void PXWindowCreate(PXWindow* const window, const unsigned int width, const unsigned int height, const PXBool async);
	PXPublic void PXWindowCreateHidden(PXWindow* const window, const unsigned int width, const unsigned int height, const PXBool async);
	PXPublic void PXWindowDestruct(PXWindow* const window);

	PXPublic PXProcessThreadID PXWindowThreadProcessID(const PXWindowID windowID);

	PXPublic PXWindowID PXWindowFindViaTitleA(const PXTextASCII windowTitle);
	PXPublic PXWindowID PXWindowFindViaTitleW(const PXTextUNICODE windowTitle);
	PXPublic PXWindowID PXWindowFindViaTitleU(const PXTextUTF8 windowTitle);

	PXPublic void PXWindowIconCorner();
	PXPublic void PXWindowIconTaskBar();

	PXPublic void PXWindowLookupAdd(const PXWindow* PXWindow);
	PXPublic PXWindow* PXWindowLookupFind(const PXWindowID PXWindowID);
	PXPublic void PXWindowLookupRemove(const PXWindow* PXWindow);

	PXPublic void PXWindowSize(PXWindow* PXWindow, unsigned int* x, unsigned int* y, unsigned int* width, unsigned int* height);
	PXPublic void PXWindowSizeChange(PXWindow* PXWindow, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height);
	PXPublic void PXWindowPosition(PXWindow* PXWindow, unsigned int* x, unsigned int* y);
	PXPublic void PXWindowPositionChange(PXWindow* PXWindow, const unsigned int x, const unsigned int y);
	PXPublic void PXWindowPositonCenterScreen(PXWindow* PXWindow);
	PXPublic void PXWindowCursor(PXWindow* PXWindow);
	//voidPXWindowCursor(const CursorIcon cursorIcon);
	PXPublic void PXWindowCursorTexture();
	PXPublic void PXWindowCursorCaptureMode(PXWindow* PXWindow, const PXWindowCursorMode cursorMode);
	//voidPXWindowScreenShotTake(Image image);

	PXPublic unsigned char PXWindowFrameBufferSwap(PXWindow* PXWindow);

	PXPublic unsigned char PXWindowInteractable(PXWindow* PXWindow);

	PXPublic unsigned char PXWindowCursorPositionInWindowGet(PXWindow* window, int* x, int* y);
	PXPublic unsigned char PXWindowCursorPositionInDestopGet(PXWindow* window, int* x, int* y);



	// Event functions
	PXPublic void TriggerOnMouseScrollEvent(const PXWindow* window, const Mouse* mouse);
	PXPublic void TriggerOnMouseClickEvent(const PXWindow* window, const MouseButton mouseButton, const ButtonState buttonState);
	PXPublic void TriggerOnMouseClickDoubleEvent(const PXWindow* window, const MouseButton mouseButton);
	PXPublic void TriggerOnMouseMoveEvent(const PXWindow* window, const int positionX, const int positionY, const int deltaX, const int deltaY);
	PXPublic void TriggerOnMouseEnterEvent(const PXWindow* window, const Mouse* mouse);
	PXPublic void TriggerOnMouseLeaveEvent(const PXWindow* window, const Mouse* mouse);


	PXPublic void TriggerOnKeyBoardKeyEvent(const PXWindow* window, const KeyBoardKeyInfo keyBoardKeyInfo);

	// Keyboard
	//typedef void (*KeyBoardKeyEvent)(const KeyBoardKeyInfo keyBoardKeyInfo);

	//typedef void (*FocusEnterEvent)();
	//typedef void (*FocusLeaveEvent)();

	//typedef void (*WindowCreatedEvent)(const PXWindow* PXWindow);
	//typedef void (*WindowSizeChangedEvent)(const PXSize width, const PXSize height);
	//typedef void (*WindowClosingEvent)(unsigned char* allowClosing);
	//typedef void (*WindowClosedEvent)();


	unsigned int CursorIconToID(const CursorIcon cursorIcon);

#ifdef __cplusplus
}
#endif

#endif
