#pragma once

#include "Shader.h"

#include "../../Utility/List.hpp"

namespace BF
{
	class ShaderProgram
	{
	protected:
		public:
		unsigned int ID;
		List<Shader> ShaderList;			

		void AddShader(AsciiString& vertexShader, AsciiString& fragmentShader);
	};
}