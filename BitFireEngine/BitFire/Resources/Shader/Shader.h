#pragma once

#include "ShaderType.h"

#include "../Resource.h"
#include "../../Utility/ASCIIString.h"

namespace BF
{
	class Shader : public Resource
	{
		public:
		ShaderType Type;
		ASCIIString Content;

		Shader();
		Shader(ShaderType type, ASCIIString& content);
	};
}