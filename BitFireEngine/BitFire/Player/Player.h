#pragma once

#include "../Configuration/ConfigContainer.h"
#include "../OpenGL/Window/InputContainer.h"
#include "../Graphics/Camera/FirstPersonCamera.h"

namespace BF
{
	class Player
	{
	public:
		ConfigContainer Config;
		InputContainer Input;
		FirstPersonCamera Camera;

		Player();
	};
}