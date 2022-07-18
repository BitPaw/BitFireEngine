#pragma once

#include <OS/Window.h>

namespace BF
{
	class WindowP
	{
		private:
		

		public:
		Window _window;
		
		WindowP();
		~WindowP();

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
		//void Cursor(const WindowCursorIcon cursorIcon);
		void CursorTexture();
		void CursorCaptureMode(const WindowCursorMode cursorMode);

		//void ScreenShotTake(Image image);

		int FrameBufferInitialize();
		bool FrameBufferSwap();
		bool FrameBufferContextRegister();
		bool FrameBufferContextRelease();

		bool Interactable();
	};
}
