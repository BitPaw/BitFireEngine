#pragma once

#include <OS/OSDefine.h>
#include "../Controller/KeyBoardKey.h"
#include "../Container/Dictionary.hpp"
#include "../Async/Thread.h"
#include "../Controller/KeyBoardKey.h"

#include "CursorMode.h"

#if defined(OSUnix)
#define WindowID unsigned int
#elif defined(OSWindows)
#include <wtypes.h>
#include <windef.h>
#define WindowID HWND
#endif
#include "CursorIcon.h"

#define UseRawMouseData 1

namespace BF
{
	enum class ButtonState
	{
		Down,
		Hold,
		Release
	};

	enum class MouseButton
	{
		Left,
		Middle,
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
	typedef void (*MouseScrollEvent)();
	typedef void (*MouseClickEvent)(const MouseButton mouseButton, const ButtonState buttonState);
	typedef void (*MouseClickDoubleEvent)(const MouseButton mouseButton);
	typedef void (*MouseMoveEvent)(const short x, const short y);

	// Keyboard
	typedef void (*KeyBoardKeyEvent)(const KeyBoardKeyInfo keyBoardKeyInfo);

	// Window
	//typedef void (*WindowCreatingEvent)();
	typedef void (*WindowCreatedEvent)(Window& window);
	typedef void (*WindowSizeChangedEvent)(const size_t width, const size_t height);
	typedef void (*WindowClosingEvent)(bool& allowClosing);
	typedef void (*WindowClosedEvent)();

	struct WindowCreationInfo
	{
		public:
		bool Async;

		Window* CreatedWindow;
		wchar_t Title[256];
		int X;
		int Y;
		int Width;
		int Height;
	};

	class Window
	{
		private:
		static Dictionary<WindowID, Window*> _windowLookup;
		static Window* _currentWindow;

		CursorMode _cursorMode;

		public:
		WindowID ID;

		#if defined(OSUnix)
		#elif defined(OSWindows)
		HCURSOR CursorID;
		HDC HandleDeviceContext;
		HGLRC OpenGLRenderingContext;
		#endif

		// Interneal
		ThreadID MessageThreadID;
		bool IsRunning;

		MouseClickEvent MouseClickCallBack;
		MouseClickDoubleEvent MouseClickDoubleCallBack;

		MouseMoveEvent MouseMoveCallBack;
		KeyBoardKeyEvent KeyBoardKeyCallBack;
		WindowCreatedEvent WindowCreatedCallBack;
		WindowSizeChangedEvent WindowSizeChangedCallBack;
		WindowClosingEvent WindowClosingCallBack;
		WindowClosedEvent WindowClosedCallBack;

		Window();
		~Window();

#if defined(OSWindows)
		static LRESULT CALLBACK OnWindowEvent(HWND windowsID, UINT eventID, WPARAM wParam, LPARAM lParam);
#endif

		static ThreadFunctionReturnType WindowThead(void* windowCreationInfoAdress);

		void Create();
		void Create(const unsigned int width, const unsigned int height, const char* title);
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
		CursorMode CursorCaptureMode();
		void CursorCaptureMode(const CursorMode cursorMode);
	};
}
