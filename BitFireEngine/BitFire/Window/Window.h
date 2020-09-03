#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private :
	GLFWwindow* _window;

public:
	Window();
	~Window();
	bool Exit;

	bool Create(const int width, const int height, const char* title);
	void Update();
};

