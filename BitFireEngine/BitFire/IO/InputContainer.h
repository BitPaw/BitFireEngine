#pragma once

#include "Device/KeyBoard/KeyBoard.h"
#include "Device/Mouse/Mouse.h"

class InputContainer
{
public:
	KeyBoard KeyBoardInput;
	Mouse MouseInput;

	InputContainer();
};