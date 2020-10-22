#pragma once

#include "../../IO/Device/KeyBoard/KeyBoard.h"
#include "../../IO/Device/Mouse/Mouse.h"

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