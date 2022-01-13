#include "MeshStructure.h"

#include <stdlib.h>
#include <stdio.h>

BF::MeshStructure::MeshStructure()
{
	Original = true;

	VertexArrayID = -1;

	VertexBufferID = -1;
	VertexDataSize = 0;
	VertexData = nullptr;

	VertexDataBlockListSize = 4;
	VertexDataBlockList[0] = 3;
	VertexDataBlockList[1] = 3;
	VertexDataBlockList[2] = 4;
	VertexDataBlockList[3] = 2;
	VertexDataBlockFullSize = 0;

	IndexBufferID = -1;
	IndexDataSize = 0;
	IndexData = nullptr;

	RenderType = RenderMode::Invalid;


	Height = 0;
	Width = 0;
	Depth = 0;
}

BF::MeshStructure::~MeshStructure()
{
	free(VertexData);
	free(IndexData);
}

void BF::MeshStructure::Allocate(size_t vertecDataSize, size_t indexDataSize)
{
	VertexDataSize = vertecDataSize;
	VertexData = (float*)malloc(vertecDataSize * sizeof(float));

	IndexDataSize = indexDataSize;
	IndexData = (unsigned int*)malloc(indexDataSize * sizeof(unsigned int));
}

void BF::MeshStructure::DeAllocate()
{
	VertexDataSize = 0;
	free(VertexData);
	VertexData = nullptr;

	IndexDataSize = 0;
	free(IndexData);
	IndexData = nullptr;
}

void BF::MeshStructure::MeshLink(MeshStructure& mesh)
{
	Original = false;

	VertexBufferID = mesh.VertexBufferID;
	VertexDataSize = mesh.VertexDataSize;
	VertexData = nullptr;

	VertexDataBlockListSize = 0;
	VertexDataBlockList[0] = 0;
	VertexDataBlockList[1] = 0;
	VertexDataBlockList[2] = 0;
	VertexDataBlockList[3] = 0;
	VertexDataBlockFullSize = 0;

	IndexBufferID = mesh.IndexBufferID;;
	IndexDataSize = mesh.IndexDataSize;;
	IndexData = nullptr;

	RenderType = mesh.RenderType;

	SizeCheck();
}

void BF::MeshStructure::SizeCheck()
{
	for (size_t index = 0; index < VertexDataSize; )
	{
		float x = VertexData[index++];
		float y = VertexData[index++];
		float z = VertexData[index++];

		if (x > Width) Width = x;
		if (y > Height) Height = y;
		if (z > Depth) Depth = z;
	}
}

void BF::MeshStructure::TexturePointScale(float scale)
{
	TexturePointScale(scale, scale);
}

void BF::MeshStructure::TexturePointScale(float x, float y)
{
	for (size_t i = 9; i < VertexDataSize; i += 12)
	{
		VertexData[i] *= x;
		VertexData[i+1] *= y;
	}
}

void BF::MeshStructure::PrintData()
{
	if (!Original)
	{
		printf
		(
			"+-------------+\n"
			"| Shared Data |\n"
			"+-------------+\n"
		);
		return;
	}

	printf
	(
		"+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+ [VertexData %i]\n"
		"| Pos-X | Pos-Y | Pos-Z | Nor-X | Nor-Y | Nor-Z | Red   | Green | Blue  | Alpha | Tex-X | Tex-Y |\n",
		VertexBufferID
	);

	for (size_t i = 0; i < VertexDataSize; i++)
	{
		printf("| %6.2f ", VertexData[i]);

		if (((i + 1) % (3 + 3 + 4 + 2)) == 0)
		{
			printf("|\n");
		}
	}

	printf
	(
		"+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+ [IndexData %i]\n",
		IndexBufferID
	);

	for (size_t i = 0; i < IndexDataSize; i++)
	{
		printf("| %5i ", IndexData[i]);

		if (((i + 1) % (4)) == 0)
		{
			printf("|\n");
		}
	}

	printf("+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+\n");
}