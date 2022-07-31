#ifndef CWindowInclude
#define CWindowInclude

#include <stddef.h>

#include <OS/OSVersion.h>

#if defined(OSUnix)

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#define CWindowID XID // XID is CWindow
#define OpenGLConextID GLXContext

#elif defined(OSWindows)
#include <Windows.h>
#define CWindowID HWND
#define OpenGLConextID HGLRC
#endif

#include <Device/KeyBoardKey.h>
#include <Async/Thread.h>

#define UseRawMouseData 1
#define CWindowTitleSizeMax 256
#define CWindowSizeDefault -1

#ifdef __cplusplus
extern "C"
{
#endif

	// The mode in which the mouse pointer will be.
	typedef enum CWindowCursorMode_
	{	
		CWindowCursorIgnore, 	// Show the cursor but dont register any Input.	
		CWindowCursorShow, 	// Show the cursor and register Input as normal.	
		CWindowCursorInvisible, 	// Hide Cursor. You can still use it as normal. Not locked.
		CWindowCursorLock,
		CWindowCursorLockAndHide
	}
	CWindowCursorMode;

	typedef enum ButtonState_
	{
		ButtonInvalid,
		ButtonDown,
		ButtonHold,
		ButtonRelease
	}
	ButtonState;

	typedef enum MouseButton_
	{
		MouseButtonInvalid,
		MouseButtonLeft,
		MouseButtonMiddle,
		MouseButtonRight
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

	typedef struct KeyBoardKeyInfo_
	{
		KeyBoardKey Key;
		ButtonState Mode;
		unsigned short Repeat; // Die Wiederholungsanzahl für die aktuelle Meldung.Der Wert gibt an, wie oft die Tastatureingabe automatisch angezeigt wird, wenn der Benutzer den Schlüssel hält.Die Wiederholungsanzahl ist immer 1 für eine WM _ KEYUP - Nachricht.
		unsigned short ScanCode;// Der Scancode.Der Wert hängt vom OEM ab.
		unsigned short SpecialKey;// Gibt an, ob es sich bei der Taste um eine erweiterte Taste handelt, z.B.die rechte ALT - und STRG - Taste, die auf einer erweiterten Tastatur mit 101 oder 102 Tasten angezeigt werden.Der Wert ist 1, wenn es sich um einen erweiterten Schlüssel handelt.andernfalls ist es 0.
		unsigned short KontextCode; // Der Kontextcode.Der Wert ist für eine WM _ KEYUP - Nachricht immer 0.
		unsigned short PreState; // Der vorherige Schlüsselzustand.Der Wert ist immer 1 für eine WM _ KEYUP - Nachricht.
		unsigned short GapState;
	}
	KeyBoardKeyInfo;

	// Mouse
	typedef void (*MouseScrollEvent)(const MouseScrollDirection mouseScrollDirection);
	typedef void (*MouseClickEvent)(const MouseButton mouseButton, const ButtonState buttonState);
	typedef void (*MouseClickDoubleEvent)(const MouseButton mouseButton);
	typedef void (*MouseMoveEvent)(const int positionX, const int positionY, const int deltaX, const int deltaY);
	typedef void (*MouseEnterEvent)();
	typedef void (*MouseLeaveEvent)();

	// Keyboard
	typedef void (*KeyBoardKeyEvent)(const KeyBoardKeyInfo keyBoardKeyInfo);

	typedef void (*FocusEnterEvent)();
	typedef void (*FocusLeaveEvent)();

	typedef void (*WindowCreatedEvent)(void* CWindow);
	typedef void (*WindowSizeChangedEvent)(const size_t width, const size_t height);
	typedef void (*WindowClosingEvent)(unsigned char* allowClosing);
	typedef void (*WindowClosedEvent)();

	// 	static Dictionary<CWindowID, CWindow*> _windowLookup;

	typedef struct CWindow_
	{
		volatile unsigned char IsRunning;
		CWindowID ID;
		OpenGLConextID OpenGLConext;

		// Live data
		unsigned char HasSizeChanged;
		CWindowCursorMode CursorModeCurrent;

		int MousePositionX;
		int MousePositionY;
		int MouseDeltaX;
		int MouseDeltaY;

		unsigned int X;
		unsigned int Y;
		unsigned int Width;
		unsigned int Height;

		wchar_t Title[CWindowTitleSizeMax];

#if defined(OSUnix)
		Display* DisplayCurrent;
		CWindowIDCWindowRoot;
#elif defined(OSWindows)
		HCURSOR CursorID;
		HDC HandleDeviceContext;
#endif

		// Interneal
		ThreadID MessageThreadID;

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
	CWindow;

#if defined(OSUnix)
	static void CWindowEventHandler(CWindow& cWindow, const XEvent& event);
#elif defined(OSWindows)
	static LRESULT CALLBACK CWindowEventHandler(HWND cWindowsID, UINT eventID, WPARAM wParam, LPARAM lParam);
#endif

	static ThreadResult CWindowCreateThread(void*CWindowAdress);

	extern void CWindowConstruct(CWindow* CWindow);
	extern void CWindowCreate(CWindow* CWindow, const unsigned int width, const unsigned int height, const char* title, unsigned char async);
	extern void CWindowDestruct(CWindow* CWindow);

	extern void CWindowIconCorner();
	extern void CWindowIconTaskBar();

	extern void CWindowLookupAdd(const CWindow* CWindow);
	extern CWindow* CWindowLookupFind(const CWindowID CWindowID);
	extern void CWindowLookupRemove(const CWindow* CWindow);

	extern void CWindowSize(CWindow* CWindow, unsigned int* x, unsigned int* y, unsigned int* width, unsigned int* height);
	extern void CWindowSizeChange(CWindow* CWindow, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height);
	extern void CWindowPosition(CWindow* CWindow, unsigned int* x, unsigned int* y);
	extern void CWindowPositionChange(CWindow* CWindow, const unsigned int x, const unsigned int y);
	extern void CWindowPositonCenterScreen(CWindow* CWindow);
	extern void CWindowCursor(CWindow* CWindow);
	//voidCWindowCursor(const CursorIcon cursorIcon);
	extern void CWindowCursorTexture();
	extern void CWindowCursorCaptureMode(CWindow* CWindow, const CWindowCursorMode cursorMode);
	//voidCWindowScreenShotTake(Image image);
	extern int CWindowFrameBufferInitialize(CWindow* CWindow);
	extern unsigned char CWindowFrameBufferSwap(CWindow* CWindow);
	extern unsigned char CWindowFrameBufferContextRegister(CWindow* CWindow);
	extern unsigned char CWindowFrameBufferContextRelease(CWindow* CWindow);
	extern unsigned char CWindowInteractable(CWindow* CWindow);

	extern unsigned char CWindowCursorPositionInWindowGet(CWindow* window, int* x, int* y);
	extern unsigned char CWindowCursorPositionInDestopGet(CWindow* window, int* x, int* y);
#ifdef __cplusplus
}
#endif

#endif