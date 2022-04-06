#pragma once


#include <Resource.h>
#include <File/FileActionResult.hpp>
#include <cstdlib>
#include <Shader/GLSL/ShaderType.h>

namespace BF
{
	class Shader : public Resource
	{
		public:
		ShaderType Type;
		size_t ContentSize;
		char* Content;	

		Shader();
		Shader(const ShaderType type);
		~Shader();

		size_t FullSizeInMemory();
		FileActionResult Load(const wchar_t* filePath);
	};
}