#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <chrono>

#include "../IO/Devies/KeyBoard/KeyBoard.h"
#include "../IO/Devies/Mouse/Mouse.h"
#include "../IO/DataType/Texture.h"
#include "../IO/DataType/Texture.h"
#include "../IO/TextureLoader.h"
#include "../Mathmatic/Interpolate.h"

class Window
{
private :
	static std::chrono::steady_clock::time_point _lastTimeStamp;
	GLFWwindow* _window;

	static std::chrono::steady_clock::time_point GetCurrentTimeStamp();
	void UpdateDeltaTime();

public:
	static KeyBoard* KeyBoardInput;
	static Mouse* MouseInput;
	static float GetDeltaTime();
	float GetRunnedTime();

	Window();
	Window(const int width, const int height, const char* title);
	~Window();
	bool Exit;

	bool Create(const int width, const int height, const char* title);
	void Update();

	
};

