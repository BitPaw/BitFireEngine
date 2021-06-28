#pragma once

#include "Shader.h"

#include "../Container/List.hpp"
#include "../Container/AsciiString.h"

namespace BF
{
	class ShaderProgram
	{
		protected:
		public:
		unsigned int ID;
		Shader ShaderList[2];

		void AddShader(char* vertexShaderPath, char* fragmentShaderFilePath);
		void Load();

		bool IsLoaded();
	};
}