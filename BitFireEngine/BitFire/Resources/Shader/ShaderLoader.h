#pragma once

#include "Shader.h"

#include "../../IO/File/FileLoader.h"

namespace BF
{
	class ShaderLoader
	{
		public:
		static ShaderType CheckShaderType(AsciiString& fileExtension);
		static void LoadFromFile(AsciiString& filePath, Shader& shader);
	};
}