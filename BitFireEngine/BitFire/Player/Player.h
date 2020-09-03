#pragma once

#include "../Configuration/ConfigContainer.h"
#include "../IO/InputContainer.h"

#include "../Graphics/Camera/FirstPersonCamera.h"

class Player
{
public:
	ConfigContainer Config;
	InputContainer Input;
	FirstPersonCamera Camera;

	Player();
};