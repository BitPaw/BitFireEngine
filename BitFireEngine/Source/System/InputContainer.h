#pragma once

#include "Device/Mouse/MouseCache.h"
#include "Device/KeyBoard/KeyBoardCache.h"

namespace BF
{
	class InputContainer
	{
		public:
		KeyBoardCache KeyBoardInput;
		MouseCache MouseInput;

		InputContainer();
	};
}