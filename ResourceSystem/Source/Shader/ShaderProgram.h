#pragma once

#include "Shader.h"

#include "../Container/List.hpp"
#include "../Container/AsciiString.h"

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