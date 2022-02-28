#pragma once

#include "KeyBoard/KeyBoard.h"
#include "Mouse/Mouse.h"

namespace BF
{
	class InputContainer
	{
		public:
		KeyBoard KeyBoardInput;
		Mouse MouseInput;

		InputContainer();
	};
}