#include "Mouse.h"

BF::Mouse::Mouse()
{
	ResetInput();
}

BF::Mouse::~Mouse()
{

}

void BF::Mouse::ResetInput()
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

void BF::Mouse::ResetAxis()
{
	InputAxis.X = 0;
	InputAxis.Y = 0;
}

bool BF::Mouse::ShoudRegisterInput()
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