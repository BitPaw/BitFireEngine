#pragma once

#include "../../OpenGL/Render/RenderMode.h"
#include "../../Utility/LinkedList.hpp"
#include "../Shader/ShaderProgram.h"

namespace BF
{
	struct ModelRenderInformation
	{
	public:
		unsigned int RenderID = -1;
		bool ShouldItBeRendered = false;
		unsigned int VertexArrayID = -1;
		unsigned int IndexBufferID = -1;
		unsigned int VertexBufferID = -1;
		unsigned int ShaderProgramID = -1;

		RenderMode RenderType;
		ShaderProgram* UsedShaderProgram;

		const unsigned int DataBlockSizeInBytes = sizeof(float) * (3 + 3 + 4 + 2);

		List<float> VertexData;
		List<unsigned int> IndexData;
	};
}
