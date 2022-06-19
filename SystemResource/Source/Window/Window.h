#pragma once

#include <Async/Thread.h>
#include <Controller/KeyBoardKey.h>
#include <Controller/KeyBoardKey.h>
#include <Container/Dictionary.hpp>
#include <OS/OSDefine.h>

#include "CursorMode.h"

#if defined(OSUnix)

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#define WindowID XID // XID is Window
#define OpenGLConextID GLXContext

#elif defined(OSWindows)

#include <wtypes.h>
#include <windef.h>
#define WindowID HWND
#define OpenGLConextID HGLRC

#endif

#include "CursorIcon.h"
#include <Media/Image/Image.h>

#define UseRawMouseData 1
#define WindowTitleSizeMax 256

namespace BF
{
	enum class ButtonState
	{
        Invalid,

		Down,
		Hold,
		Release
	};

	enum class MouseButton
	{
        Invalid,

		Left,
		Middle,
		Right
	};

	enum class MouseScrollDirection
	{
        Invalid,

		Up,
		Down,
		Left,
		Right
	};


	struct KeyBoardKeyInfo
	{
		KeyBoardKey Key;
		ButtonState Mode;
		unsigned short Repeat; // Die Wiederholungsanzahl für die aktuelle Meldung.Der Wert gibt an, wie oft die Tastatureingabe automatisch angezeigt wird, wenn der Benutzer den Schlüssel hält.Die Wiederholungsanzahl ist immer 1 für eine WM _ KEYUP - Nachricht.
		unsigned short ScanCode;// Der Scancode.Der Wert hängt vom OEM ab.
		unsigned short SpecialKey;// Gibt an, ob es sich bei der Taste um eine erweiterte Taste handelt, z.B.die rechte ALT - und STRG - Taste, die auf einer erweiterten Tastatur mit 101 oder 102 Tasten angezeigt werden.Der Wert ist 1, wenn es sich um einen erweiterten Schlüssel handelt.andernfalls ist es 0.
		unsigned short KontextCode; // Der Kontextcode.Der Wert ist für eine WM _ KEYUP - Nachricht immer 0.
		unsigned short PreState; // Der vorherige Schlüsselzustand.Der Wert ist immer 1 für eine WM _ KEYUP - Nachricht.
		unsigned short GapState;
	};

	class Window;

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

	typedef void (*WindowCreatedEvent)(Window& window);
	typedef void (*WindowSizeChangedEvent)(const size_t width, const size_t height);
	typedef void (*WindowClosingEvent)(bool& allowClosing);
	typedef void (*WindowClosedEvent)();

	class Window
	{
		private:
		static Dictionary<WindowID, Window*> _windowLookup;

		public:
		bool IsRunning;
		WindowID ID;
		OpenGLConextID OpenGLConext;

		// Live data
		bool HasSizeChanged;
		CursorMode CursorModeCurrent;

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

		Window();
		~Window();

#if defined(OSUnix)
        static void OnWindowEvent(BF::Window& window, const XEvent& event);
#elif defined(OSWindows)
		static LRESULT CALLBACK OnWindowEvent(HWND windowsID, UINT eventID, WPARAM wParam, LPARAM lParam);
#endif

		static ThreadFunctionReturnType WindowCreateThread(void* windowAdress);

		void Create(bool async = true);
		void Create(const unsigned int width, const unsigned int height, const char* title, bool async = true);
		void Destroy();

		void IconCorner();
		void IconTaskBar();

		void Size
		(
			unsigned int& x,
			unsigned int& y,
			unsigned int& width,
			unsigned int& height
		);
		void SizeChange
		(
			const unsigned int x,
			const unsigned int y,
			const unsigned int width,
			const unsigned int height
		);
		void Position(unsigned int& x, unsigned int& y);
		void PositionChange(const unsigned int x, const unsigned int y);
		void PositonCenterScreen();

		void Cursor();
		void Cursor(const CursorIcon cursorIcon);
		void CursorTexture();
		void CursorCaptureMode(const CursorMode cursorMode);

		void ScreenShotTake(Image image);

		int FrameBufferInitialize();
		bool FrameBufferSwap();
		bool FrameBufferContextRegister();
		bool FrameBufferContextRelease();


		bool Interactable();
	};
}
