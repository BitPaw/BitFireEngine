#pragma once

#include "Device/KeyBoard/KeyBoard.h"
#include "Device/Mouse/Mouse.h"

class InputContainer
{
public:
	static KeyBoard KeyBoardInput;
	static Mouse MouseInput;

	InputContainer();
};