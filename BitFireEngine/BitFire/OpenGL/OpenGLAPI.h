#pragma once

#include "Window/Window.h"
#include "Shader/System/ShaderFile.h"
#include "Shader/System/ShaderLoader.h"

#include "../IO/Message/MessagerSystem.h"

class OpenGLAPI
{
private:
	Window* _window;
	ShaderFile _shaderFile;	

public:
	bool IsRunning;
	OpenGLAPI();
	void Update();
};