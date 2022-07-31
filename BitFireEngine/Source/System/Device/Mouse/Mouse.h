#pragma once

#include "../InputButton.h"

namespace BF
{
	class Mouse
	{
		public:
		int Position[2]; // Window-Position (0/0 to x/y)
		int InputAxis[2]; // Relative Input (-x/-y to 0/0 to x/y)

		InputButton LeftButton;
		InputButton ScrollButton;
		InputButton RightButton;

		InputButton CustomButton1;
		InputButton CustomButton2;
		InputButton CustomButton3;
		InputButton CustomButton4;
		InputButton CustomButton5;

		Mouse();

		void ResetInput();
		void ResetAxis();
	};
}