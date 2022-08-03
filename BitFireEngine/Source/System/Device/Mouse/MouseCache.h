#pragma once

namespace BF
{
	class MouseCache
	{
		public:
		int Position[2]; // Window-Position (0/0 to x/y)
		int InputAxis[2]; // Relative Input (-x/-y to 0/0 to x/y)

		unsigned char LeftButton;
		unsigned char ScrollButton;
		unsigned char RightButton;

		unsigned char CustomButton1;
		unsigned char CustomButton2;
		unsigned char CustomButton3;
		unsigned char CustomButton4;
		unsigned char CustomButton5;

		MouseCache();

		void ResetInput();
		void ResetAxis();
	};
}