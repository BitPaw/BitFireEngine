#pragma once

#include "../../../Mathematic/Geometry/Point.hpp"
#include "CursorMode.h"
#include "../InputButton.h"

namespace BF
{
	class Mouse
	{
		public:
		Point<float> Position;
		Point<float> InputAxis;
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