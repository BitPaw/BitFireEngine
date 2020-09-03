#pragma once
#include <string>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class ShaderLoader
{
public:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	static void CheckShader(const unsigned int programmID, const unsigned int shaderID);
};

