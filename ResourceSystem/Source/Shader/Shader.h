#pragma once

#include "ShaderType.h"
#include "../Resource.h"

namespace BF
{
	class Shader : public Resource
	{
		public:
		ShaderType Type;
		char* Content;

		Shader();
		Shader(ShaderType type, char* content);

		void Load();
	};
}