#ifndef WindowInclude
#define WindowInclude

#include <stddef.h>

#include <Async/Thread.h>

#if defined(OSUnix)

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#define WindowID XID // XID is Window
#define OpenGLConextID GLXContext

#elif defined(OSWindows)
#include <Windows.h>
#define WindowID HWND
#define OpenGLConextID HGLRC

#endif
#include <Device/KeyBoardKey.h>

#define UseRawMouseData 1
#define WindowTitleSizeMax 256

#ifdef __cplusplus
extern "C"
{
#endif

	// The mode in which the mouse pointer will be.
	typedef enum WindowCursorMode_
	{
		// Show the cursor but dont register any Input.
		WindowCursorIgnore,

		// Show the cursor and register Input as normal.
		WindowCursorShow,

		// Hide Cursor. You can still use it as normal. Not locked.
		WindowCursorInvisible,

		WindowCursorLock,

		WindowCursorLockAndHide
	}
	WindowCursorMode;


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
	typedef void (*MouseMoveEvent)(const double positionX, const double positionY, const double deltaX, const double deltaY);
	typedef void (*MouseEnterEvent)();
	typedef void (*MouseLeaveEvent)();

	// Keyboard
	typedef void (*KeyBoardKeyEvent)(const KeyBoardKeyInfo keyBoardKeyInfo);

	typedef void (*FocusEnterEvent)();
	typedef void (*FocusLeaveEvent)();

	typedef void (*WindowCreatedEvent)(void* window);
	typedef void (*WindowSizeChangedEvent)(const size_t width, const size_t height);
	typedef void (*WindowClosingEvent)(unsigned char* allowClosing);
	typedef void (*WindowClosedEvent)();

	// 	static Dictionary<WindowID, Window*> _windowLookup;

	typedef struct Window_
	{
		volatile unsigned char IsRunning;
		WindowID ID;
		OpenGLConextID OpenGLConext;

		// Live data
		unsigned char HasSizeChanged;
		WindowCursorMode CursorModeCurrent;

		double MousePositionX;
		double MousePositionY;
		double MouseDeltaX;
		double MouseDeltaY;

		unsigned int X;
		unsigned int Y;
		unsigned int Width;
		unsigned int Height;

		wchar_t Title[WindowTitleSizeMax];

#if defined(OSUnix)
		Display* DisplayCurrent;
		WindowID WindowRoot;
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
	Window;

#if defined(OSUnix)
	static void WindowEventHandler(BF::Window& window, const XEvent& event);
#elif defined(OSWindows)
	static LRESULT CALLBACK WindowEventHandler(HWND windowsID, UINT eventID, WPARAM wParam, LPARAM lParam);
#endif

	static ThreadFunctionReturnType WindowCreateThread(void* windowAdress);

	extern void WindowConstruct(Window* window);
	extern void WindowCreate(Window* window, const unsigned int width, const unsigned int height, const char* title, unsigned char async);
	extern void WindowDestruct(Window* window);

	extern void WindowIconCorner();
	extern void WindowIconTaskBar();

	extern void WindowLookupAdd(const Window* window);
	extern Window* WindowLookupFind(const WindowID windowID);
	extern void WindowLookupRemove(const Window* window);

	extern void WindowSize(Window* window, unsigned int* x, unsigned int* y, unsigned int* width, unsigned int* height);
	extern void WindowSizeChange(Window* window, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height);
	extern void WindowPosition(Window* window, unsigned int* x, unsigned int* y);
	extern void WindowPositionChange(Window* window, const unsigned int x, const unsigned int y);
	extern void WindowPositonCenterScreen(Window* window);
	extern void WindowCursor(Window* window);
	//void WindowCursor(const CursorIcon cursorIcon);
	extern void WindowCursorTexture();
	extern void WindowCursorCaptureMode(Window* window, const WindowCursorMode cursorMode);
	//void WindowScreenShotTake(Image image);
	extern int WindowFrameBufferInitialize(Window* window);
	extern unsigned char WindowFrameBufferSwap(Window* window);
	extern unsigned char WindowFrameBufferContextRegister(Window* window);
	extern unsigned char WindowFrameBufferContextRelease(Window* window);
	extern unsigned char WindowInteractable(Window* window);


#ifdef __cplusplus
}
#endif

#endif