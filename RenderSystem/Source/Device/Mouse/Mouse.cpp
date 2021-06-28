#include "Mouse.h"

BF::Mouse::Mouse()
{
	ResetInput();
}

void BF::Mouse::ResetInput()
{
	Position[0] = 0;
	Position[1] = 0;
	ResetAxis();
	Mode = CursorMode::Ignore;

	LeftButton.Value = 0;
	ScrollButton.Value = 0;
	RightButton.Value = 0;

	CustomButton1.Value = 0;
	CustomButton2.Value = 0;
	CustomButton3.Value = 0;
	CustomButton4.Value = 0;
	CustomButton5.Value = 0;
}

void BF::Mouse::ResetAxis()
{
	InputAxis[0] = 0;
	InputAxis[1] = 0;
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