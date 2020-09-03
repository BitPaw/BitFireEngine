#include "Mesh.h"

Mesh::Mesh() : Mesh(nullptr, 0, nullptr, 0, 0)
{

}

Mesh::Mesh(Vertex* vertexList, unsigned int nrVertexes, unsigned int* indices, unsigned int nrIndices, unsigned char dimension)
{
	Dimension = dimension;
	VertexList = vertexList;
	VertexListSize = nrVertexes * dimension;
	AmountOfVertexes = nrVertexes;
	Indices = indices;
	IndiceListSize = nrIndices;
}

Mesh::~Mesh()
{
	for (unsigned int i = 0; i < VertexListSize; i++)
	{
		delete &VertexList[i];
	}

	for (unsigned int i = 0; i < IndiceListSize; i++)
	{
		delete &Indices[i];
	}
}

float* Mesh::GetVertexData()
{
	unsigned int dynamicIndex = 0;
	float* data = new float[VertexListSize * (4 + 4)];

	
	for (unsigned int i = 0; i < AmountOfVertexes; i++)
	{
		Vertex* vertex = &VertexList[i];

		data[dynamicIndex++] = vertex->NormalizedPosition->X;
		data[dynamicIndex++] = vertex->NormalizedPosition->Y;
		data[dynamicIndex++] = vertex->NormalizedPosition->Z;

		if (Dimension == 3 || true)
		{
			//data[dynamicIndex++] = vertex->CurrentPosition->Z;
		}	

		data[dynamicIndex++] = 1;

		data[dynamicIndex++] = 1;
		data[dynamicIndex++] = 1;
		data[dynamicIndex++] = 1;
		data[dynamicIndex++] = 1;
	}
	

	return data;
}

unsigned int* Mesh::GetIndices()
{
	return Indices;
}