#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace BF
{
	class ShaderLoader
	{
		public:
		static unsigned int CompileShader(unsigned int type, const std::string& source);
		static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	};
}