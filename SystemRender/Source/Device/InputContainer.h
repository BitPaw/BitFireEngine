#pragma once

#include "KeyBoard/KeyBoard.h"
#include "Mouse/Mouse.h"

namespace BF
{
	class InputContainer
	{
		public:
		static KeyBoard KeyBoardInput;
		static Mouse MouseInput;

		InputContainer();
	};
}