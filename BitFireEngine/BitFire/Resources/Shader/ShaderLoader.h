#pragma once

#include "Shader.h"

#include "../../IO/File/FileLoader.h"

namespace BF
{
	class ShaderLoader
	{
		public:
		static ShaderType CheckShaderType(ASCIIString& fileExtension);
		static void LoadFromFile(ASCIIString& filePath, Shader& shader);
	};
}