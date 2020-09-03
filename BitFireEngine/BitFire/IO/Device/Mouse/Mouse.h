#pragma once

#include "../../../Mathematic/Geometry/Point.h"
#include "CursorMode.h"

class Mouse
{
public:
	Point Position;
	Point InputAxis;
	CursorMode Mode;

	bool LeftButton;
	bool ScrollButton;
	bool RightButton;

	bool CustomButton1;
	bool CustomButton2;
	bool CustomButton3;
	bool CustomButton4;
	bool CustomButton5;

	Mouse();
	~Mouse();

	void ResetInput();
	void ResetAxis();

	bool ShoudRegisterInput();
};