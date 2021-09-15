#pragma once

#include "../Shader/ShaderProgram.h"
#include "../../../SystemRender/Source/RenderMode.h"

namespace BF
{
	struct ModelRenderInformation
	{
		public:
		bool ShouldItBeRendered;	
		unsigned int VertexArrayID;	// VAO
		
		unsigned int VertexBufferID; // VBO
		float* VertexData;
		unsigned int VertexDataSize;
		unsigned int VertexDataBlockSize;		

		unsigned int IndexBufferID; // IBO
		unsigned int* IndexData;
		unsigned int IndexDataSize;

		RenderMode RenderType;

		unsigned int ShaderProgramID;
		ShaderProgram* UsedShaderProgram;

		ModelRenderInformation();
		~ModelRenderInformation();

		void Allocate(unsigned int vertexDataBlockSize, unsigned int indexSize);


		void PrintGPUData();
	};
}
