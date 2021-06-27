#pragma once

#include "CursorMode.h"
#include "../InputButton.h"

namespace BF
{
	class Mouse
	{
		public:
		float Position[2];
		float InputAxis[2];
		CursorMode Mode;

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

		bool ShoudRegisterInput();
	};
}