#pragma once

#include "Shader.h"

#include "../Container/List.hpp"
#include "../Container/AsciiString.h"

namespace BF
{
	class ShaderProgram
	{
		public:
		unsigned int ID;
		Shader ShaderList[2];

		ShaderProgram();

		void AddShader(const char* vertexShaderPath, const char* fragmentShaderFilePath);
		void Load();

		bool IsLoaded();
	};
}