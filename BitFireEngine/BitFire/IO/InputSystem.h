#pragma once

#include "Device/KeyBoard/KeyBoard.h"
#include "Device/Mouse/Mouse.h"

namespace BF
{
	class InputSystem
	{
		public:
		Mouse MouseInput;
		KeyBoard KeyBoardInout;
	};
}