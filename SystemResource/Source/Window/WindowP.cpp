#include "WindowP.h"

#include <Memory/Memory.h>

BF::WindowP::WindowP()
{
	MemorySet(&_window, sizeof(Window), 0);
}

BF::WindowP::~WindowP()
{
	Destroy();
}

void BF::WindowP::Create(const unsigned int width, const unsigned int height, const char* title, bool async)
{
	WindowCreate(&_window, width, height, title, async);
}

void BF::WindowP::Destroy()
{
	WindowDestroy(&_window);
}

void BF::WindowP::IconCorner()
{
}

void BF::WindowP::IconTaskBar()
{
}

void BF::WindowP::Size(unsigned int& x, unsigned int& y, unsigned int& width, unsigned int& height)
{
	WindowSize(&_window, &x, &y, &width, &height);
}

void BF::WindowP::SizeChange(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height)
{
	WindowSizeChange(&_window, x, y, width, height);
}

void BF::WindowP::Position(unsigned int& x, unsigned int& y)
{
	WindowPosition(&_window, &x, &y);
}

void BF::WindowP::PositionChange(const unsigned int x, const unsigned int y)
{
	WindowPositionChange(&_window, x, y);
}

void BF::WindowP::PositonCenterScreen()
{
	WindowPositonCenterScreen(&_window);
}

void BF::WindowP::Cursor()
{
	WindowCursor(&_window);
}

void BF::WindowP::CursorTexture()
{
}

void BF::WindowP::CursorCaptureMode(const WindowCursorMode cursorMode)
{
	WindowCursorCaptureMode(&_window, cursorMode);
}

int BF::WindowP::FrameBufferInitialize()
{
	return WindowFrameBufferInitialize(&_window);
}

bool BF::WindowP::FrameBufferSwap()
{
	return WindowFrameBufferSwap(&_window);
}

bool BF::WindowP::FrameBufferContextRegister()
{
	return WindowFrameBufferContextRegister(&_window);
}

bool BF::WindowP::FrameBufferContextRelease()
{
	return WindowFrameBufferContextRelease(&_window);
}

bool BF::WindowP::Interactable()
{
	return WindowInteractable(&_window);
}
