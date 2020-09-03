#pragma once

#include "../../../Mathematic/Geometry/Point.h"

class Mouse
{
public:
	Point Position;
	Point InputAxis;
	bool EnableInputAxis;

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
};