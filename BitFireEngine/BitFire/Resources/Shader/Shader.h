#pragma once

#include "ShaderType.h"

#include "../Resource.h"
#include "../../Utility/AsciiString.h"

namespace BF
{
	class Shader : public Resource
	{
		public:
		ShaderType Type;
		AsciiString Content;

		Shader();
		Shader(ShaderType type, AsciiString& content);
	};
}