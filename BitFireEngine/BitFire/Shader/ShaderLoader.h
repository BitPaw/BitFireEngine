#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class ShaderLoader
{
public:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string vertexShader, const std::string fragmentShader);

	static void CheckShader(const unsigned int shaderID);
	static int CheckProgram(const unsigned int programID);
};

