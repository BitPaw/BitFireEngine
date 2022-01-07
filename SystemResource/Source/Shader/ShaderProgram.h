#pragma once

#include "Shader.h"

#include "../Container/List.hpp"
#include "../Container/AsciiString.h"

#define ShaderListSize 2

namespace BF
{
	class ShaderProgram
	{
		public:
		unsigned int ID;
		//size_t ShaderListSize;
		Shader ShaderList[ShaderListSize];

		ShaderProgram();

		void AddShader(const wchar_t* vertexShaderPath, const wchar_t* fragmentShaderFilePath);
		void Load();

		bool IsLoaded();
	};
}