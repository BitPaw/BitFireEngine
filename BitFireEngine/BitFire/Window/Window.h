#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "../IO/KeyBoard.h"

class Window
{
private :
	GLFWwindow* _window;


public:
	static KeyBoard* KeyBoardInput;

	Window();
	~Window();
	bool Exit;

	bool Create(const int width, const int height, const char* title);
	void Update();

	
};

