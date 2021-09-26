#include "ModelRenderInformation.h"

BF::ModelRenderInformation::ModelRenderInformation()
{
	ShouldItBeRendered = true;
	VertexArrayID = -1;
	IndexBufferID = -1;
	VertexBufferID = -1;
	ShaderProgramID = -1;

	RenderType = RenderMode::Triangle;
	
	ShaderProgramID = -1;
	UsedShaderProgram = nullptr;

	VertexDataBlockSize =  (3 + 3 + 4 + 2);

	VertexData = nullptr;
	VertexDataSize = 0;

	IndexData = nullptr;
	IndexDataSize = 0;
}

BF::ModelRenderInformation::~ModelRenderInformation()
{
	free(IndexData);
	free(VertexData);
}

void BF::ModelRenderInformation::Allocate(unsigned int vertexDataBlockSize, unsigned int indexSize)
{
	IndexDataSize = indexSize;
	VertexDataSize = indexSize * vertexDataBlockSize;
	VertexDataBlockSize = vertexDataBlockSize;

	VertexData = static_cast<float*>(malloc(VertexDataSize * sizeof(float)));
	IndexData = static_cast<unsigned int*>(malloc(IndexDataSize * sizeof(unsigned int)));
}

void BF::ModelRenderInformation::PrintGPUData()
{
	int vertexSize = RenderType == RenderMode::Square ? 4 : 3;

	printf("+---[VertexData]--------------------------------------------------------------+\n");

	for (size_t i = 0; i < VertexDataSize; )
	{
		for (size_t j= 0; j < VertexDataBlockSize; j++)
		{
			printf("| %7.2f ", VertexData[i++]);
		}

		printf("|\n");
	}

	printf("+---[IndexData]---------------------------------------------------------------+\n");

	for (size_t i = 0; i < IndexDataSize; i++)
	{
		for (size_t j = 0; j < vertexSize; j++)
		{
			printf("| %4i ", IndexData[i++]);
		}

		printf("|\n");
	}

	printf("+----------------------------------------------------------------+\n");
}