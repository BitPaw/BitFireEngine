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
	EnableInputAxis = true;

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