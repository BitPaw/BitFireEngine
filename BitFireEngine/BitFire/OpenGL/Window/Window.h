#pragma once

#ifndef BF_Window
#define BF_Window

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#include "../../IO/InputContainer.h"
#include "../../Graphics/Camera/FirstPersonCamera.h"
#include "../../Time/TimeCollection.h"
#include "../../Configuration/VideoConfig.h"
#include "../../Player/Player.h"

class Window
{
private:
	static Window* _instance;
	GLFWwindow* _window;
	GLFWcursor* _cursor;
	GLFWmonitor* _montor;
	bool _exitWindow;

	void UpdateInput();
	bool Create();

public:
	static Window* GetInstance();

	Player* CurrentPlayer;

	Window(Player* player);
	~Window();

	// Window Utility	
	void ResizeWindow(const int width, const int height);
	void SetCursorTexture(std::string filePath);
	void SetCursorMode(CursorMode mode);
	void SetVideoRefreshRate(RefreshRateMode mode);
	void SetWindowPosition(unsigned int x, unsigned int y);
	void SetWindowPositionToCenter();

	bool ShouldExit();

	void Update();
};
#endif 