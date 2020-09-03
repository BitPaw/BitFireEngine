#include "Mouse.h"

Mouse::Mouse()
{
	ResetInput();
}

Mouse::~Mouse()
{

}

void Mouse::ResetInput()
{
	Position = Point();
	ResetAxis();
	Mode = CursorMode::Ignore;

	LeftButton = false;
	ScrollButton = false;
	RightButton = false;

	CustomButton1 = false;
	CustomButton2 = false;
	CustomButton3 = false;
	CustomButton4 = false;
	CustomButton5 = false;
}

void Mouse::ResetAxis()
{
	InputAxis.X = 0;
	InputAxis.Y = 0;
}

bool Mouse::ShoudRegisterInput()
{
	switch (Mode)
	{
	case CursorMode::Ignore:
		return false;

	case CursorMode::Show:
	case CursorMode::Invisible:
	case CursorMode::Locked:
	default:
		return true;
	}
}