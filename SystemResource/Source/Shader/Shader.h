#pragma once

#include "ShaderType.h"
#include "../Resource.h"
#include "../File/FileActionResult.hpp"
#include <cstdlib>

namespace BF
{
	class Shader : public Resource
	{
		public:
		ShaderType Type;
		char* Content;
		size_t ContentSize;

		Shader();
		Shader(ShaderType type, const wchar_t* content);

		FileActionResult Load();
	};
}