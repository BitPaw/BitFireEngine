#include "Window.h"

#include <Memory/Memory.h>

BF::Window::Window()
{
	CWindowConstruct(this);
}

BF::Window::~Window()
{
	CWindowDestruct(this);
}

void BF::Window::Create(const unsigned int width, const unsigned int height, const char* title, bool async)
{
	CWindowCreate(this, width, height, title, async);
}

void BF::Window::Destroy()
{
	CWindowDestruct(this);
}

void BF::Window::IconCorner()
{
}

void BF::Window::IconTaskBar()
{
}

void BF::Window::Size(unsigned int& x, unsigned int& y, unsigned int& width, unsigned int& height)
{
	CWindowSize(this, &x, &y, &width, &height);
}

void BF::Window::SizeChange(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height)
{
	CWindowSizeChange(this, x, y, width, height);
}

void BF::Window::Position(unsigned int& x, unsigned int& y)
{
	CWindowPosition(this, &x, &y);
}

void BF::Window::PositionChange(const unsigned int x, const unsigned int y)
{
	CWindowPositionChange(this, x, y);
}

void BF::Window::PositonCenterScreen()
{
	CWindowPositonCenterScreen(this);
}

void BF::Window::Cursor()
{
	CWindowCursor(this);
}

void BF::Window::CursorTexture()
{
}

void BF::Window::CursorCaptureMode(const CWindowCursorMode cursorMode)
{
	CWindowCursorCaptureMode(this, cursorMode);
}

int BF::Window::FrameBufferInitialize()
{
	return CWindowFrameBufferInitialize(this);
}

bool BF::Window::FrameBufferSwap()
{
	return CWindowFrameBufferSwap(this);
}

bool BF::Window::FrameBufferContextRegister()
{
	return CWindowFrameBufferContextRegister(this);
}

bool BF::Window::FrameBufferContextRelease()
{
	return CWindowFrameBufferContextRelease(this);
}

bool BF::Window::Interactable()
{
	return CWindowInteractable(this);
}