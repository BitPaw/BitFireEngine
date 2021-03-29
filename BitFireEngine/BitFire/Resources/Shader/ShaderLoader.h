#pragma once

#include "Shader.h"

namespace BF
{
	class ShaderLoader
	{
		public:
		static ShaderType CheckShaderType(AsciiString& fileExtension);
		static void LoadFromFile(AsciiString& filePath, Shader& shader);
	};
}